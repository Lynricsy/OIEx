/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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

const long long maxN = 50;
const long long maxM = 590;
long long totN;
long long totM;
long long val[maxN];
long long hav[5];
long long DP[maxN][maxN][maxN][maxN];

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totN; ++i) {
    val[i] = read();
  }
  for (int i = 1, x; i <= totM; ++i) {
    x = read();
    ++hav[x];
  }
  DP[0][0][0][0] = val[1];
  for (int i = 0; i <= hav[1]; ++i) {
    for (int j = 0; j <= hav[2]; ++j) {
      for (int k = 0; k <= hav[3]; ++k) {
        for (int l = 0; l <= hav[4]; ++l) {
          long long nowT = i + 2 * j + 3 * k + 4 * l + 1;
          if (i)
            DP[i][j][k][l] =
                max(DP[i][j][k][l], DP[i - 1][j][k][l] + val[nowT]);
          if (j)
            DP[i][j][k][l] =
                max(DP[i][j][k][l], DP[i][j - 1][k][l] + val[nowT]);
          if (k)
            DP[i][j][k][l] =
                max(DP[i][j][k][l], DP[i][j][k - 1][l] + val[nowT]);
          if (l)
            DP[i][j][k][l] =
                max(DP[i][j][k][l], DP[i][j][k][l - 1] + val[nowT]);
        }
      }
    }
  }
  write(DP[hav[1]][hav[2]][hav[3]][hav[4]]);
  return 0;
} // Thomitics Code