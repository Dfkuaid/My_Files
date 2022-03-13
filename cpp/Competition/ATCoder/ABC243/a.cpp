#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int v, a, b, c;

int main() {
    read(v), read(a), read(b), read(c);
    v %= (a + b + c);
    if (v < a) puts("F");
    else if (v < a + b) puts("M");
    else puts("T");
    return (0 - 0);
}
