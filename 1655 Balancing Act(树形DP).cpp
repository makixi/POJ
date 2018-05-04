#include<iostream>
#include<algorithm>
#include<cstdio> 
#include<string>
#include<cstring>
using namespace std;
const int maxn=20005;
const int inf=0x3f3f3f3f;
int head[maxn],tot=0;
int dp[maxn];//儿子中节点数最多的分支节点数。
int sum[maxn];//i为根的子树节点总数 
struct node{
	int to,nex;
}e[maxn<<1]; 
int res1,res2;
void add(int a,int b){
	e[tot].to=b;e[tot].nex=head[a];
	head[a]=tot++;
}
void dfs(int u,int pre){
	sum[u]=1;
	dp[u]=0;
	for(int i=head[u];i+1;i=e[i].nex){
		int v=e[i].to;
		if(v==pre)continue;
		dfs(v,u);
		sum[u]+=sum[v];
		dp[u]=max(dp[u],sum[v]);
	}
}
void dfs2(int u,int pre,int from){
	int tmp=max(dp[u],from);
	if(tmp<res2){
		res2=tmp;
		res1=u;
	}else if(tmp==res2&&u<res1)
		res1=u;
	for(int i=head[u];i+1;i=e[i].nex){
		int v=e[i].to;
		if(v==pre)continue;
		dfs2(v,u,from+sum[u]-sum[v]);
	}
}
int main(){
	int t,n;
	scanf("%d",&t);
	while(t--){
		memset(head,-1,sizeof(head));
		memset(dp,0,sizeof(dp));
		tot=0;
		scanf("%d",&n);
		for(int i=0;i<n-1;++i){
			int a,b;
			scanf("%d%d",&a,&b);
			add(a,b);
			add(b,a);
		}
		dfs(1,0);
		res2=inf;
		res1=inf;
		dfs2(1,0,0);
		cout<<res1<<" "<<res2<<"\n";
	}
	return 0;
}
