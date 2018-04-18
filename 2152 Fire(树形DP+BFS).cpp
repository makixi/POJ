/*
	一道TLE了很久的题目……
	主要要注意把queue放全局。
	**放临时的话会比较费时间 
	主要难度在于想dp数组及意义 dp[i][j]表示 i城市由j城市负责消防相关 
	ans[i]表示i城市及子树消防方面花少钱数 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf = 0x3f3f3f3f;
const int maxn = 1010;
int head[maxn], tot, dis[maxn][maxn], d[maxn], w[maxn];
int dp[maxn][maxn];//i城市由j城市负责消防相关 
int ans[maxn];
int n;
queue<int> q;
struct node {
	int to, nex, w;
}e[maxn << 1];
void add(int a, int b, int c) {
	e[tot].to = b;
	e[tot].nex = head[a];
	e[tot].w = c;
	head[a] = tot++;
}
void dfs(int pre,int u) {
	for (int i = head[u]; i + 1; i = e[i].nex) {
		int v = e[i].to;
		if (v == pre)continue;
		dfs(u, v);
	}
	for (int v = 1; v <= n; ++v) {//v负责u
		if (dis[u][v] <= d[u]) {
			int tmp=0;
			for (int i = head[u]; i + 1; i = e[i].nex) {
				int k = e[i].to;
				if (k == pre)continue;
				tmp += min(dp[k][v] - w[v], ans[k]);
			} 
			dp[u][v] = w[v]+tmp;
		}
		else dp[u][v] = inf;
	}
	for (int i = 1; i <= n; ++i)ans[u] = min(ans[u], dp[u][i]);
}
int main() {
	ios::sync_with_stdio(false);
	int t;
	scanf("%d", &t);
	while (t--) {
		tot = 1;
		memset(head, -1, sizeof(head));
		memset(dis, 0, sizeof(dis));
		memset(ans, 63, sizeof(ans));
		memset(dp, 0, sizeof(dp));
		scanf("%d", &n);
		for (int i = 1; i <= n; ++i)scanf("%d", &w[i]);
		for (int i = 1; i <= n; ++i)scanf("%d", &d[i]);
		for (int i = 0; i < n - 1; ++i) {
			int a, b, c;
			scanf("%d%d%d", &a, &b, &c);
			add(a, b, c);
			add(b, a, c);
		}		
		for (int i = 1; i <= n; ++i){
			dis[i][i]=0;
			q.push(i);
			while(!q.empty()){
				int u=q.front();q.pop();
				for (int j = head[u]; j + 1; j = e[j].nex) {
					int v = e[j].to;
					if (!dis[i][v]&&v!=i) {
						dis[i][v] = dis[i][u] + e[j].w;
						q.push(v);
					}
				}
			}
		}
		dfs(0, 1);
		printf("%d\n",ans[1]);
	}
	return 0;
}
