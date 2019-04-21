#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll M=1000000007;
bool f[25][25];
ll dp[1<<20][20];
int tot,n,m,color[25];

int main(){
    cin >> n;
    for (int i=1;i<=n;i++){
        cin >> m;
        for (int j=1;j<=m;j++) color[tot+j]=i;
        for (int j=1;j<m;j++){
            int u,v;
            cin >> u >> v;
            f[tot+u-1][tot+v-1]=1;
            f[tot+v-1][tot+u-1]=1;
        }
        tot+=m;
    }
    for (int i=1;i<=tot;i++)
        for (int j=1;j<=tot;j++)
            if (color[i]!=color[j]) f[i-1][j-1]=1;
    for (int i=0;i<tot;i++) dp[1<<i][i]=1;
    for (int i=1;i<(1<<tot);i++)
        for (int j=0;j<tot;j++) if (i&(1<<j))
        for (int k=0;k<tot;k++) if (!(i&(1<<k)))
            if (f[j][k]) (dp[i|(1<<k)][k]+=dp[i][j])%=M;
    ll ans=0;
    for (int j=0;j<tot;j++) (ans+=dp[(1<<tot)-1][j])%=M;
    cout << ans << endl;
}
