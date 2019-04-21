#include<bits/stdc++.h>
#define pb push_back
using namespace std;
typedef long long ll;
const int maxn=405;
const int maxm=305*405;
const int M=998244353;
ll f[maxm],nf[maxm],inv[maxm],p2[maxm];
ll dp[maxn][maxn][3],d[2][maxn],t[maxn],v[maxn],tot;
int n,m,sz[maxn];
vector <int> h[maxn];
typedef vector<int> VI;
struct cmp {
    bool operator()(const VI u,const VI v){
        return u.size()>v.size();
    }
};
priority_queue <VI, vector<VI>, cmp > pq;
namespace fft{
    struct num{
        double x,y;
        num() {x=y=0;}
        num(double x,double y):x(x),y(y){}
    };
    inline num operator+(num a,num b) {return num(a.x+b.x,a.y+b.y);}
    inline num operator-(num a,num b) {return num(a.x-b.x,a.y-b.y);}
    inline num operator*(num a,num b) {return num(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);}
    inline num conj(num a) {return num(a.x,-a.y);}
    int base=1;
    vector<num> roots={{0,0},{1,0}};
    vector<int> rev={0,1};
    const double PI=acosl(-1.0);
    void ensure_base(int nbase){
        if (nbase<=base) return;
        rev.resize(1<<nbase);
        for (int i=0;i<(1<<nbase);i++)
            rev[i]=(rev[i>>1]>>1)+((i&1)<<(nbase-1));
        roots.resize(1<<nbase);
        while (base<nbase){
            double angle=2*PI/(1<<(base+1));
            for (int i=1<<(base-1);i<(1<<base);i++){
                roots[i<<1]=roots[i];
                double angle_i=angle*(2*i+1-(1<<base));
                roots[(i<<1)+1]=num(cos(angle_i),sin(angle_i));
            }
            base++;
        }
    }
    void fft(vector<num> &a,int n=-1){
        if (n==-1) n=a.size();
        assert((n&(n-1))==0);
        int zeros=__builtin_ctz(n);
        ensure_base(zeros);
        int shift=base-zeros;
        for (int i=0;i<n;i++)
            if (i<(rev[i]>>shift))
                swap(a[i],a[rev[i]>>shift]);
        for (int k=1;k<n;k<<=1){
            for (int i=0;i<n;i+=2*k){
                for (int j=0;j<k;j++){
                    num z=a[i+j+k]*roots[j+k];
                    a[i+j+k]=a[i+j]-z;
                    a[i+j]=a[i+j]+z;
                }
            }
        }
    }
    vector<num> fa,fb;
    vector <int> multiply_mod(vector<int> &a,vector<int> &b,int m,int eq=0){
        int need=a.size()+b.size()-1;
        int nbase=0;
        while ((1<<nbase)<need) nbase++;
        ensure_base(nbase);
        int sz=1<<nbase;
        if (sz>(int)fa.size()) fa.resize(sz);
        for (int i=0;i<(int)a.size();i++){
            int x=(a[i]%m+m)%m;
            fa[i]=num(x&((1<<15)-1),x>>15);
        }
        fill(fa.begin()+a.size(),fa.begin()+sz,num{0,0});
        fft(fa,sz);
        if (sz>(int)fb.size()) fb.resize(sz);
        if (eq) copy(fa.begin(),fa.begin()+sz,fb.begin());
        else{
            for (int i=0;i<(int)b.size();i++){
                int x=(b[i]%m+m)%m;
                fb[i]=num(x&((1<<15)-1),x>>15);
            }
            fill(fb.begin()+b.size(),fb.begin()+sz,num{0,0});
            fft(fb,sz);
        }
        double ratio=0.25/sz;
        num r2(0,-1),r3(ratio,0),r4(0,-ratio),r5(0,1);
        for (int i=0;i<=(sz>>1);i++){
            int j=(sz-i)&(sz-1);
            num a1=(fa[i]+conj(fa[j]));
            num a2=(fa[i]-conj(fa[j]))*r2;
            num b1=(fb[i]+conj(fb[j]))*r3;
            num b2=(fb[i]-conj(fb[j]))*r4;
            if (i!=j){
                num c1=(fa[j]+conj(fa[i]));
                num c2=(fa[j]-conj(fa[i]))*r2;
                num d1=(fb[j]+conj(fb[i]))*r3;
                num d2=(fb[j]-conj(fb[i]))*r4;
                fa[i]=c1*d1+c2*d2*r5;
                fb[i]=c1*d2+c2*d1;
            }
            fa[j]=a1*b1+a2*b2*r5;
            fb[j]=a1*b2+a2*b1;
        }
        fft(fa,sz);fft(fb,sz);
        vector <int> res(need);
        for (int i=0;i<need;i++){
            ll aa=fa[i].x+0.5;
            ll bb=fb[i].x+0.5;
            ll cc=fa[i].y+0.5;
            res[i]=(aa+((bb%m)<<15)+((cc%m)<<30))%m;
        }
        return res;
    }
    vector<int> square_mod(vector<int> &a,int m){
        return multiply_mod(a,a,m,1);
    }
};

void dfs(int u,int fa){
    //cout<<u<<' '<<fa<<endl;
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
    //freopen("large.out","w",stdout);
    inv[1]=nf[0]=f[0]=p2[0]=1;
    for (int i=2;i<maxm;i++) inv[i]=M-(M/i)*inv[M%i]%M;
    for (int i=1;i<maxm;i++) f[i]=f[i-1]*i%M,nf[i]=nf[i-1]*inv[i]%M,p2[i]=p2[i-1]*2%M;
    cin >> n;
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
        vector <int> vp; vp.resize(m+1); vp[0]=0;
        for (int j=1;j<=m;j++) vp[j]=v[j]*nf[j]%M;
        pq.push(vp);
    }
    while (pq.size()>1){
        VI u=pq.top(); pq.pop();
        VI v=pq.top(); pq.pop();
        VI w=fft::multiply_mod(u,v,M);
        pq.push(w);
    }
    VI s=pq.top();
    ll ans=0;
    for (int j=0;j<s.size();j++) (ans+=s[j]*f[j])%=M;
    cout << (ans+M)%M << endl;
}
