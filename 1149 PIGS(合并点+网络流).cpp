/*
	��ͼ�ҹ���ϵ��~
	������������ã�
	1. ��������ڵ����������Դ��ȫ��ͬ������԰����Ǻϲ���һ����
	2. ��������ڵ��������ȥ����ȫ��ͬ������԰����Ǻϲ���һ����
	3. ����ӵ� u ���� v ��һ������Ϊ +�޵ıߣ����� u �� v ��Ψһ������Դ������ v �� u
	��Ψһ����ȥ������԰� u �� v �ϲ���һ���ڵ㡣
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
				if (!belong[num])e[st][i] += pig[num];//num��Ȧ�ĵ�һ���˿� 
				else e[belong[num]][i] = inf;//��num��Ȧ����һ���˿��� 
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
