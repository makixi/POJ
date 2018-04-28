#include<iostream>
#include<cstring>
#include<cmath>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=5010;
const int maxm=1e6+10;
struct node{
	int to;
	int nextNode;
	int cap;
	int flow;
	int cost;
}e[maxm];
int head[maxn],tot;
int pre[maxn],dis[maxn];
bool vis[maxn];
void add(int u,int v,int cap,int cost){
	e[tot].to = v;e[tot].cap = cap;e[tot].cost = cost;
	e[tot].flow = 0;e[tot].nextNode = head[u];head[u] = tot++;
	e[tot].to = u;e[tot].cap = 0;e[tot].cost = -cost;
	e[tot].flow = 0;e[tot].nextNode = head[v];head[v] = tot++;
}
bool spfa(int s,int t){
	queue<int> q;
	memset(dis,inf,sizeof(dis));
	memset(pre,-1,sizeof(pre));
	dis[s]=0;vis[s]=true;
	q.push(s);
	while(!q.empty()){
		int u=q.front();q.pop();
		vis[u]=false;
		for(int i=head[u];i!=-1;i=e[i].nextNode){
			int v=e[i].to;
			if(e[i].cap>e[i].flow&&dis[v]>dis[u]+e[i].cost){
				dis[v]=dis[u]+e[i].cost;
				pre[v]=i;
				if(!vis[v]){
					vis[v]=true;
					q.push(v);
				}
			}
		}
	}
	return pre[t]!=-1;
}
int mcmf(int s,int t,int &cost){
	int flow=0;
	cost=0;
	while(spfa(s,t)){
		int minn=inf;
		for (int i = pre[t]; i != -1; i = pre[e[i ^ 1].to])
			if(e[i].cap-e[i].flow<minn)
				minn=e[i].cap-e[i].flow;
		for (int i = pre[t]; i != -1; i = pre[e[i ^ 1].to]){
			e[i].flow += minn;
			e[i ^ 1].flow -= minn;
			cost += e[i].cost * minn;
		}
		flow += minn;
	}
	return flow;
}
int main(){
	int n,k,st,des;
	while(scanf("%d%d",&n,&k)!=EOF){
		memset(head,-1,sizeof(head));
		tot=0;
		int s = 0, en = 2 * n*n + 1;
		add(s, 1, k, 0);
		add(2 * n*n, en, k, 0);//cap cost
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++) {
				int a;
				scanf("%d",&a);
				add((i - 1)*n + j, (i - 1)*n + j + n * n, 1, -a);
				add((i - 1)*n + j, (i - 1)*n + j + n * n, inf, 0);
				if (i<n) add((i - 1)*n + j + n * n, i*n + j, inf, 0);
				if (j<n) add((i - 1)*n + j + n * n, (i - 1)*n + j + 1, inf, 0);
			}
		int cost=0;
		mcmf(s,en,cost); 
		cout << -cost << "\n";
	}
	return 0;
}

