#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

inline ll random(ll x) {return 1ll * rand() * rand() % x;}

int main() {
    srand((unsigned)time(NULL));
    freopen("in.txt", "w", stdout);
    int k = random(10); // printf("%d\n", k);
    while (k --) {
        int lena = random(100) + 1, lenb = random(100) + 1;
        printf("%d\n", random(min(lena, lenb)) + 1);
        for (int i = 1; i <= lena; ++ i)
          if (rand() & 1) putchar(random(26) + 'A');
          else putchar(random(26) + 'a');
        puts("");
        for (int i = 1; i <= lenb; ++ i)
          if (rand() & 1) putchar(random(26) + 'A');
          else putchar(random(26) + 'a');
        puts("");
    }
    puts("0"); return 0;
}
