/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <map>
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
long long A[maxN];
long long B[maxN];
long long sumA[maxN];
long long sumB[maxN];
long long cntA;
long long cntB;
long long totANS;

bool cmp(long long a, long long b) { return a > b; }

int main() {
  freopen("apart.in", "r", stdin);
  freopen("apart.out", "w", stdout);
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    A[i] = read();
    B[i] = read();
  }
  sort(A + 1, A + totN + 1, cmp);
  sort(B + 1, B + totN + 1, cmp);
  for (int i = 1; i <= totN; ++i) {
    sumA[i] = sumA[i - 1] + A[i];
    sumB[i] = sumB[i - 1] + B[i];
  }
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= totN; ++j) {
      totANS = max(totANS, min(sumA[i] - (i + j) * 10, sumB[j] - (i + j) * 10));
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code