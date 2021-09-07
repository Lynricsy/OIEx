/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
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
int totN;
int totM;
int totV;
int totE;
long long C[maxN];
long long D[maxN];
long double K[maxN];
long long mp[209][209];
long double DP[2090][2090][2];
long double minANS = INF;

// struct Edge {
//   long long nxt;
//   long long to;
//   long long val;
// } edges[maxN];
// long long cnt_edges;
// long long head[maxN];
// void add_edge(long long u, long long v, long long w) {
//   ++cnt_edges;
//   edges[cnt_edges].nxt = head[u];
//   head[u] = cnt_edges;
//   edges[cnt_edges].to = v;
//   edges[cnt_edges].val = w;
// }

int main() {
  totN = read();
  totM = read();
  totV = read();
  totE = read();
  for (int i = 1; i <= totN; ++i) {
    C[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    D[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    scanf("%Lf", &K[i]);
  }
  // for (int i = 1, u, v, w; i <= totE; ++i) {
  //   u = read();
  //   v = read();
  //   w = read();
  //   add_edge(u, v, w);
  //   add_edge(v, u, w);
  // }
  memset(mp, 0x3f, sizeof(mp));
  // memset(DP, 0x3f, sizeof(DP));
  for (int i = 1, u, v; i <= totE; ++i) {
    u = read();
    v = read();
    mp[u][v] = mp[v][u] = min({mp[u][v], mp[v][u], read()});
  }
  for (int k = 1; k <= totV; ++k) {
    for (int i = 1; i <= totV; ++i) {
      for (int j = 1; j <= totV; ++j) {
        mp[i][j] = min(mp[i][j], mp[i][k] + mp[k][j]);
      }
    }
  }
  for (int i = 1; i <= totV; ++i) {
    mp[i][i] = mp[i][0] = mp[0][i] = 0;
  }
  for (int i = 0; i <= totN; ++i) {
    for (int j = 0; j <= totN; ++j) {
      DP[i][j][0] = DP[i][j][1] = INF;
    }
  }
  DP[1][0][0] = DP[1][1][1] = 0;
  for (int i = 2; i <= totN; ++i) {
    DP[i][0][0] = DP[i - 1][0][0] + mp[C[i - 1]][C[i]];
    for (int j = 1; j <= min(i, totM); ++j) {
      DP[i][j][0] = min(DP[i - 1][j][0] + mp[C[i - 1]][C[i]],
                        DP[i - 1][j][1] + mp[C[i - 1]][C[i]] * (1 - K[i - 1]) +
                            mp[D[i - 1]][C[i]] * K[i - 1]);
      DP[i][j][1] = min(DP[i - 1][j - 1][0] + mp[C[i - 1]][C[i]] * (1 - K[i]) +
                            mp[C[i - 1]][D[i]] * K[i],
                        DP[i - 1][j - 1][1] +
                            mp[C[i - 1]][C[i]] * (1 - K[i - 1]) * (1 - K[i]) +
                            mp[C[i - 1]][D[i]] * (1 - K[i - 1]) * K[i] +
                            mp[D[i - 1]][C[i]] * K[i - 1] * (1 - K[i]) +
                            mp[D[i - 1]][D[i]] * K[i - 1] * K[i]);
    }
  }
  for (int i = 0; i <= totM; ++i) {
    minANS = min(minANS, DP[totN][i][0]);
    minANS = min(minANS, DP[totN][i][1]);
  }
  printf("%.2Lf", minANS);
  return 0;
} // Thomitics Code