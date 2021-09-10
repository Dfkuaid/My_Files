#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Point {
    ll x, y;

    inline Point operator - (const Point b) const {
        return (Point){x - b.x, y - b.y};
    }
    inline Point operator + (const Point b) const {
        return (Point){x + b.x, y + b.y};
    }
} d[N];

inline ll dot(Point a, Point b) {return a.x * b.x + a.y * b.y;}
inline ll cross(Point a, Point b) {return a.x * b.y - a.y * b.x;}
inline ll dis(Point a, Point b) {return dot(a - b, a - b);}

int T, nxt[N << 2], len, f[N << 2], n;
ll e[N], h[N]; int s[N << 2], t[N << 1];

inline void Reset() {
    len = 0; mset(nxt, 0);
}

inline ll horn_calc(int x) {
    int y = x + 1, z = x + 2;
	if (y > n) y = y % n; if (z > n) z = z % n;
	return cross(d[y] - d[x], d[z] - d[y]);
}

inline ll edge_calc(int x) {
    return dis(d[x], x + 1 > n ? d[1] : d[x + 1]);
}

int KMP(int *a, int la, int *b, int lb) { 
	nxt[0] = 0;
    for (int i = 1, j = 0; i <= la; ++ i) {
        while (j && a[i] != a[j]) j = nxt[j];
        nxt[i + 1] = ++ j;
    }
    for (int i = 1, j = 0; i <= lb; ++ i) {
        while (j && b[i] != a[j]) j = nxt[j];
        f[i] = j ++;
    }
	int cnt = 0;
	for (int i = 1; i <= lb; ++ i)
	  if (f[i] == la) ++ cnt;
	return cnt;
}
int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
	scanf("%d", &T);
	while (T --) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++ i)
		  scanf("%d%d", &d[i].x, &d[i].y);
		for(int i = 1; i <= n; ++ i) {
			e[i] = edge_calc(i);
			h[i] = horn_calc(i);
		}
		int ls = 0, lt = 0;
		for (int i = 1; i <= n; ++ i)
		  s[++ ls] = e[i], s[++ ls] = h[i];
		for (int i = 1; i <= n; ++ i)
		  s[++ ls] = e[i], s[++ ls] = h[i];
        // for (int i = 1; i <= ls; ++ i)
        //   printf("%d ", s[i]);
        // printf("\n");
		for(int i = n << 1; i >= 1; -- i)
		  t[++ lt] = s[i];
        // for (int i = 1; i <= lt; ++ i)
        //   printf("%d ", t[i]);
        // printf("\n");
		printf("%d\n", KMP(t, lt, s, ls));
	}
}
