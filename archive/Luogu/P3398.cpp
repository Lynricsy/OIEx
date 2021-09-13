/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <sstream>
#include <type_traits>
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

const long long maxN = 1000090;
struct Edge {
  long long nxt;
  long long to;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

long long totN;
long long totQ;
long long siz[maxN];
long long Sson[maxN];
long long dep[maxN];
long long fa[maxN];
long long top[maxN];
long long cntNODE;
long long ID[maxN];

void DFS1(long long nowX, long long fath) {
  long long maxx = -1;
  dep[nowX] = dep[fath] + 1;
  siz[nowX] = 1;
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
  top[nowX] = ftop;
  if (!Sson[nowX]) {
    return;
  }
  DFS2(Sson[nowX], ftop);
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa[nowX] || vir == Sson[nowX]) {
      continue;
    }
    DFS2(vir, vir);
  }
}
long long LCA(long long x, long long y) {
  while (top[x] != top[y]) {
    if (dep[top[x]] < dep[top[y]]) {
      swap(x, y);
    }
    x = fa[top[x]];
  }
  if (dep[x] < dep[y]) {
    swap(x, y);
  }
  return y;
}
long long dis(long long u, long long v) {
  long long s = LCA(u, v);
  return abs(dep[s] - dep[u]) + abs(dep[s] - dep[v]);
}

int main() {
  totN = read();
  totQ = read();
  for (int i = 1, u, v; i <= totN - 1; ++i) {
    u = read();
    v = read();
    add_edge(u, v);
    add_edge(v, u);
  }
  DFS1(1, 0);
  DFS2(1, 1);
  for (int i = 1, a, b, c, d, x, y; i <= totQ; ++i) {
    a = read();
    b = read();
    c = read();
    d = read();
    x = LCA(a, b);
    y = LCA(c, d);
    if (dis(x, c) + dis(x, d) == dis(c, d) ||
        dis(y, a) + dis(y, b) == dis(a, b)) {
      puts("Y");
    } else {
      puts("N");
    }
  }
  return 0;
} // Thomitics Code