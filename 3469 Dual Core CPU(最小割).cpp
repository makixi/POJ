#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF INT_MAX
#define MAXE 1000000
#define MAXV 20100
typedef struct{
	int s,t,r,nex;
}Edge;
Edge edge[MAXE];
int n,m,st,des,tot,maxflow;
int head[MAXV],Layer[MAXV];
void addedge(int x,int y,int c){
	edge[tot].s=x;edge[tot].t=y;edge[tot].r=c;
	edge[tot].nex=head[x];head[x]=tot++;
	edge[tot].s=y;edge[tot].t=x;edge[tot].r=0;
	edge[tot].nex=head[y];head[y]=tot++;
}
int bfs(){
	int i,v,tmp;
	queue <int>q;
	memset(Layer,0,sizeof(Layer));
	Layer[st]=1;
	q.push(st);
	while(!q.empty()){
		v=q.front();q.pop();
		for(i=head[v];i!=-1;i=edge[i].nex){
			tmp=edge[i].t;
			if(!Layer[tmp] && edge[i].r){
				Layer[tmp]=Layer[v]+1;
				if(tmp==des) return 1;
				q.push(tmp);
			}
		}
	}
	return 0;
}
int dfs(int cur,int cp){
	if(cur==des) return cp;
	int tmp=0,i,a,t;
	for(i=head[cur];i!=-1 && tmp<cp;i=edge[i].nex){
		a=edge[i].t;
		if(Layer[a]==Layer[cur]+1 && edge[i].r){
			t=dfs(a,min(edge[i].r,cp-tmp));
			edge[i].r-=t;
			edge[i^1].r+=t;
			tmp+=t;
		}
	}
	if (!tmp) Layer[cur]=-1;	
	return tmp;
}
int dinic(){
	int maxflow=0;
	while(bfs()) maxflow+=dfs(st,INF);
	return maxflow;
}
int main(){
	int i,a,b,c;
	while(~scanf("%d%d",&n,&m)){
		st=0;des=n+1,tot=0;
		memset(head,-1,sizeof(head));
		for(i=1;i<=n;i++){
			scanf("%d%d",&a,&b);
			addedge(st,i,a);	
			addedge(i,des,b);
		}
		for(i=0;i<m;i++){
			scanf("%d%d%d",&a,&b,&c);
			addedge(a,b,c);		
			addedge(b,a,c);
		}
		cout<<dinic()<<"\n";
	}
	return 0;
}
