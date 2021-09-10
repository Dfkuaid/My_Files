#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int stack[N],frt;
char a[N],b[N];

inline int index(char c){
    if (c == '(' || c== ')')
      return 1;
    else return 2;
}

int main(){
    scanf("%s",a);
    int len = strlen(a);
    for (int i = 0;i < len;i ++){
        if (a[i] == '(' || a[i] == '['){
            stack[++ frt] = i;
            if (a[i] == '(') b[i] = ')';
            else b[i] = ']';
        }
        else if (frt && index(a[i]) == index(a[stack[frt]]))
          b[stack[frt --]] = '*',b[i] = '*';
        else if (a[i] == ']') b[i] = '[';
        else b[i] = '(';
    }
    for (int i = 0;i < len;i ++){
        if (a[i] == ')' || a[i] == ']')
          if (b[i] != '*') putchar(b[i]);
        putchar(a[i]);
        if (a[i] == '(' || a[i] == '[')
          if (b[i] != '*') putchar(b[i]);
    }
    return 0;
}
