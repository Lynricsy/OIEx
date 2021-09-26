/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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
long long totQ;
long long tim[maxN][19];
long long col[maxN];

struct Edge {
  long long nxt;
  long long to;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1, u, v; i <= totM; ++i) {
    u = read();
    v = read();
    add_edge(u, v);
    add_edge(v, u);
  }
  totQ = read();
  for (int i = 1, v, d; i <= totQ; ++i) {
    v = read();
    d = read();
    col[i] = read();
    tim[v][d] = i;
  }
  for (int i = 10; i; --i) {
    for (int j = 1; j <= totN; ++j) {
      for (int k = head[j]; k; k = edges[k].nxt) {
        long long vir = edges[k].to;
        tim[vir][i - 1] = max(tim[vir][i - 1], tim[j][i]);
      }
    }
  }
  for (int i = 1, x = 0; i <= totN; ++i) {
    for (int j = 0; j <= 10; ++j) {
      x = max((long long)x, tim[i][j]);
    }
    write(col[x], '\n', 1);
  }
  return 0;
} // Thomitics Code