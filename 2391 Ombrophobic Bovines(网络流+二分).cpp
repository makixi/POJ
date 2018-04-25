/*
	long long 教我做人
	告诉你n个城市，每个城市初始有多少牛和下雨时候可以容纳多少牛
	问至少需要多少时间，使所有的牛在下雨的时候都能够被容纳。
	
	建立源点和汇点
	然后拆点
	将st与每个点i相连 容量为初始牛的数量
	将每个点i'与des相连 容量为最终牛的数量
	二分中 
	将可以连的两点i与j'相连 容量为inf
	跑一下最大流~ 
*/
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
typedef long long ll;
const int inf=0x3f3f3f3f;
const ll INF=1e16;
const int maxn=405;
int e[maxn][maxn];
bool vis[maxn];
int init[maxn],ed[maxn];
ll dis[maxn][maxn];
int Layer[maxn];
int n,m,des,st,tot;
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
ll Dinic(){
	ll maxFlow=0;
	int i;
	deque<int>q;
	while(CountLayer()){
		q.push_back(st);
		memset(vis,false,sizeof(vis));
		vis[st]=true;
		while(!q.empty()){
			int nd=q.back();
			if(nd==des){
				ll minn=inf;
				int minst;
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
	while(scanf("%d%d",&n,&m)!=EOF){
		ll sum=0;
		for(int i=1;i<=n;++i){
			scanf("%d%d",&init[i],&ed[i]);
			sum+=init[i];
		}
		memset(dis,inf,sizeof(dis));
		for(int i=0;i<m;++i){
			int a,b;
			ll c;
			scanf("%d%d%lld",&a,&b,&c);
			dis[a][b]=dis[b][a]=min(dis[a][b],c);
		}
		for(int k=1;k<=n;++k)
			for(int i=1;i<=n;++i)
				for(int j=1;j<=n;++j)
					dis[i][j]=min(dis[i][j],dis[i][k]+dis[k][j]);
		st=2*n+1;
		des=2*n+2;
		int nn=n;
		n=2*n+2;
		ll l=0,r=INF,ans=-1;
		while(l<=r){
			ll mid=(l+r)>>1;
			memset(e,0,sizeof(e));
			for(int i=1;i<=nn;++i){
				e[st][i]=init[i];
				e[i+nn][des]=ed[i];
				e[i][i+nn]=inf;
			}
			for(int i=1;i<=nn;++i)
				for(int j=1;j<=nn;++j)
					if(dis[i][j]<=mid)
						e[i][j+nn]=inf;
			ll tmp=Dinic();
			if(tmp>=sum)ans=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<ans<<"\n";
	} 
	return 0;
}

