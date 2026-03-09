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
        
        # 1. 初始化变量与锁（保证多线程安全）
        self.lock = threading.Lock()
        self.latest_msg = None
        self.seq = 0
        
        # 2. 配置并发回调组
        self.callback_group = ReentrantCallbackGroup()

        # 3. 串口初始化
        serial_port_path = '/dev/ttyACM0'
        # 强烈建议使用 921600，200Hz 下 115200 吞吐量压力较大
        baud_rate = 921600 
        
        try:
            self.serial_port = serial.Serial(
                port=serial_port_path,
                baudrate=baud_rate,
                timeout=0,           # 非阻塞读
                write_timeout=0      # 非阻塞写
            )
            # 开启 Linux 内核串口低延迟模式
            os.system(f"sudo setserial {serial_port_path} low_latency")
            self.get_logger().info(f'串口 {serial_port_path} 已打开，频率目标: 200Hz')
        except Exception as e:
            self.get_logger().error(f'串口启动失败: {e}')
            exit(1)

        # 4. 配置高性能 QoS
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT, # 传感器模式：不重传，延迟最低
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # 5. 订阅解算数据（异步接收）
        self.subscription = self.create_subscription(
            AutoaimData,
            'autoaim_topic',
            self.autoaim_callback,
            qos_profile,
            callback_group=self.callback_group
        )

        # 6. 核心：200Hz 定时器 (1.0 / 200 = 0.005s)
        self.send_timer = self.create_timer(
            0.005, 
            self.timer_send_callback,
            callback_group=self.callback_group
        )
        
        self.get_logger().info('200Hz 发送节点已就绪')

    def autoaim_callback(self, msg):
        """
        更新最新数据：解算节点算出一帧，这里就存一帧
        """
        with self.lock:
            self.latest_msg = msg

    def timer_send_callback(self):
        """
        主发送循环：由定时器驱动，确保严格的 200Hz 频率
        """
        # 即使视觉没算出新数据，我们也发（电控端需要连续的心跳/控制流）
        # 如果 self.latest_msg 是 None，说明还没收到第一帧
        if self.latest_msg is None:
            return

        with self.lock:
            yaw = self.latest_msg.yaw_angle_diff
            pitch = self.latest_msg.pitch_angle_diff
            fire = self.latest_msg.fire

        # 打包数据
        packet = pack_autoaim_data(yaw, pitch, fire, self.seq)
        
        try:
            # 执行物理写入
            self.serial_port.write(packet)
            # 序号自增
            self.seq = (self.seq + 1) % 256
            
            # 调试用：每秒打印一次实际发送状态，防止阻塞
            self.get_logger().info(f'发送内容 -> Yaw: {yaw:.3f}, Pitch: {pitch:.3f}, Fire: {fire}, HEX: {packet.hex()}',throttle_duration_sec=0.5)
            
        except serial.SerialException as e:
            self.get_logger().error(f"串口写入异常: {e}")

    def __del__(self):
        if hasattr(self, 'serial_port'):
            self.serial_port.close()

def main(args=None):
    rclpy.init(args=args)
    
    node = AutoAimSender()
    # 使用 MultiThreadedExecutor 保证 Timer 和 Subscription 不互斥
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