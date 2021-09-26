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
template <typename T> inline void write(T x, char ch = '\n', bool ij = false) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
  if (ij) {
    putchar(ch);
  }
}

const long long maxN = 100090;
// const long long maxN = 90;
long long totN;
long long totM;
long long totS;
long long depth[maxN];
long long fath[maxN];
long long siz[maxN];
long long top[maxN];
long long Sson[maxN];

struct Edge {
  long long to;
  long long nxt;
} edges[maxN << 1];
long long head[maxN << 1];
long long cnt_edges;
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
}

void DFS1(long long nowX, long long fa) {
  siz[nowX] = 1;
  depth[nowX] = depth[fa] + 1;
  fath[nowX] = fa;
  long long maxx = -1;
  for (long long i = head[nowX]; i; i = edges[i].nxt) {
    long long v = edges[i].to;
    if (v == fa)
      continue;
    DFS1(v, nowX);
    siz[nowX] += siz[v];
    if (siz[v] > maxx) {
      maxx = siz[v];
      Sson[nowX] = v;
    }
  }
}

void DFS2(long long nowX, long long topf) {
  top[nowX] = topf;
  if (!Sson[nowX]) {
    return;
  }
  DFS2(Sson[nowX], topf);
  for (long long i = head[nowX]; i; i = edges[i].nxt) {
    long long v = edges[i].to;
    if (v == Sson[nowX] || v == fath[nowX])
      continue;
    DFS2(v, v);
  }
}

long long LCA(long long u, long long v) {
  while (top[u] != top[v]) {
    if (depth[top[u]] < depth[top[v]]) {
      swap(u, v);
    }
    u = fath[top[u]];
  }
  if (depth[u] < depth[v]) {
    swap(u, v);
  }
  // while (u != v && u != top[u]) {
  //   u = fath[u];
  // }
  // while (u != v) {
  //   v = fath[v];
  // }
  return v;
}

int main() {
  totN = read();
  totM = read();
  totS = read();
  for (long long i = 1, u, v; i <= totN - 1; ++i) {
    u = read();
    v = read();
    add_edge(u, v);
    add_edge(v, u);
  }
  DFS1(totS, 0);
  DFS2(totS, totS);
  for (long long i = 1, u, v; i <= totM; ++i) {
    u = read();
    v = read();
    write(LCA(u, v), '\n', true);
  }
  return 0;
} // Thomitics Code