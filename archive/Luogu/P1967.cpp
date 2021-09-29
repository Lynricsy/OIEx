/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
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

const long long maxN = 5E4 + 90;
long long totN;
long long totM;
long long totQ;
long long fath[maxN];
long long siz[maxN];
long long Sson[maxN];
long long depth[maxN];
long long ID[maxN];
long long num[maxN];
long long top[maxN];
long long cntNODE;
long long perchis[maxN];
string WORK;

struct sEdge {
  long long from;
  long long to;
  long long val;
} sedges[maxN];
bool operator<(sEdge a, sEdge b) { return a.val > b.val; }

struct notEdge {
  long long pre;
  long long to;
} nes[maxN];

struct Edge {
  long long nxt;
  long long to;
  long long val;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long x, long long y, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[x];
  head[x] = cnt_edges;
  edges[cnt_edges].to = y;
  edges[cnt_edges].val = w;
}

void DFS1(long long nowX, long long fa, long long dep) {
  fath[nowX] = fa;
  depth[nowX] = dep;
  siz[nowX] = 1;
  long long max = -1;
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa) {
      continue;
    }
    DFS1(vir, nowX, dep + 1);
    perchis[vir] = edges[i].val;
    siz[nowX] += siz[vir];
    if (siz[vir] > max) {
      max = siz[vir];
      Sson[nowX] = vir;
    }
  }
}

void DFS2(long long nowX, long long nowTOP) {
  top[nowX] = nowTOP;
  ++cntNODE;
  ID[nowX] = cntNODE;
  num[cntNODE] = perchis[nowX];
  if (!Sson[nowX]) {
    return;
  }
  DFS2(Sson[nowX], nowTOP);
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == Sson[nowX] || vir == fath[nowX]) {
      continue;
    }
    DFS2(vir, vir);
  }
}

struct Node {
  long long l, r;
  long long maxx, minn;
  long long sum;
  bool tag;
  Node *lch, *rch;
  void pushup() {
    maxx = max(lch->maxx, rch->maxx);
    minn = min(lch->minn, rch->minn);
    sum = lch->sum + rch->sum;
  }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag = 0;
    if (l == r) {
      maxx = minn = sum = num[l];
      lch = rch = NULL;
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  void maketag() {
    tag ^= true;
    long long premax = maxx;
    long long premin = minn;
    maxx = -premin;
    minn = -premax;
    sum = -sum;
  }
  void pushdown() {
    if (!tag) {
      return;
    }
    lch->maketag();
    rch->maketag();
    tag = 0;
  }
  inline bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  inline bool OUTrange(long long L, long long R) { return (l > R) || (L > r); }
  void update(long long L, long long R) {
    if (INrange(L, R)) {
      maketag();
    } else if (!OUTrange(L, R)) {
      pushdown();
      lch->update(L, R);
      rch->update(L, R);
      pushup();
    }
  }
  void Nupdate(long long x, long long w) {
    if (l == r) {
      sum = minn = maxx = w;
      return;
    }

    if (tag) {
      pushdown();
    }
    if (x < l || x > r) {
      return;
    } else {
      if (x <= lch->r) {
        lch->Nupdate(x, w);
      } else if (x >= rch->l) {
        rch->Nupdate(x, w);
      }
    }
    pushup();
  }
  long long qMAX(long long L, long long R) {
    if (INrange(L, R)) {
      return maxx;
    } else if (OUTrange(L, R)) {
      return -2147483647;
    }
    pushdown();
    return max(lch->qMAX(L, R), rch->qMAX(L, R));
  }
  long long qMIN(long long L, long long R) {
    if (INrange(L, R)) {
      return minn;
    } else if (OUTrange(L, R)) {
      return 2147483647;
    }
    pushdown();
    return min(lch->qMIN(L, R), rch->qMIN(L, R));
  }
  long long qSUM(long long L, long long R) {
    if (INrange(L, R)) {
      return sum;
    } else if (OUTrange(L, R)) {
      return 0;
    }
    pushdown();
    return lch->qSUM(L, R) + rch->qSUM(L, R);
  }
};

Node *rot;

void updRANGE(long long x, long long y) {
  while (top[x] != top[y]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    rot->update(ID[top[x]], ID[x]);
    x = fath[top[x]];
  }
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  if (x != y) {
    rot->update(ID[x] + 1, ID[y]);
  }
}
long long qRANGEsum(long long x, long long y) {
  long long nowANS = 0;
  while (top[x] != top[y]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    nowANS += rot->qSUM(ID[top[x]], ID[x]);
    x = fath[top[x]];
  }
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  if (x != y) {
    nowANS += rot->qSUM(ID[x] + 1, ID[y]);
  }
  return nowANS;
}
long long qRANGEmin(long long x, long long y) {
  long long nowANS = 2147483647;
  while (top[x] != top[y]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    nowANS = min(rot->qMIN(ID[top[x]], ID[x]), nowANS);
    x = fath[top[x]];
  }
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  if (x != y) {
    nowANS = min(rot->qMIN(ID[x] + 1, ID[y]), nowANS);
  }
  return nowANS;
}
long long qRANGEmax(long long x, long long y) {
  long long nowANS = -2147483647;
  while (top[x] != top[y]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    nowANS = max(rot->qMAX(ID[top[x]], ID[x]), nowANS);
    x = fath[top[x]];
  }
  if (depth[x] > depth[y]) {
    swap(x, y);
  }
  if (x != y) {
    nowANS = max(rot->qMAX(ID[x] + 1, ID[y]), nowANS);
  }
  return nowANS;
}
void updNODE(long long x, long long w) {
  long long nx;
  nx = max(ID[nes[x].pre], ID[nes[x].to]);
  rot->Nupdate(nx, w);
}

long long bfa[maxN];

long long findfa(long long x) {
  if (bfa[x] == x) {
    return x;
  } else {
    return bfa[x] = findfa(bfa[x]);
  }
}

void Kruskal() {
  for (int i = 1; i <= maxN - 50; ++i) {
    bfa[i] = i;
  }
  for (int i = 1; i <= totM; ++i) {
    if (findfa(sedges[i].from) != findfa(sedges[i].to)) {
      add_edge(sedges[i].from, sedges[i].to, sedges[i].val);
      add_edge(sedges[i].to, sedges[i].from, sedges[i].val);
      bfa[findfa(sedges[i].from)] = findfa(sedges[i].to);
    }
  }
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totM; ++i) {
    sedges[i].from = read();
    sedges[i].to = read();
    sedges[i].val = read();
  }
  sort(sedges + 1, sedges + totM + 1);
  Kruskal();
  for (int i = 1; i <= totN; ++i) {
    if (!depth[i]) {
      DFS1(i, 0, 1);
      DFS2(i, i);
    }
  }
  rot = new Node(1, totN);
  totQ = read();
  for (int i = 1, x, y; i <= totQ; ++i) {
    x = read();
    y = read();
    if (findfa(x) != findfa(y)) {
      puts("-1");
    } else {
      write(qRANGEmin(x, y), '\n', 1);
    }
  }
  return 0;
} // Thomitics Code