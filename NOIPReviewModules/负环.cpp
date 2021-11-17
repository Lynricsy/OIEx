/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
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

long long totT;
long long totN;
long long totM;

long long DIS[maxN];
bool vis[maxN];
long long updated[maxN];
queue<long long> Q;

struct Edge {
  long long nxt;
  long long to;
  long long val;
} edges[maxN];
long long head[maxN];
long long cnt_edges;
void add_edge(long long u, long long v, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].val = w;
}
void clear(queue<long long> &q) {
  queue<long long> empty;
  swap(empty, q);
}

void SPFA() {
  while (!Q.empty()) {
    Q.pop();
  }
  memset(updated, 0, sizeof(updated));
  memset(vis, 0, sizeof(vis));
  Q.push(1);
  DIS[1] = 0;
  vis[1] = true;
  while (!Q.empty()) {
    long long nowX = Q.front();
    Q.pop();
    vis[nowX] = false;
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      long long w = edges[i].val;
      if (DIS[vir] > DIS[nowX] + w) {
        DIS[vir] = DIS[nowX] + w;
        if (!vis[vir]) {
          Q.push(vir);
          vis[vir] = true;
          ++updated[vir];
          if (updated[vir] >= totN) {
            puts("YES");
            return;
          }
        }
      }
    }
  }
  puts("NO");
}

int main() {
  totT = read();
  for (int _ = 1; _ <= totT; ++_) {
    cnt_edges = 0;
    memset(head, 0, sizeof(head));
    memset(edges, 0, sizeof(edges));
    memset(DIS, 0x3f, sizeof(DIS));
    totN = read();
    totM = read();
    for (int i = 1, u, v, w; i <= totM; ++i) {
      u = read();
      v = read();
      w = read();
      if (w > 0) {
        add_edge(u, v, w);
        add_edge(v, u, w);
      } else {
        add_edge(u, v, w);
      }
    }
    SPFA();
  }
  return 0;
} // Thomitics Code