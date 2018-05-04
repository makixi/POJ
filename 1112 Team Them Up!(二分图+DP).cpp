#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
const int N=110;
int g[N][N];
int r[N][N];//ģ��ͼ
int c[N];// Ⱦ����ɫ
int num[N][2]; int snt; // ��ͨ����
int s[N]; //ÿ����������ͨ����
bool dp[N][N];// ǰi����ͨ�����ܷ����ΪJ�˵�һ��
int ans[N][N];// ǰi����ͨ�������ΪJ�˵�һ���ѡ��ѡ��0һ�黹��1һ�飩
int n;
bool flag ; 
void dfs (int rt)  {
    for (int i=1;i<=n;i++) 
        if (r[rt][i]) {
            if (c[i]==-1) {
                c[i]=c[rt]^1;
                num[snt][c[i]]++;
                s[i]=snt;
                dfs (i);
                if (flag) return ;
            }
            if (c[i]==c[rt]) {flag=1; return;}
        }
    return ;
} 
int main (){
    ios::sync_with_stdio(false);
    cin>>n; 
    for (int i=1;i<=n;i++) {
        int x;
        while (cin>>x&&x) g[i][x]=1;
    }
    for (int i=1;i<=n;i++)
        for (int j=1;j<=n;j++) 
            if (j!=i&&g[j][i]==0)
                r[i][j]=r[j][i]=1;//���໥��ʶ���˽�������ߣ���������һ���ڲ�ͬ�ķ��飬��0��1��Ⱦɫ���⣩
    memset (c,-1,sizeof (c));
    for (int i=1;i<=n;i++) 
        if (c[i]==-1) {
            c[i]=0;
            num[++snt][0]++;
            s[i]=snt;
           	dfs (i);
            if (flag) {
                cout<<"No solution"<<endl;
                break;
            }
        }
    if (!flag) {
        dp[0][0]=1;
        for (int i=1;i<=snt;i++)
            for (int j=n/2;j>=0;j--) {
                if (j>=num[i][0]&&dp[i-1][j-num[i][0]])
                    {dp[i][j]=1; ans[i][j]=0;}
                if (j>=num[i][1]&&dp[i-1][j-num[i][1]])
                    {dp[i][j]=1; ans[i][j]=1;}
            }
        int t1;
        for (int i=n/2;i>=0;i--)  
            if (dp[snt][i]) {t1=i;break;}
        int _n=t1; int _s=snt;
        while (_s) {
            for (int i=1;i<=n;i++) 
                if (s[i]==_s&&c[i]==ans[_s][_n])  c[i]=-1;
            _n-=num[_s][ans[_s][_n]];
            _s--;
        }
        cout<<n-t1;
        for (int i=1;i<=n;i++)
            if (c[i]>=0)  cout<<" "<<i;
        cout<<endl;  
        cout<<t1;
        for (int i=1;i<=n;i++)
            if (c[i]<0)  cout<<" "<<i;
        cout<<endl;    
    }
    return 0;
}
