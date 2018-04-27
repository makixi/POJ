#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=1e4+10;
const int maxm=1e5+10;
struct dot{
	int x,y;
	dot(){}
	dot(int xx,int yy):x(xx),y(yy){}
}man[maxn],house[maxn];
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
int step(int i, int j){
    return abs(man[i].x-house[j].x) + abs(man[i].y-house[j].y);
}
int main(){
	int N,M;
	while(scanf("%d%d",&N,&M)!=EOF){
		if(!N||!M)break;
		int mindex=0,hindex=0;
		getchar();
		for(int i=0;i<N;++i){
			char maze[105];
			scanf("%s",maze);
			for(int j=0;j<M;++j)
				if(maze[j]=='H')house[hindex++]=dot(i,j);
				else if(maze[j]=='m')man[mindex++]=dot(i,j);
		}
		//house 0 to hindex-1
		//man 0 to mindex-1
		int st=hindex+mindex,des=hindex+mindex+1;
		n=hindex+mindex+2;
		memset(head,-1,sizeof(head));
		for(int i=0;i<mindex;++i)
			add(st,i,1,0);
		for(int i=0;i<hindex;++i)
			add(i+mindex,des,1,0);
		for (int i = 0; i < mindex; i++)
        	for (int j = 0; j < hindex; j++)
        		add(i,mindex+j,inf,step(i,j));
        int cost=0;
        mcmf(st,des,cost);
        cout<<cost<<"\n";
	}
	return 0;
}
