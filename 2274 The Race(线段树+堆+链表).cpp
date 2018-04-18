/*
	��������get���ᳬ������ 
	Ȼ�����һ�� �����λ��A->B->C A�ܳ���BҲ�ܳ���C  ��ôA����B�¼�һ����A����C�緢��
	�����ȴ����������㿪ʼ����
	�տ�ʼ��priority_queue������ ����MLE ���˶�������ͬһ����˼������
	ԭ����λ�� A->B->C->D ��������A->C->B->D  ��ʱ��pre�����nex�������Ҫ����
	���ϡ� 
*/
#include<cstdio>
#include<cstring>
#include<iostream>
#include<queue>
#include<algorithm>
using namespace std;
#define MAXN 250010
#define INF 0x3f3f3f3f
#define lson l,mid,p<<1
#define rson mid+1,r,p<<1|1
int n;
int pos[MAXN],v[MAXN];
struct Tree{
	int l,r;
	int sum;
}tree[MAXN<<2];
int nex[MAXN],pre[MAXN];
int top;
//----------��[l,r]�в�ѯ[L,R],��p��ʼ--------------//
void update(int st,int i){
	if(tree[st].l==tree[st].r){
		tree[st].sum++;
		return;
	}
	int mid=(tree[st].l+tree[st].r)>>1;
    if(i<=mid) update(st<<1,i);
    else update(st<<1|1,i);
    tree[st].sum=(tree[st<<1].sum+tree[st<<1|1].sum)%1000000;
}
int query(int st,int l,int r){
	if (tree[st].l == l && tree[st].r == r) 
		return tree[st].sum;
	int mid=(tree[st].l+tree[st].r)>>1;
    int ans=0;
    if (r<=mid) ans+=query(st<<1,l,r);
    else if (l>mid) ans+=query(st<<1|1,l,r);
    else ans+=(query(st<<1,l,mid)+query(st<<1|1,mid+1,r));
	return ans%1000000;
} 
struct node
{
    int x,y;//x ������ ��y ��¼ x �ĺ�ڵ�
    double k1,k2;//k1��¼ʱ�䣬k2��ʾ�н��ľ���
//-------------���캯����ʼ��----------------------//
    node(){
        x=0;y=0;
        k1=0;k2=0;
    }
    node(int x1,int y1,double t1,double t2){
        x=x1;y=y1;
        k1=t1;k2=t2;
    }
}heap[MAXN*10];
//priority_queue<node> q;
void Swap(int i,int j){
    node t;
    t=heap[i];
    heap[i]=heap[j];
    heap[j]=t;
}
//--------------��������--------------------------//
bool operator<(node a,node b){
    return a.k1<b.k1||(a.k1==b.k1&&a.k2<b.k2);
}
void heap_increase(int i)//�㷨����91ҳ
{
    while(i>1)//��֤������������ķ�Χ
    {
        int j=i>>1;//���Ƕ��� i �ĸ��׽ڵ�
        if(heap[i]<heap[j]) Swap(i,j);
        else break;
        i=j;
    }
}

void heap_decrease(int i){
    while((i<<1)<=top){
        int j=i<<1;//i ���Ƕ��� j �ĸ��׽ڵ�
        if(j+1<=top&&heap[j+1]<heap[j])
            j++;//����С�Ķ���ά����С��
        if(heap[j]<heap[i]) Swap(i,j);
        else break;
        i=j;
    }
}
void pri_queue(){
    Swap(1,top);
    top--;
    heap_decrease(1);
}
void build(int st,int l,int r){
	tree[st].l=l;
	tree[st].r=r;
	tree[st].sum=0;
	if(l==r)return;
	int mid=(l+r)>>1;
	build(st<<1,l,mid);
	build(st<<1|1,mid+1,r);
}
void add(int i,int j){
    double dis,time;
    if(v[i]>v[j]) time=double(pos[j]-pos[i])/(v[i]-v[j]);
    else time=INF;
    dis=pos[i]+v[i]*time;
    node temp=node(i,j,time,dis);
    heap[++top]=temp;
    heap_increase(top);
}
int main(){
    scanf("%d",&n);
    int ans=0;
    build(1,0,100);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&pos[i],&v[i]);
        update(1,v[i]);
		ans+=query(1,v[i]+1,100);
        ans%=1000000;//ע��,����ģ���򣬵����һ�����ڴ�
    }
    printf("%d\n",ans);
    deal_heap();
    nex[0]=1;pre[n+1]=n;
    pos[n+1]=INF;v[n+1]=INF;
    pos[0]=0;v[0]=-INF;
    add(0,1);
    for(int i=1;i<=n;i++){
        nex[i]=i+1;
        pre[i]=i-1;
        add(i,nex[i]);
    }
    for(int i=1;i<=10000;i++){
        if(heap[1].k1>=INF)break;
        if(pre[heap[1].y]!=heap[1].x || nex[heap[1].x]!=heap[1].y){
                        --i;
                        pri_queue();
                        continue;
        }
        printf("%d %d\n",heap[1].x,nex[heap[1].x]);
        int tempx=heap[1].x,tempy=nex[heap[1].x];
        int tempx_pre=pre[tempx],tempy_nex=nex[tempy];
        pri_queue();
        nex[tempx_pre]=tempy;     pre[tempy]=tempx_pre;
        nex[tempy]=tempx;         pre[tempx]=tempy;
        nex[tempx]=tempy_nex;    pre[tempy_nex]=tempx;
        add(tempx,tempy_nex);
        add(tempx_pre,tempy);
        add(tempy,tempx);
    }
    return 0;
}
