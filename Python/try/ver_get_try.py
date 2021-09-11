import os

def Get_ver():
    with open('./update.ini','r') as f:
        line = f.readline()
        line_num = line.split()
        a = line_num[0]

    return a

ver = Get_ver()
print(ver)

s = input("键入'Enter'以退出")