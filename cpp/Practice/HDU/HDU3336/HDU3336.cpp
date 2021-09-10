#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;
const int MOD = 10007;

int t, n, nxt[N], num[N], ans;
char s[N];

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d%s", &n, s); ans = 0;
        for (int i = 0; i <= n; ++ i) num[i] = 1;
        int p = -1; nxt[0] = -1;
        for (int q = 0; q < n; ++ q) {
            while (p != -1 && s[q] != s[p]) p = nxt[p];
            ++ p, nxt[q + 1] = p;
        }
        for (int i = n; i >= 1; -- i)
          num[nxt[i]] += num[i];
        for (int i = 1; i <= n; ++ i)
          (ans += num[i]) %= MOD;
        cout << ans << endl;
    }
    return 0;
}