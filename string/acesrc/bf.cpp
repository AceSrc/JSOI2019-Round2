#include <bits/stdc++.h>
using namespace std;

const int maxn = 1000000 + 7;
char s[maxn];
int MinimalRep(const char *s, int n) {
  int i = 0, j = 1;
  while (i < n && j < n) {
    int k = 0; 
    while (k < n && s[(i + k) % n] == s[(j + k) % n])
      k++;
    while (k >= n) break;
    if (s[(i + k) % n] > s[(j + k) % n])
      i = max(i + k + 1, j + 1);
    else j = max(i + 1, j + k + 1);
  }
  return min(i, j);
}

int main(int argc, char **argv) {
  scanf("%s", s);
  int n = strlen(s);
  for (int i = 0; i < n; i++) {
    printf("%d ", 1 + MinimalRep(s, i + 1));
  }
  puts("");
  return 0;
}
