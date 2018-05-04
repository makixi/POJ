#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <cstdlib>
#include <time.h>
using namespace std;
#define maxn 105
const int move_ma[8][2] = {///���ƶ�
    {-2, -1}, {-2, 1}, {-1, -2}, {1, -2},
    {-1, 2}, {1, 2}, {2, -1}, {2, 1}
};
const int no[4][2] = {///���
    {-1, 0}, {0, -1}, {0, 1}, {1, 0}
};
const int move_shuai[4][2] = {///���ƶ�
    {1, 0}, {-1, 0}, {0, 1}, {0, -1}
};
int Max[maxn][10][10], cnt[maxn][10][10];
int vis[maxn][10][10][2];
///�����λ�� �н�λ�� �ҽ�λ�� 0:������ 1:������
///״̬�µ�ʧ�ܲ���
///0��ʾ�ұ�ʤ
int out[maxn][10][10];
///������ ���״̬���״̬���ж����ֺϷ�״̬
struct node {
    int a, b, c;///��λ�� �н�λ�� �ҽ�λ��
    int id;///0:������ 1:������
    int step;///���״̬��ʧ�ܵĲ���
    node (int _a, int _b, int _c, int _id, int _s) {
        a = _a, b = _b, c = _c, id = _id, step = _s;
    }
};
queue <node> q;
bool balk (int now, int next, int i, int j) {
    int x = now/9, y = now%9;
    int xx = next/9, yy = next%9;
    for (int k = 0; k < 8; k++) 
        if (xx == x+move_ma[k][0] && yy == y+move_ma[k][1]) { 
            int xxx = x+no[k/2][0], yyy = y+no[k/2][1];
            if (xxx == i/3+7 && yyy == i%3+3) return 1;
            if (xxx == j/3 && yyy == j%3+3) return 1;
        }
    return 0;
}
int relation (int x, int y, int i, int j, int who) {
    ///0:�ұذ� 1:�ұ�ʤ 2:��һ��
    int x1 = i/3, y1 = i%3;///�н�
    int x2 = j/3, y2 = j%3;///��˧
    y1 += 3, y2 += 3;
    if (y1 == y2) {///�������(�м�û����) ʤ������
        if (y == y1) {
            if (x > x1+7 || x < x2) {
                if (who == 0) return 1;
                return 0;
            }
            else return 2;
        }
        if (who == 0) return 1;
        else return 0;
    }
    if (who == 1) {
        int d1 = abs (x-x2), d2 = abs (y-y2);
        if ((d1 == 1 && d2 == 2) || (d1 == 2 && d2 == 1))
            return 0;///������Ե�
        return 2;
    }
    ///����
    if (x > 2 || y < 3 || y > 5) return 2;//��������
    if (y == y2) {
        if (x2-x == 1) return 1;///���ҽ����²�
        if (x-x2 == 1) {///���ҽ����ϲ�
            if (y1 == y) return 2;///�ен��ı���
            return 1;
        }
        return 2;
    }
    if (x == x2 && abs (y-y2) == 1 && y <= 5 && y >= 3) {///���ҽ������Ҳ�
        if (y1 == y)return 2;///�ез����ı���
        return 1;
    }
    return 2;
}
int x, y, xx, yy, xxx, yyy;
int main () {
    while (!q.empty ()) q.pop ();
    memset (vis, -1, sizeof vis);
    memset (Max, 0, sizeof Max);
    memset (out, 0, sizeof out);
    memset (cnt, 0, sizeof cnt);
    for (int x = 0; x < 10; x++) 
		for (int y = 0; y < 9; y++) {///����λ��
        	for (int i = 0; i < 9; i++) {///�н�λ��
            	for (int j = 0; j < 9; j++) {///�ҽ�λ��
                	if ((y-3 == j%3 && x == j/3) || (y-3 == i%3 && x-7 == i/3)) continue;
                	int res0 = relation (x, y, i, j, 0);
                	int res1 = relation (x, y, i, j, 1);
                	if (!res0) vis[x*9+y][i][j][0] = 1, q.push (node (x*9+y, i, j, 0, 1));
                	else if (res0 == 1) vis[x*9+y][i][j][0] = 0;
                	if (!res1) vis[x*9+y][i][j][1] = 1, q.push (node (x*9+y, i, j, 1, 1));
                	else if (res1 == 1) vis[x*9+y][i][j][1] = 0;
                	for (int k = 0; k < 4; k++) {///������
                    	int next_x = j/3+move_shuai[k][0], next_y = j%3+move_shuai[k][1];
                   		if (next_x < 0 || next_x >= 3 || next_y < 0 || next_y >= 3) continue;
                    	if (next_x == x && next_y+3 == y) continue;///�����غϵ�״̬�Ѿ��������
                    	out[x*9+y][i][j]++;
                	}
            	}
        	}
    	}
    while (!q.empty ()) {
        node now = q.front (); q.pop ();
        int x = now.c/3, y = now.c%3;///��˧
        int ma_x = now.a/9, ma_y = now.a%9;///����
        if (now.id == 0) {///��һ���������� ��һ���ǵ�����
            for (int i = 0; i < 4; i++) {///���߽�
                int xx = now.b/3+move_shuai[i][0], yy = now.b%3+move_shuai[i][1];///��һ���н���λ��
                if (xx < 0 || xx >= 3 || yy < 0 || yy >= 3) continue;
                if (vis[now.a][xx*3+yy][now.c][1] != -1) continue;
                if (xx+7 == ma_x && yy+3 == ma_y) continue;///�н������غ�
                vis[now.a][xx*3+yy][now.c][1] = now.step+1;
                q.push (node (now.a, xx*3+yy, now.c, 1, now.step+1));
            }
            for (int i = 0; i < 8; i++) {
                int xx = ma_x+move_ma[i][0], yy = ma_y+move_ma[i][1];
                if (xx < 0 || xx >= 10 || yy < 0 || yy >= 9) continue;
                if (vis[xx*9+yy][now.b][now.c][1] != -1) continue;
                if (xx == now.b/3+7 && yy == now.b%3+3) continue;///�н������غ�
                if (xx == x && yy == y+3) continue;///�������˧���غ�
                if (balk (xx*9+yy, now.a, now.b, now.c)) continue;///���
                vis[xx*9+yy][now.b][now.c][1] = now.step+1;
                q.push (node (xx*9+yy, now.b, now.c, 1, now.step+1));
            }
        }
        else {///��һ����������
            for (int i = 0; i < 4; i++) {
                int xx = x+move_shuai[i][0], yy = y+move_shuai[i][1];///��һ���ҵ�λ��
                if (xx < 0 || xx >= 3 || yy < 0 || yy >= 3) continue;
                if (vis[now.a][now.b][xx*3+yy][0] != -1) continue;
                if (xx == ma_x && yy+3 == ma_y) continue;///��һ���������غ�
                Max[now.a][now.b][xx*3+yy] = max (Max[now.a][now.b][xx*3+yy], now.step);
                if (++cnt[now.a][now.b][xx*3+yy] == out[now.a][now.b][xx*3+yy]) {
                    vis[now.a][now.b][xx*3+yy][0] = Max[now.a][now.b][xx*3+yy]+1;
                    q.push (node (now.a, now.b, xx*3+yy, 0, vis[now.a][now.b][xx*3+yy][0]));
                }
            }
        }
    }   
	int t;
    cin >> t;
    int who;
    while (t--) {
        cin >> x >> y >> xx >> yy >> xxx >> yyy >> who;
        xx -= 7, yy -= 3;
        yyy -= 3;
        int res = vis[x*9+y][xx*3+yy][xxx*3+yyy][who];
        if (res == 0)  cout << "Lucky guy!" << endl;
        else  cout << "Lose in " << res << " steps T.T!" << endl;
    }
    return 0;
}
