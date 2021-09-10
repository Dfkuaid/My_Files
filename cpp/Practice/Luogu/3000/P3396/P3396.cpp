#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 150100;
const int INF = 0x3fffffff;

int sum[500][500];
int n,m,size,val[N];

int main(){
    // freopen("P3396_1.in","r",stdin);
    // freopen("out.txt","w",stdout);
    
    scanf("%d%d",&n,&m);
//    cout << n << m;
    size = sqrt(n);
    for (int i = 1;i <= n;i ++){
        scanf("%d",&val[i]);
        for (int p = 1;p <= size;p ++)
          sum[p][i % p] += val[i];
    }
    while (m --){
//        cout << m << endl;
        char opt;
        int x,y;
        cin >> opt;
        scanf("%d%d",&x,&y);
        if (opt == 'A'){
            if (x <= size) printf("%d\n",sum[x][y]);
            else{
                int res = 0;
                for (int i = y;i <= n;i += x)
                  res += val[i];
                printf("%d\n",res);
            }
        }
        else{
            for (int i = 1;i <= size;i ++)
              sum[i][x % i] += y - val[x];
            val[x] = y;
        }
    }
    return 0;
}
