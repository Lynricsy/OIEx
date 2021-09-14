/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
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
long long nums[maxN];
unordered_set<long long> S;
// long long DIS[maxN];
unordered_map<long long, long long> DIS;
// long long deg[maxN];
unordered_map<long long, long long> deg;
queue<long long> Q;
long long maxNUM;
long long totANS;

struct Edge {
  long long nxt;
  long long to;
} edges[maxN << 1];
long long cnt_edges;
// long long head[maxN];
map<long long, long long> head;
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}
// long long cntNODE;
// map<long long, long long> M;
// long long raw[maxN];

int main() {
  freopen("poem.in", "r", stdin);
  freopen("poem.out", "w", stdout);
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
    maxNUM = max(maxNUM, nums[i]);
    // if (S.find(nums[i]) == S.end()) {
    //   ++cntNODE;
    //   M[nums[i]] = cntNODE;
    //   raw[cntNODE] = nums[i];
    // }
    S.insert(nums[i]);
  }
  for (int i = 1; i <= totN; ++i) {
    if (S.find(nums[i] << 1) != S.end()) {
      add_edge(nums[i], nums[i] << 1);
      ++deg[nums[i] << 1];
    }
    if ((!(nums[i] % 3)) && (S.find(nums[i] / 3) != S.end())) {
      add_edge(nums[i], nums[i] / 3);
      ++deg[nums[i] / 3];
    }
  }
  for (auto i : S) {
    if (!deg[i]) {
      Q.push(i);
      DIS[i] = 1;
    }
  }
  cerr << (Q.size()) << endl;
  while (!Q.empty()) {
    long long nowX = Q.front();
    Q.pop();
    for (int i = head[nowX]; i; i = edges[i].nxt) {
      long long vir = edges[i].to;
      if (DIS[vir]) {
        continue;
      }
      DIS[vir] = DIS[nowX] + 1;
      Q.push(vir);
    }
  }
  for (auto i : S) {
    totANS = max(totANS, DIS[i]);
  }
  write(totANS);
  return 0;
} // Thomitics Code