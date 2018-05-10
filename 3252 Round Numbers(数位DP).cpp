#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
typedef long long ll;
int a[80];
ll dp[35][80];
ll dfs(int pos,int sum,bool lead,bool limit){
    if(pos==-1) return sum>=32;
    if(!limit && !lead && dp[pos][sum]!=-1) 
		return dp[pos][sum];
    int up=limit?a[pos]:1;
    ll ans=0;
    for(int i=0;i<=up;i++){
    	if(lead&&i==0)ans+=dfs(pos-1,sum,lead&&i==0,limit&&i==a[pos]);
        else ans+=dfs(pos-1,sum+(i==0?1:-1),lead && i==0,limit && i==a[pos]);
    }
    if(!limit && !lead) dp[pos][sum]=ans;
    return ans;
}
ll solve(ll x){
    int pos=0;
    while(x){
        a[pos++]=x&1;
        x>>=1;
    }
    return dfs(pos-1,32,true,true);
}
int main(){
    ll l,r;
    memset(dp,-1,sizeof(dp));
    while(scanf("%lld%lld",&l,&r)!=EOF){
        printf("%lld\n",solve(r)-solve(l-1));
    }
    return 0;
}
