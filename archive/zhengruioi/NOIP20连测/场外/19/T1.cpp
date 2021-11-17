/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <scoped_allocator>
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
template <typename T>
inline void write(initializer_list<T> WRITE_NUMS, char ch) {
  for (auto i : WRITE_NUMS) {
    write(i);
    putchar(ch);
  }
}

const long long maxN = 1090;
long long totN;
// long long nums[maxN][7];

struct Num {
  long long val[7];
  long long *operator[](long long b) { return &val[b]; }
} A[maxN], B[maxN];

bool operator<(Num a, Num b) {
  for (int i = 1; i <= 6; ++i) {
    if (a.val[i] != b.val[i]) {
      return a.val[i] < b.val[i];
    }
  }
  return false;
}

bool operator==(Num a, Num b) {
  for (int i = 1; i <= 6; ++i) {
    if (a.val[i] != b.val[i]) {
      return false;
    }
  }
  return true;
}
bool operator!=(Num a, Num b) { return !(a == b); }

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= 6; ++j) {
      A[i].val[j] = read();
    }
    for (int j = 1; j <= 6; ++j) {
      A[i].val[j] -= read();
    }
  }
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= 6; ++j) {
      B[i].val[j] = read();
    }
    for (int j = 1; j <= 6; ++j) {
      B[i].val[j] -= read();
    }
  }
  for (int i = 2; i <= totN; ++i) {
    for (int j = 1; j <= 6; ++j) {
      A[i].val[j] = A[i].val[j] + A[i - 1].val[j];
      B[i].val[j] = B[i].val[j] + B[i - 1].val[j];
    }
  }
  sort(A + 1, A + totN);
  sort(B + 1, B + totN);
  for (int i = 1; i <= totN; ++i) {
    if (A[i] != B[i]) {
      puts("No");
      return 0;
    }
  }
  puts("Yes");
  return 0;
} // Thomitics Code