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
long long totN;
long long cnt;
// struct Edge {
//   long long to;
//   long long nxt;
// } edges[maxN];
// long long head[maxN];
// long long cnt_edges;
// void add_edge(long long u, long long v) {
//   ++cnt_edges;
//   edges[cnt_edges].nxt = head[u];
//   head[u] = cnt_edges;
//   edges[cnt_edges].to = v;
// }

char str[maxN];
long long DP[maxN][3];
int FC[maxN][3];
long long maxANS;

void DFS(long long x) {
  if (str[x] == '0') {
    DP[x][0] = 1;

    FC[x][0] = 1;
    return;
  }
  DFS(++cnt);
  if (str[x] == '1') {
    DP[x][0] = max(DP[x + 1][1], DP[x + 1][2]) + 1;
    DP[x][1] = max(DP[x + 1][0], DP[x + 1][2]);
    DP[x][2] = max(DP[x + 1][1], DP[x + 1][0]);

    FC[x][0] = min(FC[x + 1][1], FC[x + 1][2]) + 1;
    FC[x][1] = min(FC[x + 1][0], FC[x + 1][2]);
    FC[x][2] = min(FC[x + 1][1], FC[x + 1][0]);
  } else {
    long long nK = ++cnt;
    DFS(nK);
    DP[x][0] = max(DP[x + 1][1] + DP[nK][2], DP[x + 1][2] + DP[nK][1]) + 1;
    DP[x][1] = max(DP[x + 1][0] + DP[nK][2], DP[x + 1][2] + DP[nK][0]);
    DP[x][2] = max(DP[x + 1][1] + DP[nK][0], DP[x + 1][0] + DP[nK][1]);

    FC[x][0] = min(FC[x + 1][1] + FC[nK][2], FC[x + 1][2] + FC[nK][1]) + 1;
    FC[x][1] = min(FC[x + 1][0] + FC[nK][2], FC[x + 1][2] + FC[nK][0]);
    FC[x][2] = min(FC[x + 1][1] + FC[nK][0], FC[x + 1][0] + FC[nK][1]);
  }
  maxANS = max(DP[x][0], maxANS);
}

int main() {
  scanf("%s", str + 1);
  totN = strlen(str + 1);
  DFS(++cnt);
  write(maxANS);
  putchar(' ');
  write(min({FC[1][0], FC[1][1], FC[1][2]}));
  return 0;
} // Thomitics Code