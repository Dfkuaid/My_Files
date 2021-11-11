#include <bits/stdc++.h>
#include <sys/time.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int n, cnt; ll st_s, st_m, ed_s, ed_m;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

void dfs(int rst, int lmt) {
    if (!rst) {++ cnt; return;} if (rst < lmt) return;
    for (int i = lmt; i <= rst; ++ i)
      for (int j = 1; j * i <= rst; ++ j)
        dfs(rst - i * j, i + 1);
}

int main() {
    struct timeval tv; read(n);
    gettimeofday(&tv, NULL); st_s = tv.tv_sec, st_m = tv.tv_usec;
    dfs(n, 1);
    gettimeofday(&tv, NULL); ed_s = tv.tv_sec, ed_m = tv.tv_usec;
    printf("The answer is %d.\nstart time: %lld : %lld, end time: %lld : %lld.\n", cnt, st_s, st_m, ed_s, ed_m);
    printf("used time: %lld ms.\n", (ed_m - st_m) / 1000);
    return 0;
}
