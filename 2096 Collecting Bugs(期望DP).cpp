#include<iostream>
#include<algorithm>
#include<cstdio>
#include<string>
#include<cstring>
using namespace std;
const int maxn=1100;
const int inf=0x3f3f3f3f;
double dp[maxn][maxn];
int main(){
	int n,s;
	while(scanf("%d%d",&n,&s)!=EOF){
		dp[n][s]=0;
		for(int i=n;i>=0;--i)
			for(int j=s;j>=0;--j){
				if(i==n&&j==s)continue;
				//dp[i][j]=i*j/n/s*dp[i][j]+i*(s-j)/n/s*dp[i][j+1]+(n-i)*j/n/s*dp[i+1][j]+(n-i)(s-j)/n/s+1  
				dp[i][j]=(n*s+i*(s-j)*dp[i][j+1]+(n-i)*j*dp[i+1][j]+(n-i)*(s-j)*dp[i+1][j+1])/(n*s-i*j);
			}
		printf("%.4lf\n",dp[0][0]);
	}
	return 0;
}
