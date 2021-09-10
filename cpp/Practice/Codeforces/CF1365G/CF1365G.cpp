#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n, id[N], bitnum[N], cnt; ull w[20];

int main() {
    scanf("%d", &n);
    for (int i = 0; i < 1 << 13; ++ i) {
        bitnum[i] = bitnum[i >> 1] + (i & 1);
        if (bitnum[i] == 6) id[++ cnt] = i;
        if (cnt == n) break;
    }
    for (int j = 0; j < 13; ++ j) {
        vector <int> v;
        for (int i = 1; i <= n; ++ i)
          if (id[i] & (1 << j)) v.push_back(i);
        int vsiz = v.size();
        if (vsiz) {
            printf("? %d ", vsiz);
            for (int i = 0; i < vsiz; ++ i) {
                printf("%d", v[i]);
                if (i < vsiz - 1) printf(" ");
            }
            printf("\n"); fflush(stdout);
            cin >> w[j];
        } else w[j] = 0;
        
    }
    printf("! ");
    for (int i = 1; i <= n; ++ i) {
        ull res = 0;
        for (int j = 0; j < 13; ++ j)
          if (!(id[i] & (1 << j))) res |= w[j];
        printf("%llu", res);
        if (i < n) printf(" ");
    }
    return 0;
}