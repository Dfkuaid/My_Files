#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int t, n;

int main() {
    scanf("%d", &t);
    while (t --) {
        scanf("%d", &n);
        int maxx = 0;
        while (n) {
            maxx = max(maxx, n % 10);
            n /= 10;
        }
        cout << maxx << endl;
    }
    return 0;
}