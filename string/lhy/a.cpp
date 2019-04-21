#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int M=998244353;
const int maxn=1000005;
const int E=10;
const ll base=19260817;
ll h[maxn],p[maxn],np[maxn],f[maxn];
char s[maxn];
set <int> S;
int n,m;
ll pow_(ll x,ll y){
    ll res=1;
    while (y){
        if (y&1) res=res*x%M;
        x=x*x%M; y>>=1;
    }
    return res;
}

ll hashval(int l,int r){
    --l;
    ll ret=(f[r]-f[l]*p[r-l])%M;
    return ret<0?ret+M:ret;
}

ll F(int x,int rl,int len){
    if (x+len-1<=rl) return hashval(x,x+len-1);
    int v=len-(rl-x+1);
    return (hashval(x,rl)*p[v]+hashval(1,v))%M;
}

int lcp(int x,int y,int rl){
    int l=0,r=rl+1;
    while (r-l>1){
        int mid=(l+r)>>1;
        if (F(x,rl,mid)==F(y,rl,mid)) l=mid; else r=mid;
    }
    return l;
}

bool cmp(int x,int y,int rl){
    if (x<=0) return x+1;
    int len=lcp(x,y,rl);
    if (len==rl) return x<y;
    return s[(x+len-1)%rl+1]<s[(y+len-1)%rl+1];
}

int nxt[maxn];
void kmp(char *s) {
    int n = strlen(s + 1);
    int p = 0;
    nxt[1] = 0;
    for (int i = 2; i <= n; i++) {
        while (p != 0 && s[i] != s[p + 1]) p = nxt[p];
        if (s[i] == s[p + 1]) p++;
        nxt[i] = p;
    }
}

int main(){
    scanf("%s",s+1);
    n=strlen(s+1);
    for (int i=1;i<=n;i++) f[i]=(f[i-1]*base+s[i])%M;
    np[0]=1; np[1]=pow_(base,M-2);
    for (int i=2;i<=n;i++) np[i]=np[i-1]*np[1]%M;
    p[0]=1; for (int i=1;i<=n;i++) p[i]=p[i-1]*base%M;

    kmp(s);
    for (int i=1;i<=n;i++){
        for (int j=max(1,i-E);j<=i;j++) if (S.find(j)==S.end()) S.insert(j);
        while (S.size()>E){
            int ret=0;
            for (auto x:S) if (cmp(ret,x,i)) ret=x;
            S.erase(ret);
        }
        int ret=-1;
        for (auto x:S) if (!cmp(ret,x,i)) ret=x;
        if (i % (i - nxt[i]) == 0) {
            ret %= (i - nxt[i]);
            if (ret == 0) ret = i - nxt[i];
        }
        printf("%d ",ret);
    }
    return 0;
}
