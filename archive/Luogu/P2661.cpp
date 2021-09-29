/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <initializer_list>
#include <queue>
#include <utility>
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
struct Edge {
  long long to;
  long long nxt;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
long long totANS = INF;
long long vis[maxN];
long long cntVIS;
long long DIS[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

void BFS(long long stX) {
  ++cntVIS;
  queue<long long> Q;
  Q.push(stX);
  vis[stX] = cntVIS;
  DIS[stX] = 0;
  while (!Q.empty()) {
    long long nowX = Q.front();
    Q.pop();
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (vis[vir] == cntVIS) {
        totANS = min(totANS, DIS[vir] - DIS[stX]);
      }
      if (!vis[vir]) {
        DIS[vir] = DIS[nowX] + 1;
        vis[vir] = cntVIS;
        Q.push(vir);
      }
    }
  }
}

long long totN;

int main() {
  totN = read();
  for (int i = 1, x; i <= totN; ++i) {
    x = read();
    add_edge(i, x);
  }
  for (int i = 1; i <= totN; ++i) {
    if (vis[i]) {
      continue;
    }
    BFS(i);
  }
  write(totANS);
  return 0;
} // Thomitics Code