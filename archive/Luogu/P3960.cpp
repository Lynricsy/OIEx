/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
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
long long totN;
long long totM;
long long totQ;

long long arand() { return rand() % 1919810 + 1; }

struct Node {
  long long l, r;
  long long siz;
  long long rnd;
  long long lch, rch;
} nodes[maxN];
long long cntNODE;

long long insert(long long L, long long R) {
  ++cntNODE;
  nodes[cntNODE].l = L;
  nodes[cntNODE].r = R;
  nodes[cntNODE].lch = nodes[cntNODE].rch = 0;
  nodes[cntNODE].siz = R - L + 1;
  nodes[cntNODE].rnd = arand();
  return cntNODE;
}

void pushup(long long x) {
  nodes[x].siz = nodes[nodes[x].lch].siz + nodes[nodes[x].rch].siz +
                 (nodes[x].r - nodes[x].l + 1);
}

long long merge(long long lTree, long long rTree) {
  if (!lTree || !rTree) {
    return lTree + rTree;
  }
  if (nodes[lTree].rnd < nodes[rTree].rnd) {
    nodes[lTree].rch = merge(nodes[lTree].rch, rTree);
    pushup(lTree);
    return lTree;
  } else {
    nodes[rTree].lch = merge(lTree, nodes[rTree].lch);
    pushup(rTree);
    return rTree;
  }
}

void mksiz(long long nowX, long long K) {
  if (K >= (nodes[nowX].r - nodes[nowX].l + 1)) {
    return;
  }
  long long wR = nodes[nowX].l + K - 1;
  long long NowNode = insert(wR + 1, nodes[nowX].r);
  nodes[nowX].r = wR;
  nodes[nowX].rch = merge(NowNode, nodes[nowX].rch);
  pushup(nowX);
}

void spilt(long long MTree, long long K, long long &XTree, long long &YTree) {
  if (!MTree) {
    XTree = YTree = 0;
    return;
  }
  if (nodes[nodes[MTree].lch].siz >= K) {
    YTree = MTree;
    spilt(nodes[MTree].lch, K, XTree, nodes[MTree].lch);
  } else {
    mksiz(MTree, K - nodes[nodes[MTree].lch].siz);
    XTree = MTree;
    spilt(nodes[MTree].rch,
          K - nodes[nodes[MTree].lch].siz -
              (nodes[MTree].r - nodes[MTree].l + 1),
          nodes[MTree].rch, YTree);
  }
  pushup(MTree);
}
long long rot[maxN];

int main() {
  srand(time(0));
  totN = read();
  totM = read();
  totQ = read();
  for (int i = 1; i <= totN; ++i) {
    rot[i] = insert((i - 1) * totM + 1, i * totM - 1);
  }
  for (int i = 1; i <= totN; ++i) {
    rot[totN + 1] = merge(rot[totN + 1], insert(i * totM, i * totM));
  }
  for (int i = 1, x = 0, y = 0; i <= totQ; ++i) {
    x = read();
    y = read();
    if (y == totM) {
      long long X, Y, Z;
      spilt(rot[totN + 1], x, X, Y);
      spilt(X, x - 1, X, Z);
      write(nodes[Z].l);
      putchar('\n');
      rot[totN + 1] = merge(X, merge(Y, Z));
    } else {
      long long X, Y, Z;
      spilt(rot[x], y, X, Y);
      spilt(X, y - 1, X, Z);
      write(nodes[Z].l);
      putchar('\n');
      long long A, B, C;
      spilt(rot[totN + 1], x, A, B);
      spilt(A, x - 1, A, C);
      rot[x] = merge(X, merge(Y, C));
      rot[totN + 1] = merge(A, merge(B, Z));
    }
  }
  return 0;
} // Thomitics Code