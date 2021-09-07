/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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

const long long maxN = 590;
long long totN;
long long nums[maxN];
long long DP[maxN][maxN];

int main() {
  totN = read();
  for (int i = 1; i <= totN; i++) {
    nums[i] = read();
  }
  memset(DP, 0x3f, sizeof(DP));
  for (int i = 1; i <= totN; ++i) {
    DP[i][i] = 1;
  }
  for (int i = 1; i < totN; ++i) {
    DP[i][i + 1] = 1 + (nums[i] != nums[i + 1]);
  }
  for (int l = 3; l <= totN; ++l) {
    for (int i = 1; i + l - 1 <= totN; ++i) {
      long long j = i + l - 1;
      if (nums[i] == nums[j]) {
        DP[i][j] = min(DP[i][j], DP[i + 1][j - 1]);
      }
      for (int k = i; k < j; ++k) {
        DP[i][j] = min(DP[i][j], DP[i][k] + DP[k + 1][j]);
      }
    }
  }
  write(DP[1][totN]);
  return 0;
} // Thomitics Code