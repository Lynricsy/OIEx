/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <atomic>
#include <bits/stdc++.h>
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

const long long maxN = 39;
long long totN;
long long totM;
short mapp[maxN][maxN];
long long idx[maxN][maxN];
bool vis[maxN][maxN];
long long DIS[maxN * maxN];
long long totS;
bool Dvis[maxN * maxN];

long long delt[8][2] = {{-2, 1}, {1, -2}, {-1, 2},  {2, -1},
                        {1, 2},  {2, 1},  {-1, -2}, {-2, -1}};
struct Edge {
  long long nxt;
  long long to;
  long long val;
} edges[maxN * maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].val = 1;
}
struct Node {
  long long ID;
  long long dis;
};

void DFS(long long ID, long long x, long long y) {
  if (vis[x][y]) {
    return;
  }
  vis[x][y] = true;
  for (int i = 0; i < 8; ++i) {
    long long tx = x + delt[i][0];
    long long ty = y + delt[i][1];
    if (vis[tx][ty]) {
      continue;
    }
    if (mapp[tx][ty] == 1) {
      DFS(idx[tx][ty], tx, ty);
    }
    add_edge(ID, idx[tx][ty]);
  }
}
void Dijkstra() {
  memset(DIS, 0x3f, sizeof DIS);
  priority_queue<Node> Q;
  Q.push({totS, 0});
  DIS[totS] = 0;
  while (!Q.empty()) {
    Node tmp = Q.top();
    Q.pop();
    long long nowX = tmp.ID;
    if (Dvis[nowX]) {
      continue;
    }
    Dvis[nowX] = 1;
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (DIS[vir] > DIS[nowX] + edges[i].val) {
        DIS[vir] = DIS[nowX] + edges[i].val;
        Q.push({vir, DIS[vir]});
      }
    }
  }
}

void prefix() {
  for (int i = 1; i <= maxN - 2; ++i) {
    for (int j = 1; j <= maxN - 2; ++j) {
      idx[i][j] = (i - 1) * totM + j;
    }
  }
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= totM; ++j) {
      mapp[i][j] = read();
    }
  }
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= totM; ++j) {
      if (mapp[i][j] == 3 || !mapp[i][j]) {
        DFS(idx[i][j], i, j);
      }
    }
  }
  return 0;
} // Thomitics Code