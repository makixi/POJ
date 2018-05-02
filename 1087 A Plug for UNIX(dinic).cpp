#include <iostream>
#include <string>
#include <map>
#include <cstdio>
#include <cstring> 
#include <queue>
#include <algorithm>
using namespace std;
#define MAXV 810				//最大值设为400贡献了RE一次
#define INF 0x3f3f3f3f
#define min(a,b) (a>b?b:a)
map<string,int> rec_dev;
char str[30],stmp[30];
int rec_dev_sum;
int res[MAXV][MAXV];			//保存图的信息
int n,m,k;
int	dis[MAXV];
int source,sink,maxflow;
int bfs(){
	int k;
	queue<int> q;
    memset(dis,-1,sizeof(dis));
    dis[sink]=0;
    q.push(sink);
    while(!q.empty()){
		k=q.front();
		q.pop();
        for(int i=0;i<MAXV;i++)
            if(dis[i]==-1 && res[i][k]){
                dis[i] = dis[k] + 1;
                q.push(i);
            }
        if(k==source) return 1;
    }
	return 0;
}
int dfs(int cur,int cp){
    if(cur==sink)	return cp;
    int tmp=cp,t;
    for(int i=0;i<MAXV && tmp;i++)
        if(dis[i]+1==dis[cur] && res[cur][i]){
            t=dfs(i,min(res[cur][i],tmp));
            res[cur][i]-=t;
            res[i][cur]+=t;
            tmp-=t;
        }
    return cp-tmp;
}
void dinic(){					//dinic不用解释了
    maxflow=0;
    while(bfs()) maxflow+=dfs(source,INF);
}
int main(){
	int i;
	while(~scanf("%d",&n)){
		memset(res,0,sizeof(res));
		rec_dev.clear();
		rec_dev_sum=1;
		source=0;sink=MAXV-1;
		for(i=0;i<n;i++){
			scanf("%s",str);
			rec_dev[str]=rec_dev_sum++;
			res[rec_dev[str]][sink]=1;			//插在电源的插座指向汇点
		}
		scanf("%d",&m);
		for(i=0;i<m;i++){
			scanf("%s%s",stmp,str);
			rec_dev[stmp]=rec_dev_sum++;
			if(!rec_dev[str])rec_dev[str]=rec_dev_sum++;
			res[source][rec_dev[stmp]]=1;			//源点指向设备
			res[rec_dev[stmp]][rec_dev[str]]=1;		//设备指向插座
		}
		scanf("%d",&k);
		for(i=0;i<k;i++){
			scanf("%s%s",str,stmp);
			if(!rec_dev[str])rec_dev[str]=rec_dev_sum++;
			if(!rec_dev[stmp])rec_dev[stmp]=rec_dev_sum++;
			res[rec_dev[str]][rec_dev[stmp]]=INF;	//插座对插座是无限
		}
		dinic();
		printf("%d\n",m-maxflow);
	}
	return 0;
}
