#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;

const int Ns = 50000 + 7;
const int maxn = (100000 + 7) * 4;
const int maxm = (100000 + 7) * 4;

int N;
int last[maxm], idx[maxm];
int deg[maxm];
bitset<Ns> V[Ns], dead;
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

vector<int> e[maxm];
void add(int t1, int x, int xflag, int t2, int y, int yflag) {
    int A = id(t1, x, xflag);
    int B = id(t2, y, yflag);
    e[A].push_back(B);
}

int T, n, m;
bool vis[maxn];
bool reachable[maxn];
int bfs(int st, int p) {
    static int o[maxn];
    int h = 0, t = -1;
    int rt = 0;
    o[++t] = st;
    vis[st] = true;
    while (h <= t) {
        int u = o[h++];
        //cout << u << ' ' << tim[u] << ' ' << idx[u] << endl;
        for (auto &v : e[u]) {
            if (vis[v]) continue;
            vis[v] = true;
            if (!(v & 1) && !reachable[ idx[v] ]) {
                assert(idx[v] <= n);
                V[p].set(idx[v]);
                rt++;
                reachable[ idx[v] ] = true;
            }
            o[++t] = v;
        }
    }
    if (reachable[ idx[st] ]) 
        rt = -1;
    for (int i = 0; i <= t; i++) {
        reachable[ idx[ o[i] ] ] = false;
        vis[ o[i] ] = false;
    }
    return rt;
}

int main(int argc, char **argv) {
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
            e[ptr->second].push_back(t->second);
            e[t->second + 1].push_back(ptr->second + 1);
        }
    }

    static int result[maxn];
    for (int i = 1; i <= n; i++) 
        if (last[i] != 0) {
            result[i] = bfs(id(last[i], i, true), i);
            if (result[i] == -1) {
                assert(i <= n);
                dead.set(i);
            }
        }

    //for (int i = 1; i <= n; i++) {
        //for (int j = 1; j <= n; j++) cout << V[i][j];
        //cout << endl;
    //}

    for (int i = 1; i <= n; i++) {
        if (last[i] == 0) printf("%d", n - 1 - (int)dead.count()); 
        else {
            if (result[i] == -1) printf("0");
            else printf("%d", n - 1 - (int)(V[i] | dead).count());
        }
        if (i != n) printf(" ");
    }
    puts("");
    return 0;
} 




