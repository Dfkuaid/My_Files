#define DEBUG

#include <bits/stdc++.h>
#define db double
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 20;
const int M = 300010;
const double eps = 1e-8;
const int INF = 0x3fffffff;

template <typename T>
inline T ABS(const T x) {return x < 0 ? -x : x;}

template <typename T>
inline T Min(const T a, const T b) {return a < b ? a : b;}

struct Pig {db x, y;} p[N];
int T, n, m, f[M], line[N][N], frt[M];

inline void solve(db &a, db &b, db a1, db a2, db b1, db b2) {
    b = (b2 * a1 * a1 - b1 * a2 * a2) / (a2 * a1 * a1 - a1 * a2 * a2);
    a = (b1 - b * a1) / (a1 * a1);
}

inline db calc(db a, db b, db x) {return a * x * x + b * x;}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    for (int i = 0; i < (1 << 18); ++ i) {
        int j = 1;
        while ((j <= 18) && (i & (1 << (j - 1)))) ++ j;
        frt[i] = j;
    }
    scanf("%d", &T);
    while (T --) {
        mset(line, 0), mset(f, 0x3f);
        scanf("%d%d", &n, &m); f[0] = 0;
        for (int i = 1; i <= n; ++ i)
          scanf("%lf%lf", &p[i].x, &p[i].y);
        for (int i = 1; i <= n; ++ i)
          for (int j = 1; j <= n; ++ j) {
              if (ABS(p[i].x - p[j].x) <= eps) continue;
              db a, b;
              solve(a, b, p[i].x, p[j].x, p[i].y, p[j].y);
            //   cout << i << " " << j << " " << a << " " << b << endl;
              if (a > -eps) continue;
              for (int k = 1; k <= n; ++ k)
                if (ABS(calc(a, b, p[k].x) - p[k].y) <= eps)
                  line[i][j] |= (1 << (k - 1));
          }
        // for (int i = 1; i <= n; ++ i) {
        //     for (int j = 1; j <= n; ++ j)
        //       printf("%d ", line[i][j]);
        //     printf("\n");
        // }
          
        for (int i = 0; i < (1 << n); ++ i) {
            int j = frt[i]; //printf("%d %d\n", i, f[i]);
            f[i | (1 << (j - 1))] = Min(f[i | (1 << (j - 1))], f[i] + 1);
            for (int k = 1; k <= n; ++ k)
              f[i | line[j][k]] = Min(f[i | line[j][k]], f[i] + 1);
        }
        // for (int i = 0; i < (1 << n); ++ i) printf("%d ", f[i]);
        // printf("\n");
        printf("%d\n", f[(1 << n) - 1]);
    }
    return 0;
}