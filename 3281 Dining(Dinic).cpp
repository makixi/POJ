#include<iostream>
#include<cstring>
#include<cmath>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=505;
int e[maxn][maxn];
bool vis[maxn];
int Layer[maxn];
int n,m,des,st,tot;
struct node{
	int u,to,nex,w;
}edge[40005];
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
	int f,d;
	while(scanf("%d%d%d",&n,&f,&d)!=EOF){
		memset(e,0,sizeof(e));
		st=503;
		des=504;
		for(int i=1;i<=f;++i)
			e[st][i+200]+=1;
		for(int i=1;i<=d;++i)
			e[i+300][des]+=1;
		for(int i=1;i<=n;++i){
			e[i][i+100]+=1;
			int fnum,dnum,tmp;
			scanf("%d%d",&fnum,&dnum);
			for(int j=1;j<=fnum;++j){//found
				scanf("%d",&tmp);
				e[tmp+200][i]+=1;
			}
			for(int j=1;j<=dnum;++j){
				scanf("%d",&tmp);
				e[i+100][tmp+300]+=1;
			}
		}
		n=des;
		cout<<Dinic()<<"\n"; 
	}
	return 0;
}
