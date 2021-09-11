from selenium import webdriver
from bs4 import BeautifulSoup
from lxml import etree
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
        print('目标文件夹已存在!')
        return True
    return False


def each(url,path_z,Num):
    browser = webdriver.Firefox()
    browser.get(url)
    browser.implicitly_wait(3)

    # html_each = requests.get(url)
    # soup = BeautifulSoup(html_each.content,'lxml')
    # print(soup.prettify())
    
    pic_url = browser.find_element_by_xpath("//section[@id='image-container']/a/img").get_attribute('src')
    # print(pic_url)
    Pic_save(path_z + str(Num) + '.jpg',pic_url)
    browser.quit()

def mulu(base_url,path_a):
    url_list = []
    # html = get_html(base_url)
    html = requests.get(base_url)
    # print(html.text)
    html_x = etree.HTML(html.content)
    soup = BeautifulSoup(html.content,'lxml')
    
    page_num = 0
    page_num_s = html_x.xpath('//div[@id="info"]/div[1]/text()')
    print(len(page_num_s[0]))
    flag = False
    for i in range(len(page_num_s[0])):
        if page_num_s[0][i] == ' ' :
            if flag == True:
                break
            else:
                flag = True
                continue
        if flag == False:
            continue
        # print(page_num_s[0][i])
        page_num = page_num * 10 + int(page_num_s[0][i])
    # print(page_num)

    name_a = (soup.find('h1')).get_text()
    #ver = 0
    path_z = path_a + name_a + '\\'
    if Create(path_a + name_a):
        time.sleep(3)
        #ver = Get_ver(path_z)
    
    # print(soup.prettify())
    for i in range(1,page_num + 1):
        url_list.append(base_url + 'list/' + str(i) + '/#pagination-page-top')
        print(url_list[i - 1])
        i = i + 1
    #if i - int(ver) == 0:
    #    print('无可更新章节，3秒后自动退出')
    #    time.sleep(3)
    #    return
    #print('共' + str(i) + '章节，需更新' + str(i - int(ver)) + '章，获取各章节地址成功！')
    j = page_num - 1
    while j >= 0:
        # print(j)
        # print(url_list[j])
        each(url_list[j],path_z,j + 1)
        j = j - 1
    #Update(path_z,i)

def main():
    base_url = str(input('请输入漫画首页地址： \n'))
    path_a = str(input('请输入储存位置： \n'))
    path_a = path_a + '\\'
    mulu(base_url,path_a)
    print('Finished saving!')

if __name__ == '__main__':
    main()
