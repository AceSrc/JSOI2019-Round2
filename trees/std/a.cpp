#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 7;
const int mod = 998244353;
const int inv2 = (mod + 1) / 2;

int pow(int x, int times) {
    int rt = 1, base = x;
    while (times) {
        if (times & 1) rt = (long long)rt * base % mod;
        base = (long long)base * base % mod;
        times >>= 1;
    }
    return rt;
}

long long f[maxn][maxn][2], g[2][maxn][3];
long long candy[maxn][maxn], Str[maxn][maxn], ans[2];
int sz[maxn], m[maxn];
vector<int> e[maxn];


void dp(int u, int pre) {
    for (auto &v : e[u]) {
        if (v == pre) continue;
        dp(v, u);
    }

    int idx = 0;
    memset(g, 0, sizeof(g));
    g[idx][1][0] = 1; // top free
    g[idx][1][1] = 0; // top used and pointing up
    g[idx][1][2] = 0; // top used but not pointing up
    sz[u] = 1;
    for (auto &v : e[u]) {
        if (v == pre) continue;
        //if (u == 1) cout << g[idx][1][1] << endl;
        for (int j = 1; j <= sz[u]; j++) 
        for (int k = 1; k <= sz[v]; k++) {
            (g[idx ^ 1][j + k][0] += g[idx][j][0] * f[v][k][0]) %= mod;

            (g[idx ^ 1][j + k][1] += g[idx][j][1] * f[v][k][0]) %= mod;
            (g[idx ^ 1][j + k - 1][1] += g[idx][j][0] * f[v][k][1]) %= mod;

            (g[idx ^ 1][j + k][2] += g[idx][j][2] * f[v][k][0]) %= mod;
            (g[idx ^ 1][j + k - 1][2] += g[idx][j][1] * f[v][k][1] % mod * inv2) %= mod; 
            (g[idx ^ 1][j + k - 1][2] += g[idx][j][0] * f[v][k][1]) %= mod;
        }
        sz[u] += sz[v];
        idx ^= 1;
        memset(g[idx ^ 1], 0, sizeof(g[idx]));
    } 
    for (int j = 1; j <= sz[u]; j++) {
        f[u][j][0] = (g[idx][j][0] + g[idx][j][2]) % mod;
        f[u][j][1] = (g[idx][j][1] + g[idx][j][0] * 2 % mod) % mod;
    }
    //cout << u << endl;
    //for (int i = 1; i <= sz[u]; i++) cout << f[u][i][0] << ' ' << f[u][i][1] << endl;
}



long long step[maxn], inv[maxn];
long long C(int n, int m) {
    return step[n] * inv[m] % mod * inv[n - m] % mod;
}

int main(int argc, char **argv) {
    step[0] = 1;
    for (int i = 1; i < maxn; i++) step[i] = step[i - 1] * i % mod;
    inv[0] = inv[1] = 1;
    for (int i = 2; i < maxn; i++) inv[i] = mod - (mod / i) * inv[mod % i] % mod;
    for (int i = 2; i < maxn; i++) inv[i] = inv[i - 1] * inv[i] % mod;

    Str[0][0] = 1;
    for (int i = 1; i < maxn; i++) {
        for (int j = 1; j <= i; j++) 
            Str[i][j] = (Str[i - 1][j - 1] + Str[i - 1][j] * (i - 1 + j) % mod) % mod;
    }

    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &m[i]);
        for (int j = 1; j <= m[i]; j++) vector<int>().swap(e[j]);
        for (int j = 1, u, v; j < m[i]; j++) {
            scanf("%d%d", &u, &v);
            e[u].push_back(v);
            e[v].push_back(u);
        }
        dp(1, -1);
        for (int j = 1; j <= m[i]; j++) candy[i][j] = f[1][j][0];
    }

    //for (int i = 1; i <= n; i++) {
        //for (int j = 1; j <= m[i]; j++) cout << candy[i][j] << ' ';
        //cout << endl;
    //}

    int tot = 0;
    int idx = 0;
    memset(g, 0, sizeof(g));
    
    g[idx][0][0] = 1;

    int A = 0;

    for (int u = 1; u <= n; u++) {
        for (int i = 0; i <= tot; i++) 
        for (int j = 1; j <= m[u]; j++) 
        for (int k = 0; k < j; k++) 
        for (int flag = 0; flag < 2; flag++) {
            if (u != n) {
                (g[idx ^ 1][i + j - k][(k & 1) ^ flag] += g[idx][i][flag] * candy[u][j] % mod * Str[j][j - k]) %= mod;
            }
            else {
                if (i == 0) continue;
                long long coe = (Str[j - 1][j - k - 1] + Str[j - 1][j - k] * (j - k)) % mod;
                (ans[(k & 1) ^ flag] += g[idx][i][flag] * candy[u][j] % mod * coe % mod * step[i] % mod * C(i + j - k - 2, j - k - 1) % mod * step[j - k - 1]) %= mod;
            }
        }

        idx ^= 1;
        memset(g[idx ^ 1], 0, sizeof(g[idx ^ 1]));
        tot += m[u];

        //printf("%d\n");
        //for (int i = 1; i <= tot; i++) printf("%d %d\n", g[idx][i][0], g[idx][i][1]);
        //puts("");
                 
    }
    cout << ((ans[0] - ans[1]) % mod + mod) % mod << endl;
    return 0; 
}

