/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
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
long long nxt[maxN];
char A[maxN];
char B[maxN];
long long LenA;
long long LenB;

void pref() {
  long long j = 0;
  for (int i = 2; i <= LenB; ++i) {
    while (j && (B[i] != B[j + 1])) {
      j = nxt[j];
    }
    if (B[i] == B[j + 1]) {
      ++j;
    }
    nxt[i] = j;
  }
}

void K() {
  long long j = 0;
  for (int i = 1; i <= LenA; ++i) {
    while (j && (A[i] != B[j + 1])) {
      j = nxt[j];
    }
    if (A[i] == B[j + 1]) {
      ++j;
    }
    if (j == LenB) {
      write(i - LenB + 1);
      putchar('\n');
    }
  }
}

int main() {
  scanf("%s", A + 1);
  scanf("%s", B + 1);
  LenA = strlen(A + 1);
  LenB = strlen(B + 1);
  pref();
  K();
  for (int i = 1; i <= LenB; ++i) {
    write(nxt[i]);
    putchar(' ');
  }
  return 0;
} // Thomitics Code