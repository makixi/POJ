/*
	�ò����������ȥ������
	����û����ȫ���� ���쿴�����һ��ӦҲû�뵽�ܺõķ���
	�������صط������ڽ�ͼ��ʱ��Ҫ��¼һ��rnex��rhead
	��Ŀ��㿪ʼ���� �ȼ�¼��t��ÿ����ľ��루�����˵ľ���inf��
	Ȼ��dis�����������������ز����ٵ�һ������
	���������Ǻ���ͨ�ص�A*���·�� 
*/ 
#include<iostream>
#include<vector>
#include<queue>
#include<cstring>
#include<cstdio>
#include<algorithm>
using namespace std;
const int maxn=1001;
const int inf=0x3f3f3f3f;
int n,m,k,s,t,tot;
int head[maxn],rhead[maxn];
int dis[maxn];
bool vis[maxn];
struct edge{
	int u,to,w,nex,rnex;
}e[100005];
struct node{
	int u,g;
	node(){}
	node(int uu,int gg):u(uu),g(gg){}
	bool operator < (const node &n)const{
		return dis[u]+g>dis[n.u]+n.g;
	}
};
void add(int a,int b,int c){
	e[tot].u=a;
	e[tot].to=b;
	e[tot].nex=head[a];
	e[tot].w=c;
	e[tot].rnex=rhead[b];//ע�⣡�� 
	rhead[b]=tot;
	head[a]=tot;
	++tot;
}
int main(){
	while(scanf("%d%d",&n,&m)!=EOF){
		memset(head,-1,sizeof(head));
		memset(rhead,-1,sizeof(rhead));
		memset(dis,inf,sizeof(dis));
		memset(vis,false,sizeof(vis));
		tot=1;
		for(int i=0;i<m;++i){
			int x,y,w;
			scanf("%d%d%d",&x,&y,&w);
			add(x,y,w);//add(y,x,w);
		}
		scanf("%d%d%d",&s,&t,&k);
		priority_queue<node> q;
		q.push(node(t,0));
		dis[t]=0;
		while(!q.empty()){
			node nd=q.top();q.pop();
			if(vis[nd.u])continue;
			vis[nd.u]=true;
			for(int i=rhead[nd.u];i!=-1;i=e[i].rnex){
				if(dis[e[i].u]>dis[nd.u]+e[i].w){
					dis[e[i].u]=dis[nd.u]+e[i].w;
					q.push(node(e[i].u,0));
				}
			}
		}
		if(dis[s]==inf){
			cout<<-1<<"\n";
			continue;
		}
		q.push(node(s,0));
		if(s==t)++k;
		bool flag=false;
		while(!q.empty()){
			node nd=q.top();q.pop();
			if(nd.u==t){
				if(k>1)--k;
				else{
					cout<<nd.g<<"\n";
					flag=true;
					break;
				}
			}
			for(int i=head[nd.u];i!=-1;i=e[i].nex){
				q.push(node(e[i].to,e[i].w+nd.g));
			}
		}
		if(!flag)cout<<-1<<"\n";
	}
	return 0;
}
