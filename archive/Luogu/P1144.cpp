/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <queue>
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
const long long MOD = 100003;
long long totN;
long long totM;

bool vis[maxN];
long long DIS[maxN];
long long totANS;
long long nums[maxN];
struct Edge {
  long long nxt;
  long long to;
} edges[maxN << 1];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

void BFS(long long nowS) {
  memset(vis, 0, sizeof vis);
  queue<long long> Q;
  Q.push(nowS);
  DIS[nowS] = 1;
  vis[nowS] = true;
  nums[nowS] = 1;
  while (!Q.empty()) {
    long long nowX = Q.front();
    Q.pop();
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (!vis[vir]) {
        vis[vir] = true;
        DIS[vir] = DIS[nowX] + 1;
        Q.push(vir);
      }
      if (DIS[vir] == DIS[nowX] + 1) {
        nums[vir] += nums[nowX];
        nums[vir] %= MOD;
      }
    }
  }
}

int main() {
  freopen("P1144_1.in", "r", stdin);
  freopen("P.out", "w", stdout);
  totN = read();
  totM = read();
  for (int i = 1, u, v; i <= totM; ++i) {
    u = read();
    v = read();
    add_edge(u, v);
    add_edge(v, u);
  }
  BFS(1);
  for (int i = 1; i <= totN; ++i) {
    write(nums[i]);
    putchar('\n');
  }
  return 0;
} // Thomitics Code