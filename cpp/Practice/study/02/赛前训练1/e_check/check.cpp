#include <bits/stdc++.h>
#define ll long long
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int main() {
    int t; scanf("%d", &t);
    for (int i = 1; i <= t; ++ i) {
        system("./task");
        printf("Case #%d: ", i);
        system("./e"); system("./e_hyl");
        if (system("diff ./out.txt ./hyl.txt")) {
            printf("Wrong Answer!\n"); return 0;
        } else printf("Accpeted!\n");
    }
    return 0;
}
