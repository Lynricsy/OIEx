/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <set>
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
long long totANS;
struct Edge {
  long long nxt;
  long long to;
  long long val;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
long long Mid;
long long L;
long long R;
bool flag;
void add_edge(long long u, long long v, long long w) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
  edges[cnt_edges].val = w;
}

struct Node {
  long long val;
  long long cnt;
};

Node DFS(long long nowX, long long fath) {
  long long nowCNT = 0;
  long long edge = 0;
  multiset<long long> S;
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fath) {
      continue;
    }
    Node Nson = DFS(vir, nowX);
    if (Nson.val + edges[i].val >= Mid) {
      ++nowCNT;
    } else {
      S.insert(Nson.val + edges[i].val);
    }
    nowCNT += Nson.cnt;
  }
  while (!S.empty()) {
    auto it = S.upper_bound(0);
    long long nt = *it;
    S.erase(it);
    it = S.lower_bound(Mid - nt);
    if (it != S.end()) {
      // S.erase(nt);
      S.erase(it);
      ++nowCNT;
    } else {
      edge = nt;
      // break;
    }
  }
  if (nowCNT >= totM) {
    flag = true;
  }
  return {edge, nowCNT};
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1, u, v, w; i <= totN - 1; ++i) {
    u = read();
    v = read();
    w = read();
    add_edge(u, v, w);
    add_edge(v, u, w);
    R += w;
  }
  while (L <= R) {
    Mid = (L + R) >> 1;
    flag = false;
    DFS(1, 0);
    if (flag) {
      L = Mid + 1;
      totANS = Mid;
    } else {
      R = Mid - 1;
    }
  }
  write(totANS);
  return 0;
} // Thomitics Code