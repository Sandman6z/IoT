#bin文件串口传输工具
#zhongziming 20200627
#bilibili:netube_99

import serial
import struct
import os
import time

try:
    com = input("串口号：")
    bote = input("波特率：")
    ser=serial.Serial(com,int(bote),timeout=1)
except Exception as e :
    print("启动串口异常:",e)

file_addr = input("bin文件：")
f_byte = int(input("每帧数据量(Byte)："))
f_delay = 1/int(input("帧速率："))-0.005#减去一点时间作为速度补偿
f_number = int(os.path.getsize(file_addr)/f_byte)#求出一共有多少帧画面
print("已解析 %d 帧画面，开始传输..."%(f_number))

#读取bin数据
binfile = open(file_addr,'rb')#打开一个文件
for i in range(f_number):
    ser.write(binfile.read(f_byte))#读取并发送一帧画面
    time.sleep(f_delay)

print("传输结束.")
ser.close()