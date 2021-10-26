#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

#define mset(l, x) memset(l, x, sizeof(l))

class BigNum {
    private:
        int len; int val[120];
    public:
        BigNum();
        BigNum(int);
        BigNum(const char*);
        BigNum(long long);
        
        BigNum operator + (const BigNum &) const;
        BigNum operator - (const BigNum &) const;
        BigNum operator * (const BigNum &) const;
        BigNum operator / (const int &) const;
        int operator % (const int &) const;
        BigNum &operator = (const BigNum &);
        
        bool operator > (const BigNum &) const;
        bool operator < (const BigNum &) const;
        bool operator >= (const BigNum &) const;
        bool operator <= (const BigNum &) const;
        bool operator == (const BigNum &) const;

        void Print(char);
};

BigNum::BigNum() {len = 0; mset(val, 0);}

BigNum::BigNum(const char x[]) {
    len = strlen(x); mset(val, 0);
    for (int i = len; i >= 1; -- i)
      val[i] = (int)(x[len - i] - '0');
}

BigNum::BigNum(int x) {
    len = 0; mset(val, 0); if (!x) len = 1;
    while (x) val[++ len] = x % 10, x /= 10;
}

BigNum::BigNum(long long x) {
    len = 0; mset(val, 0); if (!x) len = 1;
    while (x) val[++ len] = x % 10, x /= 10;
}

void BigNum::Print(char c) {
    for (int i = len; i >= 1; -- i)
      putchar(val[i] + '0');
    putchar(c);
}

BigNum & BigNum::operator = (const BigNum &T) {
    len = T.len;
    for (int i = 1; i <= len; i ++)
      val[i] = T.val[i];
    return *this;
}

bool BigNum::operator > (const BigNum &T) const {
    if (len > T.len) return true;
    else if (len < T.len) return false;
    for (int i = len; i >= 1; i --)
      if (val[i] > T.val[i]) return true;
      else if (val[i] < T.val[i]) return false;
    return false;
}

bool BigNum::operator < (const BigNum &T) const {
    if (len < T.len) return true;
    else if (len > T.len) return false;
    for (int i = len; i >= 1; i --)
      if (val[i] < T.val[i]) return true;
      else if (val[i] > T.val[i]) return false;
    return false;
}

bool BigNum::operator >= (const BigNum &T) const {
    if (len > T.len) return true;
    else if (len < T.len) return false;
    for (int i = len; i >= 1; i --)
      if (val[i] > T.val[i]) return true;
      else if (val[i] < T.val[i]) return false;
    return true;
}

bool BigNum::operator <= (const BigNum &T) const {
    if (len < T.len) return true;
    else if (len > T.len) return false;
    for (int i = len; i >= 1; i --)
      if (val[i] < T.val[i]) return true;
      else if (val[i] > T.val[i]) return false;
    return true;
}

bool BigNum::operator == (const BigNum &T) const {
    if (len != T.len) return false;
    for (int i = 1; i <= len; ++ i)
      if (val[i] != T.val[i]) return false;
    return true;
}

BigNum BigNum::operator + (const BigNum &T) const {
    BigNum t(*this); int l = max(len, T.len);
    for (int i = 1; i <= l; i ++){
        t.val[i] += T.val[i];
        t.val[i + 1] += t.val[i] / 10;
        t.val[i] %= 10;
    }
    if (t.val[l + 1]) t.len = l + 1;
    else  t.len = l;
    return t;
}

BigNum BigNum::operator - (const BigNum &T) const {
    BigNum t(*this);
    for (int i = 1; i <= len; ++ i) {
        if (t.val[i] < T.val[i]) -- t.val[i + 1], t.val[i] += 10;
        t.val[i] -= T.val[i];
    }
    while (t.len && !t.val[t.len]) -- t.len;
    if (!t.len) ++ t.len; return t;
}

BigNum BigNum::operator * (const BigNum &T) const {
    BigNum t; int l = len + T.len - 1;
    for (int i = 1;i <= len;i ++)
      for (int j = 1;j <= T.len;j ++){
          t.val[i + j - 1] += val[i] * T.val[j];
          t.val[i + j] += t.val[i + j - 1] / 10;
          t.val[i + j - 1] %= 10;
      }
    while (t.val[l + 1]) l ++;
    t.len = l; return t;
}

BigNum BigNum::operator / (const int &T) const {
    BigNum t; int tmp = 0; t.len = len;
    for (int i = len; i >= 1; -- i) {
        tmp = tmp * 10 + val[i];
        t.val[i] = tmp / T; tmp %= T;
    }
    while (t.len && !t.val[t.len]) -- t.len;
    if (!t.len) ++ t.len; return t;
}

int BigNum::operator % (const int &T) const {
    BigNum t; int tmp = 0; t.len = len;
    for (int i = len; i >= 1; -- i) {
        tmp = tmp * 10 + val[i];
        t.val[i] = tmp / T; tmp %= T;
    }
    while (t.len && !t.val[t.len]) -- t.len;
    if (!t.len) ++ t.len; return tmp;
}


int cnt, cnt1, cnt2, cnt3; char s[N];
BigNum n, a[N], m1[N], m2[N], m3[N];

#define lb(l, len, x) lower_bound(l + 1, l + len + 1, x)
#define ub(l, len, x) upper_bound(l + 1, l + len + 1, x)

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%s", s); n = BigNum(s);
    m1[++ cnt1] = BigNum(4), m2[++ cnt2] = BigNum(2), m3[++ cnt3] = BigNum(3);
    while (m1[cnt1] <= n) m1[cnt1 + 1] = m1[cnt1] * BigNum(4), ++ cnt1;
    while (m2[cnt2] <= n) m2[cnt2 + 1] = m2[cnt2] * BigNum(4), ++ cnt2;
    while (m3[cnt3] <= n) m3[cnt3 + 1] = m3[cnt3] * BigNum(3), ++ cnt3;
    if (n % 2 == 1) {
        int pos = ub(m3, cnt3, n) - m3 - 1;
        a[++ cnt] = m3[pos], n = n - m3[pos];
    }
    BigNum total(1);
    while (!(n == BigNum(0))) {
        if (n % 3 == 0) {
            while (!(n % 3)) total = total * BigNum(3), n = n / 3;
        } else if (n % 3 == 1) {
            int pos = ub(m1, cnt1, n) - m1 - 1;
            a[++ cnt] = total * m1[pos];
            n = n - m1[pos];
        } else {
            int pos = ub(m2, cnt2, n) - m2 - 1;
            a[++ cnt] = total * m2[pos];
            n = n - m2[pos];
        }
    }
    printf("%d\n", cnt);
    for (int i = 1; i <= cnt; ++ i) a[i].Print(' ');
    return 0;
}
