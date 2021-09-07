/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
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

stack<long long> S;

long long dfn[maxN];
long long low[maxN];
long long dfs_cnt;
bool vis[maxN];
long long cnt_DCC;
long long in_DCC[maxN];
vector<long long> DCC[maxN];
long long able[maxN];
long long nowV;
bool VIS[maxN];
long long totS;
long long totT;

struct Edge {
  long long to, nxt;
  long long val;
  long long from;
} edges[maxN << 1];
long long head[maxN];
long long cnt_edges;
void add_edge(long long u, long long v, long long w) {
  ++cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].val = w;
  edges[cnt_edges].from = u;
}

void tarjan(long long u, long long fa) {
  dfn[u] = low[u] = ++dfs_cnt;
  S.push(u);
  vis[u] = true;
  for (long long i = head[u]; i; i = edges[i].nxt) {
    long long v = edges[i].to;
    if (v == fa) {
      continue;
    }
    if (!dfn[v]) {
      tarjan(v, u);
      low[u] = min(low[u], low[v]);
    } else if (vis[v] && v != fa) {
      low[u] = min(low[u], low[v]);
    }
  }
  if (dfn[u] == low[u]) {
    ++cnt_DCC;
    while (S.top() != u) {
      in_DCC[S.top()] = cnt_DCC;
      vis[S.top()] = false;
      S.pop();
    }
    // do {
    //   v = S.top();
    //   S.pop();
    //   vis[v] = false;
    //   DCC[cnt_DCC].push_back(v);
    //   in_DCC[v] = cnt_DCC;
    // } while (v != u);
    vis[u] = false;
    S.pop();
  }
}

void DFS(long long u, bool fib) {
  if (able[u]) {
    fib = true;
  }
  if (u == nowV) {
    if (fib) {
      puts("烟花来喽！");
    } else {
      puts("玩……过头了");
    }
    exit(0);
  }
  VIS[u] = true;
  for (long long i = head[u]; i; i = edges[i].nxt) {
    long long v = edges[i].to;
    if (!VIS[v]) {
      DFS(v, fib | edges[i].val);
    }
  }
}

int main() {
  totN = read();
  totM = read();
  for (long long i = 1; i <= totM; ++i) {
    long long u = read();
    long long v = read();
    long long w = read();
    add_edge(u, v, w);
    add_edge(v, u, w);
  }
  tarjan(1, 0);
  for (long long i = 1; i <= cnt_edges; i += 2) {
    if (in_DCC[edges[i].from] == in_DCC[edges[i].to] && edges[i].val) {
      able[in_DCC[edges[i].from]] = true;
    }
  }
  memset(head, 0, sizeof(head));
  cnt_edges = 0;
  for (long long i = 1; i <= totM << 1; ++i) {
    if (in_DCC[edges[i].from] != in_DCC[edges[i].to]) {
      add_edge(in_DCC[edges[i].from], in_DCC[edges[i].to], edges[i].val);
    }
  }
  totS = read();
  totT = read();
  totS = in_DCC[totS];
  nowV = in_DCC[totT];
  DFS(totS, false);
  puts("祭典……结束了");
  return 0;
} // Thomitics Code