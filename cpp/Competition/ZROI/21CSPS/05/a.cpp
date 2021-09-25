#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 100010;

char s[N]; int n, cnt, sum;

inline bool cmp(char a, char b) {return a > b;}

int main() {
#ifdef LOCAL
    freopen("task_a.txt", "r", stdin);
    freopen("out1.txt", "w", stdout);
#endif
    scanf("%s", s); n = strlen(s);
    for (int i = 0; i < n; ++ i)
      sum += s[i] - '0', cnt += (s[i] == '0');
    // printf("%d %d\n", sum, cnt);
    if (!cnt || sum % 3) printf("-1");
    else {
        sort(s, s + n, cmp);
        printf("%s", s);
    }
    return 0;
}
