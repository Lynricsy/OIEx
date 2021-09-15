/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
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

const long long maxN = 100090;
long long totN;
long long totQ;
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

long long siz[maxN];
long long Sson[maxN];
long long top[maxN];
long long dep[maxN];
long long fa[maxN];

void DFS1(long long nowX, long long fath) {
  long long maxx = -1;
  siz[nowX] = 1;
  fa[nowX] = fath;
  dep[nowX] = dep[fath] + 1;
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
  top[nowX] = ftop;
  if (!Sson[nowX]) {
    return;
  }
  DFS2(Sson[nowX], ftop);
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == Sson[nowX] || vir == fa[nowX]) {
      continue;
    }
    DFS2(vir, vir);
  }
}

auto LCA(long long a, long long b) {
  if (a == b) {
    return a;
  }
  while (top[a] != top[b]) {
    if (dep[top[a]] < dep[top[b]]) {
      swap(a, b);
    }
    a = fa[top[a]];
  }
  if (dep[a] > dep[b]) {
    swap(a, b);
  }
  return a;
}

auto dis(long long x, long long y) {
  long long s = LCA(x, y);
  return abs(dep[s] - dep[x]) + abs(dep[s] - dep[y]);
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
  for (int i = 1, x, y, z, f; i <= totQ; ++i) {
    x = read();
    y = read();
    z = read();
    auto a = LCA(x, y);
    auto b = LCA(y, z);
    auto c = LCA(x, z);
    if (a == b) {
      f = c;
    } else if (a == c) {
      f = b;
    } else if (b == c) {
      f = a;
    }
    write(f);
    putchar(' ');
    a = dis(x, f);
    b = dis(y, f);
    c = dis(z, f);
    write(dis(x, f) + dis(y, f) + dis(z, f));
    putchar('\n');
  }
  return 0;
} // Thomitics Code