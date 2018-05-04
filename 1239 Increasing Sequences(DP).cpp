#include<iostream>
#include<algorithm>
#include<cstdio>
#include<cstring>
#include<cmath>
using namespace std;
const int inf=0x3f3f3f3f;
const int maxn=100;
int dp[maxn];
char str[maxn];
bool isgreater(int i,int j,int m,int n){
    while(str[i]=='0'&&i<=j)i++;
    while(str[m]=='0'&&m<=n)m++;
    if(i>j)return false;
    if(m>n)return true;
    int a=j-i+1,b=n-m+1; //长度，也就是位数
    if(a>b)return true;
    else if(a<b)return false;
    else{
        for(int k=i,p=m;k<=j;k++,p++) //位数相同，逐位比较
            if(str[k]>str[p])return true;
            else if(str[k]<str[p])return false;
    }
    return false;
} 
int main(){
	while(scanf("%s",str+1)!=EOF){
		int n=strlen(str+1);
		if(n==1&&str[1]=='0')break;
		for(int i=1;i<=n;++i){
			dp[i]=i;
			for(int j=i-1;j>=1;--j)
				if(isgreater(j+1,i,j-dp[j]+1,j)){
					dp[i]=i-j;
					break;
				}
		}
		int tt=n-dp[n]+1;
        dp[tt]=dp[n];
        for(int i=tt-1;i>=1;i--){
            if(str[i]=='0'){
                dp[i]=dp[i+1]+1;
                continue;
            }
            for(int j=tt;j>i;j--) //求出长度最大的
                if(isgreater(j,j+dp[j]-1,i,j-1)){
                    dp[i]=j-i;
                    break;
                }
        }
        for(int i=1;i<=dp[1];i++) cout<<str[i];
        int pp=dp[1]+1;
        while(pp<=n){
        	cout<<",";
            for(int i=pp;i<pp+dp[pp];i++)cout<<str[i];
            pp=pp+dp[pp];
        }
        cout<<"\n";
	}
	return 0;
}
