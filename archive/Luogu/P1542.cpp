/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cmath>
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

const long long maxN = 1090;
long long totN;
long long A[maxN];
long long B[maxN];
long long P[maxN];
long double L = 0;
long double R = 1E9;
long double Mid;
long double ANS;

bool check(long double x) {
  long double sum = 0;
  for (int i = 1; i <= totN; ++i) {
    sum += P[i] / x;
    if (sum > B[i]) {
      return false;
    }
    if (sum < A[i]) {
      sum = A[i];
    }
  }
  return true;
}

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    A[i] = read();
    B[i] = read();
    P[i] = read();
  }
  Mid = (L + R) / 2.0;
  while (R - L >= 0.000001) {
    Mid = (L + R) / 2.0;
    if (check(Mid)) {
      ANS = Mid;
      R = Mid;
    } else {
      L = Mid;
    }
  }
  printf("%.2Lf", ANS);
  return 0;
} // Thomitics Code