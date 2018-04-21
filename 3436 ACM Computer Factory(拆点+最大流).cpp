#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=150;
int e[maxn][maxn],g[maxn][11];
int etmp[maxn][maxn];
bool vis[maxn];
int Layer[maxn];
int n,m,des,st;
struct node{
	int from,to,c;
	node(){}
	node(int ff,int tt,int cc):from(ff),to(tt),c(cc){}
};
bool CountLayer(){
	queue<int> q;
	memset(Layer,0xff,sizeof(Layer));
	Layer[st]=0;
	q.push(st);
	while(!q.empty()){
		int u=q.front();q.pop();
		for(int i=1;i<=n;++i)
			if(e[u][i]>0&&Layer[i]==-1){
				Layer[i]=Layer[u]+1;
				if(i==des)return true;
				else q.push(i);
			}
	}
	return false;
}
int Dinic(){
	int maxFlow=0,i;
	deque<int>q;
	while(CountLayer()){
		q.push_back(st);
		memset(vis,false,sizeof(vis));
		vis[st]=true;
		while(!q.empty()){
			int nd=q.back();
			if(nd==des){
				int minn=inf,minst;
				for(int i=1;i<q.size();++i){
					int vs=q[i-1];
					int ve=q[i];
					if(e[vs][ve]>0&&minn>e[vs][ve]){
						minn=e[vs][ve];
						minst=vs;
					}
				}
				maxFlow+=minn;
				for(int i=1;i<q.size();++i){
					e[q[i-1]][q[i]]-=minn;
					e[q[i]][q[i-1]]+=minn;
				}
				while(!q.empty()&&q.back()!=minst){
					vis[q.back()]=false;
					q.pop_back();
				}
			}else{ 
				for(i=1;i<=n;++i)
					if(e[nd][i]>0&&Layer[i]==Layer[nd]+1&&!vis[i]){
						vis[i]=true;
						q.push_back(i);
						break;
					}
				if(i>n)q.pop_back();
			} 
		}
	}
	return maxFlow;
}
int main(){
	while(scanf("%d%d",&m,&n)!=EOF){
		memset(e,0,sizeof(e));
		st=n*2+1;des=n*2+2;
		for(int i=1;i<=n;++i){
			scanf("%d",&e[i][i+n]);//cap
			for(int j=0;j<m;++j)scanf("%d",&g[i][j]);
			for(int j=0;j<m;++j)scanf("%d",&g[i+n][j]);
		}
		for(int i=1;i<=n;++i){//in
			bool flag=true;
			for(int j=0;j<m;++j){
				if(g[i][j]!=0&&g[i][j]!=2)
					flag=false;
					break;
				}
			if(flag)e[st][i]=inf;
		}
		for(int i=n+1;i<=2*n;++i){//out
			bool flag=true;
			for(int j=0;j<m;++j)
				if(g[i][j]!=1){
					flag=false;
					break;
				}
			if(flag)e[i][des]=inf;
		}
		for(int j=n+1;j<=2*n;++j)
			for(int i=1;i<=n;++i){
				bool flag=true;
				for(int k=0;k<m;++k)
					if(g[j][k]!=g[i][k]&&g[i][k]!=2){
						flag=false;
						break;
					}
				if(flag)e[j][i]=inf;
			}
		for(int i=1;i<=des;++i)
			for(int j=1;j<=des;++j)etmp[i][j]=e[i][j];
		vector<node> v;
		int nn=n;
		n=n*2+2;
		cout<<Dinic()<<" ";
		for(int j=nn+1;j<=2*nn;++j)
			for(int i=1;i<=nn;++i)
				if(j-nn!=i&&etmp[j][i]!=e[j][i]) 
					v.push_back(node(j-nn,i,etmp[j][i]-e[j][i]));
		cout<<v.size()<<"\n";
		for(int i=0;i<v.size();++i)
			cout<<v[i].from<<" "<<v[i].to<<" "<<v[i].c<<"\n";
	}
	return 0;
}
