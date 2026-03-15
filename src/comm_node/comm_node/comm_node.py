import rclpy
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from rclpy.callback_groups import ReentrantCallbackGroup
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy

import serial
import os
import threading
from comm_node.pack import pack_autoaim_data
from interface.msg import AutoaimData

class AutoAimSender(Node):
    def __init__(self):
        super().__init__('autoaim_sender')
        
        self.lock = threading.Lock()
        self.latest_msg = None
        self.seq = 0
        self.callback_group = ReentrantCallbackGroup()

        serial_port_path = '/dev/dji_vcp'
        baud_rate = 921600 
        
        try:
            self.serial_port = serial.Serial(
                port=serial_port_path,
                baudrate=baud_rate,
                timeout=0,           # 非阻塞读
                write_timeout=0      # 非阻塞写
            )
            os.system(f"sudo setserial {serial_port_path} low_latency")
            self.get_logger().info(f'串口 {serial_port_path} 已打开，频率目标: 200Hz')
        except Exception as e:
            self.get_logger().error(f'串口启动失败: {e}')
            exit(1)


        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT, # 传感器模式：不重传，延迟最低
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        self.subscription = self.create_subscription(
            AutoaimData,
            'autoaim_topic',
            self.autoaim_callback,
            qos_profile,
            callback_group=self.callback_group
        )

        self.send_timer = self.create_timer(
            0.005, # 200Hz
            self.timer_send_callback,
            callback_group=self.callback_group
        )
        
        self.get_logger().info('200Hz 发送节点已就绪')

    def autoaim_callback(self, msg):
        with self.lock:
            self.latest_msg = msg

    def timer_send_callback(self):
        if self.latest_msg is None:
            return

        with self.lock:
            yaw = self.latest_msg.yaw_angle_diff
            pitch = self.latest_msg.pitch_angle_diff
            fire = self.latest_msg.fire

        packet = pack_autoaim_data(yaw, pitch, fire, self.seq)
        
        try:
            self.serial_port.write(packet)
            self.seq = (self.seq + 1) % 256
            self.get_logger().info(f'发送内容 -> Yaw: {yaw:.3f}, Pitch: {pitch:.3f}, Fire: {fire}, HEX: {packet.hex()}',throttle_duration_sec=0.5)
            
        except serial.SerialException as e:
            self.get_logger().error(f"串口写入异常: {e}")

    def __del__(self):
        if hasattr(self, 'serial_port'):
            self.serial_port.close()

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