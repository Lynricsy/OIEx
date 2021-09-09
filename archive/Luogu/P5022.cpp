/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
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
long long totM;
vector<long long> edges[100090];
long long firstcm[maxN];
bool flag[maxN];
long long ans[maxN];
long long cntANS;
// bool mapp[maxN][maxN];

namespace sol01 {
void DFS(long long nowX) {
  ++cntANS;
  ans[cntANS] = nowX;
  flag[nowX] = true;
  for (auto &&i : edges[nowX]) {
    if (flag[i]) {
      continue;
    }
    flag[i] = true;
    DFS(i);
  }
}
int main() {
  for (int i = 1, x, y; i <= totM; i++) {
    x = read();
    y = read();
    // add_edges(x,y);
    // add_edges(y,x);
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  for (int i = 1; i <= totN; i++) {
    sort(edges[i].begin(), edges[i].end());
  }
  DFS(1);
  for (int i = 1; i <= totN; i++) {
    write(ans[i]);
    putchar(' ');
  }
  return 0;
}
} // namespace sol01

namespace sol02 {

long long nowANS[maxN];
long long delU;
long long delV;
struct Edge {
  long long from;
  long long to;
} tedges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edges(long long x, long long y) {
  ++cnt_edges;
  tedges[cnt_edges].from = x;
  tedges[cnt_edges].to = y;
}
bool checkDic(long long a[], long long b[]) {
  for (int i = 1; i <= totN; ++i) {
    if (a[i] != b[i]) {
      return a[i] > b[i];
    }
  }
  return false;
}
void DFS(long long nowX) {
  ++cntANS;
  nowANS[cntANS] = nowX;
  flag[nowX] = true;
  for (auto &&i : edges[nowX]) {
    if (flag[i] || (nowX == delV && i == delU) || (nowX == delU && i == delV)) {
      continue;
    }
    flag[i] = true;
    DFS(i);
  }
}
int main() {
  memset(ans, 0x3f, sizeof ans);
  for (int i = 1, x, y; i <= totM; i++) {
    x = read();
    y = read();
    add_edges(x, y);
    // add_edges(y, x);
    edges[x].push_back(y);
    edges[y].push_back(x);
  }
  for (int i = 1; i <= totN; i++) {
    sort(edges[i].begin(), edges[i].end());
  }
  for (int i = 1; i <= totM; ++i) {
    delV = tedges[i].from;
    delU = tedges[i].to;
    memset(nowANS, 0, sizeof nowANS);
    cntANS = 0;
    memset(flag, 0, sizeof(flag));
    DFS(1);
    if (checkDic(ans, nowANS) && cntANS == totN) {
      memcpy(ans, nowANS, sizeof nowANS);
    }
  }
  for (int i = 1; i <= totN; i++) {
    write(ans[i]);
    putchar(' ');
  }
  return 0;
}
} // namespace sol02

int main() {
  freopen("P5022_16.in", "r", stdin);
  freopen("P5022_16.ans", "w", stdout);
  totN = read();
  totM = read();
  if (totM == totN - 1) {
    sol01::main();
  } else {
    sol02::main();
  }
  return 0;
}