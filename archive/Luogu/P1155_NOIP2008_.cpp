/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <queue>
#include <stack>
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
long long nums[maxN];
long long minp[maxN];
int col[maxN];
bool nonflag;
stack<long long> st[2];
long long nowNUM;
bool vis[maxN];

struct Edge {
  long long nxt;
  long long to;
} edges[maxN << 1];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

void prefix() {
  minp[totN + 1] = INF;
  for (int i = totN; i >= 1; --i) {
    minp[i] = min(minp[i + 1], nums[i]);
  }
  for (int i = 1; i <= totN; ++i) {
    for (int j = i + 1; j <= totN; ++j) {
      if (nums[i] < nums[j] && minp[j + 1] < nums[i]) {
        add_edge(i, j);
        add_edge(j, i);
      }
    }
  }
}

void colorIT(long long x) {
  queue<long long> Q;
  Q.push(x);
  col[x] = 0;
  vis[x] = true;
  while (!Q.empty()) {
    long long nowX = Q.front();
    Q.pop();
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (vis[vir]) {
        if (col[vir] == col[nowX]) {
          nonflag = true;
          return;
        }
        continue;
      }
      col[vir] = col[nowX] ^ 1;
      vis[vir] = true;
      Q.push(vir);
    }
  }
}

bool check(bool ws) {
  if (st[ws].empty() || st[ws].top() != nowNUM + 1) {
    return false;
  }
  return true;
}

void Pop(bool ws) {
  ++nowNUM;
  st[ws].pop();
  if (ws) {
    putchar('d');
  } else {
    putchar('b');
  }
  putchar(' ');
}

void Push(long long nx, bool ws) {
  if (ws) {
    while (check(false)) {
      Pop(false);
    }
  }
  while (!st[ws].empty() && st[ws].top() < nx) {
    if (!check(ws)) {
      Pop(ws ^ 1);
    } else {
      Pop(ws);
    }
  }
  if (ws) {
    while (check(false)) {
      Pop(false);
    }
  }
  st[ws].push(nx);
  if (ws) {
    putchar('c');
  } else {
    putchar('a');
  }
  putchar(' ');
}

void work() {
  for (int i = 1; i <= totN; ++i) {
    Push(nums[i], col[i]);
  }
  while (!st[0].empty()) {
    if (!check(0)) {
      Pop(true);
    } else {
      Pop(false);
    }
  }
  while (!st[1].empty()) {
    Pop(true);
  }
}

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  prefix();
  for (int i = 1; i <= totN; ++i) {
    if (!vis[i]) {
      colorIT(i);
    }
  }
  if (nonflag) {
    puts("0");
    return 0;
  }
  work();
  return 0;
} // Thomitics Code