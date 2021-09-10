#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

ll q, p, x, tag;

priority_queue <ll> pq;

int main() {
    scanf("%lld", &q);
    while (q --) {
        scanf("%lld", &p);
        if (p == 1) {
            scanf("%lld", &x); pq.push(-x + tag);
        } else if (p == 2) {
            scanf("%lld", &x); tag += x;
        } else {
            x = pq.top(); pq.pop(); x = -x;
            printf("%lld\n", x + tag);
        }
    }
    return 0;
}