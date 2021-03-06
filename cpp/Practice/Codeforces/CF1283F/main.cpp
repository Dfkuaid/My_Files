#define LOCAL
#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 200010;
const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int n, arr[N], cnt[N];

priority_queue <int> q;

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(n);
    for (int i = 1; i < n; ++ i) read(arr[i]);
    for (int i = 1; i < n; ++ i) ++ cnt[arr[i]];
    for (int i = 1; i <= n; ++ i)
      if (!cnt[i]) q.push(-i);
    printf("%d\n", arr[1]);
    for (int i = n - 1; i; -- i) {
        int x = -q.top(); q.pop();
        printf("%d %d\n", arr[i], x);
        if (!(-- cnt[arr[i]])) q.push(-arr[i]);
    }
    return (0 - 0);
}
