#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T ABS(T x) {return x < 0 ? -x : x;}

inline int gcd(int x, int y) {return y ? gcd(y, x % y) : x;}

struct Vector {
    int x, y, z;
    
    inline Vector() {x = y = z = 0;}
    inline Vector(int _x, int _y, int _z) : x(_x), y(_y), z(_z) {}

    inline bool operator == (const Vector b) const {
        return x == b.x && y == b.y && z == b.z;
    }
    
    inline bool operator < (const Vector b) const {
        return x == b.x ? (y == b.y ? z < b.z : y < b.y) : x < b.x;
    }
    
    inline Vector operator ^ (const Vector b) const {
        return Vector(y * b.z - z * b.y, z * b.x - x * b.z, x * b.y - y*b.x);
    }
    
    inline void simplify() {
        int g = gcd(ABS(x), gcd(ABS(y), ABS(z)));
        if (!g) return;
        if ((*this) < Vector(0, 0, 0)) g *= -1;
        x /= g, y /= g, z /=g;
    }
} v[N];

int n, ans;

vector <Vector> now;

signed main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n); ans = n * (n - 1) * (n - 2) / 6;
    for (int i = 1; i <= n; ++ i)
      read(v[i].x), read(v[i].y), read(v[i].z);
    for (int i = 1; i <= n; ++ i) {
        now.clear();
        for (int j = i + 1; j <= n; ++ j) {
            Vector flat = v[i] ^ v[j];
            flat.simplify();
            now.push_back(flat);
        }
        sort(now.begin(), now.end());
        for (int j = 0, lst = 0; j < now.size(); lst = j) {
            while (j < now.size() && now[j] == now[lst]) ++ j;
            int len = j - lst; ans -= len * (len - 1) / 2;
            if (now[lst] == Vector(0, 0, 0)) ans -= len * (n - i - len);
        }
    }
    printf("%d", ans); return 0;
}
