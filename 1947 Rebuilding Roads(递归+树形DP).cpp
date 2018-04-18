/*
	存个图 只存孩子
	题目给的提示很明显了啊  前者是后者的父亲 如果建无向图不同这么提醒的
	然后就是DP了……
	其实在枚举
	状态转移方程
	dp[u][k]=min(dp[u][k],dp[u][k-s]+dp[child][s]-1)
*/
#include<iostream>
#include<vector>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=155;
const int inf=0x3f3f3f3f;
int n,p;
int sum[maxn],num[maxn];
int dp[maxn][maxn];
vector<int> e[maxn];
void dfs(int u){
	sum[u]=1;
	if(e[u].size()==0)return;
	for(int i=0;i<e[u].size();++i){
		int child=e[u][i];
		dfs(child);
		sum[u]+=sum[child];
		for(int j = sum[u];j>0;j--)
            for(int k = 1; k < j ; k++ )
                dp[u][j] = min(dp[u][j-k]+dp[child][k]-1,dp[u][j]);
	}
}
int main(){
	while(scanf("%d%d",&n,&p)!=EOF){
		memset(sum,0,sizeof(sum));
		memset(num,0,sizeof(num));
		memset(dp,inf,sizeof(dp));
		for(int i=1;i<=n;++i)e[i].clear();
		for(int i=0;i<n-1;++i){
			int x,y;
			scanf("%d%d",&x,&y);
			e[x].push_back(y);
			num[x]++;
		}
		for(int i=1;i<=n;++i)dp[i][1]=num[i];
		dfs(1);
		int ans = dp[1][p];
        for(int i=2;i<=n;i++) ans = min(ans,dp[i][p]+1);//别忘了把连接父节点的边算上 
        cout<<ans<<"\n";
	}
	return 0;
}
