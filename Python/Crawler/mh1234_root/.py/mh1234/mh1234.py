from selenium import webdriver
from bs4 import BeautifulSoup
from lxml import etree
import requests
import time
import os

def is_num(s):
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

def check():
    # 获取当前文件路径
    current_path = os.path.abspath(__file__)
    # 获取当前文件的父目录
    # father_path = os.path.abspath(os.path.dirname(current_path) + os.path.sep + ".")
    # config.ini文件路径,获取当前目录的父目录的父目录与congig.ini拼接
    config_file_path=os.path.join(os.path.abspath(os.path.dirname(current_path) + os.path.sep + ".."),'config.ini')
    save_path=os.path.join(os.path.abspath(os.path.dirname(current_path) + os.path.sep + ".."),'save')

    #print('config.ini:')
    if not os.path.exists(config_file_path):
        # print('No')
        with open(config_file_path,'w') as f:
            f.write(save_path)
        # print('Finished creating')
    # else:
        # print('Yes')
    with open(config_file_path,'r') as f:
        line = f.readline()
    # print('储存位置:' + line)
    
    # print('save:')
    if not os.path.exists(save_path):
        # print('No')
        os.makedirs(save_path)
        # print('Finished creating')
    # else:
        # print('Yes')
    return line

def Pic_save(url,path):
    respone = requests.get(url)
    with open(path,'wb') as f:
        f.write(respone.content)
    return

def Get_ver(path):
    with open(path + 'update.ini','r') as f:
        line = f.readline()
        line_num = line.split()
        a = line_num[0]
    return a

def Update(path,num):
    s = str(num)
    with open(path + 'update.ini','w') as f:
        f.write(s)
    return

def Create(path):
    if not os.path.exists(path):
        os.makedirs(path)
        with open(path + '/update.ini','w') as f:
            f.write('0')
    else:
        print('目标文件夹已存在， 3秒后进入更新状态')
        return True
    return False

def each(url,name,path_z,num):
    browser = webdriver.Firefox()
    browser.get(url)
    browser.implicitly_wait(3)

    # html_each = requests.get(url)
    # soup = BeautifulSoup(html_each.content,'lxml')

    # print(soup.prettify())
    # print(name + ' ' + url)

    page_num = ''
    f = False
    page_num_l = browser.find_element_by_xpath("//p[@class='img_info']").text
    # print(page_num_l)
    for i in range(len(page_num_l)):
        if f == True and is_num(page_num_l[i]):
            page_num = page_num + page_num_l[i]
        if page_num_l[i] == '/':
            f = True
    page_num = int(page_num)
    # print(page_num)

    os.mkdir(path_z + name)
    path_s = path_z + name + '/'

    for i in range(1,page_num + 1):
        url_new = url + '?p=' + str(i)
        browser.get(url_new)
        Pic_url = browser.find_element_by_xpath("//div[@id='images']/img").get_attribute('src')
        # print(Pic_url)
        Pic_save(Pic_url,path_s + str(i) + '.jpg')

    print('章节' + name + '储存完成！')
    browser.quit()
    return

def mulu(base_url,path_a):
    url_list = []
    name_list = []
    # html = get_html(base_url)
    html = requests.get(base_url)
    # print(html.text)
    soup = BeautifulSoup(html.content,'lxml')
    name_a = (soup.find('h1')).get_text()
    litags_path = soup.find('ul',attrs={'id':'chapter-list-1'})
    # print(name_a)
    # print(litags_path)

    ver = 0
    path_z = path_a + '/' + name_a + '/'
    if Create(path_a + '/' + name_a):
        time.sleep(3)
        ver = Get_ver(path_z)

    i = 0
    litags = litags_path.find_all('li')
    for li in litags:
        # print(li)
        url_list.append('https://www.mh1234.com' + li.find('a')['href'])
        name_list.append((li.find('a').get_text()))
        i = i + 1

    if i - int(ver) == 0:
        print('无可更新章节，3秒后自动退出')
        time.sleep(3)
        return
    print('共' + str(i) + '章节，需更新' + str(i - int(ver)) + '章，获取各章节地址成功！')
    j = int(ver)
    while j <= i - 1:
        # print(j)
        # print(url_list[j])
        each(url_list[j],name_list[j],path_z,i - j)
        Update(path_z,j + 1)
        j = j + 1
    return

def main():
    print('初始化中...')
    pa = check()
    os.system('cls')
    print('mh1234(https://www.mh1234.com/)爬虫 - Dfkuaid')
    print('储存位置为 ' + pa + ' ，有需要请在config.ini文件中更改')
    base_url = input('请输入漫画首页地址:\n')
    mulu(base_url,pa)
    print('Finished saving!')
    os.system('pause')

if __name__ == "__main__":
    main()