/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <shared_mutex>
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

long long totN;
long long totM;
long long totS;

struct Edge {
  long long to;
  long long nxt;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

long long fath[maxN];
long long top[maxN];
long long depth[maxN];
long long Sson[maxN];
long long siz[maxN];

void DFS1(long long x, long long fa) {
  siz[x] = 1;
  fath[x] = fa;
  depth[x] = depth[fa] + 1;
  for (int i = head[x]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa) {
      continue;
    }
    DFS1(vir, x);
    siz[x] += siz[vir];
    if (siz[vir] > siz[Sson[x]]) {
      Sson[x] = vir;
    }
  }
}
void DFS2(long long x, long long ftop) {
  top[x] = ftop;
  if (!Sson[x]) {
    return;
  }
  DFS2(Sson[x], ftop);
  for (int i = head[x]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == Sson[x] || vir == fath[x]) {
      continue;
    }
    DFS2(vir, vir);
  }
}
long long LCA(long long x, long long y) {
  while (top[x] != top[y]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    x = fath[top[x]];
  }
  if (depth[x] < depth[y]) {
    swap(x, y);
  }
  return y;
}

int main() {
  totN = read();
  totM = read();
  totS = read();
  for (int i = 1, u, v; i <= totN - 1; ++i) {
    u = read();
    v = read();
    add_edge(u, v);
    add_edge(v, u);
  }
  DFS1(totS, 0);
  DFS2(totS, totS);
  for (int i = 1, x, y; i <= totM; ++i) {
    x = read();
    y = read();
    write(LCA(x, y), '\n', 1);
  }
  return 0;
} // Thomitics Code