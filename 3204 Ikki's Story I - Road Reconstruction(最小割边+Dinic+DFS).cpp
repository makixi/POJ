#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define inf 0x3f3f3f3f
#define maxm 1002000
#define maxn 20100
typedef struct{
	int s,t,r,nex;
}Edge;
Edge edge[maxm];
int n,m,st,des,tot,maxflow;
int head[maxn],Layer[maxn],mark[maxn];
void add(int x,int y,int c){
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
	while(bfs()) maxflow+=dfs(st,inf);
	return maxflow;
}
void dfs1(int u){
	if(mark[u])return;
	mark[u]=1;
	for(int i=head[u];i+1;i=edge[i].nex){
		int v=edge[i].t;
		if(!mark[v]&&edge[i].r>0)dfs1(v);
	}
}
void dfs2(int u){
	if(mark[u])return;
	mark[u]=2;
	for(int i=head[u];i+1;i=edge[i].nex){
		int v=edge[i].t;
		if(!mark[v]&&edge[i^1].r>0)dfs2(v);
	}
}
int main(){
	int m;
	while(~scanf("%d%d",&n,&m)){
		memset(head,-1,sizeof(head));
		memset(mark,0,sizeof(mark));
		tot=0;
		while(m--){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			add(a,b,c);
		}
		st=0,des=n-1;
		int res=dinic(),ans=0;
		dfs1(st);
		dfs2(des);
		for(int i=0;i<tot;i+=2)  
            if(mark[edge[i^1].t]==1&&mark[edge[i].t]==2&&edge[i].r==0)
				ans++;  
        cout<<ans<<endl;
	}
	return 0;
}
