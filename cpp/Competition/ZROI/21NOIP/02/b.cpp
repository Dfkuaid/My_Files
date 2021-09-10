#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

struct Node {int val, pre, mod;} p[N];

int n, k, vis[N], ctuse[10], cnt, tal;

queue <int> q;

void print(int x) {
    if (!x) {return;} print(p[x].pre); 
    printf("%d", p[x].val);
}

int main() {
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= k; ++ i) {
        int x; scanf("%d", &x);
        ctuse[x] = 1;
    }
    p[0] = (Node){0, -1, 0}; q.push(0);
    while (q.size()) {
        int now = q.front(), i = 0; q.pop();
        if (p[now].mod == 0) i = 1;
        for (; i <= 9; ++ i) if (!ctuse[i]) {
            int nmod = (p[now].mod * 10 + i) % n;
            if (!vis[nmod]) {
                vis[nmod] = 1; p[++ cnt] = (Node){i, now, nmod};
                if (!nmod) {tal = cnt; print(tal); return 0;}
                q.push(cnt);
            }
        }
    }
    printf("-1"); return 0;
}