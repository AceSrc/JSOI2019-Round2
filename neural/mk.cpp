#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef pair<int,int> pi;
typedef long long ll;
const int maxn=5555;
const ll M=998244353;
int tp;
int n,m;
pi a[maxn];
mt19937_64 gen;

void print_tree(int n){
    //return;
    cout << n << endl;
    random_shuffle(a+1,a+n);
    for (int i=1;i<n;i++)
        if (rand()%2) cout << a[i].F << ' ' << a[i].S << endl;
        else cout << a[i].S << ' ' << a[i].F << endl;
}

void random_tree(int n){
    for (int i=1;i<n;i++) a[i]=(pi){i+1,gen()%i+1};
    print_tree(n);
}

void binary_tree(int n){
    for (int i=1;i<n;i++) a[i]=(pi){i+1,(i+1)/2};
    print_tree(n);
}

void special_tree(int n){
    for (int i=1;i<n;i++) a[i]=(pi){i+1,i-(i+1)%2};
    print_tree(n);
}

void star_tree(int n){
    if (n<=60){
        for (int i=1;i<n;i++) a[i]=(pi){1,i+1};
    } else {
        for (int i=1;i<n-30;i++) a[i]=(pi){i,i+1};
        for (int i=n-30;i<n;i++) a[i]=(pi){i+1,gen()%i+1};
    }
    print_tree(n);
}

void line_tree(int n,int op=0){
    if (n<=20||op==1){
        for (int i=1;i<n;i++) a[i]=(pi){i,i+1};
    } else {
        for (int i=1;i<n-10;i++) a[i]=(pi){i,i+1};
        for (int i=n-10;i<n;i++) a[i]=(pi){i+1,gen()%i+1};
    }
    print_tree(n);
}

void Random_tree(int n){
    int x=gen()%5;
    //cout<<"H"<<x<<endl;
    //cout<<x<<endl;
    if (x==0) random_tree(n);
    else if (x==1) special_tree(n);
    else if (x==2) line_tree(n);
    else if (x==3) star_tree(n);
    else binary_tree(n);
}

int sz[maxn];
void fill_sz(int n,int m){
    assert(n>=m);
    for (int i=0;i<m;i++) n--,sz[i]=1;
    for (int i=0;i<n;i++) sz[gen()%m]++;
}

int main(int argc, char **argv){
    //special_tree(10);
    //freopen("large.in","w",stdout);
    assert(argc >= 2);
    freopen(argv[1], "w", stdout);
    int tp = atoi(argv[2]);
    gen.seed(tp * 10 + 9 +19260817);
    if (tp==21){
        // sample 1
        n=5; m=2;
        cout << m << endl;
        fill_sz(n,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp==22){
        // sample 2
        n=6; m=3;
        cout << m << endl;
        fill_sz(n,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp==1){
        // 5 point
        n=10; m=3;
        cout << m << endl;
        fill_sz(n,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp==2){
        // 5 point
        n=15; m=4;
        cout << m << endl;
        fill_sz(n,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp==3){
        // 5 point
        // 300 * (1~2 point) tree
        cout << 300 << endl;
        m=300;
        for (int i=0;i<m;i++) Random_tree(1+gen()%2);
    }
    if (tp==4 || tp == 5 || tp == 6){
        // 15 point
        // 300 * (1~3 point) tree
        cout << 300 << endl;
        m=300;
        for (int i=0;i<m;i++) Random_tree(1+gen()%3);
    }
    if (tp==7 || tp == 8 || tp == 9 || tp == 10){
        // 20 point
        // 50 * (50 point) tree
        cout << 50 << endl;
        m=50;
        for (int i=0;i<m;i++) Random_tree(50);
    }
    if (tp==11 || tp == 12 || tp == 13 || tp == 14){
        // 20 point
        // 300 * line_tree, sum(m)<=5000
        cout << 4 + 5 + 50 << endl;
        for (int i=0;i<2;i++) line_tree(1500,1);
        line_tree(800,1);
        line_tree(400,1);


        m = 5;
        fill_sz(700,m);
        for (int i=0;i<m;i++) line_tree(sz[i],1);
        m = 50;
        fill_sz(100,m);
        for (int i=0;i<m;i++) line_tree(sz[i],1);
    }
    if (tp >= 15 && tp <= 18){
        // 30 point
        // 300 * tree, sum(m)<=5000
        cout << 4 + 5 + 100 << endl;
        special_tree(1500);
        star_tree(1500);
        for (int i=0;i<2;i++) Random_tree(500);

        m = 5;
        fill_sz(800,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
        m = 100;
        fill_sz(200,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp == 19){
        // 5 point
        // 2 * tree, sum(m)<=5000
        cout << 2 << endl;
        star_tree(2500);
        line_tree(2500);
    }
    if (tp == 20) {
        // 5 point
        // 300 * tree, sum(m)<=5000
        m = 6;
        cout << m << endl;
        Random_tree(3500);
        fill_sz(1500, m - 1);
        for (int i = 0; i < m - 1; i++) Random_tree(sz[i]);
    }
}
