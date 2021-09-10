#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <map>
#include <cstring>
#include <windows.h>
#include "tree_paint.h"
using namespace std;

int n,tot;
string stoint[200001];
map <string,tree> node;

void paint_p(tree a){
    cout << a.get_num() << endl;
    cout << "Index: " << a.get_index() << endl;
    printf("Son_num: %d\n",a.get_son_t());
    cout << "Father: " << node[a.get_father()].get_index() << endl;
    for (int i = 0;i < a.get_son_t();i ++)
      cout << "Son" << i + 1 << " is " << node[a.get_son(i)].get_index() << endl;
    cout << endl;
}

bool file_wr_a(){
    while (true)
    {
        system("cls");
        printf("�Ƿ����ļ���д����Y/N��\n");
        string fil = "";
        cin >> fil;
        if (fil == "Y")
          return true;
        else if (fil == "N")
          return false;
        else{
            printf("�����������������룡\n");
            Sleep(2);
            continue;
        }
    }
}

int main(){
    //printf("Nothing here...\n");
    bool f = false;
    if (file_wr_a()){
        printf("����������ļ�����Ϊ.txt��ʽ�����������չ����:\n");
        char name_in[50];
        scanf("%s",name_in);
        printf("���������ļ�����Ϊ.txt��ʽ�����������չ����:\n");
        char name_out[50];
        scanf("%s",name_out);
        f = true;
        freopen(name_in,"r",stdin);
        freopen(name_out,"w",stdout);
    }
    if (!f)
      printf("��������:\n"); 
    scanf("%d",&n);
    if (!f)
      printf("�������ߣ�ÿ������������һ����Ϊ���ڵ㣬�ڶ�����Ϊ�ӽڵ�\n");
    while (n --){
        string fa,son;
        cin >> fa >> son;
        if (!node[fa].get_vis()){
            node[fa].vis(true);
            node[fa].ch_in(fa,tot);
            stoint[tot] = fa;
            tot ++;
        }
        if (!node[son].get_vis()){
            node[son].vis(true);
            node[son].ch_in(son,tot);
            stoint[tot] = son;
            tot ++;
        }
        node[son].new_fa(fa);
        node[fa].new_son(son);
    }
    for (int i = 0;i < tot;i ++)
      paint_p(node[stoint[i]]);
    if (f){
    	fclose(stdin);
    	fclose(stdout);
	}
	else
      system("pause");
    return 0;
}
