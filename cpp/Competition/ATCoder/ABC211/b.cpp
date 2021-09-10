#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

string s, t[4] = {"H", "2B", "3B", "HR"};

int res[4];

int main() {
    for (int i = 1; i  <= 4; ++ i) {
        cin >> s;
        for (int j = 0; j < 4; ++ j)
          if (t[j] == s) res[j] |= 1;
    }
    if (res[0] && res[1] && res[2] && res[3])
      cout << "Yes";
    else cout << "No";
    return 0;
}