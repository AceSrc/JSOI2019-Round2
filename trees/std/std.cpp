#include <bits/stdc++.h>
using namespace std;

const int maxn = 5000 + 7;
const int mod = 998244353;
const int inv2 = (mod + 1) / 2;

//int pow(int x, int times) {
    //int rt = 1, base = x;
    //while (times) {
        //if (times & 1) rt = (long long)rt * base % mod;
        //base = (long long)base * base % mod;
        //times >>= 1;
    //}
    //return rt;
//}

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

    int tot = 0;
    int idx = 0;
    memset(g, 0, sizeof(g));
    
    g[idx][0][0] = 1;

    for (int u = 1; u <= n; u++) {
        static long long S[maxn][2];
        static long long O[maxn][2];
        memset(S, 0, sizeof(S));
        memset(O, 0, sizeof(O));
        for (int j = 1; j <= m[u]; j++) {
            for (int k = 0; k < j; k++) {
                (O[j - k][k & 1] += candy[u][j] * Str[j][j - k]) %= mod;
                long long coe = (Str[j - 1][j - k - 1] + Str[j - 1][j - k] * (j - k)) % mod;
                coe = coe * candy[u][j] % mod * step[j - k - 1] % mod;
                (S[j - k][k & 1] += coe) %= mod;
            }
        }

        for (int i = 0; i <= tot; i++) 
        for (int j_k = 1; j_k <= m[u]; j_k++) 
        for (int k_1 = 0; k_1 < 2; k_1++) 
        for (int flag = 0; flag < 2; flag++) {
            if (u != n) {
                (g[idx ^ 1][i + j_k][k_1 ^ flag] += g[idx][i][flag] * O[j_k][k_1]) %= mod;
            }
            else {
                if (i == 0) continue;
                (ans[k_1 ^ flag] += g[idx][i][flag] * S[j_k][k_1] % mod * step[i] % mod * C(i + j_k - 2, j_k - 1) % mod) %= mod;
            }
        }

        idx ^= 1;
        memset(g[idx ^ 1], 0, sizeof(g[idx ^ 1]));
        tot += m[u];
    }
    cout << ((ans[0] - ans[1]) % mod + mod) % mod << endl;
    return 0; 
}

