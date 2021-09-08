/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <csetjmp>
#include <cstdio>
#include <type_traits>
#include <utility>
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

const long long maxN = 100090;
long long totT;
long long totN;
bool nums[maxN];
long long Cm;
long long Cn;
long long fac[maxN];
const long long MOD = 998244353;
long long inv[maxN];

long long quick_pow(long long a, long long b) {
  if (a == 1) {
    return 1;
  }
  long long ans = 1;
  long long base = a;
  while (b) {
    if (b & 1) {
      ans *= base;
      ans %= MOD;
    }
    base *= base;
    base %= MOD;
    b >>= 1;
  }
  return ans;
}

void prefix() {
  fac[1] = fac[0] = 1;
  for (long long i = 2; i <= maxN - 2; ++i) {
    fac[i] = fac[i - 1] * i;
    fac[i] %= MOD;
    inv[i] = quick_pow(fac[i], MOD - 2);
  }
  inv[1] = inv[0] = 1;
}
long long C(long long n, long long m) {
  if (n < m) {
    swap(n, m);
  }
  return fac[n] * inv[n - m] % MOD * inv[m] % MOD;
}

int main() {
  prefix();
  totT = read();
  while (totT--) {
    totN = read();
    for (int i = 1; i <= totN; ++i) {
      nums[i] = getchar() - '0';
    }
    getchar();
    for (int i = 1; i <= totN; ++i) {
      if (!nums[i]) {
        ++Cn;
      } else if ((i + 1 <= totN) && nums[i + 1]) {
        ++Cn;
        ++Cm;
        ++i;
      }
    }
    write(C(Cn, Cm));
    putchar('\n');
    Cn = 0;
    Cm = 0;
  }
  return 0;
} // Thomitics Code