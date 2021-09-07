/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstring>
#include <queue>
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

long long totA;
long long totK;
long long antinums[19];
bool antiN[11];
vector<long long> Knum;
const long long maxN = 1000090;

struct Edge {
  long long nxt;
  long long to;
} edges[1000090 << 1];
long long cnt_edges;
long long head[1000090];
long long DIS[maxN];
bool vis[maxN];
vector<long long> Last;

void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}
long long minDIS = INF;

void BFS(long long totS) {
  memset(vis, 0, sizeof vis);
  queue<long long> Q;
  Q.push(totS);
  vis[totS] = true;
  while (!Q.empty()) {
    long long nowX = Q.front();
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      DIS[vir] = min(DIS[vir], DIS[nowX] + 1);
      if (!vis[vir]) {
        Q.push(vir);
        vis[vir] = true;
      }
    }
  }
}

int main() {
  memset(DIS, 0x3f, sizeof DIS);
  totA = read();
  totK = read();
  for (int i = 1; i <= totK; ++i) {
    antinums[i] = read();
    antiN[antinums[i]] = true;
  }
  for (int i = 1; i <= 9; ++i) {
    if (!antiN[i]) {
      Knum.push_back(i);
    }
  }
  for (auto snum : Knum) {
    long long now = snum;
    long long last = now;
    for (int i = 0; i <= 19; ++i) {
      now = (now * 10) % totA;
      add_edge(last, now);
      last = now;
    }
  }

  return 0;
} // Thomitics Code