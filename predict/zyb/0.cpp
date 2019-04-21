#include<bits/stdc++.h>
using namespace std;
#define M 100005
#define N 50005

#define pb push_back
int T,n,m,q[M],tot;
map<int,int>ma;
struct node {
    int id,t,x,y;
}b[M];
struct pa {
    int x,y;
};
vector<pa>A[M],B[M];
vector<int>C[M],D[M];
bitset<N>ans[N],die[N*2],Ans;
int nx[N],ny[N];
inline bool check(int x,int y) {
    if (!C[x].size()) return true;
    if (y!=C[x][C[x].size()-1]) return true;
    return false;
}
inline int find(int x,int t) {
    int l=0,r=C[x].size()-1,s=0;
    while (l<=r) {
        int mid=(l+r)>>1;
        if (t>=C[x][mid]) s=mid,l=mid+1;
        else r=mid-1;
    }
    return s;
}
inline int Find(int x,int t) {
    int l=0,r=C[x].size()-1,s=C[x].size();
    while (l<=r) {
        int mid=(l+r)>>1;
        if (t<=C[x][mid]) s=mid,r=mid-1;
        else l=mid+1;
    }
    return s;
}
inline void work(int x,int nx,int y,int ny) {
    int X=D[x][nx];
    if (nx+1<C[x].size()) {
        if (ny<C[y].size())
        die[X]=die[X]|die[D[x][nx+1]]|die[D[y][ny]];
        else die[X]=die[X]|die[D[x][nx+1]],die[X][y]=1;
    }
    else {
        if (ny<C[y].size())
        die[X]=die[X]|die[D[y][ny]];
        else die[X][y]=1;
        die[X][x]=1;
    }
}
inline bool cmp(node x,node y) {
    return x.t<y.t;
}
int main() {
    //freopen("0.in","r",stdin);
    scanf("%d%d%d",&T,&n,&m);
    for (int i=1;i<=m;i++) {
        scanf("%d%d%d%d",&b[i].id,&b[i].t,&b[i].x,&b[i].y);
        q[i]=b[i].t;
    }
    sort(q+1,q+1+m);
    q[0]=q[1]-1;
    for (int i=1;i<=m;i++) if (q[i]!=q[i-1]) ma[q[i]]=++tot;//,t[tot]=;
    for (int i=1;i<=m;i++) b[i].t=ma[b[i].t];
    sort(b+1,b+1+m,cmp);
    int mm=m;
    for (int i=1;i<=m;i++) {
        if (b[i].id==0) {
            A[b[i].t].pb(pa{b[i].x,b[i].y});
            if (check(b[i].x,b[i].t)) C[b[i].x].pb(b[i].t);
        }
        else B[b[i].t].pb(pa{b[i].x,b[i].y});
    }
    int nn=0;
    for (int i=1;i<=n;i++)
    for (int j=0;j<C[i].size();j++) D[i].pb(++nn);
    //for (int i=1;i<=n;i++) die[i][i]=1;
    for (int i=1;i<=n;i++) nx[i]=C[i].size();
    for (int i=tot;i;i--) {
        //for (auto p:A[i]) tmp[p.x]=die[p.x],tmp[p.y]=die[p.y];
        for (auto p:A[i])
        ny[p.y]=nx[p.y];
        for (auto p:A[i]) {
            int s=find(p.x,i);
            nx[p.x]=s;
            //s=find(p.y,i+1);

        }
        for (auto p:A[i]) work(p.x,nx[p.x],p.y,ny[p.y]);
        //for (auto dp:B[i]) ans[p.x]=ans[p.x]|die[p.y],ans[p.y]=ans[p.y]|die[p.x];
    }
    for (int i=1;i<=tot+1;i++) {
        for (auto p:A[i-1]) {
            int s=find(p.x,i-1);
            die[D[p.x][s]]=ans[p.x];
        }
        for (auto p:A[i-1]) {
            int s=find(p.x,i-1);
            ans[p.y]=ans[p.y]|die[D[p.x][s]];
        }
        for (auto p:B[i]) {
            int s=Find(p.y,i);
            if (s<C[p.y].size()) ans[p.x]=ans[p.x]|die[D[p.y][s]];
            else ans[p.x][p.y]=1;
            s=Find(p.x,i);
            if (s<C[p.x].size()) ans[p.y]=ans[p.y]|die[D[p.x][s]];
            else ans[p.y][p.x]=1;
        }
    }
    for (int i=1;i<=n;i++) if (ans[i][i]) Ans[i]=1;
    for (int i=1;i<n;i++) {
        if (Ans[i]) printf("0 ");
        else printf("%d ",n-1-(int)(ans[i]|Ans).count());
    }
    if (Ans[n]) printf("0\n");
    else printf("%d\n",n-1-(int)(ans[n]|Ans).count());
}



