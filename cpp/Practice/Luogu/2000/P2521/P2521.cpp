#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 300010;
const int INF = 0x3fffffff;

struct City {
    int x, y;
    inline bool operator < (const City b) const {return x == b.x ? (y < b.y) : (x < b.x);}
    inline City operator - (const City b) const {return (City){x - b.x, y - b.y};}
    inline int operator * (const City b) const {return x * b.y - y * b.x;}
    inline double calc() {return sqrt(x * x + y * y);}
} c[N];

set <City> s;

int del[N], opt[N], v[N], m, q;
double nowans, ans[N];

inline void insert(City t) {
    set<City>::iterator it = s.lower_bound(t);
    City b = *it, a = *-- it;
    if ((t - a) * (b - t) >= 0) return;
    nowans -= (a - b).calc();
    while (it != s.begin()) {
        a = *it, b = *-- it;
        if ((t - a) * (b - a) >= 0) 
          nowans -= (a - b).calc(), s.erase(a);
        else break;
    }
    it = s.lower_bound(t);
    while (it != --s.end()) {
        a = *it, b = *++ it;
        if ((t - a) * (b - a) <= 0)
          nowans -= (a - b).calc(), s.erase(a);
        else break;
    }
    it = s.lower_bound(t), b = *it, a = *-- it;
    nowans += (t - a).calc() + (t - b).calc(), s.insert(t);
}

int main() {
    int n, x, y; scanf("%d%d%d%d", &n, &x, &y, &m);
    s.insert((City){0, 0}); s.insert((City){n, 0});
    s.insert((City){x, y}); nowans = (City){x, y}.calc() + (City){x - n, y}.calc();
    for (int i = 1; i <= m; ++ i) scanf("%d%d", &c[i].x, &c[i].y);
    scanf("%d", &q);
    for (int i = 1; i <= q; ++ i) {
        scanf("%d", &opt[i]);
        if (opt[i] == 1) scanf("%d", &v[i]), del[v[i]] = 1;
    }
    for (int i = 1; i <= m; ++ i)
      if (!del[i]) insert(c[i]);
    for (int i = q; i; -- i) {
        if (opt[i] == 1) insert(c[v[i]]);
        else ans[i] = nowans;
    }
    for (int i = 1; i <= q; ++ i)
      if (opt[i] == 2) printf("%.2lf\n" , ans[i]);
    return 0;
}