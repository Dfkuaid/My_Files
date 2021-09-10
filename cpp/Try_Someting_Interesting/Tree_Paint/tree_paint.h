#include <iostream>
#include <cstring> 
#include <cstdio>

using namespace std;

class tree{
//public:
private:
    string index;
    int num;
    int sontot;
    string son[11];
    string fa;
    bool f;
public:
    tree(string x,int a);
    tree();
    ~tree();
    string get_father();
    void new_fa(string x);
    //void paint_p();
    void ch_in(string x,int a);
    void new_son(string x);
    int get_num();
    int get_son_t();
    string get_index();
    string get_son(int x);
    void vis(bool x);
    bool get_vis();
};

tree::tree(string x,int a)
{
    index = x;
    num = a;
    fa = num;
}

tree::tree()
{
    f = false;
    sontot = 0;
}

tree::~tree()
{
}

string tree::get_father(){
    return fa;
}

void tree::new_fa(string x){
    fa = x;
    return;
}

void tree::ch_in(string x,int a){
    index = x;
    num = a;
    fa = index;
}

void tree::new_son(string x){
    son[sontot] = x;
    sontot += 1;
}

int tree::get_num(){
    return num;
}

int tree::get_son_t(){
    return sontot;
}

string tree::get_index(){
    return index;
}

string tree::get_son(int x){
    return son[x];
}

void tree::vis(bool x){
    f = x;
}

bool tree::get_vis(){
    return f;
}