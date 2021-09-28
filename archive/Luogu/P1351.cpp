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
const long long MOD = 10007;

long long totN;
long long maxANS;
long long totANS;
long long val[maxN];
long long deg[maxN];

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
  for (int i = 1, u, v; i <= totN - 1; ++i) {
    u = read();
    v = read();
    add_edge(u, v);
    add_edge(v, u);
    ++deg[u];
    ++deg[v];
  }
  for (int i = 1; i <= totN; ++i) {
    val[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    if (deg[i] == 1) {
      continue;
    }
    long long max1 = 0;
    long long max2 = 0;
    long long sumP = 0;
    long long Psum = 0;
    for (int j = head[i]; j; j = edges[j].nxt) {
      long long vir = edges[j].to;
      if (val[vir] > max1) {
        max2 = max1;
        max1 = val[vir];
      } else if (val[vir] > max2) {
        max2 = val[vir];
      }
      sumP = (sumP + val[vir] % MOD * val[vir] % MOD) % MOD;
      Psum = (Psum + val[vir]) % MOD;
    }
    Psum *= Psum;
    Psum %= MOD;
    totANS = (totANS + Psum - sumP + MOD) % MOD;
    if (max1 && max2) {
      maxANS = max(maxANS, max1 * max2);
    }
  }
  write(maxANS, ' ', 1);
  write((totANS + MOD) % MOD);
  return 0;
} // Thomitics Code