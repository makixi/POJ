#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int maxn = 200002;
int sa[maxn], rank[maxn], height[maxn];
int wa[maxn], wb[maxn], wv[maxn], wd[maxn];
int cmp(int *r, int a, int b, int l){
    return r[a] == r[b] && r[a+l] == r[b+l];
}
void da(int *r, int n, int m){          //  倍增算法 r为待匹配数组  n为总长度 m为字符范围
    int i, j, p, *x = wa, *y = wb, *t;
    for(i = 0; i < m; i ++) wd[i] = 0;
    for(i = 0; i < n; i ++) wd[x[i]=r[i]] ++;
    for(i = 1; i < m; i ++) wd[i] += wd[i-1];
    for(i = n-1; i >= 0; i --) sa[-- wd[x[i]]] = i;
    for(j = 1, p = 1; p < n; j *= 2, m = p){
        for(p = 0, i = n-j; i < n; i ++) y[p ++] = i;
        for(i = 0; i < n; i ++) if(sa[i] >= j) y[p ++] = sa[i] - j;
        for(i = 0; i < n; i ++) wv[i] = x[y[i]];
        for(i = 0; i < m; i ++) wd[i] = 0;
        for(i = 0; i < n; i ++) wd[wv[i]] ++;
        for(i = 1; i < m; i ++) wd[i] += wd[i-1];
        for(i = n-1; i >= 0; i --) sa[-- wd[wv[i]]] = y[i];
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i ++)
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p - 1: p ++;
    }
}
void calheight(int *r, int n){           //  求height数组。
    int i, j, k = 0;
    for(i = 1; i <= n; i ++) rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i ++]] = k)
        for(k ? k -- : 0, j = sa[rank[i]-1]; r[i+k] == r[j+k]; k ++);
}
void solve(int n, int l1, int l2){
    int maxl = 0;
    for(int i = 2; i < n; i++)
        if(height[i] > maxl){
            if(sa[i-1] >= 0 && sa[i-1] < l1 && sa[i] > l1)
                maxl = height[i];
            if(sa[i] >= 0 && sa[i] < l1 && sa[i-1] > l1)
                maxl = height[i];
        }
    printf("%d\n", maxl);
}
int main(){
    char s1[maxn], s2[maxn];
    int s[maxn], r[maxn];
    scanf("%s%s", s1, s2);
    int l1 = strlen(s1), l2 = strlen(s2);
    int n = 0;
    for(int i = 0; i < l1; i++)s[n++] = (s1[i]-'a'+1);
    s[n++] = 28;
    for(int i = 0; i < l2; i++)s[n++] = (s2[i]-'a'+1);
    s[n] = 0;
    da(s,n+1,30);
    calheight(s,n);
    solve(n, l1, l2);
    return 0;
}
