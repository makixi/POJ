#include<iostream>
#include<cmath>
#include<cstdio>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
using namespace std;
const int inf=0x3f3f3f3f;
#define Maxn 7800 //6^5=3125个状态
#define Maxm 120
int dp[Maxn],ba[7],pri[7],num[Maxm],sp[Maxm],state[Maxm];
int s;
map<int,int>myp;
bool iscan(int * a,int i){
    int tt[5]={0},tmp=state[i]; //求出该种优惠的各物品个数
    int j=0;
    while(tmp){
        tt[j++]=tmp%6;
        tmp/=6;
    }
    for(int j=0;j<5;j++) //判断是否能选
        if(a[j]<tt[j])
            return false;
    return true;
}
int main(){
   	ba[0]=1;
   	for(int i=1;i<=5;i++) //预处理进制的,
        ba[i]=ba[i-1]*6;
    int b;
    while(~scanf("%d",&b)){
        myp.clear();
        int sta=0;
        for(int i=0;i<b;i++){
            int c,k;
            scanf("%d%d%d",&c,&k,&pri[i]);
            myp[c]=i; //对应物品号 离散化处理
            sta+=k*ba[i]; //最后要达到的状态
        }
        memset(dp,inf,sizeof(dp));//初始化
        dp[0]=0;//最初的状态
        scanf("%d",&s);
        for(int i=1;i<=s;i++){
            scanf("%d",&num[i]);
            int tt=0;
            for(int j=1;j<=num[i];j++){
                int c,k;
                scanf("%d%d",&c,&k);
                tt+=ba[myp[c]]*k;//当前优化方案的状态
            }
            state[i]=tt;
            scanf("%d",&sp[i]);//优惠花费
        }
        for(int i=1;i<=sta;i++){
            int kid[5]={0};
            int tt=i,j=0;
            while(tt){
                kid[j++]=tt%6;
                tt/=6;
            }
            for(int p=0;p<j;p++) //不用优惠的话
                for(int q=1;q<=kid[p];q++) //对每种可以选不超过该物品数量的个数
                    dp[i]=min(dp[i-ba[p]*q]+pri[p]*q,dp[i]);
            for(int j=1;j<=s;j++)//选择每一种优惠
                if(i>=state[j]&&iscan(kid,j))//能否选
                    dp[i]=min(dp[i-state[j]]+sp[j],dp[i]);    
		}
        printf("%d\n",dp[sta]);//买到这么多物品最小花费
    }
   return 0;
}
