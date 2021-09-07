/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <future>
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
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

const long long maxN = 10090;
long long totN;
long long totM;
long long A[maxN];
long long B[maxN];
vector<long long> E[maxN];
long long Deg[maxN];
long long last[maxN];
long long totANS;

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totM; ++i) {
    A[i] = read();
    B[i] = read();
    ++Deg[A[i]];
    ++Deg[B[i]];
  }
  for (int i = totM; i >= 1; --i) {
    long long u = A[i];
    long long v = B[i];
    if (Deg[u] > Deg[v]) {
      swap(u, v);
    }
    if (Deg[u] == Deg[v] && u > v) {
      swap(u, v);
    }
    E[u].push_back(v);
  }
  for (int i = 1; i <= totN; ++i) {
    for (auto v : E[i]) {
      last[v] = i;
    }
    for (auto v : E[i]) {
      for (auto w : E[v]) {
        if (last[w] == i) {
          ++totANS;
        }
      }
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code