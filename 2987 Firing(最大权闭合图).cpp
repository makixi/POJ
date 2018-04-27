#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
#define MAXE 500000
#define MAXV 20100
typedef struct{
	int s,t,r,nex;
}Edge;
Edge edge[MAXE];
int n,m,st,des,tot,maxflow;
int head[MAXV],Layer[MAXV];
int visit[MAXV];
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
ll dfs(int cur,int cp){
	if(cur==des) return cp;
	ll tmp=0;
	int i,a,t;
	for(i=head[cur];i!=-1 && tmp<cp;i=edge[i].nex){
		a=edge[i].t;
		if(Layer[a]==Layer[cur]+1 && edge[i].r){
			t=dfs(a,min((ll)edge[i].r,cp-tmp));
			edge[i].r-=t;
			edge[i^1].r+=t;
			tmp+=t;
		}
	}
	if (!tmp) Layer[cur]=-1;	
	return tmp;
}
ll dinic(){
	ll maxflow=0;
	while(bfs()) maxflow+=dfs(st,inf);
	return maxflow;
}
void DFS(int u){
    visit[u]=1;
    for(int i=head[u], v; i>=0; i=edge[i].nex)
        if(edge[i].r>0&&!visit[v=edge[i].t]) 
			DFS(v);
}
int main(){
	int i,a,b,c,w,u,v;
	while(~scanf("%d%d",&n,&m)){
		st=0;des=n+1,tot=0;
		memset(head,-1,sizeof(head));
		ll sum=0;
        for(int i=1; i<=n; i++){
            scanf("%d",&w);
            if(w>0) sum+=w,add(st,i,w);
            if(w<0)  add(i,des,-w);;
        }
        while(m--){
            scanf("%d%d",&u,&v);
            add(u,v,inf);
        }
        ll maxflow=dinic();
        memset(visit,0,sizeof(visit));
        DFS(st);
        int ans=0;
        for(int i=1; i<=n; i++) ans+=visit[i];
        cout<<ans<<" "<<sum-maxflow<<"\n";
	}
	return 0;
}
