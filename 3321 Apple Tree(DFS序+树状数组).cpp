#include<iostream>
#include<vector>
using namespace std;
#define lowbit(i) ((i)&(-i))
const int maxn=2000010;
int cnt;
vector<vector<int> > e(maxn/2);
int s[maxn],d[maxn],c[maxn];
bool apple[maxn];
void dfs(int v){//记录dfs序 
	s[v]=++cnt;
	for(int i=0;i<e[v].size();++i)dfs(e[v][i]);
	d[v]=++cnt;
}
int getsum(int x){
	int res = 0;
	for (int i = x; i >= 1; i -= lowbit(i))res += c[i];
	return res;
}
void update(int x, int v){
	for (int i = x; i <= cnt; i += lowbit(i))c[i] += v;
}
int main(){
	cnt=0;
	int n;
	cin>>n;
	for(int i=0;i<n-1;++i){
		int a,b;
		scanf("%d%d",&a,&b);
		e[a].push_back(b);
	}
	dfs(1);
	fill(apple,apple+n+1,true);//刚开始都有苹果 
	int m;
	cin>>m;
	for(int i=1;i<=cnt;++i)update(i,1);
	while(m--){
		char ch;
		int q;
		cin>>ch>>q;
		if(ch=='Q') printf("%d\n", (getsum(d[q]) - getsum(s[q] - 1)) / 2);
		else{
			if (apple[q]) {
				update(s[q], -1); 
				update(d[q], -1);
				apple[q] = 0;
			}
			else {
				update(s[q], 1); 
				update(d[q], 1);
				apple[q] = 1;
			}
		}
	}
	return 0;
}
