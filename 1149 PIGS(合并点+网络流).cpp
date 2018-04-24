/*
	画图找规律系列~
	几个定则可以用：
	1. 如果几个节点的流量的来源完全相同，则可以把它们合并成一个。
	2. 如果几个节点的流量的去向完全相同，则可以把它们合并成一个。
	3. 如果从点 u 到点 v 有一条容量为 +∞的边，并且 u 是 v 的唯一流量来源，或者 v 是 u
	的唯一流量去向，则可以把 u 和 v 合并成一个节点。
*/ 
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
const int maxn=105;
const int maxm = 1010;
int e[maxn][maxn];
bool vis[maxn];
int Layer[maxn];
int n,m,des,st;
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
	int pig[maxm], m, belong[maxm], num;
	while(scanf("%d%d",&m,&n)!=EOF) {
		memset(e, 0, sizeof(e));
		memset(belong, 0, sizeof(belong));
		st = n + 1, des = n + 2;
		for (int i = 1; i <= m; ++i) scanf("%d", &pig[i]);
		for (int i = 1; i <= n; ++i) {
			int l; 
			scanf("%d", &l);
			for (int j = 1; j <= l; ++j) {
				scanf("%d", &num);
				if (!belong[num])e[st][i] += pig[num];//num猪圈的第一名顾客 
				else e[belong[num]][i] = inf;//向num猪圈的上一名顾客连 
				belong[num] = i;
			}
			scanf("%d", &num);
			e[i][des] = num;
		}
		n = des;
		cout<<Dinic()<<"\n";
	}
	return 0;
}
