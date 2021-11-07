#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int main() {
    int t; read(t);
    for (int i = 1; i <= t; ++ i) {
        system("./task"); printf("Case #%d: ", i);
        system("./POJ3415"); system("./std");
        if (system("diff out.txt std.txt > res.txt")) {
            puts("Wrong Answer!"); return 0;
        } else puts("Accpeted!");
    }
    return 0;
}
