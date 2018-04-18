/*
	�տ�������ʱ�����
	��ʵ����Ϊû������ؼ���island��ĿС�ڵ���13
	�������һ�����ͺ�����Ҫ��״ѹ��
	Ȼ��͵�ˮ�����ˡ���
	��ȻҪע��ans2/2 
*/
#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
int n,m;
int val[15],maze[13][13];
int dp[1<<13][13][13];  //dp[state][i][j]��ʾstate״̬�µ����ڶ�����Ϊi�����һ����Ϊjʱ�����Ž�
long long num[1<<13][13][13];   //num[state][i][j]Ϊ��Ӧ��·����Ŀ
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        scanf("%d%d",&n,&m);
        for(int i=0;i<n;i++)scanf("%d",&val[i]);
        memset(maze,0,sizeof(maze));
        int u,v;
        while(m--){
            scanf("%d%d",&u,&v);
            u--;v--;
            maze[u][v]=maze[v][u]=1;
        }
        if(n==1){
            printf("%d 1\n",val[0]);
            continue;
        }
        memset(dp,-1,sizeof(dp));
        memset(num,0,sizeof(num));
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j && maze[i][j]){
                    dp[(1<<i)|(1<<j)][i][j]=val[i]+val[j]+val[i]*val[j];
                    num[(1<<i)|(1<<j)][i][j]=1;
                }
        for(int i=0;i<(1<<n);i++)
            for(int j=0;j<n;j++)
                if((i&(1<<j)))
                    for(int k=0;k<n;k++)
                        if(maze[j][k] && j!=k && (i&(1<<k)) && dp[i][j][k]!=-1)
                            for(int x=0;x<n;x++)
                                if(maze[k][x] && j!=x && k!=x && (i&(1<<x))==0){
                                    int tmp=dp[i][j][k]+val[x]+val[k]*val[x];
                                    if(maze[j][x])
                                        tmp+=val[j]*val[k]*val[x];
                                    if(dp[i|(1<<x)][k][x]<tmp){
                                        dp[i|(1<<x)][k][x]=tmp;
                                        num[i|(1<<x)][k][x]=num[i][j][k];
                                    }else if(dp[i|(1<<x)][k][x]==tmp)
                                        num[i|(1<<x)][k][x]+=num[i][j][k];
                                }
        int ans1=0;
        long long ans2=0;
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(i!=j && maze[i][j]){
                    if(ans1<dp[(1<<n)-1][i][j]){
                        ans1=dp[(1<<n)-1][i][j];
                        ans2=num[(1<<n)-1][i][j];
                    }else if(ans1==dp[(1<<n)-1][i][j])
                        ans2+=num[(1<<n)-1][i][j];
                }
        cout<<ans1<<" "<<ans2/2<<endl;
    }
    return 0;
}
