/**************************************************************
 * Problem: Luogu P3520
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm: 求无向图欧拉回路
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <future>
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

const long long maxN = 1090;
long long totN;
long long totM;
long long rot;
stack<long long> Cir;
bool vis[maxN];
queue<long long> Q;
struct Edge {
  long long nxt;
  long long to;
} edges[maxN << 1];
long long cnt_edges = 1;
long long head[maxN];
long long now[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}
long long deg[maxN];
long long cntC;

void DFS(long long nowX) {
  Cir.push(nowX);
  deg[nowX] -= 2;
  for (int i = now[nowX]; i; i = edges[i].nxt) {
    now[nowX] = i;
    if (vis[i]) {
      continue;
    }
    vis[i] = vis[i ^ 1] = true;
    long long vir = edges[i].to;
    if (vir == rot && nowX != rot) {
      ++cntC;
      Cir.push(vir);
      return;
    }
    DFS(vir);
    return;
  }
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1, u, v, a, b; i <= totM; ++i) {
    u = read();
    v = read();
    a = read();
    b = read();
    if (!(a ^ b)) {
      continue;
    }
    add_edge(u, v);
    add_edge(v, u);
    ++deg[u];
    ++deg[v];
  }
  for (int i = 1; i <= totN; ++i) {
    now[i] = head[i];
  }
  for (int i = 1; i <= totN; ++i) {
    if (deg[i] & 1) {
      puts("NIE");
      return 0;
    }
  }
  for (int i = 1; i <= totN; ++i) {
    if (!deg[i]) {
      continue;
    }
    rot = i;
    while (deg[i]) {
      DFS(i);
    }
  }
  write(cntC, '\n', 1);
  for (int i = 1; i <= cntC; ++i) {

    long long nowROT = Cir.top();
    long long y = -1;
    long long nowCNT = 0;
    y = Cir.top();
    Q.push(y);
    Cir.pop();
    y = Cir.top();
    while (y != nowROT) {
      y = Cir.top();
      Q.push(y);
      Cir.pop();
      ++nowCNT;
    }
    write(nowCNT, ' ', 1);
    while (!Q.empty()) {
      write(Q.front(), ' ', 1);
      Q.pop();
    }
    putchar('\n');
  }
  return 0;
} // Thomitics Code