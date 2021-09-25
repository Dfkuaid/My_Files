#include <bits/stdc++.h>
#define ll long long
using namespace std;

inline int random(int x) {
    return (ll)rand() * rand() % x;
}

int main() {
    freopen("task_a.txt", "w", stdout);
    srand((unsigned)time(NULL));
    int n = 1000;
    for (int i = 1; i <= n; ++ i)
      printf("%d", random(10));
    return 0;
}
