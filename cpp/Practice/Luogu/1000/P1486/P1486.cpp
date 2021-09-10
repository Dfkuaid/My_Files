#define DEBUG

#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 2000010;
const int UPL = 300010;
const int INF = 0x3fffffff;

struct Node {int ls, rs, sum;} p[N];

int n, m, cnt, ans, tag, rt;

inline void pushup(int k) {
    p[k].sum = p[p[k].ls].sum + p[p[k].rs].sum;
}

inline void add(int &k, int l, int r, int x) {
    if (!k) k = ++ cnt;
    if (l == r) {++ p[k].sum; return;}
    int mid = l + r >> 1;
    if (x <= mid) add(p[k].ls, l, mid, x);
    else add(p[k].rs, mid + 1, r, x);
    pushup(k);
}

inline void update(int &k, int l, int r, int x) {
    if (!k) return;
    int mid = l + r >> 1;
    if (mid > x) update(p[k].ls, l, mid, x);
    else {
        p[k].sum -= p[p[k].ls].sum;
        ans += p[p[k].ls].sum; p[k].ls = 0;
    } if (mid < x) update(p[k].rs, mid + 1, r, x);
    pushup(k);
}

inline int kth(int k, int l, int r, int x) {
    if (l == r) return l;
    int mid = l + r >> 1, rsum = p[p[k].rs].sum;
    if (rsum >= x) return kth(p[k].rs, mid + 1, r, x);
    else return kth(p[k].ls, l, mid, x - rsum);
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif

    scanf("%d%d", &n, &m);
    char c; int x;
    while (n --) {
        cin >> c >> x;
        if (c == 'I') {
            if (x >= m) add(rt, -UPL, UPL, x - tag);
        } else if (c == 'A') tag += x;
        else if (c == 'S') {
            tag -= x; update(rt, -UPL, UPL, m - tag - 1);
        } else  {
            if (x > p[rt].sum) {printf("-1\n"); continue;}
            printf("%d\n", kth(rt, -UPL, UPL, x) + tag);
        }
    }
    printf("%d", ans);
    return 0;
}