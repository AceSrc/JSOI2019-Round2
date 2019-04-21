#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int maxn=405;
const int maxm=5005;
const ll M=998244353;
ll f[maxm],nf[maxm],inv[maxm],p2[maxm];
ll dp[maxn][maxn][3],d[2][maxm],t[maxm],v[maxm],s[maxm],ss[maxm],tot;
int n,m,sz[maxn];
vector <int> h[maxn];
void dfs(int u,int fa){
    ll tmp[2][maxn][3];
    for (int o=0;o<2;o++)
    for (int i=0;i<3;i++)
    for (int j=0;j<=m;j++) tmp[o][j][i]=0;
    int o=0; tmp[0][0][0]=1;
    for (auto v:h[u]){
        if (v==fa) continue;
        dfs(v,u);
        for (int i=0;i<=sz[u];i++)
        for (int j=0;j<=sz[v];j++){
            ll res=dp[v][j][0]+dp[v][j][1]+dp[v][j][2];
            ll ret=dp[v][j][1]+dp[v][j][2]*2;
            (tmp[o^1][i+j][0]+=tmp[o][i][0]*res)%=M;
            (tmp[o^1][i+j][1]+=tmp[o][i][1]*res)%=M;
            (tmp[o^1][i+j][2]+=tmp[o][i][2]*res)%=M;
            (tmp[o^1][i+j][1]+=tmp[o][i][0]*ret)%=M;
            (tmp[o^1][i+j][2]+=tmp[o][i][1]*ret)%=M;
        }
        for (int i=0;i<=sz[u];i++) tmp[o][i][0]=tmp[o][i][1]=tmp[o][i][2]=0;
        sz[u]+=sz[v]; o^=1;
    }
    for (int i=0;i<=sz[u];i++){
        (dp[u][i+1][2]+=tmp[o][i][0])%=M;
        (dp[u][i][1]+=tmp[o][i][1])%=M;
        if (i) (dp[u][i-1][0]+=tmp[o][i][2]*inv[2])%=M;
    }
    sz[u]++;
}
ll C(ll x,ll y){
    return f[x]*nf[y]%M*nf[x-y]%M;
}

int main(){
    //freopen("large.in","r",stdin);
    inv[1]=nf[0]=f[0]=p2[0]=1;
    for (int i=2;i<maxm;i++) inv[i]=M-(M/i)*inv[M%i]%M;
    for (int i=1;i<maxm;i++) f[i]=f[i-1]*i%M,nf[i]=nf[i-1]*inv[i]%M,p2[i]=p2[i-1]*2%M;
    cin >> n; s[0]=1;
    for (int i=1;i<=n;i++){
        cin >> m;
        for (int j=1;j<=m;j++) vector<int>().swap(h[j]),sz[j]=0;
        for (int j=1;j<m;j++){
            int u,v;
            cin >> u >> v;
            h[u].pb(v); h[v].pb(u);
        }
        for (int j=1;j<=m;j++)
            for (int k=0;k<=m;k++)
                dp[j][k][0]=dp[j][k][1]=dp[j][k][2]=0;
        dfs(1,0);
        for (int j=1;j<=m;j++) t[j]=f[j]*(dp[1][j][0]+dp[1][j][1]+dp[1][j][2])%M;
        for (int j=0;j<=m;j++) v[j]=0;
        for (int j=1;j<=m;j++)
        for (int k=0;k<j;k++){
            if (k&1) (v[j-k]-=t[j]*C(j-1,k))%=M;
            else (v[j-k]+=t[j]*C(j-1,k))%=M;
        }
        for (int j=1;j<=m;j++) v[j]=v[j]*nf[j]%M;
        for (int j=0;j<=m+tot;j++) ss[j]=0;
        for (int j=0;j<=tot;j++)
            for (int k=1;k<=m;k++)
                (ss[j+k]+=s[j]*v[k])%=M;
        tot+=m;
        for (int j=0;j<=tot;j++) s[j]=ss[j];
    }
    ll ans=0;
    for (int j=0;j<=tot;j++) (ans+=s[j]*f[j])%=M;
    cout << (ans+M)%M << endl;
}
