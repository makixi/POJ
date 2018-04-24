#include<iostream>
#include<string>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<queue>
#include<cstdio>
using namespace std;
const int MAXN=255;
const int INF=1000000000;
int cap[MAXN][MAXN],flow[MAXN][MAXN],low[MAXN][MAXN],high[MAXN][MAXN];
int r[MAXN],c[MAXN],q[MAXN],in[MAXN],out[MAXN],d[MAXN];
//in[u]:u������ߵ������½��,out[u]:u���г��ߵ������½��,fa[]:dinic�еĲ��
bool vist[MAXN];
void Init(){
	memset(in,0,sizeof(in));
	memset(out,0,sizeof(out));
	memset(low,0,sizeof(low));
 	memset(cap,0,sizeof(cap));
	memset(high,0,sizeof(high));
	memset(flow,0,sizeof(flow));
}
bool bfs(int s,int t,int n){
 	int i,tmp;
 	memset(d,-1,sizeof(d));
 	queue<int>Q;
 	Q.push(s);
 	d[s]=0;
 	while(!Q.empty()){
  		tmp=Q.front();
  		Q.pop();
  		for(i=0;i<n;i++)
   			if(cap[tmp][i]>0&&d[i]==-1){
    			d[i]=d[tmp]+1;
    			Q.push(i);
   			}
 	}
 	if(d[t]!=-1)return true;
 	else return false;
}
int dfs(int k,int t,int n,int sum){
 	if(k==t)return sum;
 	int i,os=sum;
 	for(i=0;i<n;i++)
  		if(d[i]==d[k]+1&&cap[k][i]>0){
   			int a=dfs(i,t,n,min(sum,cap[k][i]));
   			cap[k][i]-=a;
   			cap[i][k]+=a;
   			flow[k][i]+=a;
   			flow[i][k]-=a;
   			sum-=a;
  		}
  	return os-sum;
}
int dinic(int s,int t,int n){
 	int ans=0;
 	while(bfs(s,t,n))ans+=dfs(s,t,n,INF);
 	return ans;
}
void solve(int s,int t,int num,int n,int m){
	int i,j,ss,tt,res,sum=0;
	ss=num;
	tt=num+1;
 	for(i=0;i<num;i++)
		for(j=0;j<num;j++){
			cap[i][j]=high[i][j]-low[i][j];        //�ñ�����Ϊ���½�����֮��
			out[i]+=low[i][j];  //ͳ�Ƶ�i���г��ߵ������½�֮��
			in[j]+=low[i][j];  //ͳ�Ƶ�j������ߵ������½�֮��
			sum+=low[i][j];  //���бߵ������½�֮��
		}
	for(i=0;i<num;i++) {  //��Ӹ���Դ��ss�ͻ��tt������������
		cap[ss][i]=in[i];
		cap[i][tt]=out[i];
	}
	cap[t][s]=INF;   //�ڸ�������������cap[t][s]=INF
	res=dinic(ss,tt,num+2);//�Ը���������������
	if(res!=sum){ //�������������������������½�֮��,���޽�
		printf("IMPOSSIBLE\n");
		return;
	}
 	cap[t][s]=cap[s][t]=0;//ȥ����(t,s)��(s,t)
	res=dinic(s,t,num);//�ڶ�ȥ�߼�������Դ֮���ͼ��������
	for(i=1;i<=n;i++){                           //�������
 		printf("%d",flow[i][1+n]+low[i][1+n]);
		for(j=2;j<=m;j++)printf(" %d",flow[i][j+n]+low[i][j+n]);
		printf("\n");
	}
}
int main(){
    int i,j,s,t,u,v,w,m,n,num,ans,ncase;
    char ch;
    scanf("%d",&ncase);
    while(ncase--){
		Init();
		scanf("%d%d",&n,&m);
		for(i=1;i<=n;i++)scanf("%d",&r[i]);
		for(i=1;i<=m;i++)scanf("%d",&c[i]);
		for(i=1;i<=n;i++)for(j=1;j<=m;j++)high[i][j+n]=INF;
		scanf("%d",&ans);
		while(ans--){
			scanf("%d %d %c %d",&u,&v,&ch,&w);
			if(u==0&&v!=0){
				if(ch=='=')for(i=1;i<=n;i++)low[i][v+n]=high[i][v+n]=w;
				else if(ch=='<')for(i=1;i<=n;i++)high[i][v+n]=min(high[i][v+n],w-1);
				else if(ch=='>')for(i=1;i<=n;i++)low[i][v+n]=max(low[i][v+n],w+1);
			}
            else if(u!=0&&v==0){
                if(ch=='=')for(i=1;i<=m;i++)low[u][i+n]=high[u][i+n]=w;
                else if(ch=='<')for(i=1;i<=m;i++)high[u][i+n]=min(high[u][i+n],w-1);
                else if(ch=='>')for(i=1;i<=m;i++)low[u][i+n]=max(low[u][i+n],w+1);
            }
            else if(u==0&&v==0)
                for(i=1;i<=n;i++)
                    for(j=1;j<=m;j++){
                        if(ch=='=')low[i][j+n]=high[i][j+n]=w;
                        else if(ch=='<')high[i][j+n]=min(high[i][j+n],w-1);
                        else if(ch=='>')low[i][j+n]=max(low[i][j+n],w+1);
                    }
            else if(u!=0&&v!=0){
                if(ch=='=')low[u][v+n]=high[u][v+n]=w;
                else if(ch=='<')high[u][v+n]=min(high[u][v+n],w-1);
                else if(ch=='>')low[u][v+n]=max(low[u][v+n],w+1);
            }
        }
        s=0;     //Դ
   		t=n+m+1;  //��
        for(i=1;i<=n;i++)low[s][i]=high[s][i]=r[i];
        for(i=1;i<=m;i++)low[i+n][t]=high[i+n][t]=c[i];
        solve(s,t,t+1,n,m);
        printf("\n");
    }
    return 0;
}
