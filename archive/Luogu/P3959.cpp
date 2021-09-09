/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstring>
#define INF 1061109567
#define IINF 0x3f3f3f3f

using namespace std;

inline unsigned int read() {
  unsigned int x = 0;
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

const unsigned int maxN = 23;
unsigned int totN;
unsigned int totM;
unsigned int edges[maxN][1090];
unsigned int deg[maxN];
unsigned int val[maxN][maxN];
unsigned int totANS = INF;
unsigned int DIS[maxN];
unsigned int vt[maxN];
unsigned int cntNODE;
unsigned int tmpCMP;
unsigned int calcMIN;
unsigned int nowTOT;

bool cmp(unsigned int a, unsigned int b) {
  return val[tmpCMP][a] < val[tmpCMP][b];
}

void DFS(unsigned int num, unsigned int maxv) {
  for (int i = num; i <= cntNODE; ++i) {
    if (nowTOT + DIS[vt[i]] * calcMIN >= totANS) {
      return;
    }
    for (int j = maxv; j <= deg[vt[i]]; ++j) {
      if (!DIS[edges[vt[i]][j]]) {
        ++cntNODE;
        vt[cntNODE] = edges[vt[i]][j];
        calcMIN -= val[vt[cntNODE]][edges[vt[cntNODE]][1]];
        nowTOT += val[vt[i]][vt[cntNODE]] * DIS[vt[i]];
        DIS[vt[cntNODE]] = DIS[vt[i]] + 1;
        DFS(i, j + 1);
        nowTOT -= val[vt[i]][vt[cntNODE]] * DIS[vt[i]];
        DIS[vt[cntNODE]] = 0;
        calcMIN += val[vt[cntNODE]][edges[vt[cntNODE]][1]];
        --cntNODE;
      }
    }
    maxv = 1;
  }
  if (cntNODE == totN) {
    totANS = min(nowTOT, totANS);
    return;
  }
}

int main() {
  totN = read();
  totM = read();
  memset(val, 0x3f, sizeof val);
  for (int i = 1, u, v, w; i <= totM; ++i) {
    u = read();
    v = read();
    w = read();
    if (val[u][v] < w) {
      continue;
    }
    if (val[u][v] == INF) {
      ++deg[u];
      ++deg[v];
      edges[u][deg[u]] = v;
      edges[v][deg[v]] = u;
    }
    val[u][v] = val[v][u] = w;
  }
  for (int i = 1; i <= totN; ++i) {
    tmpCMP = i;
    sort(edges[i] + 1, edges[i] + totN + 1, cmp);
    calcMIN += val[i][edges[i][1]];
  }
  for (int i = 1; i <= totN; ++i) {
    nowTOT = 0;
    cntNODE = 1;
    calcMIN -= val[i][edges[i][1]];
    vt[1] = i;
    DIS[i] = 1;
    DFS(1, 1);
    DIS[i] = 0;
    calcMIN += val[i][edges[i][1]];
  }
  write(totANS);
  return 0;
} // Thomitics Code