/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <system_error>
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

const long long maxN = 10000090;
long long totN;
long long totK;
long long nums[maxN];
long long del[maxN];
long long CUR;
long long ptr;

int main() {
  totK = read();
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read() - i;
  }
  del[1] = nums[1];
  for (int i = 2; i <= totN; ++i) {
    del[i] = nums[i] - nums[i - 1];
  }
  ptr = totN;
  CUR = nums[totN];
  for (int i = 1, l, r, c; i <= totK; ++i) {
    if (i > 1) {
      l = read();
      r = read();
      c = read();
      del[l] += c;
      del[r + 1] -= c;
      if (ptr <= r && ptr >= l) {
        CUR += c;
      }
    }
    while (ptr > 1 && CUR > 0) {
      CUR -= del[ptr];
      --ptr;
    }
    if (CUR == 0) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
} // Thomitics Code