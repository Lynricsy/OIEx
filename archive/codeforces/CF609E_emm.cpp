/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
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
long long MinTree;
long long cntNode;

long long siz[maxN];
long long depth[maxN];
long long fa[maxN];
long long bfa[maxN];
long long Sson[maxN];
long long ID[maxN];
long long nums[maxN];
long long num[maxN];
long long top[maxN];

long long find(long long x) {
  if (bfa[x] == x) {
    return x;
  }
  return fa[x] = find(fa[x]);
}

struct Edge {
  long long nxt;
  long long to;
  long long val;
  bool tag;
  long long from;
} edges[maxN << 1];
long long head[maxN << 1];
long long cnt_edges;
void add_edge(long long u, long long v, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].val = w;
  edges[cnt_edges].tag = false;
  edges[cnt_edges].from = u;
}

struct Node {
  long long l, r;
  long long val;
  Node *lch, *rch;
  void pushup() { val = lch->val + rch->val; }
  Node(long long L, long long R) {
    l = L;
    r = R;
    if (l == r) {
      lch = rch = NULL;
      val = num[l];
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (L > r) || (l > R); }
  long long query(long long L, long long R) {
    if (INrange(L, R)) {
      return val;
    }
    if (OUTrange(L, R)) {
      return 0;
    }
    return lch->query(L, R) + rch->query(L, R);
  }
};

void DFS1(long long nowX, long long fath) {
  fa[nowX] = fath;
  siz[nowX] = 1;
  depth[nowX] = depth[fath] + 1;
  long long maxx = -1;
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    if (!edges[i].tag) {
      continue;
    }
    long long vir = edges[i].to;
    if (vir == fath) {
      continue;
    }
    DFS1(vir, nowX);
    siz[nowX] += siz[vir];
    nums[vir] = edges[i].val;
    if (siz[vir] > maxx) {
      maxx = siz[vir];
      Sson[nowX] = vir;
    }
  }
}

void DFS2(long long nowX, long long topf) {
  ++cntNode;
  ID[nowX] = cntNode;
  num[cntNode] = nums[nowX];
  top[Sson[nowX]] = topf;
  DFS2(Sson[nowX], topf);
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    if (!edges[i].tag) {
      continue;
    }
    long long vir = edges[i].to;
    if (vir == fa[nowX] || vir == Sson[nowX]) {
      continue;
    }
    DFS2(vir, vir);
  }
}

void Kruskal() {
  for (int i = 1; i <= cnt_edges; ++i) {
    if (find(edges[i].from) != find(edges[i].to)) {
      edges[i].tag = true;
      MinTree += edges[i].val;
      bfa[find(edges[i].from)] = find(edges[i].to);
    }
  }
}

long long Qrange(long long u, long long v) {
  while (top[u] != top[v]) {
  }
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1, u, v, w; i <= totM; ++i) {
    u = read();
    v = read();
    w = read();
    add_edge(u, v, w);
    add_edge(v, u, w);
  }
  Kruskal();
  DFS1(1, 0);
  DFS2(1, 1);
  return 0;
} // Thomitics Code