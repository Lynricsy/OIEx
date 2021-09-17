/**************************************************************
 * Problem: Luogu P1986
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm: 贪心
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
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

const long long maxN = 1000090;
struct Node {
  long long l, r;
  long long x;
} nodes[maxN];
long long totN;
long long totM;
bool operator<(Node a, Node b) { return a.r < b.r; }
bool nav[maxN];
long long totANS;

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totM; ++i) {
    nodes[i].l = read();
    nodes[i].r = read();
    nodes[i].x = read();
  }
  sort(nodes + 1, nodes + totM + 1);
  for (int i = 1; i <= totM; ++i) {
    long long x = 0;
    for (int j = nodes[i].r; j >= nodes[i].l; --j) {
      if (nav[j]) {
        ++x;
      }
    }
    for (int j = nodes[i].r; j >= nodes[i].l; --j) {
      if (x >= nodes[i].x) {
        break;
      }
      if (!nav[j]) {
        nav[j] = true;
        ++x;
      }
    }
  }
  for (int i = 1; i <= totN; ++i) {
    totANS += nav[i];
  }
  write(totANS);
  return 0;
} // Thomitics Code