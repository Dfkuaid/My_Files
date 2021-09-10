#include <bits/stdc++.h>
#define ll long long
#define mset(l, x) memset(l, x, sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int l, r, lenl, lenr;
int L[35], R[35], ans;

int main() {
    scanf("%d%d", &l, &r);
    while (l) L[lenl ++] = (l & 1), l >>= 1;
    while (r) R[lenr ++] = (r & 1), r >>= 1;
    if (lenl != lenr) {printf("0"); return 0;}
    for (int i = lenl - 1; ~i; -- i) {
        if (L[i] != R[i]) break;
        ans += (L[i] << i);
    }
    printf("%d", ans);
    return 0;
}

/* leetcode 提交代码
class Solution {
public:
    int rangeBitwiseAnd(int l, int r) {
        int lenl = 0, lenr = 0, L[35], R[35], ans = 0;
        while (l) L[lenl ++] = (l & 1), l >>= 1;
        while (r) R[lenr ++] = (r & 1), r >>= 1;
        if (lenl != lenr) {return 0;}
        for (int i = lenl - 1; ~i; -- i) {
            if (L[i] != R[i]) break;
            ans += (L[i] << i);
        }
        return ans;
    }
};
*/