/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
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

const long long maxN = 10090;
long long LEN;
char str[maxN];
long long DP[maxN];
const long long MOD = 1E9 + 9;

int main() {
  DP[0] = 1;
  scanf("%s", str + 1);
  LEN = strlen(str + 1);
  for (int i = 1, l, r; i <= LEN; ++i) {
    if (str[i] != 'W') {
      l = i;
      r = i + 1;
      for (int j = i; l >= 1 and r <= LEN; ++j) {
        if (str[r] == 'B' || str[l] == 'W') {
          break;
        }
        DP[r] += DP[l - 1];
        DP[r] %= MOD;
        --l;
        ++r;
      }
    }
  }
  write(DP[LEN]);
  return 0;
} // Thomitics Code