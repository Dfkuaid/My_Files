# 在当前文件父目录的父目录检查 config.ini 是否存在
import os

def load_file():
    # 获取当前文件路径
    current_path = os.path.abspath(__file__)
    # 获取当前文件的父目录
    father_path = os.path.abspath(os.path.dirname(current_path) + os.path.sep + ".")
    # config.ini文件路径,获取当前目录的父目录的父目录与congig.ini拼接
    config_file_path=os.path.join(os.path.abspath(os.path.dirname(current_path) + os.path.sep + ".."),'config.ini')
    save_path=os.path.join(os.path.abspath(os.path.dirname(current_path) + os.path.sep + ".."),'save')
    print('当前目录:' + current_path)
    print('当前父目录:' + father_path)
    # dirs = father_path + '\config.ini'
    # print(dirs)
    print('config.ini路径:' + config_file_path)
    print('save路径:' + save_path)

    print('config.ini:')
    if not os.path.exists(config_file_path):
        print('No')
        with open(config_file_path,'w') as f:
            f.write(save_path)
        print('Finished creating')
    else:
        print('Yes')
        with open(config_file_path,'r') as f:
            line = f.readline()
            line_num = line.split()
            a = line_num[0]
        print(a)
    
    print('save:')
    if not os.path.exists(save_path):
        print('No')
        os.makedirs(save_path)
        print('Finished creating')
    else:
        print('Yes')

    n = input('Enter "enter" to exit')
    print(n)
 
load_file()