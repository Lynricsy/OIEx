/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <string>
#include <system_error>
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

const long long maxN = 2090;
int totN;
int ID[maxN];
int xore[maxN][maxN];
int fa[maxN];
int cntE;
long long MaxTree;

struct Edge {
  int nxt;
  int to;
  int val;
  int from;
} edges[maxN * maxN];
bool operator<(Edge a, Edge b) { return a.val > b.val; }
int cnt_edges;
int head[maxN << 1];
void add_edge(long long u, long long v, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].val = w;
  edges[cnt_edges].from = u;
}

long long find(long long x) {
  if (x == fa[x]) {
    return x;
  }
  return fa[x] = find(fa[x]);
}

void ExKruskal() {
  sort(edges + 1, edges + cnt_edges + 1);
  for (int i = 1; i <= cnt_edges; ++i) {
    if (find(edges[i].from) != find(edges[i].to)) {
      ++cntE;
      MaxTree += edges[i].val;
      fa[find(edges[i].to)] = find(edges[i].from);
    }
    if (cntE == totN - 1) {
      return;
    }
  }
}

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    ID[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    fa[i] = i;
  }
  for (int i = 1; i < totN; ++i) {
    for (int j = i + 1; j <= totN; ++j) {
      xore[i][j] = ID[i] ^ ID[j];
      add_edge(i, j, xore[i][j]);
    }
  }
  ExKruskal();
  write(MaxTree);
  return 0;
} // Thomitics Code