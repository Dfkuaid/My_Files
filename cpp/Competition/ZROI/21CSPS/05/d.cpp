#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define pii pair <int, int>
using namespace std;

const int N = 1010;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T &a, T &b) {return a > b ? a : b;}
template <typename T> inline T Min(T &a, T &b) {return a < b ? a : b;}
template <typename T> inline int Sign(T x) {return x < 0 ? -1 : (x > 0 ? 1 : 0);}

struct Traingle {
    int a, b, c;
    bool operator < (const Traingle &x) const {
        return a == x.a ? (b == x.b ? c < x.c : b < x.b) : a < x.a;
    }
};

struct Point {
    ll x, y;

    Point operator - (const Point &b) const {return (Point){x - b.x, y - b.y};}
    Point operator + (const Point &b) const {return (Point){x + b.x, y + b.y};}
    inline ll operator * (const Point &b) const {return x * b.x + y * b.y;}
    inline ll operator ^ (const Point &b) const {return x * b.y - y * b.x;}
    bool operator == (const Point &b) const {return x == b.x && y == b.y;}
    bool operator < (const Point &b) const {return x == b.x ? y < b.y : x < b.x;}
} p[N];

int CCW(const Point &a, const Point &b, const Point &c) {
    return Sign(a.x * (b.y - c.y) + b.x * (c.y - a.y) + c.x * (a.y - b.y));
}

bool INTERSECT(const Point &a, const Point &b, const Point &c, const Point &d) {
    if (a == b || a == c || a == d || b == c || b == d || c == d) return false;
    return CCW(a, b, c) != CCW(a, b, d) && CCW(c, d, a) != CCW(c, d, b);
}

inline int ccw(int i, int j, int k) {return CCW(p[i], p[j], p[k]);}

inline bool intersect(int i, int j, int k, int o) {return INTERSECT(p[i], p[j], p[k], p[o]);}

int cmp_std;
inline bool cmp(int a, int b) {return ccw(cmp_std, a, b) == 1;}

int n, on_border[N];

vector <pii > edges;
set <Traingle> traingles;

/*Find the convex hull, and get the initial traingles at the same time.*/
/*Notice: We have no necessary to save the convex hull, it's useless.*/
void traingles_init() {
    int lst = 0;
    do {
        int nxt = 0; if (!lst) nxt = 1;
        /*If Starting from the initial point, all points on the boundary 
          should be arranged in a clockwise direction.*/
        for (int i = 0; i < n; ++ i)
          if (ccw(lst, nxt, i) == 1) nxt = i;
        /*Add the edge and the traingle to the set.*/
        edges.push_back({lst, nxt});
        if (lst && nxt) traingles.insert({0, nxt, lst});
        on_border[lst] = true; lst = nxt;
    } while (lst);
}

/*Use the points which are not on the boundary to try to divide the traingles.*/
void traingles_divide() {
    for (int i = 0; i < n; ++ i) {
        if (on_border[i]) continue;
        Traingle target;
        /*If the point is on the same side for all three sides of a triangle, 
         * it must be included by this triangle. We use clockwise and counter-
         * clockwise directions to judge whether it is on the same side*/
        for (auto it : traingles)
          if (ccw(it.a, it.b, i) == 1 
              && ccw(it.b, it.c, i) == 1 
              && ccw(it.c, it.a, i) == 1) {
              target = it; break;
          }
        /*After find the corresponding traingle, delete it from the set,
         * and add the new traingles and edges to the set.*/
        traingles.erase(target);
        traingles.insert({target.a, target.b, i});
        traingles.insert({target.b, target.c, i});
        traingles.insert({target.c, target.a, i});
        edges.push_back({i, target.a});
        edges.push_back({i, target.b});
        edges.push_back({i, target.c});
    }
}

int get_ans() {
    int res = 0;
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        vector <int> a, b; cmp_std = u;
        /*Divide the points to two groups.*/
        for (int i = 0; i < n; ++ i) {
            if (ccw(u, v, i) == -1) a.push_back(i);
            if (ccw(u, v, i) == +1) b.push_back(i);
        }
        sort(a.begin(), a.end(), cmp);
        sort(b.begin(), b.end(), cmp);
        vector <int> c = b; cmp_std = v;
        sort(c.begin(), c.end(), cmp);
        vector <int> pos(n);
        for (int i = 0; i < (int)c.size(); ++ i) pos[c[i]] = i;
        bool ok = true;
        int j = 0, k = -1;
        /*use two-pointers to get the answer.*/
        for (int i = 0; i < (int)a.size(); ++ i) {
            while (j < (int)b.size() && ccw(a[i], u, b[j]) == -1)
              k = max(k, pos[b[j]]), ++ j;
            if (k != -1) ok &= !intersect(u, v, a[i], c[k]);
        }
        if (ok) ++ res;
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 0; i < n; ++ i) read(p[i].x), read(p[i].y);
    sort(p, p + n); raingles_init(); raingles_divide();
    printf("%d", get_ans()); return 0;
}
