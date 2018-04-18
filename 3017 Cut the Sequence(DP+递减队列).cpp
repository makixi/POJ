#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;
typedef long long ll;
const int maxn = 1e5 + 5;
ll dp[maxn];
int a[maxn];
struct node {
	int index;
	ll val;
}q[maxn];
int main() {
	int n;
	ll m;
	bool flag = true;
	scanf("%d%lld", &n, &m);
	for (int i = 1; i <= n; ++i) { 
		scanf("%lld", &a[i]); 
		if (a[i] > m)flag = false;
	}
	if (!flag) {
		cout << -1;
		return 0;
	}
	int head = 0, tail = 0, pos = 1;
	ll sum = a[1];
	q[tail].val = dp[1] = a[1]; 
	q[tail++].index = 1;
	for (int i = 2; i <= n; ++i) {
		sum += a[i];
		while (pos<i&&sum > m)sum -= a[pos], ++pos;
		while (head<tail&&q[tail - 1].val<=a[i])tail--;
		q[tail].index = i;
		q[tail++].val = a[i];
		while (q[head].index<pos && head<tail)head++;
		dp[i] = dp[pos - 1] + q[head].val;
		for (int j = head; j < tail - 1; ++j)
			dp[i] = min(dp[i], dp[q[j].index] + q[j + 1].val);
	}
	cout << dp[n];
	return 0;
}
