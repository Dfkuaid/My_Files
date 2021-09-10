#define DEBUG
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1010;
const int INF = 0x3fffffff;

string s, t;
int n, cnt, tcnt, q[N];

map <string, int> mp;
bitset <1010> f[N], b[N], tmp;

inline bool check() {
    tmp.reset();
    for (int i = 1; i <= tcnt; ++ i)
      tmp[q[i]] = 1;
    for (int i = 1; i <= tcnt; ++ i)
      if ((tmp & b[q[i]]).any()) return false;
    return true;
}

int main() {
    #ifdef DEBUG
        freopen("in.txt", "r", stdin);
        freopen("out.txt", "w", stdout);
    #endif
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> n; int is_wrong = 0;
    for (int i = 1; i <= n; ++ i) {
        is_wrong = tcnt = 0;
        cin >> s; cin >> t; cin >> t;
        while (t != ";") {
            if (!mp[t]) is_wrong |= 1;
            q[++ tcnt] = mp[t]; cin >> t;
        }
        if (!check()) is_wrong |= 1;
        if (is_wrong || mp[s]) {
            cout << "greska\n"; continue;
        }
        cout << "ok\n"; mp[s] = ++ cnt;
        f[cnt][cnt] = 1;
        for (int j = 1; j <= tcnt; ++ j)
          f[cnt] |= f[q[j]];
        for (int j = 1; j < cnt; ++ j)
          if (!f[cnt][j] && (f[j] & f[cnt]).any()) {
              b[cnt][j] = 1;
          }
    }
    return 0;
}