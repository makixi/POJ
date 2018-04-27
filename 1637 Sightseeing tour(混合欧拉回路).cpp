#include <iostream>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
#define MAXE 500000
#define MAXV 205
typedef struct{
	int s,t,r,nex;
}Edge;
Edge edge[MAXE];
int n,m,st,des,tot,maxflow;
int head[MAXV],Layer[MAXV];
int in[MAXV];
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
	int tmp=0;
	int i,a,t;
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
	int t,m,s;
	scanf("%d",&t);
	while(t--){
		memset(head,-1,sizeof(head));
		tot=0;
		memset(in,0,sizeof(in));
		scanf("%d%d",&m,&s);
		for(int i=0;i<s;++i){
			int a,b,c;
			scanf("%d%d%d",&a,&b,&c);
			in[a]++;
			in[b]--;
			if(c==0) add(a,b,1);  
		}
		int flag=0,sum=0,d;
		st=m+1;des=m+2;n=m+2;
        for(int i=1; i<=m; i++){
            if(in[i]&1) flag=1;
            else if(in[i]<0) add(i,des,(-in[i])>>1);
            else if(in[i]>0){
                add(st,i,in[i]>>1);
                sum+=in[i]>>1;
            }
        }
        if(flag){
        	cout<<"impossible\n";
        	continue;
		}
        if(sum!=dinic()) printf("impossible\n");
        else printf("possible\n");
	}
	return 0;
}
