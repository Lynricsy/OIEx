/**************************************************************
 * Problem: codeforces 908G
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm: 数位DP
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
template <typename T> inline void write(T x, char ch = '\n', int tim = 0) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
  if (tim) {
    for (int i = 1; i <= tim; ++i) {
      putchar(ch);
    }
  }
}

const long long maxN = 709;
const long long MOD = 1E9 + 7;
long long LEN;
long long nowD;
long long totANS;
char NUM[maxN];
long long g[maxN][2];
long long DP[maxN][2];

void work() {
  memset(DP, 0, sizeof(DP));
  memset(g, 0, sizeof(g));
  g[0][1] = nowD;
  for (int i = 0; i < LEN; ++i) {
    for (int j = 0; j <= 1; ++j) {
      long long nowT = NUM[i + 1] - '0';
      for (int k = 0; k <= 9; ++k) {
        if (j && k > nowT) {
          break;
        }
        bool os = (j && k == nowT);
        if (k < nowD) {
          DP[i + 1][os] += DP[i][j];
          g[i + 1][os] += g[i][j];
        } else if (k == nowD) {
          DP[i + 1][os] += g[i][j] + DP[i][j] * 10;
          g[i + 1][os] += g[i][j];
        } else if (k > nowD) {
          DP[i + 1][os] += DP[i][j] * 10;
          g[i + 1][os] += g[i][j] * 10;
        }
        DP[i + 1][os] %= MOD;
        g[i + 1][os] %= MOD;
      }
    }
  }
  totANS += DP[LEN][0] + DP[LEN][1];
  totANS %= MOD;
}

int main() {
  scanf("%s", NUM + 1);
  LEN = strlen(NUM + 1);
  for (nowD = 1; nowD <= 9; ++nowD) {
    work();
  }
  write(totANS);
  return 0;
} // Thomitics Code