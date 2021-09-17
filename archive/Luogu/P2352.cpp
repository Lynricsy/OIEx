/**************************************************************
 * Problem: Luogu P2352 队爷的新书
 * Author: 芊枫
 * Date: 2021 Sept 17
 * Algorithm: 差分
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

const auto maxN = 1090;
long long totN;
struct Node {
  long long pos;
  long long x;
} nodes[maxN * 3 + 3];
bool operator<(Node a, Node b) {
  if (a.pos == b.pos) {
    return a.x < b.x;
  } else {
    return a.pos < b.pos;
  }
}
long long cntNODE;
long long totANS;
long long sum;

int main() {
  totN = read();
  for (int i = 1, l, r; i <= totN; ++i) {
    l = read();
    r = read();
    ++cntNODE;
    nodes[cntNODE] = {l, 1};
    ++cntNODE;
    nodes[cntNODE] = {r, 0};
    ++cntNODE;
    nodes[cntNODE] = {r + 1, -1};
  }
  sort(nodes + 1, nodes + 1 + cntNODE);
  for (int i = 1; i <= cntNODE; ++i) {
    sum += nodes[i].x;
    totANS = max(totANS, nodes[i].pos * sum);
  }
  write(totANS);
  return 0;
} // Thomitics Code