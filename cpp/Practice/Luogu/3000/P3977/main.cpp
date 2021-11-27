#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define ull unsigned long long
using namespace std;

const int N = 1 << 6;
const ull MOD = 1ull << 32;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

inline void madd(ull &x, ull y) {x = x + y < MOD ? x + y : x + y - MOD;}

struct Matrix {
    ull a[64][64], x, y;

    inline Matrix() {x = y = 0; memset(a, 0, sizeof a);}
    inline void init(int _x, int _y) {x = _x, y = _y;}

    inline void unitary(int len) {
        x = y = len; for (int i = 0; i <= len; ++ i) a[i][i] = 1;
    }

    inline Matrix operator * (const Matrix b) const {
        Matrix res; res.init(x, b.y);
        for (int i = 0; i <= res.x; ++ i)
          for (int j = 0; j <= res.y; ++ j)
            for (int k = 0; k <= y; ++ k)
              madd(res.a[i][j], a[i][k] * b.a[k][j] % MOD);
        return res;
    }

    inline void print() {
        for (int i = 0; i <= x; ++ i, puts(""))
          for (int j = 0; j <= y; ++ j)
            printf("%llu ", a[i][j]);
        puts("");
    }
} t, f;

int n, m, p, k, tp[3], is_illegal[N], single_range[10], line_range[N][2]; ull ans;

inline void print_b(int x, char c) {
    for (int i = m - 1; ~i; -- i) printf("%d", (x >> i) & 1); putchar(c);
}

inline Matrix fpow_mtx(Matrix x, int y) {
    Matrix res; res.unitary(x.x);
    while (y) {
        if (y & 1) res = res * x;
        y >>= 1; x = x * x;
    }
    return res;
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n), read(m), read(p), read(k);
    for (int i = 0; i <= 2; ++ i)
      for (int j = 1, x; j <= p; ++ j)
        read(x), tp[i] = (tp[i] << 1) | x;
    for (int i = 0; i < m; ++ i) {
        if (i + 1 < p - k) single_range[i] |= (tp[1] >> p - k - 1 - i);
        else single_range[i] |= (tp[1] << i - (p - k - 1));
        single_range[i] ^= (1 << i);
    }
    for (int s = 0; s < (1 << m); ++ s)
      for (int i = 0; i < m; ++ i)
        if (((s >> i) & 1) && (single_range[i] & s)) {
            is_illegal[s] = true; break;
        }
    for (int s = 0; s < (1 << m); ++ s) {
        if (is_illegal[s]) continue;
        for (int i = 0; i < m; ++ i) {
            if (!((s >> i) & 1)) continue;
            if (i + 1 < p - k) {
                line_range[s][0] |= (tp[0] >> p - k - 1 - i);
                line_range[s][1] |= (tp[2] >> p - k - 1 - i);
            } else {
                line_range[s][0] |= (tp[0] << i - (p - k - 1));
                line_range[s][1] |= (tp[2] << i - (p - k - 1));
          }
        }      
    }
    t.init((1 << m) - 1, (1 << m) - 1); f.init(1, (1 << m) - 1);
    for (int s1 = 0; s1 < (1 << m); ++ s1) {
        if (is_illegal[s1]) continue;
        for (int s2 = 0; s2 < (1 << m); ++ s2) {
            if (is_illegal[s2]) continue;
            if (line_range[s1][1] & s2) continue;
            if (line_range[s2][0] & s1) continue;
            t.a[s1][s2] = 1;
        }
    }
    for (int s = 0; s < (1 << m); ++ s) f.a[1][s] = !is_illegal[s];
    t = fpow_mtx(t, n - 1); f = f * t;
    for (int s = 0; s < (1 << m); ++ s) madd(ans, f.a[1][s]);
    printf("%llu", ans); return 0;
}