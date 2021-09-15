/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <queue>
#include <stack>
#include <vector>
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

const long long maxN = 190;
long long totN;
long long totM;
long long dfn[maxN];
long long low[maxN];
long long inSCC[maxN];
vector<long long> SCC[maxN];
bool flag[maxN];
long long dfs_cnt;
bool inS[maxN];
long long cntSCC;
stack<long long> S;
bool cmp(long long x, long long y) { return x > y; }

struct Edge {
  long long nxt;
  long long to;
} edges[maxN << 1];
long long cnt_edges;
long long head[maxN];
// long long inSCC[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

void Tarjan(long long nowX) {
  ++dfs_cnt;
  dfn[nowX] = dfs_cnt;
  low[nowX] = dfs_cnt;
  S.push(nowX);
  inS[nowX] = true;
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (!dfn[vir]) {
      Tarjan(vir);
      low[nowX] = min(low[nowX], low[vir]);
    } else if (inS[vir]) {
      low[nowX] = min(dfn[vir], low[nowX]);
    }
  }
  if (dfn[nowX] == low[nowX]) {
    long long y = S.top();
    ++cntSCC;
    do {
      y = S.top();
      SCC[cntSCC].push_back(y);
      S.pop();
      inS[y] = false;
      inSCC[y] = cntSCC;
    } while (y != nowX);
  }
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1, u, v; i <= totM; ++i) {
    u = read();
    v = read();
    add_edge(u, v);
  }
  for (int i = 1; i <= totN; ++i) {
    if (!dfn[i]) {
      Tarjan(i);
    }
  }
  write(cntSCC, '\n', 1);
  for (int i = 1; i <= cntSCC; ++i) {
    sort(SCC[i].begin(), SCC[i].end());
  }
  // for (int i = cntSCC; i >= 1; --i) {
  //   for (auto j : SCC[i]) {
  //     write(j, ' ', 1);
  //   }
  //   putchar('\n');
  // }
  for (int i = 1; i <= totN; ++i) {
    if (flag[inSCC[i]]) {
      continue;
    }
    flag[inSCC[i]] = true;
    for (auto j : SCC[inSCC[i]]) {
      write(j, ' ', 1);
    }
    putchar('\n');
  }
  return 0;
} // Thomitics Code