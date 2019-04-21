#include<bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef pair<int,int> pi;
typedef long long ll;
const int maxn=505;
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

void line_tree(int n){
    if (n<=20){
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
    assert(argc >= 3);
    //special_tree(10);
    freopen(argv[1], "w", stdout);
    auto tp = atoi(argv[2]);
    gen.seed(tp+19260817);
    if (tp/10==0) { // 10 v
        // 5 point
        n=10; m=3;
        cout << 3 << endl;
        fill_sz(n,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp/10==1) { // 20 v
        // 5 point
        n=20; m=5;
        cout << 5 << endl;
        fill_sz(n,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp/10==2) { // 20 v
        // 5 point
        n=20; m=5;
        cout << 5 << endl;
        fill_sz(n,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp/10==3) { // 300 v
        cout << 300 << endl;
        m=300;
        for (int i=0;i<m;i++) Random_tree(1);
    }
    if (tp/10==4) { // 600 v 
        cout << 300 << endl;
        m=300;
        for (int i=0;i<m;i++) Random_tree(1+gen()%2);
    }
    if (tp/10==5) { // 2500 v 
        m=1250;
        cout << m << endl;
        for (int i=0;i<m;i++) Random_tree(1+gen()%2);
    }
    if (tp/10==6){ // 2500 v
        cout << 50 << endl;
        m=50;
        for (int i=0;i<m;i++) Random_tree(50);
    }
    if (tp/10==7){ // 2500 v
        n = 2500, m = 300;
        cout << m << endl;
        fill_sz(n, m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    if (tp/10==8){ // 5000 v
        cout << 300 << endl;
        n=1000; m=290;
        fill_sz(n,m);
        for (int i=0;i<10;i++) line_tree(400);
        for (int i=0;i<m;i++) line_tree(sz[i]);
    }
    if (tp/10==9){ // 5000 v
        cout << 300 << endl;
        n=1000; m=290;
        fill_sz(n,m);
        for (int i=0;i<10;i++) Random_tree(400);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    //if (tp/10==7){ //  
        //// 10 point
        //cout << 300 << endl;
        //for (int i=0;i<300;i++) line_tree(400);
    //}
    //if (tp/10==8){
        //// 10 point
        //cout << 300 << endl;
        //for (int i=0;i<300;i++) Random_tree(400);
    //}
}



