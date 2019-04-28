#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Pair;

const int maxn = 50000 + 7;
const int maxm = 100000 + 7;
//const int maxn = 7 + 1;
//const int maxm = 6 + 1;

bitset<maxn> f[maxn * 3];
stack<int> manager;

int N = 0;
int T, n, m, idx[maxm * 4], last[maxn];
int token[maxm * 4], ans_token[maxn];
map<Pair, int> mp;
vector<int> e[maxm * 4], rev[maxm * 4];

int id(int t, int x, bool flag) {
    if (mp.count(Pair(t, x)) == 0) {
        idx[N] = x;
        idx[N + 1] = x;
        mp[Pair(t, x)] = N++; 
        N++;
    }
    return mp[Pair(t, x)] + flag;
}

int action[maxm], t[maxm], x[maxm], y[maxm], alias[maxm * 4];
bool usable[maxm * 4];
void add(int t1, int x, bool xflag, int t2, int y, bool yflag) {
    assert(t1 >= 1 && t1 <= T);
    assert(t2 >= 1 && t2 <= T);
    assert(x <= n && y <= n);
    int A = id(t1, x, xflag);
    int B = id(t2, y, yflag);
    if (!yflag && !usable[B] && alias[B] != -1) B = alias[B];
    if (xflag && !usable[A] && alias[A] != -1) A = alias[A];
    e[A].push_back(B);
    rev[B].push_back(A);
}

int main(int argc, char **argv) {
    scanf("%d%d%d", &T, &n, &m);
    T++;
    for (int i = 1; i <= n + m + 2; i++) manager.push(i);
    for (int i = 1; i <= m; i++) {
        scanf("%d%d%d%d", &action[i], &t[i], &x[i], &y[i]);
        assert(x[i] <= n && y[i] <= n);
        assert(t[i] >= 1 && t[i] <= T);
        if (action[i] == 0) {
            usable[id(t[i], x[i], false)] = true;
            usable[id(t[i], x[i], true)] = true;
            id(t[i] + 1, y[i], false);
        }
        else {
            id(t[i], x[i], false);
            id(t[i], y[i], false);
        }
    }

    for (int i = 0; i < N; i++) alias[i] = -1;
    for (int i = 1; i <= n; i++) last[i] = -1;
    for (auto ptr = mp.rbegin(); ptr != mp.rend(); ptr++) {
        int u = ptr->second;
        alias[u] = last[ idx[u] ];
        if (alias[u] != -1) alias[u + 1] = alias[u] + 1; 
        else alias[u + 1] = -1;
        if (last[ idx[u] ] == -1) last[ idx[u] ] = u;
        if (usable[u]) last[ idx[u]] = u;
    }

    for (int i = 1; i <= m; i++) {
        if (action[i] == 0) {
            add(t[i], x[i], false, t[i] + 1, y[i], false);
            add(t[i] + 1, y[i], true, t[i], x[i], true);
        }
        else {
            add(t[i], x[i], true, t[i], y[i], false);
            add(t[i], y[i], true, t[i], x[i], false);
        }
    }

    for (int i = 1; i <= n; i++) last[i] = -1;
    for (auto ptr = mp.rbegin(); ptr != mp.rend(); ptr++) {
        int u = ptr->second;
        if (!usable[u]) continue;
        token[u] = manager.top(); manager.pop();
        f[ token[u] ].set(idx[u]);
        if (alias[u] != -1) f[ token[u] ] |= f[ token[ alias[u] ] ];
        for (auto &v : e[u]) {
            if (usable[v]) f[ token[u] ] |= f[ token[v] ];
            else if (alias[v] != -1) f[ token[u] ] |= f[ token[ alias[v] ] ];
            else f[ token[u] ].set(idx[v]);
        }
    }


    for (auto ptr = mp.begin(); ptr != mp.end(); ptr++) {
        int u = ptr->second;
        if (!usable[u]) continue;
        for (auto &v : rev[u]) {
            if (!(v & 1)) continue;
            if (token[v]) {
                f[ token[v] ] |= f[ token[u] ];
            }
            else {
                token[v] = manager.top(); manager.pop();
                f[ token[v] ] = f[ token[u] ];
            }
        }

        u++;
        if (!token[u]) {
            token[u] = token[u - 1]; 
            f[ token[u] ].reset();
        }
        else manager.push(token[u - 1]);
        token[u - 1] = 0;

        for (auto &v : e[u]) {
            if (v & 1) continue;
            if (token[v]) f[ token[u] ] |= f[ token[v] ];
            else if (!usable[v]) f[ token[u] ].set(idx[v]);
            //else assert(v == u - 1);
        }
    }


    for (auto ptr = mp.begin(); ptr != mp.end(); ptr++) {
        int u = ptr->second + 1;
        if (!token[u] && alias[u] != -1 && !usable[u]) continue;
        if (!token[u]) {
            token[u] = manager.top();
            manager.pop();
            f[token[u]].reset();
        }
        if (!usable[u] && alias[u] != -1) {
            f[ alias[u] ] = token[u];
            token[u] = 0;
            continue;
        }
        for (auto &v : e[u]) 
            if (!(v & 1)) {
                //if (u == 1) cout << u << ' ' << v << ' ' << idx[u] << ' ' << idx[v] << endl;
                f[ token[u] ].set(idx[v]);
            }
        for (auto &v : rev[u]) {
            if (!token[v]) {
                token[v] = manager.top(); manager.pop();
                f[ token[v] ].reset();
            }
            f[ token[v] ] |= f[ token[u] ];
        }
        if (alias[u] != -1) {
            if (token[ alias[u] ] == 0) {
                token[ alias[u] ] = manager.top(); 
                manager.pop();
                f[ token[ alias[u] ] ] = f[ token[u] ];
            }
            else f[ token[ alias[u] ] ] |= f[ token[u] ];
        }
    }
    
    for (auto ptr = mp.begin(); ptr != mp.end(); ptr++) {
        if (token[ptr->second + 1]) ans_token[ idx[ ptr->second + 1 ] ] = token[ ptr->second + 1 ]; 
    }


    //for (int i = 1; i <= n; i++) {
        //if (f[ ans_token[667] ][i] != f[ ans_token[i] ][667]) {
            //cout << f[ ans_token[667] ][i] << endl;
            //cout << f[ ans_token[i] ][667] << endl;
            //cout << i << ' ' << ans_token[i] << endl;
        //}
        //assert(f[ans_token[667]][i] == f[ans_token[i]][667]);
    //}
    
    int forbid = manager.top(); manager.pop();
    f[forbid].reset();
    for (int i = 1; i <= n; i++) 
        if (f[ ans_token[i] ][i]) f[ forbid ].set(i);

    for (int i = 1; i <= n; i++) {
        if (f[forbid][i]) printf("0");
        else if (!ans_token[i]) printf("%d", n - 1 - (int)f[forbid].count());
        else printf("%d", n - 1 - (int)(f[forbid] | f[ ans_token[i] ]).count());
        if (i != n) putchar(' ');
        else puts("");
    }
    return 0;
}




