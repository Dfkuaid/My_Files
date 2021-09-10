#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 2000010;
const int INF = 0x3fffffff;

string s;
int nxt[N];

inline void getnxt() {
    int p = -1, len = s.length(); nxt[0] = -1;
    for (int q = 0; q < len; ++ q) {
        while (p != -1 && s[q] != s[p]) p = nxt[p];
        p ++, nxt[q + 1] = p;
    }
}

int main() {
    while (cin >> s) {
        if (s == ".") break;
        int len = s.length();
        if (len == 1) {printf("1\n"); continue;}
        s[len ++] = '#'; getnxt();
        int p = len - 1, k = 0, tot = 0;
        while (~p) {
            if (p == k) {tot ++; break;}
            int kl = p - nxt[p];
            if (kl != k && k != 0) {tot = 1; break;}
            k = kl, tot ++, p = nxt[p];
        }
        printf("%d\n", tot);
    }
    return 0;
}