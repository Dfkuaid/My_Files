#include <bits/stdc++.h>
#define N 100010
using namespace std;

const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c=getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

int t, n, a[N]; bool op = 0;

int main(){
    read(t);
    while (t --) {
        read(n); op = 0;
        for (int i = 1; i <= n; ++ i) {
            read(a[i]); if (a[i] >= 3) op = 1;
        }
        if (n <= 2) {puts("Yes"); continue;}
     