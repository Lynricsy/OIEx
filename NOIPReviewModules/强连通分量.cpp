/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
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

long long low[maxN];
long long dfn[maxN];
long long dfs_cnt;
bool inS[maxN];
stack<long long> S;
long long cntS;
vector<long long> SCCs[maxN];
long long inC[maxN];
bool printed[maxN];

void Tarjan(long long x) {
  S.push(x);
  ++dfs_cnt;
  low[x] = dfn[x] = dfs_cnt;
  inS[x] = true;
  for (int i = head[x]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (!dfn[vir]) {
      Tarjan(vir);
      low[x] = min(low[x], low[vir]);
    } else if (inS[vir]) {
      low[x] = min(low[x], dfn[vir]);
    }
  }
  if (dfn[x] == low[x]) {
    ++cntS;
    long long y;
    do {
      y = S.top();
      S.pop();
      inS[y] = false;
      SCCs[cntS].push_back(y);
      inC[y] = cntS;
    } while (y != x);
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
  for (int i = 1; i <= cntS; ++i) {
    sort(SCCs[i].begin(), SCCs[i].end());
  }
  write(cntS, '\n', 1);
  for (int i = 1; i <= totN; ++i) {
    if (printed[inC[i]]) {
      continue;
    }
    for (auto j : SCCs[inC[i]]) {
      write(j, ' ', 1);
    }
    printed[inC[i]] = true;
    putchar('\n');
  }
  return 0;
} // Thomitics Code