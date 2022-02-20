#include<bits/stdc++.h>
#define dd double
#define ld long double
#define ll long long
#define uint unsigned int
#define ull unsigned long long
#define N 500010
#define M number
using namespace std;

const int INF = 0x3f3f3f3f;

template <typename T> inline void read(T &x) {
    x = 0; int f = 1; char c = getchar();
    for (; !isdigit(c); c = getchar()) if (c == '-') f = -f;
    for (; isdigit(c); c = getchar()) x = x * 10 + c - '0';
    x *= f;
}

template <typename T> inline T Max(T a, T b) {return a < b ? b : a;}

struct Square {vector<int> Color, Number; int Sum;} sq[N];

int ID[5][5][5][5], f[N][40], idtot, t, Trans[40][4][4], c[4], n, cnt[4];
char s[10];

inline void PreWork() {
    for (int i = 0; i <= 4; ++ i)
      for (int j = 0; j <= 4 && i + j <= 4; ++ j)
        for (int k = 0; k <= 4 && i + j + k <= 4; ++ k) {
            int l = 4 - i - j - k;
            ID[i][j][k][l] = ++ idtot;
        }
    for (int i = 0; i <= 4; ++ i)
      for (int j = 0; j <= 4 && i + j <= 4; ++ j)
        for (int k = 0; k <= 4 && i + j + k <= 4; ++ k) {
            int l = 4 - i - j - k;
            c[0] = i; c[1] = j; c[2] = k; c[3] = l;
            for (int q = 0; q <= 3; ++ q)
              for(int w = 0; w <= 3; ++ w) {
                  if (!c[q]) continue;
                  -- c[q]; ++ c[w];
                  Trans[ID[i][j][k][l]][q][w] = ID[c[0]][c[1]][c[2]][c[3]];
                  ++ c[q]; -- c[w];
              }
        }
}

inline int MappedColor(char c){
    if(c=='B') return 0; else if(c=='G') return 1;
    else if(c=='R') return 2; else return 3;
}

inline int MappedID(int i, int j, int k, int l) {
    if (i < 0 || j < 0 || k < 0 || l < 0) return 0;
    return ID[i][j][k][l];
}

inline void Init() {
    read(n);
    for (int i = 1; i <= n; ++ i) {
        scanf("%s", s + 1);
        for (int j = 1; j <= 8; j += 2)
          sq[i].Color.push_back(MappedColor(s[j]));
        for (int j = 2; j <= 8; j += 2) {
            sq[i].Number.push_back(s[j] - '0');
            sq[i].Sum += s[j] - '0';
        }
    }
}

inline int Calc(int id, int posi) {
    if (posi > 3) return -1;
    if (sq[id].Color[posi] == 0) return sq[id].Sum - sq[id].Number[posi];
    else if (sq[id].Color[posi] == 1) return sq[id].Sum + sq[id].Number[posi];
    else if (sq[id].Color[posi] == 2) return sq[id].Sum * sq[id].Number[posi];
    if (sq[id].Number[posi] == 0) return 0;
    return sq[id].Sum / sq[id].Number[posi];
}

inline void kMax(int &a, int b) {a = Max(a, b);}

inline void Solve() {
    int ans = -INF;
    memset(f, -INF, sizeof(f));
    memset(cnt, 0, sizeof(cnt));
    for (int j = 0; j <= 3; ++ j) ++ cnt[sq[1].Color[j]];
    f[1][MappedID(cnt[0],cnt[1],cnt[2],cnt[3])] = 0;
    for(int i=1;i<=n-1;i++){
        for(int k=1;k<=idtot;k++){
            if(f[i][k]<-1e9) continue;
            f[i+1][k]=Max(f[i+1][k],f[i][k]-sq[i+1].Sum);
            for(int o=0;o<=3;o++){
                if(!Trans[k][sq[i+1].Color[o]][sq[i+1].Color[(o+2)%4]]) continue;
                kMax(f[i+1][Trans[k][sq[i+1].Color[o]][sq[i+1].Color[(o+2)%4]]],Calc(i+1,o)+f[i][k]);
            }
        }
    }
    for(int k=1;k<=idtot;k++){
        ans=Max(ans,f[n][k]);
    }
    printf("%d\n",ans);
}

inline void Clear(){
    for(int i=1;i<=n;i++){
        sq[i].Color.clear();sq[i].Number.clear();sq[i].Sum=0;
    }
}

int main(){
    freopen("in.txt","r",stdin);
    freopen("hyl.txt","w",stdout);
    PreWork();
    // assert(idtot==35);
    read(t);
    for(int i=1;i<=t;i++){
        Init();Solve();Clear();
    }
}
