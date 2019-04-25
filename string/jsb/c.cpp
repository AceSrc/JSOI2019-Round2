#include<bits/stdc++.h>
#define N 2000005
using namespace std;

char s[N];int ans[N];
int getmin(int i,int j,int k,int n){
	while (i<n&&j<n&&k<n){
		int t=s[(i+k)%n]-s[(j+k)%n];
		if (!t) ++k;
		else {
			if (t>0) i+=k+1;else j+=k+1;
			j+=i==j;k=0;
		}
	}
	return min(i,j);
}

int main(){
    scanf("%s", s);
	int n=strlen(s);
	ans[1]=0;int p=1;
	int i=0,j=1,k=0;
	while (i<n&&j<n&&k<n){
		while (p<n&&j+k>=p+1) 
			++p,ans[p]=getmin(i,j,k,p);
		int t=s[(i+k)%n]-s[(j+k)%n];
		if (!t) ++k;
		else {
			if (t>0) i+=k+1;else j+=k+1;
			j+=i==j;k=0;
		}
	}
	ans[n]=min(i,j);
	for (int i=1;i<=n;i++)
		printf("%d%c",ans[i]+1,i==n?'\n':' ');
}
