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
    gen.seed(time(0));
    if (tp/10==0) { // 10 v
        // 5 point
        n=rand() % 13 + 4; m=rand() % 4 + 1;
        cout << m << endl;
        fill_sz(n,m);
        for (int i=0;i<m;i++) Random_tree(sz[i]);
    }
    return 0;
}
