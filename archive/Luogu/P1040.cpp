/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
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
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

const long long maxN = 90;
long long totN;
long long val[maxN];
long long DP[maxN][maxN];
long long rot[maxN][maxN];

void prnt(long long x, long long y) {
  if (x > y) {
    return;
  }
  write(rot[x][y]);
  putchar(' ');
  if (x == y) {
    return;
  }
  prnt(x, rot[x][y] - 1);
  prnt(rot[x][y] + 1, y);
}

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    val[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    DP[i][i] = val[i];
    DP[i][i - 1] = 1;
    rot[i][i] = i;
  }
  for (int len = 1; len < totN; ++len) {
    for (int i = 1; i + len <= totN; ++i) {
      int j = i + len;
      DP[i][j] = val[i] + DP[i + 1][j];
      rot[i][j] = i;
      for (int k = i + 1; k < j; ++k) {
        if (DP[i][j] <= DP[i][k - 1] * DP[k + 1][j] + val[k]) {
          rot[i][j] = k;
          DP[i][j] = DP[i][k - 1] * DP[k + 1][j] + val[k];
        }
      }
    }
  }
  write(DP[1][totN]);
  putchar('\n');
  prnt(1, totN);
  return 0;
} // Thomitics Code