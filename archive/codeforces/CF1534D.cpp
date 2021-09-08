/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <set>
#include <system_error>
#include <tr1/unordered_set>
#include <utility>
#include <vector>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

using namespace std;
using namespace tr1;

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
long long jcnt;
long long ocnt;
bool isO[maxN];
bool isJ[maxN];
struct Edge {
  long long from;
  long long to;
} edges[maxN];
long long cnt_edges;
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].from = u;
  edges[cnt_edges].to = v;
}
// set<pair<int, int>> S;
vector<long long> V[maxN];

int main() {
  totN = read();
  putchar('?');
  putchar(' ');
  putchar('1');
  putchar('\n');
  fflush(stdout);
  for (int i = 1, x; i <= totN; ++i) {
    x = read();
    if (x & 1) {
      ++jcnt;
      isJ[i] = true;
    } else {
      ++ocnt;
      isO[i] = true;
    }
    if (x == 1) {
      V[1].push_back(i);
    }
  }
  if (jcnt < ocnt) {
    for (int i = 2, x; i <= totN; ++i) {
      if (isJ[i]) {
        putchar('?');
        putchar(' ');
        write(i);
        putchar('\n');
        fflush(stdout);
        for (int j = 1; j <= totN; ++j) {
          x = read();
          if (x == 1) {
            V[i].push_back(j);
          }
        }
      }
    }
  } else {
    for (int i = 2, x; i <= totN; ++i) {
      if (isO[i]) {
        putchar('?');
        putchar(' ');
        write(i);
        putchar('\n');
        fflush(stdout);
        for (int j = 1; j <= totN; ++j) {
          x = read();
          if (x == 1) {
            V[i].push_back(j);
          }
        }
      }
    }
  }
  putchar('!');
  putchar('\n');
  fflush(stdout);
  // for (auto i : S) {
  //   write(i.first);
  //   putchar(' ');
  //   write(i.second);
  //   putchar('\n');
  // }
  for (int i = 1; i <= totN; ++i) {
    for (auto j : V[i]) {
      if (j != 1) {
        write(i);
        putchar(' ');
        write(j);
        putchar('\n');
      }
    }
  }
  return 0;
} // Thomitics Code