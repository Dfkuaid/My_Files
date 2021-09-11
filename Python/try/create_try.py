import os

dirs = '~/文档/path_try'

if not os.path.exists(dirs):
    print('No')
    os.makedirs(dirs)
    print('Finished creating')
else:
    print('Yes')

s = input("键入'Enter'以退出")
