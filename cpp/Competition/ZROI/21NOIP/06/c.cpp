#define LOCAL
#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 1000010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

struct Edge {int u, v, nxt;} e[N];

int T, n, ecnt(1), head[N];

inline void reset() {ecnt = 1; mset(head, 0);}
inline int id(int x, int y) {return (y - 1) * 4 + x;}

inline void addedge(int u, int v) {
    e[ecnt].u = u, e[ecnt].v = v;
    e[ecnt].nxt = head[u], head[u] = ecnt ++;

    e[ecnt].u = v, e[ecnt].v = u;
    e[ecnt].nxt = head[v], head[v] = ecnt ++;
}

void add_middle(int i) {
    addedge(id(2, i - 1), id(1, i + 1)); addedge(id(1, i + 1), id(3, i));
    addedge(id(3, i), id(4, i + 2)); addedge(id(4, i + 2), id(2, i + 1));
    addedge(id(2, i + 1), id(4, i)); addedge(id(4, i), id(3, i + 2));
    addedge(id(3, i - 1), id(4, i + 1)); addedge(id(4, i + 1), id(2, i));
    addedge(id(2, i), id(1, i + 2)); addedge(id(1, i + 2), id(3, i + 1));
    addedge(id(3, i + 1), id(1, i)); addedge(id(1, i), id(2, i + 2));
}

void add_tail(int i) {
    addedge(id(2, i - 1), id(1, i + 1)); addedge(id(1, i + 1), id(3, i + 2));
    addedge(id(3, i + 2), id(4, i)); addedge(id(4, i), id(2, i + 1));
    addedge(id(2, i + 1), id(4, i + 2)); addedge(id(4, i + 2), id(3, i));
    addedge(id(3, i), id(2, i + 2)); addedge(id(2, i + 2), id(1, i));
    addedge(id(1, i), id(3, i + 1)); addedge(id(3, i + 1), id(1, i + 2));
    addedge(id(1, i + 2), id(2, i)); addedge(id(2, i), id(4, i + 1));
    addedge(id(4, i + 1), id(3, i - 1));
}

void dfs(int x, int fa) {
    printf("%d %d\n", (x - 1) % 4 + 1, (x - 1) / 4 + 1);
    for (int i = head[x]; i; i = e[i].nxt)
      if (e[i].v != fa) dfs(e[i].v, x);
}

int main() {
#ifdef LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    read(T);
    while (T --) {
        read(n); reset();
        if (n <= 2 || n == 4) {puts("No"); continue;} puts("Yes");
        if (n == 3) {printf("1 2\n3 1\n4 3\n2 2\n4 1\n3 3\n2 1\n1 3\n3 2\n1 1\n2 3\n4 2\n"); continue;}
        if (n == 5) {
            printf("4 1\n3 3\n4 5\n2 4\n1 2\n3 1\n4 3\n3 5\n1 4\n2 2\n3 4\n");
            printf("1 5\n2 3\n1 1\n3 2\n4 4\n2 5\n1 3\n2 1\n4 2\n"); continue;
        }
        if (n % 3 == 0) {
            addedge(id(1, 1), id(3, 2)); addedge(id(3, 2), id(1, 3));
            addedge(id(1, 3), id(2, 1)); addedge(id(2, 1), id(4, 2));
            addedge(id(4, 2), id(2, 3)); addedge(id(4, 1), id(2, 2));
            addedge(id(2, 2), id(4, 3)); addedge(id(4, 3), id(3, 1));
            addedge(id(3, 1), id(1, 2)); addedge(id(1, 2), id(3, 3));
            for (int i = 6; i < n; i += 3) add_middle(i - 2); add_tail(n - 2);
        } else if (n % 3 == 1) {
            addedge(id(1, 1), id(3, 2)); addedge(id(3, 2), id(4, 4));
            addedge(id(4, 4), id(2, 3)); addedge(id(2, 3), id(4, 2));
            addedge(id(4, 2), id(2, 1)); addedge(id(2, 1), id(1, 3));
            addedge(id(1, 3), id(3, 4)); addedge(id(4, 1), id(2, 2));
            addedge(id(2, 2), id(1, 4)); addedge(id(1, 4), id(3, 3));
            addedge(id(3, 3), id(1, 2)); addedge(id(1, 2), id(3, 1));
            addedge(id(3, 1), id(4, 3)); addedge(id(4, 3), id(2, 4));
            for (int i = 7; i < n; i += 3) add_middle(i - 2); add_tail(n - 2);
        } else {
            addedge(id(1, 1), id(2, 3)); addedge(id(2, 3), id(1, 5));
            addedge(id(1, 5), id(3, 4)); addedge(id(3, 4), id(4, 2));
            addedge(id(4, 2), id(2, 1)); addedge(id(2, 1), id(1, 3));
            addedge(id(1, 3), id(3, 2)); addedge(id(3, 2), id(4, 4));
            addedge(id(4, 4), id(2, 5)); addedge(id(4, 1), id(3, 3));
            addedge(id(3, 3), id(4, 5)); addedge(id(4, 5), id(2, 4));
            addedge(id(2, 4), id(1, 2)); addedge(id(1, 2), id(3, 1));
            addedge(id(3, 1), id(4, 3)); addedge(id(4, 3), id(2, 2));
            addedge(id(2, 2), id(1, 4)); addedge(id(1, 4), id(3, 5));
            for (int i = 8; i < n; i += 3) add_middle(i - 2); add_tail(n - 2);
        }
        dfs(id(1, 1), -1);
    }
    return 0;
}
