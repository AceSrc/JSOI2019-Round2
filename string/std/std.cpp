#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 7;
const int logmaxn = 20;

char s[maxn];

struct SA {
  int ra[maxn], rb[maxn], sa[maxn], height[maxn], rk[maxn];
  int sum[maxn];
  int _n;
  bool cmp(int *r, int a, int b, int j) {
    return r[a] == r[b] && r[a + j] == r[b + j];
  }

  void work(char *r, int &n, int m) {
    int *x = ra, *y = rb, *t, i, j, p;
    for (i = 0; i <= m; i++) sum[i] = 0;
    for (i = 0; i < n; i++) sum[ x[i] = r[i] ]++;
    for (i = 1; i <= m; i++) sum[i] += sum[i - 1];
    for (i = n - 1; i >= 0; i--) sa[ --sum[ x[i] ] ] = i;
    for (p = 0, j = 1; p < n; j <<= 1) {
      for (p = 0, i = n - j; i < n; i++) y[p++] = i;
      for (i = 0; i < n; i++) 
        if (sa[i] >= j) y[p++] = sa[i] - j;

      for (i = 0; i < m; i++) sum[i] = 0;
      for (i = 0; i < n; i++) sum[ x[i] ]++;
      for (i = 1; i < m; i++) sum[i] += sum[i - 1];
      for (i = n - 1; i >= 0; i--) 
        sa[ --sum[ x[ y[i] ] ] ] = y[i];

      t = x; x = y; y = t;
      p = 1; x[ sa[0] ] = 0;
      for (i = 1; i < n; i++) 
        if (cmp(y, sa[i - 1], sa[i], j)) x[ sa[i] ] = p - 1;
        else x[ sa[i] ] = p++;
      m = p;
    }
    int k = 0;
    n--;
    for (i = 0; i < n; i++) sa[i] = sa[i + 1];
    for (i = 0; i < n; i++) rk[ sa[i] ] = i;
    for (i = 0; i < n; height[ rk[i++] ] = k)
      for (k?k--:0, j = rk[i]? sa[ rk[i] - 1 ] : n; r[i + k] == r[j + k]; k++);
  }

  int bits[maxn];
  int lcp[maxn][logmaxn];
  void init_lcp(int n) {
    _n = n;
    for (int i = 0; i < n; i++) lcp[i][0] = height[i];
    for (int j = 1; (1 << j) < n; j++) 
      for (int i = (1 << j) - 1; i < n; i++) 
        lcp[i][j] = min(lcp[i][j - 1], lcp[i - (1 << (j - 1))][j - 1]);

    bits[0] = -1;
    for (int i = 1; i <= n; i++) bits[i] = bits[i / 2] + 1;
  }

  int LCP(int x, int y) {
    if (x == y) return _n - sa[x];
    if (x > y) swap(x, y);
    int l = bits[y - x];
    return min(lcp[y][l], lcp[x + (1 << l)][l]);
  }

} sa;

//d[n++] = 0;
//Forward.work(d, n, n);
//Forward.init_lcp(n);

set<int> pos, idx;

int End;
bool cmp(int a, int b) {
  if (a > b) return !cmp(b, a);
  int u = a + (End - b) + 1, v = 0, len = End - u + 1;
  //cout << u << ' ' << v << ' ' << len << ' ' << sa.LCP(u, v) << endl;
  if (sa.LCP(sa.rk[u], sa.rk[v]) < len) {
    return sa.rk[u] < sa.rk[v];
  }

  u = 0, v = len, len = a;
  if (sa.LCP(sa.rk[u], sa.rk[v]) < len) {
    return sa.rk[u] < sa.rk[v];
  }
  return a < b;
}

int main() {
  scanf("%s", s);
  int n = strlen(s);
  s[n++] = '\0';
  
  sa.work(s, n, 256);
  sa.init_lcp(n); 

  int t = 0;
  static int idx[22], Stack[maxn];
  for (int i = 0; i < n; i++) {
    idx[++t] = i;

    int _t = 0;
    Stack[++_t] = idx[1];
    for (int j = 2; j <= t; j++) {
        int u = sa.rk[ Stack[_t] ], v = sa.rk[ idx[j] ];
        int need_len = i - idx[j] + 1;
        int actual_len = sa.LCP(u, v);
        if (need_len > actual_len) {
            if (s[ Stack[_t] + actual_len ] > s[ idx[j] + actual_len] ) {
                _t = 1;
                Stack[_t] = idx[j];
            }
        }
        else {
            Stack[++_t] = idx[j];
        }
    }
    t = _t;
    for (int i = 1; i <= t; i++) idx[i] = Stack[i];

    static int o[maxn]; 
    int sz = 0;
    o[++sz] = idx[1];

    End = i;

    auto pre = 1;
    auto ptr = 1;
    for (ptr++; ptr <= t; pre = ptr, ptr++) {
        if (idx[ptr] - idx[pre] >= i - idx[ptr] + 1) {
            o[++sz] = idx[ptr];
        }
    }

    t = 0;
    for (int j = 1; j <= sz; j++) {
        idx[++t] = o[j];
    }

    sort(o + 1, o + 1 + sz, cmp);
    assert(sz <= 22);
    
    printf("%d", o[1] + 1);
    if (i != n - 1) printf(" ");
    else puts("");
  }
  return 0;
}





