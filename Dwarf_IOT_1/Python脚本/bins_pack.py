#bin文件打包整合工具
#zhongziming 20200627
#bilibili:netube_99

import struct
import os
import binascii

file_addr = input("bin文件所在地址：") + '\\'
file_name = input("bin文件前缀：")
file_number = int(input("bin文件总数："))
file_numbercode = len(str(file_number))
file_size = 0

#先打开第一个文件获取体积
file_readnum = str(0).zfill(file_numbercode)
filepath = file_addr + file_name + file_readnum + '.bin'
file_size = os.path.getsize(filepath)

print(file_size)

#读取所有bin，整合数据
data = list(range(file_number))
for i in range(file_number):
    file_readnum = str(i).zfill(file_numbercode)
    filepath = file_addr + file_name + file_readnum + '.bin'
    print("read:",filepath)
    binfile = open(filepath,'rb')#打开一个文件
    data[i] = binfile.read(file_size)
    binfile.close()

filepath = file_addr + file_name + '_pack.bin'
binfile = open(filepath,'wb')#创建一个文件
binfile.writelines(data)
binfile.close()

print('Packed')