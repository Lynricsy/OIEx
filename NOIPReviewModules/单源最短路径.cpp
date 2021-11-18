/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <climits>
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

// long long

bool vis[maxN];
long long DIS[maxN];

struct Edge {
  long long to;
  long long val;
  long long nxt;
} edges[maxN];
long long cnt_edges;
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
priority_queue<Node> Q;
void Dijkstra() {
  Q.push({totS, 0});
  DIS[totS] = 0;
  while (!Q.empty()) {
    long long nowX = Q.top().ID;
    Q.pop();
    if (vis[nowX]) {
      continue;
    }
    vis[nowX] = true;
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      long long val = edges[i].val;
      if (DIS[vir] > DIS[nowX] + val) {
        DIS[vir] = DIS[nowX] + val;
        if (!vis[vir]) {
          Q.push({vir, DIS[vir]});
        }
      }
    }
  }
}

int main() {
  totN = read();
  totM = read();
  totS = read();
  for (int i = 1, u, v, w; i <= totM; ++i) {
    u = read();
    v = read();
    w = read();
    add_edge(u, v, w);
  }
  memset(DIS, 0x3f, sizeof(DIS));
  Dijkstra();
  for (int i = 1; i <= totN; ++i) {
    write(DIS[i], ' ', 1);
  }
  return 0;
} // Thomitics Code