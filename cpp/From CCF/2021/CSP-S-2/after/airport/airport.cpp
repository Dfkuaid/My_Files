#include <bits/stdc++.h>
#define ll long long
#define pii pair <int, int>
#define mp(a, b) make_pair(a, b)
using namespace std;

const int N = 200010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}   

template <typename T> inline T Max(T a, T b) {return a > b ? a : b;}

struct Node {
    int id, x, op;
    bool operator < (const Node &b) const {return x < b.x;}
} fa[N], fb[N];
struct line {int st, ed, cnt;} la[N], lb[N];

int n, m1, m2, lacnt, lbcnt, al[N][2], bl[N][2], numa[N], numb[N], ans;

priority_queue <pii > rest, busy;

int main() {
    freopen("airport.in", "r", stdin);
    freopen("airport.out", "w", stdout);
    read(n), read(m1), read(m2);
    for (int i = 1; i <= m1; ++ i) {
        read(al[i][0]); read(al[i][1]);
        fa[2 * i - 1] = (Node){i, al[i][0], 1};
        fa[2 * i] = (Node){i, al[i][1], -1};
    }
    sort(fa + 1, fa + m1 * 2 + 1);
    for (int i = 1; i <= m2; ++ i) {
        read(bl[i][0]), read(bl[i][1]);
        fb[2 * i - 1] = (Node){i, bl[i][0], 1};
        fb[2 * i] = (Node){i, bl[i][1], -1};
    }
    sort(fb + 1, fb + m2 * 2 + 1);
    for (int i = 1; i <= m1 * 2; ++ i) {
        if (fa[i].op == 1) {
            if (rest.empty()) {
                la[++ lacnt].cnt = 1;
                la[lacnt].st = fa[i].x;
                la[lacnt].ed = al[fa[i].id][1];
                busy.push(mp(-la[lacnt].ed, lacnt));
            } else {
                pii now = rest.top(); rest.pop();
                ++ la[now.second].cnt;
                la[now.second].ed = al[fa[i].id][1];
                busy.push(mp(-la[now.second].ed, now.second));
            }
        } else {
            pii now = busy.top(); busy.pop();
            rest.push(mp(-la[now.second].st, now.second));
        }
    }
    while (rest.size()) rest.pop();
    while (busy.size()) busy.pop();
    for (int i = 1; i <= m2 * 2; ++ i) {
        if (fb[i].op == 1) {
            if (rest.empty()) {
                lb[++ lbcnt].cnt = 1;
                lb[lbcnt].st = fb[i].x;
                lb[lbcnt].ed = bl[fb[i].id][1];
                busy.push(mp(-lb[lbcnt].ed, lbcnt));
            } else {
                pii now = rest.top(); rest.pop();
                ++ lb[now.second].cnt;
                lb[now.second].ed = bl[fb[i].id][1];
                busy.push(mp(-lb[now.second].ed, now.second));
            }
        } else {
            pii now = busy.top(); busy.pop();
            rest.push(mp(-lb[now.second].st, now.second));
        }
    }
    for (int i = 1; i <= lacnt; ++ i) numa[i] = numa[i - 1] + la[i].cnt;
    for (int i = lacnt + 1; i <= n; ++ i) numa[i] = numa[i - 1];
    for (int i = 1; i <= lbcnt; ++ i) numb[i] = numb[i - 1] + lb[i].cnt;
    for (int i = lacnt + 1; i <= n; ++ i) numb[i] = numb[i - 1];
    for (int i = 0; i <= n; ++ i) ans = Max(ans, numa[i] + numb[n - i]);
    printf("%d", ans); return 0;
}
