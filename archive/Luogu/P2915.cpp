/**************************************************************
 * Problem: Luogu P2915
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm: 状压DP
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
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

const long long maxN = 17;
long long totN;
long long totK;
long long nums[maxN];
long long DP[1 << maxN][maxN];
long long totANS;

int main() {
  totN = read();
  totK = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    DP[1 << (i - 1)][i] = 1;
  }
  for (int i = 2; i < (1 << totN); ++i) {
    for (int j = 1; j <= totN; ++j) {
      if (!(i & (1 << (j - 1)))) {
        continue;
      }
      for (int k = 1; k <= totN; ++k) {
        if (!(i & (1 << (k - 1))) || j == k || abs(nums[j] - nums[k]) <= totK) {
          continue;
        }
        DP[i][j] += DP[i ^ (1 << (j - 1))][k];
      }
    }
  }
  for (int i = 1; i <= totN; ++i) {
    totANS += DP[(1 << totN) - 1][i];
  }
  write(totANS);
  return 0;
} // Thomitics Code