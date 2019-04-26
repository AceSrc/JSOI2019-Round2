#pragma GCC optimize(3)
#include<bits/stdc++.h>
#define MAXN 50000
#define MAXM 100000
#define MAXT 1000000
#define INF 1000000000
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int,int> P;
typedef bitset<50000> bs;
int T,n,m;
int type[MAXM],t[MAXM],x[MAXM],y[MAXM];
vector<P> up[MAXM],down[MAXM],hori[MAXM];
vector<int> v;
bs tmp[MAXN];
bs dead;
vector<pair<int,bs> > vn[MAXM];
vector<pair<int,bs> > changed;
void run()
{
    int sz=(int)v.size();
    for(int i=0;i<m;i++)
    {
        if(type[i]==1) {hori[t[i]].push_back(P(y[i],x[i])); hori[t[i]].push_back(P(x[i],y[i]));}
        else 
        {
            up[t[i]].push_back(P(y[i],x[i]));
            down[t[i]].push_back(P(x[i],y[i]));
        }
    }
    for(int i=0;i<n;i++) tmp[i].reset(),tmp[i].set(i);
    for(int i=sz-1;i>=0;i--)
    {
        changed.clear(); changed.shrink_to_fit();
        for(int j=0;j<(int)up[i].size();j++)
        {
            int x=up[i][j].F,y=up[i][j].S;
            changed.push_back(make_pair(y,tmp[x]));
        }
        for(int j=0;j<(int)changed.size();j++) tmp[changed[j].F]|=changed[j].S;
        for(int j=0;j<(int)hori[i].size();j++)
        {
            int x=hori[i][j].F,y=hori[i][j].S;
            vn[i].push_back(make_pair(x,tmp[y]));
        }
    }
    for(int i=0;i<n;i++) tmp[i].reset();
    for(int i=0;i<sz;i++)
    {
        changed.clear(); changed.shrink_to_fit();
        for(int j=0;j<(int)vn[i].size();j++)
        {
            int x=vn[i][j].F;
            bs y=vn[i][j].S;
            tmp[x]|=y;
        }
        for(int j=0;j<(int)down[i].size();j++)
        {
            int x=down[i][j].F,y=down[i][j].S;
            changed.push_back(make_pair(y,tmp[x]));
        } 
        for(int j=0;j<(int)changed.size();j++) tmp[changed[j].F]|=changed[j].S;
    }
}
int main()
{
    scanf("%d%d%d",&T,&n,&m);
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d%d",&type[i],&t[i],&x[i],&y[i]);
        x[i]--; y[i]--;
        v.push_back(t[i]);
    }
    sort(v.begin(),v.end());
    v.erase(unique(v.begin(),v.end()),v.end());
    for(int i=0;i<m;i++) t[i]=lower_bound(v.begin(),v.end(),t[i])-v.begin();
    run();
    for(int i=0;i<n;i++) if(tmp[i].test(i)) dead.set(i);
    for(int i=0;i<n;i++) printf("%d%c",dead.test(i)?0:n-1-(int)(tmp[i]|dead).count(),i==n-1?'\n':' ');
    return 0;
}
