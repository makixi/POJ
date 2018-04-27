#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
#define MAXE 7000010
#define MAXV 5010
typedef struct{
	int s,t,r,nex;
}Edge;
Edge edge[MAXE];
int n,m,st,des,tot,maxflow;
int head[MAXV],Layer[MAXV];
int minspf[MAXV],maxspf[MAXV],spf[MAXV];
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
int Dinic(){
	int maxflow=0;
	while(bfs()) maxflow+=dfs(st,inf);
	return maxflow;
}
int main(){
	int c,l;
	while(scanf("%d%d",&c,&l)!=EOF){
		memset(head,-1,sizeof(head));
		tot=0;
		st=c+l+1;
		des=c+l+2;
		n=des;
		for(int i=l+1;i<=l+c;++i){
			scanf("%d%d",&minspf[i],&maxspf[i]);
			add(i,des,1);
		}
		for(int i=1;i<=l;++i){
			int tmp;
			scanf("%d%d",&spf[i],&tmp);
			add(st,i,tmp);
		}
		for(int i=1;i<=l;++i)
			for(int j=l+1;j<=l+c;++j)
				if(spf[i]>=minspf[j]&&spf[i]<=maxspf[j])
					add(i,j,1);
		cout<<Dinic()<<"\n"; 
	}
	return 0;
}
