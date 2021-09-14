/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <vector>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

using namespace std;

inline long long read() {
  long long x = 0;
  int f = 1;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-')
      f = -1;
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

const long long maxN = 1000090;
long long totT;
long long cnt[1090];
char str[maxN];
long long LEN;
vector<char> ans;
long long totANS;

int main() {
  freopen("letter.in", "r", stdin);
  freopen("letter.out", "w", stdout);
  totT = read();
  scanf("%s", str + 1);
  LEN = strlen(str + 1);
  for (int i = 1; i <= LEN; ++i) {
    ++cnt[str[i]];
  }
  for (char i = 35; i <= 125; ++i) {
    if (cnt[i] == totT) {
      ++totANS;
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code