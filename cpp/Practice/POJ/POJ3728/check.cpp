#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int main() {
    int t; scanf("%d", &t);
    for (int i = 1; i <= t; ++ i) {
        system("./tasks"); printf("Case #%d: ", i);
        system("./POJ3728");  system("./std");
        if (system("diff out.txt std.txt")) {
            printf("Wrong Answer!\n"); return 0;
        } else printf("Accepted!\n");
    }
    return 0;
}