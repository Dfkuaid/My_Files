#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 60;
const int INF = 0x3fffffff;

int t,n,m,no,l,y;
char mp[N][N],m1[N][N],m2[N][N],k[2] = {'W','R'};

inline void prework(){
    for (int i = 1;i <= 55;i ++){
        y = l ^ 1;l ^= 1;
        for (int j = 1;j <= 55;j ++){
            m1[i][j] = k[y];
            y ^= 1;
        }
    }
    l = 1;
    for (int i = 1;i <= 55;i ++){
        y = l ^ 1;l ^= 1;
        for (int j = 1;j <= 55;j ++){
            m2[i][j] = k[y];
            y ^= 1;
        }
    }
}

int main(){
    prework();
    scanf("%d",&t);
    while (t --){
        no = 0;
        scanf("%d%d",&n,&m);
        for (int i = 1;i <= n;i ++)
          for (int j = 1;j <= m;j ++)
            cin >> mp[i][j];
        for (int i = 1;i <= n;i ++){
            for (int j = 1;j <= m;j ++)
              if (mp[i][j] != '.' && mp[i][j] != m1[i][j]){
                  no = 1;
                  break;
              }
            if (no) break;
        }
        if (!no){
            printf("YES\n");
            for (int i = 1;i <= n;i ++){
                 for (int j = 1;j <= m;j ++)
                   cout << m1[i][j];
                cout << endl;
            }
            continue;    
        }no = 0;
        for (int i = 1;i <= n;i ++){
            for (int j = 1;j <= m;j ++)
              if (mp[i][j] != '.' && mp[i][j] != m2[i][j]){
                  no = 1;
                  break;
              }
            if (no) break;
        }
        if (!no){
            printf("YES\n");
            for (int i = 1;i <= n;i ++){
                 for (int j = 1;j <= m;j ++)
                   cout << m2[i][j];
                cout << endl;
            }
            continue;    
        }
        else printf("NO\n");
    }
    // system("pause");
    return 0;
}