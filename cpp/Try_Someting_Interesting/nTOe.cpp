#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

string s;

int main(){
    cin >> s;
    for (int i= 0;i < s.length();i ++){
        if (s[i] == '0') printf("ZERO");
        if (s[i] == '1') printf("ONE");
        if (s[i] == '2') printf("TWO");
        if (s[i] == '3') printf("THREE");
        if (s[i] == '4') printf("FOUR");
        if (s[i] == '5') printf("FIVE");
        if (s[i] == '6') printf("SIX");
        if (s[i] == '7') printf("SEVEN");
        if (s[i] == '8') printf("EIGHT");
        if (s[i] == '9') printf("NINE");
    }
    puts("");system("pause");
    return 0;
}