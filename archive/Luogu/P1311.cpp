/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cmath>
#include <csetjmp>
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

const long long maxN = 190;
long long totN;
long long totK;
long long totP;
long long A[maxN];
long long B[maxN];
long long PREcol[59][maxN];
// long long PREcol[59];
long long totANS;
long long lst;

int main() {
  totN = read();
  totK = read();
  totP = read();
  for (int i = 1; i <= totN; ++i) {
    A[i] = read();
    B[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    for (int j = 0; j <= totK - 1; ++j) {
      PREcol[j][i] = PREcol[j][i - 1];
    }
    ++PREcol[A[i]][i];
    if (B[i] <= totP) {
      lst = i;
      totANS += PREcol[A[i]][lst] - 1;
    } else {
      totANS += PREcol[A[i]][lst];
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code