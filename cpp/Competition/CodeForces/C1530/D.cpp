#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n, vis[N], bvis[N], q1[N], l1, r1, q2[N], l2, r2;

int main() {
    scanf("%d", &t);
    while (t --) {
        mset(vis, 0); mset(bvis, 0);
        scanf("%d", &n);
        int ans = 0; l1 = l2 = 0, r1 = r2 = -1;
        for (int i = 1; i <= n; i ++) {
            int x; scanf("%d", &x);
            if (!vis[x]) ans ++, vis[x] = i, bvis[i] = x;
            cout << ans << " " << x << " " << vis[x] << endl;
            cout << i << " " << x << " " << vis[x] << " " << bvis[i] << endl;
        }
        for (int i = 1; i <= n; i ++) {
            cout << i << " " << bvis[i] << endl;
            if (!bvis[i]) q1[++ r1] = i;
        }
          
        for (int i = 1; i <= n; i ++)
          if (!vis[i]) q2[++ r2] = i;
        cout << "cnt: " << r1 << endl;
        for (int i = l1; i <= r1; i ++)
          printf("%d %d\n", q1[i], q2[i]);
        for (int i = l2; i <= r2; i ++)
          if (!bvis[q2[i]] && !vis[q2[i]]) {
              if (l2 != i) {
                  bvis[q2[i]] = q2[l2];
                  vis[q2[l2]] = q2[i];
                  l2 ++;
              } else {
                  bvis[q2[i]] = q2[l2 + 1];
                  vis[q2[l2 + 1]] = q2[i];
              }
              while (vis[q2[l2]]) l2 ++;
          }
        while (l1 <= r1 || l2 <= r2) {
            while (bvis[q1[l1]]) l1 ++;
            while (vis[q2[l2]]) l2 ++;
            if (q1[l1] != q2[l2]) {
                bvis[q1[l1]] = q2[l2];
                vis[q2[l2]] = q1[l1];
                l2 ++ , l1 ++;
            } else {
                bvis[q1[l1 + 1]] = q2[l2];
                vis[q2[l2]] = q1[l1 + 1];
                l2 ++;
            }
        }
        for (int i = 1; i <= n; i ++)
          printf("%d ", bvis[i]);
        printf("\n");
    }
    return 0;
}