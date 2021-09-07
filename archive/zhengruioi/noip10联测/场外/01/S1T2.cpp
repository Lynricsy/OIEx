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

const long long maxN = 1000090;
const long long MOD = 1e9 + 7;
long long totN;
long long totS;
bool Lef[maxN];
long long mul;
long long totANS = 1;

int main() {
  totN = read();
  totS = read();
  for (int i = 1, x; i <= totS; ++i) {
    x = read();
    Lef[x] = true;
  }
  if (totS) {
    mul = 1;
    for (int i = totN; i >= 1; --i) {
      if (!mul) {
        puts("0");
        return 0;
      }
      totANS *= mul;
      totANS %= MOD;
      if (!Lef[i]) {
        ++mul;
      } else {
        --mul;
      }
    }
  } else {
    for (int i = 1; i <= totN; ++i) {
      totANS *= i;
      totANS %= MOD;
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code