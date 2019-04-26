#include<bits/stdc++.h>
#define P 998244353
using namespace std;
int jc[100005],ny[100005];
#define N 5005
inline int C(int x,int y) {
    if (x<y) return 0;
    return 1ll*jc[x]*ny[y]%P*ny[x-y]%P;
}
int f[N][N][4];
int q[N],A[N],B[N],si[N],fa[N],Next[2*N],to[2*N],last[N];
int n,F[N][4];
struct tree {
    int tot;
    int ans[N],A[N];
    int n;
    inline void add(int x,int y) {
        Next[++tot]=last[x]; last[x]=tot; to[tot]=y;
    }
    inline void build() {
        int l=0,r=1; q[1]=1;
        while (l<r) {
            int k=q[++l];
            si[k]=0;
            for (int i=last[k];i;i=Next[i]) {
                if (fa[k]==to[i]) continue;
                fa[q[++r]=to[i]]=k;
            }
        }
    }
    inline void dp() {
        for (int i=0;i<=n;i++)
        for (int j=0;j<=n;j++)
        for (int k=0;k<=2;k++) f[i][j][k]=0;
        for (int i=n;i;i--) {
            int x=q[i];
            int s=0,s1=0;
            si[x]=1;
            f[x][0][0]=1;
            for (int j=last[x];j;j=Next[j]) {
                if (fa[x]==to[j]) continue;
                int y=to[j];
                for (int k=0;k<=si[x]+si[y];k++)
                F[k][0]=F[k][1]=F[k][2]=0;
                for (int k=0;k<=si[x];k++)
                for (int l=0;l<=si[y];l++)
                for (int a=0;a<=2;a++)
                for (int b=0;a+b<=2&&b<=1;b++) (F[k+l][a+b]+=(1ll*f[x][k][a]*f[y][l][b])%P)%=P;
                for (int k=0;k<=si[x]+si[y];k++)
                for (int l=0;l<=2;l++) f[x][k][l]=F[k][l];
                si[x]+=si[y];
            }
            for (int k=0;k<=si[x];k++) F[k][0]=F[k][1]=0;
            for (int k=0;k<=si[x];k++) {
                (F[k+1][0]+=f[x][k][0])%=P;
                (F[k][1]+=f[x][k][0])%=P;
                (F[k][1]+=f[x][k][1])%=P;
                (F[k+1][0]+=2ll*f[x][k][1]%P)%=P;
                (F[k+1][0]+=2ll*f[x][k][2]%P)%=P;
            }
            for (int k=0;k<=si[x];k++) f[x][k][0]=F[k][0],f[x][k][1]=F[k][1];
        }
        for (int i=1;i<=n;i++) ans[i]=f[1][i][0];
    }
    inline void pre(int p) {
        for (int i=0;i<=n;i++) A[i]=0;
        for (int i=0;i<=n;i++)
        for (int k=0;k<=i-p;k++) {
            if (p) {
                if (k&1) (A[i-k]-=1ll*jc[i]*C(i-p,k)%P*ans[i]%P)%=P;
                else (A[i-k]+=1ll*jc[i]*C(i-p,k)%P*ans[i]%P)%=P;
            }
            else {
                if (k&1) (A[i-k]-=1ll*jc[i]*C(i+1,k)%P*ans[i]%P)%=P;
                else (A[i-k]+=1ll*jc[i]*C(i+1,k)%P*ans[i]%P)%=P;
            }
        }
    }
}a[N];
inline int work() {
    for (int i=1;i<=n;i++)
    a[i].pre(i!=1);
    memset(A,0,sizeof(A));
    A[0]=1;
    int S=0;
    for (int i=1;i<=n;i++) {
        for (int j=0;j<=S+a[i].n;j++) B[j]=0;
        for (int j=0;j<=S;j++)
        for (int k=0;k<=a[i].n;k++)
        (B[j+k]+=1ll*A[j]*a[i].A[k]%P*C(j+k,j)%P)%=P;
        S+=a[i].n;
        for (int j=0;j<=S+a[i].n;j++) A[j]=B[j];
    }
    int ans=0;
    for (int i=0;i<=S;i++) (ans+=A[i])%=P;
    return ans;
}
inline int quick(int x,int y) {
    int s=1;
    for (;y;y>>=1,x=1ll*x*x%P) if (y&1) s=1ll*s*x%P;
    return s;
}
int main() {
    jc[0]=1;
    for (int i=1;i<=10000;i++) jc[i]=1ll*jc[i-1]*i%P;
    for (int i=0;i<=10000;i++) ny[i]=quick(jc[i],P-2);
    scanf("%d",&n);
    for (int i=1;i<=n;i++) {
        scanf("%d",&a[i].n);
        for (int j=1;j<a[i].n;j++) {
            int x,y;
            scanf("%d%d",&x,&y);
            a[i].add(x,y);
            a[i].add(y,x);
        }
        a[i].build();
        a[i].dp();
        memset(last,0,sizeof(last));
    }
    if (n==1&&a[1].n>2) return puts("0"),0;
    for (int i=0;i<a[1].n;i++) a[1].ans[i]=a[1].ans[i+1];
    a[1].ans[a[1].n]=0;
    int ans=work();
    ans=(ans+P)%P;
    printf("%d\n",ans);
}
