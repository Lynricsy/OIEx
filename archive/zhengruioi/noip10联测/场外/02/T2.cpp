/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
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
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

const long long maxN = 10090;
long long totA;
long long totK;
bool DisAble[maxN];
bool vis[maxN];
long long cnt_nodes;

struct Node {
  long long pre;
  long long val;
  long long tw;
} nodes[maxN];

void print(long long nowX) {
  if (!nowX) {
    return;
  }
  print(nodes[nowX].pre);
  write(nodes[nowX].val);
}

int main() {
  totA = read();
  totK = read();
  for (int i = 1; i <= totK; ++i) {
    long long x = read();
    DisAble[x] = true;
  }
  queue<long long> Q;
  nodes[cnt_nodes] = {1, 0, 0};
  Q.push(cnt_nodes);
  while (!Q.empty()) {
    long long nw = Q.front();
    int i = 0;
    Q.pop();
    if (!nw) {
      ++i;
    }
    for (; i <= 9; ++i) {
      if (DisAble[i]) {
        continue;
      }
      // long long nowX = nw.tw;
      long long nowV = (nodes[nw].tw * 10 + i) % totA;
      if (vis[nowV]) {
        continue;
      }
      vis[nowV] = true;
      if (!nowV) {
        print(nw);
        write(i);
        return 0;
      }
      ++cnt_nodes;
      nodes[cnt_nodes].tw = nowV;
      nodes[cnt_nodes].val = i;
      nodes[cnt_nodes].pre = nw;
      Q.push(cnt_nodes);
    }
  }
  puts("-1");
  return 0;
} // Thomitics Code