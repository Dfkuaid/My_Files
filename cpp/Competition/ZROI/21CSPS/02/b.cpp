#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 10010;
const int INF = 0x3fffffff;

char s[N];
int n, pcnt, acnt;

int main() {
    scanf("%s", s); n = strlen(s);
    for (int i = 0; i < n; ++ i) {
        if (s[i] == 'A') ++ acnt;
        else acnt ? -- acnt : ++ pcnt;
    }
    printf("%d", acnt + (pcnt & 1));
    return 0;
}