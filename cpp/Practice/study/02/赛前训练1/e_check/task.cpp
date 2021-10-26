#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

inline int random(int x) {
    return 1ll * rand() * rand() % x;
}

int main() {
    srand((unsigned)time(0));
    freopen("in.txt", "w", stdout);
    int t; t = random(40) + 1;
    printf("%d\n", t);
    while (t --) {
        int n = random(250000) + 1;
        printf("%d\n", n);
        for (int i = 1; i <= n; ++ i) {
            for (int i = 1; i <= 4; ++ i) {
                int col = random(4);
                int val = random(10);
                if (col == 0) cout << "B";
                else if (col == 1) cout << "G";
                else if (col == 2) cout << "R";
                else cout << "Y";
                printf("%d", val);
            }
            printf("\n");
        }
    }
    return 0;
}   
