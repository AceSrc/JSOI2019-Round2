#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000 + 7;

int tot = 0;
int idx[maxn * maxn], tim[maxn * maxn];
int id[maxn][maxn];
vector<int> e[maxn * maxn];
bool vis[maxn * maxn];
bool mat[maxn][maxn];

void add(int x, int y) {
    e[x].push_back(y);
    e[y ^ 1].push_back(x ^ 1);
}

void bfs(int st, int K) {
    int h = 0, t = -1;
    static int o[maxn * maxn];
    o[++t] = st;
    vis[st] = true;
    while (h <= t) {
        int u = o[h++];
        if (!(u & 1)) mat[K][idx[u]] = true;
        for (auto &v : e[u]) {
            if (vis[v]) continue;
            o[++t] = v;
        }
    }
    for (int i = 0; i <= t; i++) 
        vis[ o[i] ] = false;
}

int main(int argc, char **argv) {
    int T, n, m;
    scanf("%d%d%d", &T, &n, &m);
    for (int i = 1; i <= T + 1; i++) 
        for (int j = 1; j <= n; j++) {
            tim[tot] = i;
            idx[tot] = j;
            id[i][j * 2 - 2] = tot++; // false
            tim[tot] = i;
            idx[tot] = j;
            id[i][j * 2 - 1] = tot++; // true
        }

    for (int i = 1; i <= T; i++) {
        for (int j = 1; j <= n; j++)
            add(id[i][2 * j - 2], id[i + 1][2 * j - 2]);
    }

    for (int i = 1; i <= m; i++) {
        int action, t, x, y;
        scanf("%d%d%d%d", &action, &t, &x, &y);
        if (action == 0) {
            add(id[t][2 * x - 2], id[t + 1][2 * y - 2]);
            //add(id[t + 1][2 * y - 1], id[t][2 * x - 1]);
        }
        else {
            add(id[t][2 * x - 1], id[t][2 * y - 2]);
            //add(id[t][2 * y - 1], id[t][2 * x - 2]);
        }
    }
    for (int i = 1; i <= n; i++) {
        bfs(id[T + 1][2 * i - 1], i);
    }
    
    static bool dead[maxn * maxn];
    for (int i = 1; i <= n; i++) 
        if (mat[i][i]) dead[i] = true;
    for (int i = 1; i <= n; i++) {
        if (mat[i][i]) printf("%d ", 0);
        else {
            int cnt = 0;
            for (int j = 1; j <= n; j++) 
                if (i != j && !dead[j] && !mat[i][j]) cnt++;
            printf("%d ", cnt);
        }
    }
    puts("");
    return 0;
}
