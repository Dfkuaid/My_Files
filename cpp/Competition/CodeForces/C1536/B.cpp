#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t,n,flag;
char s[N],ls,lls;
int f[30][30][30];

int main(){
    scanf("%d",&t);
    while (t --){
        mset(f,0);
        scanf("%d%s",&n,s);flag = 0;
        for (int i = 0;i < n;i ++){
            f[0][0][s[i] - 'a' + 1] = 1;
            if (i > 0) f[0][ls - 'a' + 1][s[i] - 'a' + 1] = 1;
            if (i > 1) f[lls - 'a' + 1][ls - 'a' + 1][s[i] - 'a' + 1] = 1;
            lls = ls;ls = s[i];
        }
        for (int i = 0;i <= 26 && !flag;i ++){
            for (int j = min(i,1);j <= 26 && !flag;j ++){
                for (int k = 1;k <= 26 && !flag;k ++){
                    if (!f[i][j][k]){
                        if (i == 0){
                            if (j == 0){
                                flag = 1;
                                putchar(k + 'a' - 1);
                                putchar('\n');
                            }
                            else {
                                flag = 1;
                                putchar(j + 'a' - 1);
                                putchar(k + 'a' - 1);
                                putchar('\n');
                            }
                        }
                        else{
                            flag = 1;
                            putchar(i + 'a' - 1);
                            putchar(j + 'a' - 1);
                            putchar(k + 'a' - 1);
                            putchar('\n');
                        }
                    }
                }
            }
        }
    }
    // system("pause");
    return 0;
}