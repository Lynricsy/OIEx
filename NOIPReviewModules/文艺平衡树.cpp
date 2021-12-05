/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f
#define arand() rand() % 114514
#define mrg() merge(x, y)

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
template <typename T>
inline void write(initializer_list<T> WRITE_NUMS, char ch) {
  for (auto i : WRITE_NUMS) {
    write(i);
    putchar(ch);
  }
}

const long long maxN = 1090;

long long totN;
long long totM;

long long W, X, Y, Z;
long long rot;

struct Node {
  long long val;
  bool rev;
  long long lch, rch;
  long long rnd;
  long long siz;
} nodes[maxN];
long long cntNODE;

void pushdown(long long x) {
  if (!nodes[x].rev) {
    return;
  }
  nodes[x].rev = 0;
  swap(nodes[x].lch, nodes[x].rch);
  if (nodes[x].lch) {
    nodes[nodes[x].lch].rev ^= 1;
  }
  if (nodes[x].rch) {
    nodes[nodes[x].rch].rev ^= 1;
  }
}
void update(long long x) {
  nodes[x].siz = nodes[nodes[x].lch].siz + nodes[nodes[x].rch].siz + 1;
}

long long merge(long long Atree, long long Btree) {
  if ((!Atree) || (!Btree)) {
    return Atree + Btree;
  } else if (nodes[Atree].rnd < nodes[Btree].rnd) {
    pushdown(Atree);
    nodes[Atree].rch = merge(nodes[Atree].rch, Btree);
    update(Atree);
    return Atree;
  } else {
    pushdown(Btree);
    nodes[Btree].lch = merge(Atree, nodes[Btree].lch);
    update(Btree);
    return Btree;
  }
}

void split(long long splitX, long long K, long long &Xtree, long long &Ytree) {
  if (!splitX) {
    Xtree = Ytree = 0;
    return;
  }
  pushdown(splitX);
  if (nodes[nodes[splitX].lch].siz < K) {
    Xtree = splitX;
    split(nodes[splitX].rch, K - nodes[nodes[splitX].lch].siz - 1,
          nodes[splitX].rch, Ytree);
  } else {
    Ytree = splitX;
    split(nodes[splitX].lch, K, Xtree, nodes[splitX].lch);
  }
  update(splitX);
}

void insert(long long x) {
  ++cntNODE;
  nodes[cntNODE].lch = nodes[cntNODE].rch = 0;
  nodes[cntNODE].val = x;
  nodes[cntNODE].rev = 0;
  nodes[cntNODE].siz = 1;
  nodes[cntNODE].rnd = arand();
  split(rot, x, X, Y);
  rot = merge(merge(X, cntNODE), Y);
}

void print(long long x) {
  if (!x) {
    return;
  }
  pushdown(x);
  print(nodes[x].lch);
  write(x, ' ', 1);
  print(nodes[x].rch);
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totN; ++i) {
    insert(i);
  }
  for (int i = 1, l, r; i <= totM; ++i) {
    l = read();
    r = read();
    split(rot, l - 1, X, Y);
    split(Y, r - l + 1, W, Z);
    nodes[W].rev ^= 1;
    rot = merge(X, merge(W, Z));
  }
  print(rot);
  return 0;
} // Thomitics Code