#include <bits/stdc++.h>
using namespace std;

const int maxn = 21;
const int mod = 998244353;
int n;
int m[maxn];
int ans = 0;
int id[maxn];
int N = 0;
bool mat[maxn][maxn];

int o[maxn];
int sz;
void work(int u, int s) {
    for (int i = 1; i <= N; i++) {
        if (!mat[i][u]) continue;
        if (!((1 << (i - 1)) & s)) continue;
        if ((1 << (i - 1)) == s) {
            ans += mat[i][1];
            if (ans >= mod) ans -= mod;
            //if (mat[i][1]) {
                //for (int i = 1; i <= sz; i++) cout << o[i] << ' ';
                //cout << i << endl;
            //}
            continue;
        }
        o[++sz] = i;
        work(i, s - (1 << (i - 1)));
        sz--;
    }
}

int main(int argc, char **argv) {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &m[i]);
        for (int j = 2, u, v; j <= m[i]; j++) {
            scanf("%d%d", &u, &v);
            mat[u + N][v + N] = mat[v + N][u + N] = true;
        }
        for (int j = 1; j <= N; j++) {
            for (int k = 1; k <= m[i]; k++) {
                mat[j][k + N] = mat[k + N][j] = true;
            }
        }
        N += m[i];
    }
    o[++sz] = 1;
    work(1, (1 << N) - 2);
    cout << ans << endl;
    return 0;
}


