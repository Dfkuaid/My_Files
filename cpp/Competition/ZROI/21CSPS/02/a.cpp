#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int is_not_ip(0), cnt;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1;
    char c = getchar();
    for (; !isdigit(c); c = getchar()) {
        if (c == '.') ++ cnt;
        if (c != '.' || cnt > 3) is_not_ip |= 1;
    }
    for (; ; c = getchar())  {
        if (!isdigit(c)) {
            if (c != '.') is_not_ip |= 1;
            else if (++ cnt > 3) is_not_ip |= 1;
            break;
        }
        if (c == '0' && x == 0) is_not_ip |= 1;
        x = x * 10 + c - '0';
        if (x > 255) x = 255, is_not_ip |= 1;
    }
    x *= f;
}

int a[4];

int main() {
    for (int i = 0; i < 4; ++ i) read(a[i]);
    if (is_not_ip) printf("NO\n");
    else printf("YES\n");
    for (int i = 0; i < 4; ++ i) {
        printf("%d", a[i]);
        if (i < 3) printf(".");
    }
    return 0;
}