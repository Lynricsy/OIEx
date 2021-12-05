/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/

#include <bits/stdc++.h>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include <shared_mutex>

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
void write(const long long &x) {
  if (!x) {
    putchar('0');
    return;
  }
  char f[100];
  long long tmp = x;
  if (tmp < 0) {
    tmp = -tmp;
    putchar('-');
  }
  long long s = 0;
  while (tmp > 0) {
    f[s++] = tmp % 10 + '0';
    tmp /= 10;
  }
  while (s > 0) {
    putchar(f[--s]);
  }
}

const long long maxN = 1000090;

struct Node {
  long long lch, rch;
  long long val, siz;
  long long rnd;
  bool rev;
} nodes[maxN];

long long X, Y, Z, W;
long long rot;
long long cnt;
long long totN;
long long totM;
long long raw[maxN];

void pushdown(long long x) {
  if (!nodes[x].rev) {
    return;
  }
  swap(nodes[x].lch, nodes[x].rch);
  if (nodes[x].lch) {
    nodes[nodes[x].lch].rev ^= true;
  }
  if (nodes[x].rch) {
    nodes[nodes[x].rch].rev ^= true;
  }
  nodes[x].rev = false;
}

void update(long long nowX) {
  nodes[nowX].siz = nodes[nodes[nowX].lch].siz + nodes[nodes[nowX].rch].siz + 1;
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

void insert(long long nowX) {
  split(rot, nowX, X, Y);
  //	puts("qwq");
  ++cnt;
  nodes[cnt].lch = nodes[cnt].rch = 0;
  nodes[cnt].val = nowX;
  nodes[cnt].siz = 1;
  nodes[cnt].rnd = arand();
  rot = merge(merge(X, cnt), Y);
}

void out(long long x) {
  if (!x) {
    return;
  }
  pushdown(x);
  out(nodes[x].lch);
  // write(raw[x]);
  write(x);
  putchar(' ');
  out(nodes[x].rch);
}

int main() {
  totN = read();
  totM = read();
  srand(time(0));
  for (int i = 1; i <= totN; ++i) {
    // long long x = read();
    // raw[i] = x;

    insert(i);
    // nodes[i].val = i;
  }
  for (int i = 1; i <= totM; ++i) {
    long long l, r;
    l = read();
    r = read();
    split(rot, l - 1, X, Y);
    split(Y, r - l + 1, Y, Z);
    nodes[Y].rev ^= true;
    rot = merge(X, merge(Y, Z));
  }
  out(rot);
  return 0;
} // Thomitics Code