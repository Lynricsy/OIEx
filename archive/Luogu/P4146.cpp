/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
// #include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <type_traits>
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
long long cntNODE;
struct Node {
  long long val;
  long long maxc;
  long long atag;
  long long rtag;
  long long lch, rch;
  long long siz;
  long long rnd;
} nodes[maxN];
long long X, Y, Z;
long long rot;
long long totN;
long long totM;
long long arand() { return rand() % 114514 + 1; }
void pushup(long long nowX) {
  nodes[nowX].siz = nodes[nodes[nowX].lch].siz + nodes[nodes[nowX].rch].siz + 1;
  nodes[nowX].maxc = nodes[nowX].val;
  if (nodes[nowX].lch) {
    nodes[nowX].maxc = max(nodes[nowX].maxc, nodes[nodes[nowX].lch].maxc);
  }
  if (nodes[nowX].rch) {
    nodes[nowX].maxc = max(nodes[nowX].maxc, nodes[nodes[nowX].rch].maxc);
  }
}
void pushdown(long long nowX) {
  if (nodes[nowX].rtag) {
    if (nodes[nowX].lch) {
      nodes[nodes[nowX].lch].rtag ^= 1;
    }
    if (nodes[nowX].rch) {
      nodes[nodes[nowX].rch].rtag ^= 1;
    }
    swap(nodes[nowX].lch, nodes[nowX].rch);
    nodes[nowX].rtag = 0;
  }
  if (nodes[nowX].atag) {
    if (nodes[nowX].lch) {
      nodes[nodes[nowX].lch].atag += nodes[nowX].atag;
      nodes[nodes[nowX].lch].val += nodes[nowX].atag;
      nodes[nodes[nowX].lch].maxc += nodes[nowX].atag;
    }
    if (nodes[nowX].rch) {
      nodes[nodes[nowX].rch].atag += nodes[nowX].atag;
      nodes[nodes[nowX].rch].val += nodes[nowX].atag;
      nodes[nodes[nowX].rch].maxc += nodes[nowX].atag;
    }
    nodes[nowX].atag = 0;
    pushup(nowX);
  }
}

void split(long long MTree, long long K, long long &x, long long &y) {
  if (!MTree) {
    x = y = 0;
    return;
  }
  pushdown(MTree);
  if (nodes[nodes[MTree].lch].siz >= K) {
    y = MTree;
    split(nodes[MTree].lch, K, x, nodes[MTree].lch);
  } else {
    x = MTree;
    split(nodes[MTree].rch, K - nodes[nodes[MTree].lch].siz - 1,
          nodes[MTree].rch, y);
  }
  pushup(MTree);
}

long long merge(long long XTree, long long YTree) {
  pushdown(XTree);
  pushdown(YTree);
  if (!XTree || !YTree) {
    return XTree + YTree;
  }
  if (nodes[XTree].rnd < nodes[YTree].rnd) {
    nodes[XTree].rch = merge(nodes[XTree].rch, YTree);
    pushup(XTree);
    return XTree;
  } else {
    nodes[YTree].lch = merge(XTree, nodes[YTree].lch);
    pushup(YTree);
    return YTree;
  }
}

void insert(long long nowX) {
  ++cntNODE;
  nodes[cntNODE].lch = nodes[cntNODE].rch = 0;
  nodes[cntNODE].atag = nodes[cntNODE].rtag = 0;
  nodes[cntNODE].maxc = nodes[cntNODE].val = nowX;
  nodes[cntNODE].siz = 1;
  nodes[cntNODE].rnd = arand();
  split(rot, nowX, X, Y);
  rot = merge(merge(X, cntNODE), Y);
}

void Aupdate(long long L, long long R, long long w) {
  split(rot, L - 1, X, Y);
  split(Y, R - L + 1, Y, Z);
  nodes[Y].val += w;
  nodes[Y].maxc += w;
  nodes[Y].atag += w;
  rot = merge(merge(X, Y), Z);
}
void Rupdate(long long L, long long R) {
  split(rot, L - 1, X, Y);
  split(Y, R - L + 1, Y, Z);
  nodes[Y].rtag ^= 1;
  rot = merge(merge(X, Y), Z);
}
long long query(long long L, long long R) {
  split(rot, L - 1, X, Y);
  split(Y, R - L + 1, Y, Z);
  long long ans = nodes[Y].maxc;
  rot = merge(merge(X, Y), Z);
  return ans;
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totN; ++i) {
    insert(0);
  }
  for (int i = 1, opt, x, y, w; i <= totM; ++i) {
    opt = read();
    switch (opt) {
    case 1:
      x = read();
      y = read();
      w = read();
      Aupdate(x, y, w);
      break;
    case 2:
      x = read();
      y = read();
      Rupdate(x, y);
      break;
    case 3:
      x = read();
      y = read();
      write(query(x, y));
      putchar('\n');
      break;
    }
  }
  return 0;
} // Thomitics Code