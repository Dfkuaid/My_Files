#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int x[4];

int main() {
    for (int i = 0; i < 4; ++ i) {
        // cout << i << endl;
        char c; cin >> c;
        // cout << c << endl;
        x[i] = c - '0';
    }
    // scanf("%d%d%d%d", &x[0], &x[1], &x[2], &x[3]);
    if (x[0] == x[1] && x[1] == x[2] && x[2] == x[3])
      printf("Weak");
    else if (x[1] == (x[0] + 1) % 10 && x[2] == (x[1] + 1) % 10 && x[3] == (x[2] + 1) % 10)
      printf("Weak");
    else printf("Strong");
    return 0;
}