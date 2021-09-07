/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
// #include <bits/stdc++.h>
#include <cstdio>
#include <set>
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

long long totN;
struct Node {
  long long l, r;
  mutable long long val;
  Node(const long long &al, const long long &ar, const long long &av)
      : l(al), r(ar), val(av) {}
  inline bool operator<(const Node &rf) const { return l < rf.l; }
};
set<Node> ODT;
auto split(long long x) {
  if (x > totN) {
    return ODT.end();
  }
  auto it = --ODT.upper_bound({x, 0, 0});
  if (it->l == x) {
    return it;
  }
  long long l = it->l;
  long long r = it->r;
  long long v = it->val;
  ODT.erase(it);
  ODT.insert(Node(l, x - 1, v));
  return ODT.insert(Node(x, r, v)).first;
}
void assign(long long l, long long r, long long v) {
  auto itr = split(r + 1);
  auto itl = split(l);
  ODT.erase(itl, itr);
  ODT.insert(Node(l, r, v));
}

int main() { return 0; } // Thomitics Code