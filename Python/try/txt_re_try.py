import os

def is_number(s):
    try:
        float(s)
        return True
    except ValueError:
        pass
 
    try:
        import unicodedata
        unicodedata.numeric(s)
        return True
    except (TypeError, ValueError):
        pass
 
    return False

f = open("./re_test.txt")
line = f.readline()
line_num = line.split(' ')
#num = (int)line_num[0]
#print(line_num[0])

a = line_num[0]
print(a)

if is_number(a) == True:
    print('Yes')
else:
    print('No')

s = input("键入'Enter'以退出")