#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct P{
    int ind;
    int val;
};
P p[N];

int T;

inline int cmp(const P &a,const P &b){
    return a.val > b.val;
}

inline int check(int a,int b){
    if (a == 1 || a == 2){
        if (b == 3 || b == 4)
          return true;
        else return false;
    }
    else {
        if (b == 1 || b == 2)
          return true;
        else return false;
    }
}

int main(){
    scanf("%d",&T);
    while (T --){
        scanf("%d%d%d%d",&p[0].val,&p[1].val,&p[2].val,&p[3].val);
        p[0].ind = 1;p[1].ind = 2;
        p[2].ind = 3;p[3].ind = 4;
        sort(p,p + 4,cmp);
        if (check(p[0].ind,p[1].ind))
          printf("Yes\n");
        else printf("No\n");
    }
    return 0;
}
