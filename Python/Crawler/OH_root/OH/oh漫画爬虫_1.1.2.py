from selenium import webdriver
from bs4 import BeautifulSoup
import requests
import time
import os

def Pic_save(path,url):
    respone = requests.get(url)
    with open(path,'wb') as f:
        f.write(respone.content)

def Get_ver(path):
    with open(path + 'update.txt','r') as f:
        line = f.readline()
        line_num = line.split()
        a = line_num[0]

    return a

def Update(path,num):
    s = str(num)
    with open(path + 'update.txt','w') as f:
        f.write(s)

def Create(path):
    if not os.path.exists(path):
        os.makedirs(path)
    else:
        print('目标文件夹已存在， 3秒后进入更新状态')
        return True
    return False


def each(url,path_z,Num):
    browser = webdriver.Firefox()
    browser.get(url)
    browser.implicitly_wait(3)

    html_each = requests.get(url)
    soup = BeautifulSoup(html_each.content,'lxml')
    # print(soup.prettify())
    
    pageNum = (len(browser.find_elements_by_tag_name('option')) - 6) / 2
    pageNum = int(pageNum)
    # print(pageNum)

    name_div = soup.find('div',attrs={'class':'mh_readtitle'})
    name = (name_div.find('strong')).get_text()
    # print(name)
    
    # space = ' '
    # new = '%20'
    l = list(name)
    for o in range(len(l)):
        if l[o] == ' ':
            l[o] = '%20'
    s = ''
    for i in range(len(l)):
        s = s + l[i]
    # print(s)

    print('开始保存' + name + '！')
    
    # b = os.getcwd()
    os.mkdir(path_z + name)
    path_s = path_z + name + '\\'
    
    for i in range(pageNum):
        if i + 1 < 10:
            pageNum_c = '000' + str(i + 1)
        else:
            pageNum_c = '00' + str(i + 1)
        Pic_url = 'http://image.mljzmm.com/comic/' + Num + '/' + s + '/' + pageNum_c + '.jpg'
        # print(Pic_url)
        Pic_save(path_s + pageNum_c + '.jpg',Pic_url)
        
    # http://img.mljzmm.com/comic/14339/057/0001.jpg
    print(name + '保存完毕！')
    browser.quit()

def mulu(base_url,path_a,Num):
    url_list = []
    # html = get_html(base_url)
    html = requests.get(base_url)
    # print(html.text)
    soup = BeautifulSoup(html.content,'lxml')
    
    liTags = soup.find_all('li',attrs={'class':'fed-padding fed-col-xs6 fed-col-md3 fed-col-lg3'})
    name_a = (soup.find('h1',attrs={'class':'fed-part-eone fed-font-xvi'})).get_text()

    ver = 0
    path_z = path_a + name_a + '\\'
    if Create(path_a + name_a):
        time.sleep(3)
        ver = Get_ver(path_z)
    
    i = 0
    # print(soup.prettify())
    for li in liTags:
        url_list.append("https://www.ohmanhua.com" + \
                      li.find('a',attrs={'class':'fed-btns-info fed-rims-info fed-part-eone'})['href'])
        i = i + 1
    if i - int(ver) == 0:
        print('无可更新章节，3秒后自动退出')
        time.sleep(3)
        return
    print('共' + str(i) + '章节，需更新' + str(i - int(ver)) + '章，获取各章节地址成功！')
    j = i - int(ver) - 1
    while j >= 0:
        # print(j)
        # print(url_list[j])
        each(url_list[j],path_z,Num)
        j = j - 1
    Update(path_z,i)

def main():
    base_url = str(input('请输入漫画首页地址： \n'))
    path_a = 'f:\\ACG\\Comic\\'
    url_l = list(base_url)
    s = ''
    num = 0
    for a in url_l:
        if num == 3:
            num = num + 1
        if a == '/':
            num = num + 1
        if num == 5:
            break
        if num > 3:
            s = s + a
    mulu(base_url,path_a,s)
    print('Finished saving!')

if __name__ == '__main__':
    main()

