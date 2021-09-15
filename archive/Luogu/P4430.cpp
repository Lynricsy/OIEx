/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
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
const long long MOD = 9999991;
long long totN;
long long fac[maxN];

long long quick_pow(long long a, long long b) {
  long long ans = 1;
  long long base = a;
  while (b) {
    if (b & 1) {
      ans *= base;
      ans %= MOD;
    }
    base = (base * base) % MOD;
    b >>= 1;
  }
  return ans;
}
void prefix() {
  fac[0] = 1;
  for (int i = 1; i <= totN - 1; ++i) {
    fac[i] = fac[i - 1] * i % MOD;
  }
}

int main() {
  totN = read();
  prefix();
  write(quick_pow(totN, totN - 2) * fac[totN - 1] % MOD);
  return 0;
} // Thomitics Code