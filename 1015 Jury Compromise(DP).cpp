#include<cstdio>
#include<algorithm>
#include<iostream>
#include<cstring>
#include<vector>
using namespace std;
int dp[21][801];
vector<int> path[21][801];
int main(){
    int times=1;
    int subtraction[201],_plus[201];
    int n,m,i,j,k;
    while(~scanf("%d%d",&n,&m) && n && m){
        for(i=0;i<m;++i)//清空vector
            for(j=0;j<801;++j)
                path[i][j].clear();
        memset(dp,-1,sizeof(dp));
        int d,p;
        for(i = 0; i < n; i++){
            cin>>d>>p;
            subtraction[i] = d-p;
            _plus[i] = d+p;
        }
        int fix = 20*m;
        dp[0][fix] = 0;
        for(k = 0; k < n; k++)//选择一个
            for(i = m-1; i >= 0; i--)//进行逆推
                for(j = 0; j < 2*fix; j++)
                    if(dp[i][j] >= 0)
                        if(dp[i+1][j+subtraction[k]] <= dp[i][j] + _plus[k]){
                            dp[i+1][j+subtraction[k]] = dp[i][j] + _plus[k];
                            path[i+1][j+subtraction[k]] = path[i][j];//每次更新都要把path全部复制过来，就是因为这个才用的vector
                            path[i+1][j+subtraction[k]].push_back(k);
                        }
        for(i = 0; dp[m][fix+i] == -1 && dp[m][fix-i] == -1; i++);
        int temp = (dp[m][fix+i] > dp[m][fix-i]) ? i : -i;
        int sumD = ( dp[m][fix+temp] + temp )/2;
        int sumP = ( dp[m][fix+temp] - temp )/2;
        printf( "Jury #%d\n", times++ );
        printf( "Best jury has value %d for prosecution and value %d for defence:\n", sumD,sumP);
        for( i=0; i < m; i++ )
            printf( " %d", path[m][fix+temp][i]+1);
        printf( "\n\n" );
    }
    return 0;
}
