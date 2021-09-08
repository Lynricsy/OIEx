/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <future>
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
long long totN;
long long s[maxN];
long long totS = 1;
const long long MOD = 998244353;

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    for (int j = i; j <= totN; j += i) {
      ++s[j];
    }
  }
  s[1] = 1;
  for (int i = 2; i <= totN; ++i) {
    s[i] += totS;
    s[i] %= MOD;
    totS += s[i];
    totS %= MOD;
  }
  write(s[totN]);
  return 0;
} // Thomitics Code