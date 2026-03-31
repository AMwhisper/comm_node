import os
import time
import threading

import rclpy
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

import serial
from serial import SerialException

from comm_node.pack import pack_autoaim_data
from interface.msg import AutoaimData


class AutoAimSender(Node):
    def __init__(self):
        super().__init__('autoaim_sender')

        # ================= 基本状态 =================
        self.lock = threading.Lock()
        self.latest_msg = None
        self.latest_msg_seq = 0
        self.latest_msg_time = 0.0
        self.seq = 0
        self.callback_group = ReentrantCallbackGroup()

        self.serial_port_path = '/dev/dji_vcp'
        self.baud_rate = 921600
        self.serial_port = None
        self.serial_ready = False
        self.shutting_down = False

        # 日志节流辅助
        self.last_reconnect_log_time = 0.0

        # 调试统计
        self.last_send_time = None
        self.last_sent_msg_seq = -1
        self.last_sent_signature = None
        self.command_timeout_sec = 0.035
        self.command_deadband_yaw = 0.35
        self.command_deadband_pitch = 0.35
        self.last_pipeline_latency_ms = 0.0

        # ================= QoS =================
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # ================= 订阅 =================
        self.subscription = self.create_subscription(
            AutoaimData,
            'autoaim_topic',
            self.autoaim_callback,
            qos_profile,
            callback_group=self.callback_group
        )

        # ================= 定时器 =================
        # 重连定时器：每0.5秒尝试一次
        self.reconnect_timer = self.create_timer(
            0.5,
            self.timer_reconnect_callback,
            callback_group=self.callback_group
        )

        # 超时保护：只负责在消息过期时补发一次 0
        self.timeout_timer = self.create_timer(
            0.005,
            self.timer_timeout_callback,
            callback_group=self.callback_group
        )

        # 启动时先尝试连一次
        self.connect_serial()

        self.get_logger().info('AutoAimSender 节点已启动')

    # =========================================================
    # 订阅回调
    # =========================================================
    def autoaim_callback(self, msg: AutoaimData):
        with self.lock:
            self.latest_msg = msg
            self.latest_msg_seq += 1
            self.latest_msg_time = time.perf_counter()

        self.send_latest_command(force_timeout_zero=False)

    def normalize_command(self, yaw: float, pitch: float, fire: int):
        if abs(yaw) < self.command_deadband_yaw:
            yaw = 0.0
        if abs(pitch) < self.command_deadband_pitch:
            pitch = 0.0
        if yaw == 0.0 and pitch == 0.0:
            fire = 0
        return float(yaw), float(pitch), int(fire)

    # =========================================================
    # 串口连接
    # =========================================================
    def connect_serial(self):
        if self.shutting_down:
            return False

        # 已经可用就不重复连接
        if self.serial_port is not None:
            try:
                if self.serial_port.is_open:
                    self.serial_ready = True
                    return True
            except Exception:
                pass

        try:
            ser = serial.Serial(
                port=self.serial_port_path,
                baudrate=self.baud_rate,
                timeout=0,
                write_timeout=0
            )

            # 可选：降低串口延迟
            # 没装 setserial 或设备不支持时失败也没关系
            os.system(f"setserial {self.serial_port_path} low_latency >/dev/null 2>&1")

            self.serial_port = ser
            self.serial_ready = True
            self.get_logger().info(f'串口已连接: {self.serial_port_path}')
            return True

        except Exception as e:
            self.serial_port = None
            self.serial_ready = False

            now = time.time()
            if now - self.last_reconnect_log_time > 2.0:
                self.get_logger().warn(f'串口未连接，等待重连: {e}')
                self.last_reconnect_log_time = now
            return False

    def close_serial(self):
        ser = self.serial_port
        self.serial_port = None
        self.serial_ready = False

        if ser is not None:
            try:
                if ser.is_open:
                    ser.close()
            except Exception:
                pass

    # =========================================================
    # 重连定时器
    # =========================================================
    def timer_reconnect_callback(self):
        if self.shutting_down:
            return

        if not self.serial_ready:
            self.connect_serial()

    def send_latest_command(self, force_timeout_zero: bool):
        if self.shutting_down:
            return

        if self.latest_msg is None:
            return

        if not self.serial_ready or self.serial_port is None:
            return

        with self.lock:
            if self.shutting_down:
                return

            msg = self.latest_msg
            ser = self.serial_port
            msg_seq = self.latest_msg_seq
            msg_time = self.latest_msg_time

            if msg is None or ser is None:
                return

            # 这里统一符号
            yaw = -msg.yaw_angle_diff
            pitch = -msg.pitch_angle_diff
            fire = msg.fire
            source_timestamp = float(msg.source_timestamp)

        now = time.perf_counter()
        msg_age = now - msg_time if msg_time > 0.0 else float('inf')
        pipeline_latency_ms = (
            (now - source_timestamp) * 1000.0
            if source_timestamp > 0.0 else -1.0
        )

        if force_timeout_zero:
            yaw, pitch, fire = 0.0, 0.0, 0
            send_reason = 'timeout_zero'
        else:
            yaw, pitch, fire = self.normalize_command(yaw, pitch, fire)
            send_reason = 'new_msg'

        command_signature = (round(yaw, 4), round(pitch, 4), int(fire))

        if send_reason == 'new_msg' and msg_seq == self.last_sent_msg_seq:
            return

        if send_reason == 'timeout_zero' and self.last_sent_signature == command_signature:
            return

        packet = pack_autoaim_data(yaw, pitch, fire, self.seq)

        try:
            t0 = time.perf_counter()
            ser.write(packet)
            write_dt_ms = (time.perf_counter() - t0) * 1000.0

            self.seq = (self.seq + 1) % 256
            self.last_sent_msg_seq = msg_seq
            self.last_sent_signature = command_signature
            self.last_pipeline_latency_ms = pipeline_latency_ms

            # 低频打印，避免200Hz日志拖慢系统
            if self.last_send_time is None:
                period_ms = 1.0
            else:
                period_ms = (now - self.last_send_time) * 1000.0
            self.last_send_time = now

            self.get_logger().info(
                f'SEND yaw={yaw:.3f}, pitch={pitch:.3f}, fire={fire}, '
                f'write={write_dt_ms:.3f}ms, period={period_ms:.3f}ms, '
                f'age={msg_age * 1000.0:.1f}ms, pipeline={pipeline_latency_ms:.1f}ms, '
                f'reason={send_reason}',
                throttle_duration_sec=0.5
            )

        except (SerialException, OSError) as e:
            if not self.shutting_down:
                self.get_logger().error(f'串口写入异常，准备重连: {e}')
            self.close_serial()

    # =========================================================
    # 超时补零定时器
    # =========================================================
    def timer_timeout_callback(self):
        if self.shutting_down:
            return

        if self.latest_msg is None:
            return

        with self.lock:
            msg_time = self.latest_msg_time

        if msg_time <= 0.0:
            return

        now = time.perf_counter()
        msg_age = now - msg_time
        if msg_age <= self.command_timeout_sec:
            return

        self.send_latest_command(force_timeout_zero=True)

    # =========================================================
    # 安全关闭
    # =========================================================
    def destroy_node(self):
        self.shutting_down = True

        try:
            if hasattr(self, 'timeout_timer') and self.timeout_timer is not None:
                self.timeout_timer.cancel()
        except Exception:
            pass

        try:
            if hasattr(self, 'reconnect_timer') and self.reconnect_timer is not None:
                self.reconnect_timer.cancel()
        except Exception:
            pass

        self.close_serial()
        super().destroy_node()


def main(args=None):
    rclpy.init(args=args)

    node = AutoAimSender()
    executor = MultiThreadedExecutor()
    executor.add_node(node)

    try:
        executor.spin()
    except KeyboardInterrupt:
        node.get_logger().info('正在安全关闭...')
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
