#include <bits/stdc++.h>
using namespace std;

const int maxn = 100 + 7;
int T, n, m;
int x[maxn], t[maxn], y[maxn], o[maxn], action[maxn];
int tim[maxn], idx[maxn], id[maxn][maxn];
bool mat[maxn][maxn];

bool die(int t, int x) {
    return o[x] < t;
}

void search(int u) {
    if (u == n + 1) {
        bool flag = true;
        for (int i = 1; i <= m; i++) {
            if (action[i] == 0) {
                if (die(t[i], x[i]) && !die(t[i] + 1, y[i])) {
                    flag = false;
                    break;
                }
            }
            else {
                if (!die(t[i], x[i]) && !die(t[i], y[i])) {
                    flag = false;
                    break;
                }
            }
        }
        if (flag) {
            for (int i = 1; i <= n; i++) 
                for (int j = 1; j <= n; j++)
                    if (!die(T + 1, i) && !die(T + 1, j)) {
                        mat[i][j] = true;
                    }
        }
        return ;
    }
    for (int i = 0; i <= T + 1; i++) {
        o[u] = i;
        search(u + 1);
    }
}
int main(int argc, char **argv) {
    scanf("%d%d%d", &T, &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &action[i], &t[i], &x[i], &y[i]);
    }
    search(1);
    for (int i = 1; i <= n; i++) {
        int cnt = 0;
        for (int j = 1; j <= n; j++) 
            if (i != j &&  mat[i][j]) cnt++;
        printf("%d ", cnt);
    }
    puts("");
    return 0;
}
