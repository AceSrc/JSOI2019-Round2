#include <bits/stdc++.h>
using namespace std;

const int maxn = 1e6 + 7;

int n;
int pre[maxn];
char s[maxn];

bool Less(int i, int j, int End) {
     assert(i > j);
     // i + End - j + 1, 1
     int u = j + End - i + 1, v = 1;
     int len = pre[u];
     if (len < End - u + 1) {
        return s[v + len] < s[u + len];
     }

     u = 1, v = i - j + 1;
     len = pre[v]; 
     if (len < j - 1) {
         return s[v + len] < s[u + len];
     }
     return false;
}

int main(int argc, char **argv) {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    
    for (int i = 1; i < n; i++) 
        if (s[i] == s[i + 1]) pre[2]++;
        else break;

    int id = 2, last = 2 + pre[2] - 1;
    for (int i = 3; i <= n; i++) {
        int j = 0;
        if (last >= i) {
            j = min(last - i + 1, pre[i - id + 1]);
        }
        //if (i == 8) cout << id << ' ' << last << ' ' << last - id + 1 << endl;
        while (i + j <= n && s[1 + j] == s[i + j]) j++;
        pre[i] = j;
        if (i + pre[i] - 1 > last) {
            last = i + pre[i] - 1;
            id = i;
        }
    } 

    static int o[maxn];
    int sz = 0;
    for (int i = 1; i <= n; i++) {
        o[++sz] = i;

        int tail = 0;
        static int Stack[maxn];
        Stack[++tail] = o[1];
        for (int j = 2; j <= sz; j++) {
            while (tail >= 1 && s[i] < s[ i - o[j] + Stack[tail] ]) tail--;
            if (tail == 0 || s[i] == s[ i - o[j] + Stack[tail] ]) Stack[++tail] = o[j];
        }
        sz = 1;
        o[1] = Stack[1];
        for (int j = 2; j <= tail; j++) 
            if (i - Stack[j] < Stack[j] - o[sz]) o[++sz] = Stack[j];

        //printf("%d\n", sz);
        //for (int j = 1; j <= sz; j++) printf("%d ", o[j]);
        //puts("");

        int ans = o[1];
        for (int j = 2; j <= sz; j++) {
            if (Less(o[j], ans, i)) ans = o[j];
        }
        printf("%d", ans);
        if (i != n) putchar(' ');
        else putchar('\n');
    }
    return 0;
}


