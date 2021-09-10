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
        printf("是否开启文件读写？（Y/N）\n");
        string fil = "";
        cin >> fil;
        if (fil == "Y")
          return true;
        else if (fil == "N")
          return false;
        else{
            printf("输入有误！请重新输入！\n");
            Sleep(2);
            continue;
        }
    }
}

int main(){
    //printf("Nothing here...\n");
    bool f = false;
    if (file_wr_a()){
        printf("请键入输入文件名（为.txt格式，输入包含拓展名）:\n");
        char name_in[50];
        scanf("%s",name_in);
        printf("请键入输出文件名（为.txt格式，输入包含拓展名）:\n");
        char name_out[50];
        scanf("%s",name_out);
        f = true;
        freopen(name_in,"r",stdin);
        freopen(name_out,"w",stdout);
    }
    if (!f)
      printf("请键入边数:\n"); 
    scanf("%d",&n);
    if (!f)
      printf("请键入各边，每行两个数，第一个数为父节点，第二个数为子节点\n");
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
