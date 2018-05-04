#include<iostream>
#include<algorithm>
#include<string>
#include<cstring>
using namespace std;
int dp[120][120];
int main(){
	string s;
	while(cin>>s&&s!="end"){
		memset(dp,0,sizeof(dp));
		int len=s.length();
		for(int i=len-2;i>=0;--i){
			for(int j=i+1;j<len;++j){
				if((s[i]=='('&&s[j]==')')||(s[i]=='['&&s[j]==']'))
					dp[i][j]=max(dp[i][j],dp[i+1][j-1]+2);
				for(int k=i;k<j;++k)
					dp[i][j]=max(dp[i][j],dp[i][k]+dp[k+1][j]);
			}
		}
		cout<<dp[0][len-1]<<"\n";
	}
	return 0;
}
