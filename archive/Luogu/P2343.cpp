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
#define arand() rand() % 114514 + 1
#define mrg() merge(X, Y)
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
long long X, Y, Z;
long long rot;
long long cntNODE;
long long totQ;
long long totN;

struct Node {
  long long lch, rch;
  long long val;
  long long rnd;
  long long siz;
} nodes[maxN];

void update(long long nowX) {
  nodes[nowX].siz = nodes[nodes[nowX].lch].siz + nodes[nodes[nowX].rch].siz + 1;
}

void spilt(long long Mtree, long long K, long long &x, long long &y) {
  if (!Mtree) {
    x = y = 0;
    return;
  }
  if (nodes[Mtree].val <= K) {
    x = Mtree;
    spilt(nodes[Mtree].rch, K, nodes[Mtree].rch, y);
  } else {
    y = Mtree;
    spilt(nodes[Mtree].lch, K, x, nodes[Mtree].lch);
  }
  update(Mtree);
}

long long merge(long long Xtree, long long Ytree) {
  if (!Xtree || !Ytree) {
    return Xtree + Ytree;
  }
  if (nodes[Xtree].rnd > nodes[Ytree].rnd) {
    nodes[Xtree].rch = merge(nodes[Xtree].rch, Ytree);
    update(Xtree);
    return Xtree;
  } else {
    nodes[Ytree].lch = merge(Xtree, nodes[Ytree].lch);
    update(Ytree);
    return Ytree;
  }
}

long long Kth(long long nowT, long long K) {
  while (true) {
    if (K <= nodes[nodes[nowT].lch].siz) {
      nowT = nodes[nowT].lch;
    } else if (K == nodes[nodes[nowT].lch].siz + 1) {
      return nodes[nowT].val;
    } else {
      K -= nodes[nodes[nowT].lch].siz + 1;
      nowT = nodes[nowT].rch;
    }
  }
}

void insert(long long nowX) {
  ++cntNODE;
  nodes[cntNODE].lch = nodes[cntNODE].rch = 0;
  nodes[cntNODE].val = nowX;
  nodes[cntNODE].siz = 1;
  nodes[cntNODE].rnd = arand();
  spilt(rot, nowX, X, Y);
  rot = merge(merge(X, cntNODE), Y);
}
void del(long long nowX) {
  spilt(rot, nowX, X, Z);
  spilt(X, nowX - 1, X, Y);
  Y = merge(nodes[Y].lch, nodes[Y].rch);
  rot = merge(merge(X, Y), Z);
}

long long pre(long long nowX) {
  spilt(rot, nowX - 1, X, Y);
  return Kth(X, nodes[X].siz);
}

long long nxt(long long nowX) {
  spilt(rot, nowX, X, Y);
  return Kth(Y, 1);
}
long long thK(long long nowX) {
  spilt(rot, nowX - 1, X, Y);
  return nodes[X].siz + 1;
}

int main() {
  srand(time(0));
  totN = read();
  totQ = read();
  for (int i = 1, x; i <= totN; ++i) {
    x = read();
    insert(x);
  }
  for (int i = 1, opt, x; i <= totQ; ++i) {
    opt = read();
    x = read();
    switch (opt) {
    case 2:
      insert(x);
      break;
    case 1:
      write(Kth(rot, nodes[rot].siz - x + 1));
      putchar('\n');
      break;
    }
  }
  return 0;
} // Thomitics Code