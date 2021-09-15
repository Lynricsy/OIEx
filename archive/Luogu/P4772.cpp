/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <vector>
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

const long long maxN = 23;
const long long maxR = 590;

struct Node {
  long long x;
  long long y;
};

long long totR;
long long totC;
long long totN;
long long DIS[maxN][maxN];
char mapp[maxR][maxR];
// bool vis[maxR][maxR];
// vector<pair<long long,long long>> S;
Node St[maxN];
// long long Sty[maxN];
long long delt[6][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};
long long Sdis[maxN][maxN];
long long DP[(1 << 16) + 23][maxN];
string DPS[(1 << 16) + 23][maxN];

void BFS(long long nowS) {
  memset(DIS, 0, sizeof(DIS));
  // memset(vis, 0, sizeof vis);
  queue<Node> Q;
  Q.push({St[nowS]});
  DIS[St[nowS].x][St[nowS].y] = 1;
  while (!Q.empty()) {
    Node tmp = Q.front();
    Q.pop();
    // if (vis[tmp.x][tmp.y]) {
    //   continue;
    // }
    // vis[tmp.x][tmp.y] = true;
    for (int i = 1; i <= 4; ++i) {
      long long tx = tmp.x + delt[i][0];
      long long ty = tmp.y + delt[i][1];
      if (tx < 1 || ty < 1 || tx > totR || ty > totC || DIS[tx][ty] ||
          mapp[tx][ty] == '*') {
        continue;
      }
      DIS[tx][ty] = DIS[tmp.x][tmp.y] + 1;
      Q.push({tx, ty});
    }
  }
}

int main() {
  totR = read();
  totC = read();
  totN = read();
  for (int i = 1; i <= totR; ++i) {
    scanf("%s", mapp[i] + 1);
  }
  for (int i = 1; i <= totR; ++i) {
    for (int j = 1; j <= totC; ++j) {
      if (mapp[i][j] >= 'A' && mapp[i][j] <= 'Z') {
        St[mapp[i][j] - 'A' + 1].x = i;
        St[mapp[i][j] - 'A' + 1].y = j;
      }
    }
  }
  for (int i = 1; i <= totN; ++i) {
    BFS(i);
    for (int j = 1; j <= totN; ++j) {
      Sdis[i][j] = DIS[St[j].x][St[j].y] - 1;
    }
  }
  memset(DP, 0x3f, sizeof(DP));
  DP[1][1] = 0;
  DPS[1][1] = "A";
  for (long long i = 2; i < (1 << (totN)); ++i) {
    if (!(i & 1)) {
      continue;
    }
    for (int j = 1; j <= totN; ++j) {
      if (!(i & (1 << (j - 1)))) {
        continue;
      }
      for (int k = 2; k <= totN; ++k) {
        if (!(i & (1 << (k - 1))) || j == k) {
          continue;
        }
        if (DP[i][k] > DP[i ^ (1 << (k - 1))][j] + Sdis[j][k]) {
          DP[i][k] = DP[i ^ (1 << (k - 1))][j] + Sdis[j][k];
          DPS[i][k] = DPS[i ^ (1 << (k - 1))][j] + char(k + 'A' - 1);
        }
        if (DP[i][k] == DP[i ^ (1 << (k - 1))][j] + Sdis[j][k] &&
            (DPS[i][k] > (DPS[i ^ (1 << (k - 1))][j] + char(k + 'A' - 1)))) {
          DPS[i][k] = DPS[i ^ (1 << (k - 1))][j] + char(k + 'A' - 1);
        }
      }
    }
  }
  long long Epos = (1 << totN) - 1;
  string ans = DPS[Epos][2];
  long long minANS = DP[Epos][2];
  for (int i = 3; i <= totN; ++i) {
    if (minANS > DP[Epos][i]) {
      minANS = DP[Epos][i];
      ans = DPS[Epos][i];
    } else if (minANS == DP[Epos][i] && ans > DPS[Epos][i]) {
      ans = DPS[Epos][i];
    }
  }
  write(minANS);
  putchar('\n');
  for (auto i : ans) {
    putchar(i);
  }
  return 0;
} // Thomitics Code