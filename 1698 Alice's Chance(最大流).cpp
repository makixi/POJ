/*
	���ճ̱������еĵ�Ū������
	�����Ӱ�����������㣬��ӵ�ӰI������������Ϊ1�ıߡ�
	Դ����ÿһ����Ӱ������ΪD�ıߡ�ÿһ��������һ������1�ıߡ�
	���������������sum{d[i]}����ԣ����򲻿��ԡ�
*/
#include<iostream>
#include<cstring>
#include<queue>
#include<algorithm>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=405;
int e[maxn][maxn];
bool vis[maxn];
int Layer[maxn];
int n=405,m,des,st;
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
	int t;
	scanf("%d",&t);
	while(t--){
		int num,ans=0;
		scanf("%d",&num);
		memset(e,0,sizeof(e));
		st=401,des=402;
		for(int i=1;i<=num;++i){
			int tmp[10];
			for(int j=1;j<=7;++j){
				scanf("%d",&tmp[j]);
			}
			int d,w;
			scanf("%d%d",&d,&w);
			e[st][i]+=d;
			ans+=d;
			for(int j=1;j<=w;++j){
				for(int k=1;k<=7;++k){
					if(!tmp[k])continue;
					e[i][50+(j-1)*7+k]+=1;
				}
			}
		}
		for(int j=51;j<=400;++j)e[j][des]+=1;
		int res=Dinic();
		//cout<<res<<"\n";
		if(res==ans)cout<<"Yes\n";
		else cout<<"No\n";
	}
	return 0;
}
