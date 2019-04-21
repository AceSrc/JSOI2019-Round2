#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;

const int maxn = 50000 + 7;
const int maxm = 100000 + 7;

int N;
int token[maxm * 4];
int last[maxn], idx[maxm * 4];
int deg[maxm * 4];
map<Pair, int> mp;

int id(int t, int x, bool flag) {
    if (mp.count(Pair(x, t)) == 0) {
        idx[N] = x;
        idx[N + 1] = x;
        mp[Pair(x, t)] = N++;
        N++;
    } 
    if (flag) last[x] = max(last[x], t);
    return mp[Pair(x, t)] + flag;
}

vector<int> e[maxm * 4];
bitset<maxn> dead;
bitset<maxn> f[maxm], ans[maxn];
int manager;
void add(int t1, int x, int xflag, int t2, int y, int yflag) {
    int A = id(t1, x, xflag);
    int B = id(t2, y, yflag);
    deg[A]++;
    e[B].push_back(A);
}

int main(int argc, char **argv) {
    int T, n, m;
    scanf("%d%d%d", &T, &n, &m);
    while (m--) {
        int c;
        scanf("%d", &c);
        if (c == 0) {
            int t, x, y;
            scanf("%d%d%d", &t, &x, &y);
            add(t, x, false, t + 1, y, false);
            add(t + 1, y, true, t, x, true);
        }
        else {
            int t, x, y;
            scanf("%d%d%d", &t, &x, &y);
            add(t, x, true, t, y, false);
            add(t, y, true, t, x, false);
        }
    } 
    for (auto ptr = mp.begin(); ptr != mp.end(); ptr++) {
        auto t = ptr;
        t++;
        if (t == mp.end()) break;
        if (t->first.first == ptr->first.first) {
            deg[ptr->second]++;
            e[t->second].push_back(ptr->second);
            deg[t->second + 1]++;
            e[ptr->second + 1].push_back(t->second + 1);
        }
    }

    static int o[maxm * 4];
    static bool origin[maxm * 4];
    int h = 0, t = -1;
    for (int i = 0; i < N; i++) {
        if (deg[i] == 0) {
            o[++t] = i;        
            origin[i] = true;
        }
    }
    while (h <= t) {
        int u = o[h++];
        if (!(u & 1) && token[u]) f[ token[u] ].set(idx[u]);

        for (auto &v : e[u]) {
            if (!token[v]) {
                token[v] = ++manager;
            }
            if (token[u]) f[ token[v] ] |= f[ token[u] ];
            else if (!(u & 1)) f[ token[v] ].set(idx[u]);
            deg[v]--;
            if (deg[v] == 0) o[++t] = v;
        }
    }

    for (int i = 1; i < N; i += 2) 
        if (token[i]) ans[ idx[i] ] |= f[ token[i] ];

    for (int i = 1; i <= n; i++) 
        if (ans[i][i]) dead.set(i);
    for (int i = 1; i <= n; i++) {
        if (last[i] == 0) printf("%d", n - 1 - (int)dead.count());
        else if (ans[i][i]) printf("0");
        else printf("%d", n - 1 - (int)(ans[i] | dead).count());
        if (i != n) printf(" ");
    }
    puts("");
    return 0;
}



