/*
	����������� ��ţ��������һ���·����С  ����Ҫ��ȫƥ��
	��Ȼ��·����С ���ܸ�floyd���·
	Ȼ��ʼ��㡭��
	Դ�㵽ÿ����ţ��һ��capΪ1����
	ÿ������������capΪm
	��ţ�ͻ���֮���ö��ֵķ���
	����һ��maxdis
	Ȼ��ÿһ��ѭ��������ţ����������·С�ڵ���maxdis������¿��Խ���
	����ţ��������capΪ1
	��һ��dinic �������c���Ƕ�ƥ����
	Ȼ�����ѭ���ҵ�Min(maxdis) 
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
const int maxn=300;
int e[maxn][maxn];
bool vis[maxn];
int dis[maxn][maxn];
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
	int k,c,m;
	while(scanf("%d%d%d",&k,&c,&m)!=EOF){
		//k  1~k
		//c  k+1~k+c
		st=k+c+1;
		des=k+c+2;
		for(int i=1;i<=k+c;++i)
			for(int j=1;j<=k+c;++j){
				scanf("%d",&dis[i][j]);
				if(dis[i][j]==0)dis[i][j]=inf;
			}
		for(int l=1;l<=k+c;++l)//floyd 
			for(int i=1;i<=k+c;++i)
				for(int j=1;j<=k+c;++j)
					if(i!=j)
						dis[i][j]=min(dis[i][j],dis[i][l]+dis[l][j]);
		n=k+c+2;
		int l=1,r=inf,res=1;
		while(l<=r){
			int mid=(l+r)>>1;
			memset(e,0,sizeof(e));
			for(int i=1;i<=k;++i)e[i][des]=m;
			for(int i=k+1;i<=k+c;++i)e[st][i]=1;
			for(int i=k+1;i<=k+c;++i)
				for(int j=1;j<=k;++j)
					if(dis[i][j]<=mid)e[i][j]=1;
			int ans=Dinic();
			if(ans==c)res=mid,r=mid-1;
			else l=mid+1;
		}
		cout<<res<<"\n";
	}
	return 0;
}
