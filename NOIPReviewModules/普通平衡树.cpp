/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <ratio>
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
template <typename T>
inline void write(initializer_list<T> WRITE_NUMS, char ch) {
  for (auto i : WRITE_NUMS) {
    write(i);
    putchar(ch);
  }
}

const long long maxN = 1090;

long long X, Y, Z;
long long rot;
long long cntNODE;
long long totN;

struct Node {
  long long val;
  long long rnd;
  long long lch, rch;
  long long siz;
} nodes[maxN];

void update(long long x) {
  nodes[x].siz = nodes[nodes[x].lch].siz + nodes[nodes[x].rch].siz + 1;
}

void split(long long MTree, long long K, long long &lTree, long long &rTree) {
  if (!MTree) {
    lTree = rTree = 0;
    return;
  }
  if (K >= nodes[MTree].val) {
    lTree = MTree;
    split(nodes[MTree].rch, K, nodes[MTree].rch, rTree);
  } else {
    rTree = MTree;
    split(nodes[MTree].lch, K, lTree, nodes[MTree].lch);
  }
  update(MTree);
}
long long merge(long long xTree, long long yTree) {
  if (!xTree || !yTree) {
    return xTree + yTree;
  }
  if (nodes[xTree].rnd >= nodes[yTree].rnd) {
    nodes[xTree].rch = merge(nodes[xTree].rch, yTree);
    update(xTree);
    return xTree;
  } else {
    nodes[yTree].lch = merge(xTree, nodes[yTree].lch);
    update(yTree);
    return yTree;
  }
}

void mrg() { merge(X, Y); }
long long arand() {
  return (((rand() % 9834757 + 1) * 34 - 2383) - 391) % 1145140 + 1;
}
long long Kth(long long K, long long NTree) {
  while (true) {
    if (nodes[nodes[NTree].lch].siz + 1 == K) {
      return nodes[NTree].val;
    } else if (nodes[nodes[NTree].lch].siz >= K) {
      NTree = nodes[NTree].lch;
    } else {
      K -= nodes[nodes[NTree].lch].siz + 1;
      NTree = nodes[NTree].rch;
    }
  }
}
long long pre(long long x) {
  split(rot, x - 1, X, Y);
  return Kth(nodes[X].siz, X);
}
long long nxt(long long x) {
  split(rot, x, X, Y);
  return Kth(1, Y);
}
void insert(long long x) {
  split(rot, x, X, Y);
  ++cntNODE;
  nodes[cntNODE].rnd = arand();
  nodes[cntNODE].siz = 1;
  nodes[cntNODE].val = x;
  nodes[cntNODE].lch = nodes[cntNODE].rch = 0;
  rot = merge(merge(X, cntNODE), Y);
}
void del(long long x) {
  split(rot, x, X, Y);
  split(X, x - 1, X, Z);
  Z = merge(nodes[Z].lch, nodes[Z].rch);
  rot = merge(merge(X, Z), Y);
}
long long thK(long long x) {
  split(rot, x - 1, X, Y);
  long long res = nodes[X].siz + 1;
  mrg();
  return res;
}
int main() {
  totN = read();
  for (int i = 1, opt, x; i <= totN; ++i) {
    opt = read();
    x = read();
    if (opt == 1) {
      insert(x);
    } else if (opt == 2) {
      del(x);
    } else if (opt == 3) {
      write(thK(x), '\n', 1);
    } else if (opt == 4) {
      write(Kth(x, rot), '\n', 1);
    } else if (opt == 5) {
      write(pre(x), '\n', 1);
      mrg();
    } else if (opt == 6) {
      write(nxt(x), '\n', 1);
      mrg();
    }
  }
  return 0;
} // Shirakami Ling Code