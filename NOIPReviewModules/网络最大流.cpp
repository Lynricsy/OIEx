/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
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
long long totT;
long long maxFLOW;

struct Edge {
  long long to;
  long long nxt;
  long long flow;
} edges[maxN];
long long cnt_edges = 1;
long long head[maxN];
void add_edge(long long u, long long v, long long f) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].flow = f;

  ++cnt_edges;
  edges[cnt_edges].nxt = head[v];
  head[v] = cnt_edges;
  edges[cnt_edges].to = u;
  edges[cnt_edges].flow = 0;
}

long long DIS[maxN];
long long now[maxN];

bool BFS() {
  memset(DIS, 0x3f, sizeof(DIS));
  queue<long long> Q;
  Q.push(totS);
  DIS[totS] = 0;
  now[totS] = head[totS];
  while (!Q.empty()) {
    long long nowX = Q.front();
    Q.pop();
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (DIS[vir] != INF || !edges[i].flow) {
        continue;
      }
      DIS[vir] = DIS[nowX] + 1;
      now[vir] = head[vir];
      Q.push(vir);
      if (vir == totT) {
        return true;
      }
    }
  }
  return false;
}

long long DFS(long long nowX, long long inFLOW) {
  if (nowX == totT || !inFLOW) {
    return inFLOW;
  }
  long long outFLOW = 0;
  long long nowOUT = 0;
  for (int i = now[nowX]; i && inFLOW; i = edges[i].nxt) {
    long long vir = edges[i].to;
    now[nowX] = i;
    if (DIS[vir] != DIS[nowX] + 1 || !edges[i].flow) {
      continue;
    }
    nowOUT = DFS(vir, min(inFLOW, edges[i].flow));
    inFLOW -= nowOUT;
    outFLOW += nowOUT;
    edges[i].flow -= nowOUT;
    edges[i ^ 1].flow += nowOUT;
  }
  return outFLOW;
}

int main() {
  totN = read();
  totM = read();
  totS = read();
  totT = read();
  for (int i = 1, u, v, w; i <= totM; ++i) {
    u = read();
    v = read();
    w = read();
    add_edge(u, v, w);
  }
  while (BFS()) {
    maxFLOW += DFS(totS, INF);
  }
  write(maxFLOW);
  return 0;
} // Thomitics Code