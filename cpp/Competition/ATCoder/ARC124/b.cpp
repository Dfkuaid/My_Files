#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

struct Node {
    int ch[2], cnt;
};

struct Trie {
    Node p[N]; int cnt;

    inline void insert(int x) {
        int now = 0;
        for (int i = 30; i >= 0; -- i)
          if (p[now].ch[(x >> i) & 1])
            now = p[now].ch[(x >> i) & 1];
          else now = p[now].ch[(x >> i) & 1] = ++ cnt;
        ++ p[now].cnt;
    }

    inline void Delete(int x) {
        int now = 0;
        for (int i = 30; i >= 0; -- i)
          now = p[now].ch[(x >> i) & 1];
        -- p[now].cnt;
    }

    inline int query(int x) {
        int now = 0;
        for (int i = 30; i >= 0; -- i) {
            int k = (x >> i) & 1;
            if (p[now].ch[k])
              now = p[now].ch[k];
            else return 0;
        }
        return p[now].cnt;
    }
};
Trie t;

int n, a[N], b[N], ans[N], cnt;

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &a[i]);
    for (int i = 1; i <= n; ++ i)
      scanf("%d", &b[i]);
    for (int i = 1; i <= n; ++ i)
      for (int j = 1; i <= n; ++ j) {
          t.insert(a[i] ^ b[j]);
          if (t.query(a[i] ^ b[i]) == n)
      }
        
    
    return 0;
}