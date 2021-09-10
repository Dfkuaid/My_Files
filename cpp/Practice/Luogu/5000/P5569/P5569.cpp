#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3f3f3f3f;

int n,res;
vector<int> v;

int main(){
    scanf("%d",&n);
    v.push_back(INF);
    for (int i = 1;i <= n;i ++){
        int x;
        scanf("%d",&x);
        v.push_back(x);
    }
    v.push_back(INF + 1);
    for (int i = 1;i <= n - 1;i ++){
        int j = 0,k = 0;
        for (j = 1;j <= n;j ++)
          if (v[j - 1] < v[j + 1]) break;
        int now = v[j - 1] + v[j];
        for (k = j - 1;k >= 0;k --)
          if (v[k] > now) break;
        v.erase(v.begin() + j - 1);
        v.erase(v.begin() + j - 1);
        v.insert(v.begin() + k + 1,now);
        res += now;
    }
    printf("%d",res);
    return 0;
}
