/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <utility>
#include <vector>
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

const long long maxN = 1090;
long long totA;
long long totB;
long long totNUM;
long long Acnt;
vector<long long> V;
bool usd[maxN];
long long sum;
long long Asum;

int main() {
  totA = read();
  totB = read();
  for (int i = 1; sum + i <= totA + totB; ++i) {
    sum += i;
    ++totNUM;
  }
  for (int i = totNUM; i >= 1; --i) {
    if (Asum + i <= totA) {
      Asum += i;
      usd[i] = true;
      ++Acnt;
    }
  }
  write(Acnt, '\n', 1);
  for (int i = totNUM; i >= 1; --i) {
    if (usd[i]) {
      write(i, ' ', 1);
    }
  }
  putchar('\n');
  write(totNUM - Acnt, '\n', 1);
  for (int i = totNUM; i >= 1; --i) {
    if (!usd[i]) {
      write(i, ' ', 1);
    }
  }
  return 0;
} // Thomitics Code