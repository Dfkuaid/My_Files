#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n,X,x,a,b;
int L,R,now;

int main(){
    scanf("%d%d",&n,&X);
    while (n --){
        scanf("%d%d%d",&x,&a,&b);
        if (R + (x - now) >= b)
          R = (R - (x - now) - b) & 1 ? b - 1 : b - 2;
        else R += x - now;
        if (L - (x - now) <= a)
          L = (a - L + (x - now)) & 1 ? a + 1 : a + 2;
        else L -= (x - now);
        if (R < L){puts("NIE");return 0;}
        now = x;
    }
    printf("%d",(x + L) >> 1);
    return 0;
}
