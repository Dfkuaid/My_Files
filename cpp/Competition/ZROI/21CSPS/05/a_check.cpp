#include <bits/stdc++.h>
using namespace std;

int main() {
    int n; scanf("%d", &n);
    for (int i = 1; i <= n; ++ i) {
        printf("case #%d: \n", i);
        system("./a_tasks");
        system("./a");
        system("./a_hyl");
        if (system("diff out1.txt out2.txt")) {
            printf("Wrong Answer!\n");
            return 0;
        } else printf("Accepted!\n");
    }
    return 0;
}
