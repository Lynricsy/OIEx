/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
// #include <bits/stdc++.h>
#include <cstring>
#include <future>
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
long long totN;
long long totL;
long long totR;
long long nums[20];
long long totANS;
struct Edge {
  long long nxt;
  long long to;
  long long val;
} edges[maxN];
long long cnt_edges;
long long cntA;
long long minA = INF;
long long head[maxN];
void add_edge(long long u, long long v, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].val = w;
}
struct Node {
  long long ID;
  long long dis;
};
bool operator<(Node a, Node b) { return a.dis > b.dis; }
long long DIS[maxN];
bool vis[maxN];

void Dijkstra() {
  priority_queue<Node> Q;
  Q.push({0, 0});
  DIS[0] = 0;
  while (!Q.empty()) {
    long long nowX = Q.top().ID;
    Q.pop();
    if (vis[nowX]) {
      continue;
    }
    vis[nowX] = true;
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (DIS[vir] > DIS[nowX] + edges[i].val) {
        DIS[vir] = DIS[nowX] + edges[i].val;
        Q.push({vir, DIS[vir]});
      }
    }
  }
}

long long query(long long x) {
  long long nowANS = 0;
  for (int i = 0; i < minA; ++i) {
    if (DIS[i] <= x) {
      nowANS += (x - DIS[i]) / minA + 1;
    }
  }
  return nowANS;
}

int main() {
  totN = read();
  totL = read();
  totR = read();
  for (int i = 1, x; i <= totN; ++i) {
    x = read();
    if (x) {
      ++cntA;
      nums[cntA] = x;
      minA = min(minA, (long long)x);
    }
  }
  for (int i = 0; i < minA; ++i) {
    for (int j = 1; j <= cntA; ++j) {
      if (nums[j] != minA) {
        add_edge(i, (i + nums[j]) % minA, nums[j]);
      }
    }
  }
  memset(DIS, 0x3f, sizeof DIS);
  Dijkstra();
  totANS = query(totR) - query(totL - 1);
  write(totANS);
  return 0;
} // Thomitics Code