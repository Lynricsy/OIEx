/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
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
long long rot;
long long X, Y, Z;
long long cntNODE;
long long totN;

long long arand() { return rand() % 114514 + 3; }
struct Node {
  long long lch, rch;
  long long val;
  long long rnd;
  long long siz;
} nodes[maxN];
void update(long long nowX) {
  nodes[nowX].siz = nodes[nodes[nowX].lch].siz + nodes[nodes[nowX].rch].siz + 1;
}

void spilt(long long MTree, long long K, long long &lTree, long long &rTree) {
  if (!MTree) {
    lTree = rTree = 0;
    return;
  }
  if (nodes[MTree].val <= K) {
    lTree = MTree;
    spilt(nodes[MTree].rch, K, nodes[MTree].rch, rTree);
  } else {
    rTree = MTree;
    spilt(nodes[MTree].lch, K, lTree, nodes[MTree].lch);
  }
  update(MTree);
}
long long merge(long long XTree, long long YTree) {
  if (!XTree || !YTree) {
    return XTree + YTree;
  }
  if (nodes[XTree].rnd > nodes[YTree].rnd) {
    nodes[XTree].rch = merge(nodes[XTree].rch, YTree);
    update(XTree);
    return XTree;
  } else {
    nodes[YTree].lch = merge(XTree, nodes[YTree].lch);
    update(YTree);
    return YTree;
  }
}

void insert(long long x) {
  ++cntNODE;
  nodes[cntNODE].rnd = arand();
  nodes[cntNODE].val = x;
  nodes[cntNODE].lch = nodes[cntNODE].rch = 0;
  nodes[cntNODE].siz = 1;
  spilt(rot, x, X, Y);
  rot = merge(merge(X, cntNODE), Y);
}

void del(long long x) {
  spilt(rot, x - 1, X, Y);
  spilt(Y, x, Y, Z);
  Y = merge(nodes[Y].lch, nodes[Y].rch);
  rot = merge(merge(X, Y), Z);
}

long long Kth(long long nowR, long long K) {
  while (true) {
    if (nodes[nodes[nowR].lch].siz + 1 == K) {
      return nodes[nowR].val;
    } else if (K <= nodes[nodes[nowR].lch].siz) {
      nowR = nodes[nowR].lch;
    } else {
      K -= nodes[nodes[nowR].lch].siz + 1;
      nowR = nodes[nowR].rch;
    }
  }
}

long long nxt(long long x) {
  spilt(rot, x, X, Y);
  long long ans = Kth(Y, 1);
  merge(X, Y);
  return ans;
}
long long pre(long long x) {
  spilt(rot, x - 1, X, Y);
  long long ans = Kth(X, nodes[X].siz);
  merge(X, Y);
  return ans;
}
long long thK(long long x) {
  spilt(rot, x - 1, X, Y);
  long long ans = nodes[X].siz + 1;
  merge(X, Y);
  return ans;
}

int main() {
  totN = read();
  for (int i = 1, opt, x; i <= totN; ++i) {
    opt = read();
    x = read();
    switch (opt) {
    case 1:
      insert(x);
      break;
    case 2:
      del(x);
      break;
    case 3:
      write(thK(x), '\n', 1);
      break;
    case 4:
      write(Kth(rot, x), '\n', 1);
      break;
    case 5:
      write(pre(x), '\n', 1);
      break;
    case 6:
      write(nxt(x), '\n', 1);
      break;
    }
  }
  return 0;
} // Thomitics Code