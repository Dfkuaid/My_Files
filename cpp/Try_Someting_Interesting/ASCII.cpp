#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#define ll long long
#define mset(l,x) memset(l,x,sizeof(l))
using namespace std;

const int N = 100010;
const int INF = 0x3fffffff;

int opt,t;
string s;
char c;

int main(){
    puts("Please select mode:");
    puts("(1) Encryption.\t(2) Decrypt.");
    cin >> opt;
    do{
        t = 0;
        if (opt == 1){
            printf("Please input clear text:\n");
            cin >> s;
            for (int i = 0;i < s.length();i ++){
                int x = (int)s[i];
                if (x < 100) printf("0");
                if (x < 10) printf("0");
                printf("%d",x);
            }
        }
        else if (opt == 2){
            printf("Please enter the ciphertext(Enter '$' to end):\n");
            cin >> c;int x = 0;
            printf("RESULT:");
            while (c != '$'){
                x = x * 10 + (int)(c - '0');
                if (++ t == 3){
                    cout << (char)x;
                    x = 0;t = 0;
                }cin >> c;
            }
        }
        else printf("Error!There is no such option!");
        puts("");system("pause");system("cls");
        printf("Please select mode:\n");
        printf("(1) Encryption.\t(2) Decrypt.\n");
    }while (cin >> opt);
    return 0;
}