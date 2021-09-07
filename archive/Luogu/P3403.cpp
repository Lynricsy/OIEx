/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstring>
#include <queue>
#include <valarray>
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
long long totX;
long long totY;
long long totZ;

struct Edge {
  long long nxt;
  long long to;
  long long val;
} edges[maxN << 1];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].val = w;
}
long long DIS[maxN];
bool vis[maxN];
long long totANS;

struct Node {
  long long ID;
  long long DIS;
};
bool operator<(Node a, Node b) { return a.DIS > b.DIS; }

void Dijkstra() {
  priority_queue<Node> Q;
  Q.push({1, 1});
  // vis[1] = true;
  DIS[1] = 1;
  while (!Q.empty()) {
    long long nx = Q.top().ID;
    Q.pop();
    if (vis[nx]) {
      continue;
    }
    vis[nx] = true;
    for (int i = head[nx]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (DIS[vir] > DIS[nx] + edges[i].val) {
        DIS[vir] = DIS[nx] + edges[i].val;
        // if (!vis[vir]) {
        Q.push({vir, DIS[vir]});
        // }
      }
    }
  }
}
// priority_queue<Node> Q;
// void Dijkstra() {
//   memset(vis, 0, sizeof(vis));
//   Q.push({0, 1});
//   DIS[1] = 0;
//   while (!Q.empty()) {
//     int x = Q.top().ID;
//     Q.pop();
//     if (vis[x]) {
//       continue;
//     }
//     vis[x] = 1;
//     for (int i = head[x]; i; i = edges[i].nxt) {
//       long long y = edges[i].to;
//       if (DIS[y] > DIS[x] + edges[i].val) {
//         DIS[y] = DIS[x] + edges[i].val;
//         if (!vis[y]) {
//           Q.push({DIS[y], y});
//         }
//       }
//     }
//   }
// }

int main() {
  totN = read();
  totX = read();
  totY = read();
  totZ = read();
  if (totX == 1 || totY == 1 || totZ == 1) {
    write(totN);
    return 0;
  }
  for (int i = 0; i < totX; ++i) {
    add_edge(i, (i + totY) % totX, totY);
    add_edge(i, (i + totZ) % totX, totZ);
  }
  memset(DIS, 0x3f, sizeof DIS);
  Dijkstra();
  for (int i = 0; i < totX; ++i) {
    if (DIS[i] <= totN) {
      totANS += (totN - DIS[i]) / totX + 1;
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code