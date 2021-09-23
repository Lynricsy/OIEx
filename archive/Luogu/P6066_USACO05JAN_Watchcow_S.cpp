/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <stack>
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
stack<long long> S;
vector<long long> ans;
bool vis[maxN];
struct Edge {
  long long nxt;
  long long to;
} edges[maxN << 1];
long long cnt_edges = 1;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}
void Euler() {
  S.push(1);
  while (!S.empty()) {
    long long nowX = S.top();
    long long i = head[nowX];
    while (i && vis[i]) {
      i = edges[i].nxt;
    }
    if (i) {
      vis[i] = true;
      S.push(edges[i].to);
      head[nowX] = edges[i].nxt;
    } else {
      ans.push_back(nowX);
      S.pop();
    }
  }
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
  Euler();
  for (auto i : ans) {
    write(i, '\n', 1);
  }
  return 0;
} // Thomitics Code