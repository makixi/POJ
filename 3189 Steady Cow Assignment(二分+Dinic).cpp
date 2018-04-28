#include <iostream>
#include <queue>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define inf 0x3f3f3f3f
#define maxm 500000
#define maxn 1030
typedef struct{
	int s,t,r,nex;
}Edge;
Edge edge[maxm];
int n,m,st,des,tot,maxflow;
int head[maxn],Layer[maxn];
int c[maxn],maze[maxn][25];
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
int main(){
	int a,b;
	while(~scanf("%d%d",&n,&b)){
		st=0;des=n+b+1;
		for(int i=1;i<=n;++i)
			for(int j=1;j<=b;++j)
				scanf("%d",&maze[i][j]);
		for(int i=1;i<=b;++i)scanf("%d",&c[i]);
		int l=1,r=b,ans=-1;
		while(l<=r){
			int mid=(l+r)>>1;
			bool flag=false;	
			for(int i=1;i<=b-mid+1;++i){
				memset(head,-1,sizeof(head));
				tot=0;
				for(int j=1;j<=b;++j)
					add(st,j,c[j]);
				for(int j=1;j<=n;++j){
					for(int k=i;k<=i+mid-1;++k)
						add(maze[j][k],j+b,1);
					add(j+b,des,1);
				}
				if(dinic()==n){
					ans=mid;
					r=mid-1;
					flag=true;
					break;
				}
			}
			if(!flag)l=mid+1;
		}
		cout<<ans<<"\n";
	}
	return 0;
}
