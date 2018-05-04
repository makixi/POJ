#include<cmath>
#include<queue>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const double g=10.0,eps=1e-9;
const int N=100000+10,maxn=16,inf=9999999;
struct edge{
   int to,cap,next;
}e[N<<1];
int s,t,cnt;
int dis[N],cur[N];
int head[N];
void add(int u,int v,int c){
    e[cnt].to=v;
    e[cnt].cap=c;
    e[cnt].next=head[u];
    head[u]=cnt++;
}
bool bfs(){
    memset(dis,-1,sizeof dis);
    dis[s]=0;
    queue<int>q;
    q.push(s);
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int i=head[x];i!=-1;i=e[i].next){
            int temp=e[i].to;
            if(dis[temp]==-1&&e[i].cap>0){
                dis[temp]=dis[x]+1;
                q.push(temp);
            }
        }
    }
    return dis[t]>-1;//找到增广路
}
int dfs(int x,int cap){
    if(x==t)return cap;
    int flow=0;
    for(int i=head[x];i!=-1;i=e[i].next){
        int temp=e[i].to;
        if(dis[temp]==dis[x]+1&&e[i].cap){
            int f=dfs(temp,min(cap-flow,e[i].cap));
            e[i].cap-=f;//正向边
            e[i^1].cap+=f;//反向边
            flow+=f;
            if(flow==cap)break;
        }
    }
    if(!flow)dis[x]=-2;//不加会超时
    return flow;
}
int max_flow(){
    int flow=0,f;
    while(bfs())//还有增广路
        while((f=dfs(s,inf))>0)flow+=f;//进行多路增广
    return flow;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int k,n,m;
    cin>>k;
    while(k--){
        cin>>n>>m;
        int smin=inf,tmax=-inf;
        s=t=1;
        int a,b,c;
        for(int i=1;i<=n;i++){
            cin>>a>>b;
            if(a<=smin)smin=a,s=i;
            if(a>=tmax)tmax=a,t=i;
        }
        cnt=0;
        memset(head,-1,sizeof head);
        while(m--){
            cin>>a>>b>>c;
            add(a,b,c);//正向边
            add(b,a,c);//反向边
        }
        int ans=max_flow();
        cout<<ans<<endl;
    }
    return 0;
}
