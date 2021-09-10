#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n, a[N], b[N], ln, sum1[N], sum2[N];

inline bool cmp(int x, int y) {return x > y;}

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n);
        for (int i = 1; i <= n; i ++) scanf("%d", &a[i]);
        for (int i = 1; i <= n; i ++) scanf("%d", &b[i]);
        sort(a + 1, a + n + 1, cmp); sort(b + 1, b + n + 1,cmp);
        int src1 = 0, src2 = 0; ln = n;
        for (int i = 1; i <= n; i ++)
          sum1[i] = sum1[i - 1] + a[i];
        for (int i = 1; i <= n; i ++)
          sum2[i] = sum2[i - 1] + b[i];
        for(; n <= ln * 2 + 1; n ++){
            int lt = n - int(n / 4);
            src1 = sum1[lt - (n - ln)] + (n - ln) * 100;
            src2 = sum2[min(lt, ln)];
            // cout << src1 << " " << src2 << endl;
            if(src1 >= src2) break;
        }
        printf("%d\n", n - ln);
    }
    return 0;
}