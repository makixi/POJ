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
#define Maxn 7800 //6^5=3125��״̬
#define Maxm 120
int dp[Maxn],ba[7],pri[7],num[Maxm],sp[Maxm],state[Maxm];
int s;
map<int,int>myp;
bool iscan(int * a,int i){
    int tt[5]={0},tmp=state[i]; //��������Żݵĸ���Ʒ����
    int j=0;
    while(tmp){
        tt[j++]=tmp%6;
        tmp/=6;
    }
    for(int j=0;j<5;j++) //�ж��Ƿ���ѡ
        if(a[j]<tt[j])
            return false;
    return true;
}
int main(){
   	ba[0]=1;
   	for(int i=1;i<=5;i++) //Ԥ������Ƶ�,
        ba[i]=ba[i-1]*6;
    int b;
    while(~scanf("%d",&b)){
        myp.clear();
        int sta=0;
        for(int i=0;i<b;i++){
            int c,k;
            scanf("%d%d%d",&c,&k,&pri[i]);
            myp[c]=i; //��Ӧ��Ʒ�� ��ɢ������
            sta+=k*ba[i]; //���Ҫ�ﵽ��״̬
        }
        memset(dp,inf,sizeof(dp));//��ʼ��
        dp[0]=0;//�����״̬
        scanf("%d",&s);
        for(int i=1;i<=s;i++){
            scanf("%d",&num[i]);
            int tt=0;
            for(int j=1;j<=num[i];j++){
                int c,k;
                scanf("%d%d",&c,&k);
                tt+=ba[myp[c]]*k;//��ǰ�Ż�������״̬
            }
            state[i]=tt;
            scanf("%d",&sp[i]);//�Żݻ���
        }
        for(int i=1;i<=sta;i++){
            int kid[5]={0};
            int tt=i,j=0;
            while(tt){
                kid[j++]=tt%6;
                tt/=6;
            }
            for(int p=0;p<j;p++) //�����ŻݵĻ�
                for(int q=1;q<=kid[p];q++) //��ÿ�ֿ���ѡ����������Ʒ�����ĸ���
                    dp[i]=min(dp[i-ba[p]*q]+pri[p]*q,dp[i]);
            for(int j=1;j<=s;j++)//ѡ��ÿһ���Ż�
                if(i>=state[j]&&iscan(kid,j))//�ܷ�ѡ
                    dp[i]=min(dp[i-state[j]]+sp[j],dp[i]);    
		}
        printf("%d\n",dp[sta]);//����ô����Ʒ��С����
    }
   return 0;
}
