#include<iostream>
#include<cstring>
#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=1e4+10;
const int maxm=1e5+10;
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
int n,m;
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
			minn=min(minn,e[i].cap-e[i].flow);
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
	scanf("%d%d",&n,&m);
	memset(head,-1,sizeof(head));
	tot=0;
	while(m--){
		int u,v,c;
		scanf("%d%d%d",&u,&v,&c);
		add(u,v,1,c);
		add(v,u,1,c);
	}
	int st=0,des=n+1;
	add(st,1,2,0);
	add(n,des,2,0);
	int ans=0;
	mcmf(st,des,ans);
	cout<<ans<<"\n";
	return 0;
}
