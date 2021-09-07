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

const long long MOD = 998244353;

long long totN;
long long totM;
long long A[109][2090];
long long sum[109];
long long DP[109][2090];
long long totANS = 1;

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= totM; ++j) {
      A[i][j] = read() % MOD;
      sum[i] += A[i][j];
      sum[i] %= MOD;
    }
  }
  for (int i = 1; i <= totN; ++i) {
    totANS *= (sum[i] + 1);
    totANS %= MOD;
  }
  totANS = (totANS - 1 + MOD) % MOD;
  for (int i = 1; i <= totM; ++i) {
    memset(DP, 0, sizeof(DP));
    DP[0][0] = 1;
    for (int t = 1; t <= totN; ++t) {
      for (int k = 0; k <= ((t - 1) << 1); ++k) {
        DP[t][k] = (DP[t][k] + DP[t - 1][k] * (sum[t] - A[t][i] + MOD)) % MOD;
        DP[t][k + 1] = (DP[t][k + 1] + DP[t - 1][k]) % MOD;
        DP[t][k + 2] = (DP[t][k + 2] + DP[t - 1][k] * A[t][i]) % MOD;
      }
    }
    for (int j = totN + 1; j <= totN * 2; ++j) {
      totANS = (totANS - DP[totN][j] + MOD) % MOD;
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code