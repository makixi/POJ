#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
#define MAXN 22222
#define INF (1<<30)
int wa[MAXN], wb[MAXN], wv[MAXN], ws[MAXN];
int cmp(int *r, int a, int b, int l) {
	return r[a] == r[b] && r[a + l] == r[b + l];
}
int sa[MAXN], rak[MAXN], height[MAXN];
void SA(int *r, int n, int m) {
	int *x = wa, *y = wb;
	for (int i = 0; i<m; ++i) ws[i] = 0;
	for (int i = 0; i<n; ++i) ++ws[x[i] = r[i]];
	for (int i = 1; i<m; ++i) ws[i] += ws[i - 1];
	for (int i = n - 1; i >= 0; --i) sa[--ws[x[i]]] = i;
	int p = 1;
	for (int j = 1; p<n; j <<= 1, m = p) {
		p = 0;
		for (int i = n - j; i<n; ++i) y[p++] = i;
		for (int i = 0; i<n; ++i) if (sa[i] >= j) y[p++] = sa[i] - j;
		for (int i = 0; i<n; ++i) wv[i] = x[y[i]];
		for (int i = 0; i<m; ++i) ws[i] = 0;
		for (int i = 0; i<n; ++i) ++ws[wv[i]];
		for (int i = 1; i<m; ++i) ws[i] += ws[i - 1];
		for (int i = n - 1; i >= 0; --i) sa[--ws[wv[i]]] = y[i];
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
int n, a[MAXN], r[MAXN];
bool isok(int k) {
	bool flag = 0;
	int mx = -INF, mm = INF;
	for (int i = 2; i <= n; ++i) {
		if (height[i] >= k) {
			mm = min(mm, min(sa[i], sa[i - 1]));
			mx = max(mx, max(sa[i], sa[i - 1]));
			if (mx - mm>k) return 1;
		}
		else {
			mx = -INF, mm = INF;
		}
	}
	return 0;
}
int main() {
	while (~scanf("%d", &n) && n) {
		for (int i = 0; i<n; ++i) scanf("%d", a + i);
		--n;
		for (int i = 0; i<n; ++i) r[i] = a[i + 1] - a[i] + 88;//根据题意 仅根据变化序列 
		r[n] = 0;
		SA(r, n + 1, 176);
		int l = 0, r = n >> 1;
		while (l<r) {
			int mid = l + r + 1 >> 1;
			if (isok(mid)) l = mid;
			else r = mid - 1;
		}
		if (l >= 4) printf("%d\n", l + 1);
		else printf("%d\n", 0);
	}
	return 0;
}
