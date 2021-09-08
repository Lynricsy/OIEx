/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
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
long long siz[maxN];
long long num[maxN];
long long nums[maxN];
long long top[maxN];
long long Sson[maxN];
long long dep[maxN];
long long fa[maxN];
long long ID[maxN];
long long cntNODE;

struct Edge {
  long long nxt;
  long long to;
  long long val;
  long long from;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].from = u;
  edges[cnt_edges].val = w;
}

struct xz {
  long long sum;
  long long maxx;
};

struct Node {
  long long l, r;
  long long val;
  long long tag;
  long long maxx;
  Node *lch, *rch;
  void pushup() {
    val = lch->val + rch->val;
    maxx = max(lch->maxx, rch->maxx);
  }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag = 0;
    if (l == r) {
      lch = rch = NULL;
      val = num[l];
      maxx = num[l];
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
  }
  void maketag(long long w) {
    val += w;
    tag += w;
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (l > R) || (L > r); }
  void pushdown() {
    if (!tag) {
      return;
    }
    lch->maketag(tag);
    rch->maketag(tag);
    tag = 0;
  }
  void update(long long L, long long R, long long w) {
    if (INrange(L, R)) {
      maketag(w);
      return;
    } else if (!OUTrange(L, R)) {
      pushdown();
      lch->update(L, R, w);
      rch->update(L, R, w);
      pushup();
    }
  }
  xz query(long long L, long long R) {
    if (INrange(L, R)) {
      return {val, maxx};
    }
    if (OUTrange(L, R)) {
      return {0, -INF};
    }
    pushdown();
  }
};

void DFS1(long long nowX, long long fath) {
  long long maxx = -1;
  siz[nowX] = 1;
  dep[nowX] = dep[fath] + 1;
  fa[nowX] = fath;
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fath) {
      continue;
    }
    DFS1(vir, nowX);
    siz[nowX] += siz[vir];
    if (siz[vir] > maxx) {
      maxx = siz[vir];
      Sson[nowX] = vir;
    }
  }
}
void DFS2(long long nowX, long long ftop) {
  ++cntNODE;
  ID[nowX] = cntNODE;
  num[cntNODE] = nums[nowX];
  DFS2(Sson[nowX], ftop);
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa[nowX] || vir == Sson[nowX]) {
      continue;
    }
    DFS2(vir, vir);
  }
}

int main() { return 0; } // Thomitics Code