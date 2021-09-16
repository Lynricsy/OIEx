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

const long long maxN = 10000090;
long long MOD;
long long totT;
long long phi[maxN];
long long primes[maxN];
bool flag[maxN];
long long cnt_primes;

void Euler(long long n) {
  phi[1] = 1;
  for (int i = 2; i <= n; ++i) {
    if (!flag[i]) {
      ++cnt_primes;
      primes[cnt_primes] = i;
      phi[i] = i - 1;
    }
    for (int j = 1; j <= cnt_primes && i * primes[j] <= n; ++j) {
      flag[i * primes[j]] = true;
      if (!(i % primes[j])) {
        phi[i * primes[j]] = phi[i] * primes[j];
        break;
      } else {
        phi[i * primes[j]] = phi[i] * phi[primes[j]];
      }
    }
  }
}
long long quick_pow(long long a, long long b, long long p) {
  long long ans = 1;
  long long base = a;
  while (b) {
    if (b & 1) {
      ans *= base;
      ans %= p;
    }
    base = (base * base) % p;
    b >>= 1;
  }
  return ans;
}
long long work(long long nowX) {
  if (nowX == 1) {
    return 0;
  }
  return quick_pow(2, work(phi[nowX]) + phi[nowX], nowX);
}

int main() {
  Euler(maxN - 5);
  totT = read();
  while (totT--) {
    MOD = read();
    write(work(MOD), '\n', 1);
  }
  return 0;
} // Thomitics Code
  // P4139