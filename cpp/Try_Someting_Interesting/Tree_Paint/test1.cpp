#include <iostream>
#include <cstdlib>
#include <map>
#include <cstring>
#include "tree_paint.h"

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

int main(){
    node["GTR"].ch_in("GTR",1);
    node["DYK"].ch_in("DYK",2);
    node["GTR"].new_fa("DYK");
    node["DYK"].new_son("GTR");
    paint_p(node["GTR"]);
    paint_p(node["DYK"]);
    system("pause");
    return 0;
}