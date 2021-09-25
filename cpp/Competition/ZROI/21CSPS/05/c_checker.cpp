#include<bits/stdc++.h>
#define ll long long
using namespace std;
const int N=1e5+5,M=2e5+5;
int n,m,tot;
int head[N],ver[M],Nxt[M],du[N],sum1[N],sum2[N],sum3[N];
char op[M];
queue<int> q;
void add(int x,int y){
	ver[++tot]=y;
	Nxt[tot]=head[x];
	head[x]=tot;
}
void topo(){
	for(int i=1;i<=n;i++){
		if(du[i]==0) q.push(i);
	}
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=Nxt[i]){
			int y=ver[i];
			du[y]--;
			if(du[y]==0) q.push(y);
			if(op[i]=='R'){
				sum1[y]=max(sum1[y],sum1[x]+1);
			}
			if(op[i]=='G'){
				sum2[y]=max(sum2[y],sum2[x]+1);
			}
			if(op[i]=='B'){
				sum3[y]=max(sum3[y],sum3[x]+1);
			}
		}
	}
}
int main()
{
	freopen("out.txt", "r", stdin);
    scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		int x,y;
		scanf("%d%d",&x,&y);
		add(x,y);
		du[y]++;
	}
	
	for(int i=1;i<=m;i++){
		cin>>op[i];
	}
	
	topo();
	
	for(int i=1;i<=n;i++){
		if(sum1[i]>42||sum2[i]>42||sum3[i]>42){
			printf("Wrong Answer\n");
			return 0;
		}
	}
	
	printf("Accepted\n");
	
	return 0;
}

