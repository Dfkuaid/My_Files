#define LOCAL
#include <bits/stdc++.h>
using namespace std;

const int N = 2000010;

int lg[N];

struct Node {int ch[2], val, s;};
struct Trie {
    Node p[N]; int rt, cnt;

    inline Trie() {rt = cnt = 0;}
    void insert(int x) {
        int now = rt;
        for (int i = 20; ~i; -- i) {
            int k = (x >> i) & 1;
            if (!p[now].ch[k])
              p[now].ch[k] = ++ cnt;
            now = p[now].ch[k];
        }
        p[now].val = x;
    }

    int query_xor(int x) {
        int now = rt;
        for (int i = 20; ~i; -- i) {
            int k = !((x >> i) & 1);
            if (!p[now].ch[k])
              now = p[now].ch[!k];
            else now = p[now].ch[k];
        }
        return p[now].val ^ x;
    }
} t;

int q, marked[1 << 20];

void mark(int x) {
    marked[x] = 1;
    for (int i = 19; ~i; -- i)
      if (x >> i & 1 && !marked[x ^ (1 << i)])
        mark(x ^ (1 << i));
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    scanf("%d", &q);
    while (q --) {
        int op, x; scanf("%d%d", &op, &x);
        if (op == 1) t.insert(x), mark(x);
        else if (op == 3) printf("%d\n", t.query_xor(x));
        else {
            printf("%d ", t.query_xor(x)); 
            int res1 = 0, res2 = 0;
            for (int i = 19; ~i; -- i)
              if (x >> i & 1 && marked[res1 | (1 << i)])
                res1 |= (1 << i);
            for (int i = 19; ~i; -- i)
              if (!(x >> i & 1) && marked[res2 | (1 << i)])
                res2 |= (1 << i);
            printf("%d %d\n", res1 & x, res2 | x);
        }
    }
    return 0;
}
