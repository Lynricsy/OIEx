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
long long a[maxN];
long long totANS;
long long totN;
long long totK;

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

long long DFS(long long nowX, long long dep) {
  long long maxD = dep;
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    maxD = max(maxD, DFS(vir, dep + 1));
  }
  if (a[nowX] - 1 && maxD - dep == totK - 1) {
    ++totANS;
    // a[nowX] = 1;
    return 0;
  }
  return maxD;
}

int main() {
  totN = read();
  totK = read();
  for (int i = 1; i <= totN; ++i) {
    a[i] = read();
  }
  if (a[1] - 1) {
    ++totANS;
    a[1] = 1;
  }
  for (int i = 2; i <= totN; ++i) {
    add_edge(a[i], i);
  }
  DFS(1, 0);
  write(totANS);
  return 0;
} // Thomitics Code