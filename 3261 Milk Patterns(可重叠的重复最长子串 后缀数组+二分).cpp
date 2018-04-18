#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 20005
int wa[MAXN], wb[MAXN], wv[MAXN], ws1[MAXN];
int cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}
int sa[MAXN], rak[MAXN], height[MAXN];
void SA(int *r, int n, int m) {
	int *x = wa, *y = wb;
	for (int i = 0; i<m; ++i) ws1[i] = 0;
	for (int i = 0; i<n; ++i) ++ws1[x[i] = r[i]];
	for (int i = 1; i<m; ++i) ws1[i] += ws1[i - 1];
	for (int i = n - 1; i >= 0; --i) sa[--ws1[x[i]]] = i;
	int p = 1;
	for (int j = 1; p<n; j <<= 1, m = p) {
		p = 0;
		for (int i = n - j; i<n; ++i) y[p++] = i;
		for (int i = 0; i<n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (int i = 0; i<n; ++i) wv[i] = x[y[i]];
		for (int i = 0; i<m; ++i) ws1[i] = 0;
		for (int i = 0; i<n; ++i) ++ws1[wv[i]];
		for (int i = 1; i<m; ++i) ws1[i] += ws1[i - 1];
		for (int i = n - 1; i >= 0; --i) sa[--ws1[wv[i]]] = y[i];
		swap(x, y); x[sa[0]] = 0; p = 1;
		for (int i = 1; i<n; ++i) x[sa[i]] = cmp(y, sa[i - 1], sa[i], j) ? p - 1 : p++;
	}
	for (int i = 1; i<n; ++i) rak[sa[i]] = i;
	int k = 0;
	for (int i = 0; i<n - 1; height[rak[i++]] = k) {
		if (k) --k;
		for (int j = sa[rak[i] - 1]; r[i + k] == r[j + k]; ++k);
	}
}
int n, r[MAXN], k;
bool check(int mid){
	int i = 1; //height[0] = 0;
	while (1){
		while (i <= n && height[i] < mid)    i++;
		if (i == n + 1) break;
		int cnt = 1;
		while (i <= n && height[i] >= mid)   i++, cnt++;
		if (cnt >= k) return true;
	}
	return false;
}
int main() {
	ios::sync_with_stdio(false);
	cin >> n >> k;
	for (int i = 0; i < n; ++i) cin >> r[i], r[i]++;
	r[n] = 0;
	SA(r, n + 1, 176);
	int l = 1, r = n, ans;
	while (l<=r) {
		int mid = (r + l) >> 1;
		if (check(mid)) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	cout << ans;
	return 0;
}
