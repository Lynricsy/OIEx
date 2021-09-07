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
#define arand() (rand() % 114514)
#define mrg() merge(X, Y)
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

using namespace std;

inline int read() {
  int x = 0;
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

const int maxN = 1000090;
int totN;
int totQ;

struct Node {
  int lch, rch;
  int val;
  int rnd;
  int siz;
} nodes[maxN];

int X, Y, Z;
int rot;
int cntNODE;

void update(int x) {
  nodes[x].siz = nodes[nodes[x].lch].siz + nodes[nodes[x].rch].siz + 1;
}

void spilt(int Mtree, int K, int &x, int &y) {
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

int merge(int Xtree, int Ytree) {
  if (!Xtree || !Ytree)
    return Xtree + Ytree;
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

int Kth(int K, int nowT) {
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

void insert(int x) {
  ++cntNODE;
  nodes[cntNODE].lch = nodes[cntNODE].rch = 0;
  nodes[cntNODE].val = x;
  nodes[cntNODE].rnd = arand();
  nodes[cntNODE].siz = 1;
  spilt(rot, x, X, Y);
  rot = merge(merge(X, cntNODE), Y);
}

void del(int x) {
  spilt(rot, x, X, Z);
  spilt(X, x - 1, X, Y);
  Y = merge(nodes[Y].lch, nodes[Y].rch);
  rot = merge(merge(X, Y), Z);
}

int pre(int x) {
  spilt(rot, x - 1, X, Y);
  return Kth(nodes[X].siz, X);
}

int nxt(int x) {
  spilt(rot, x, X, Y);
  return Kth(1, Y);
}

int thK(int K) {
  spilt(rot, K - 1, X, Y);
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
    if (opt > 0) {
      insert(opt);
    } else {
      opt = -opt;
      del(Kth(opt, rot));
    }
  }
  if (nodes[rot].siz) {
    write(Kth(1, rot));
  } else {
    puts("0");
  }
  return 0;
} // Thomitics Code