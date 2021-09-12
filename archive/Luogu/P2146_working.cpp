/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <future>
#include <iostream>
#include <ratio>
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
long long totQ;
struct Edge {
  long long nxt;
  long long to;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

long long siz[maxN];
long long dep[maxN];
long long top[maxN];
long long Sson[maxN];
long long nums[maxN];
long long ID[maxN];
long long fa[maxN];
long long cntNODE;

void DFS1(long long nowX, long long fath) {
  siz[nowX] = 1;
  dep[nowX] = dep[fath] + 1;
  fa[nowX] = fath;
  long long maxx = -1;
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fath) {
      continue;
    }
    DFS1(vir, nowX);
    siz[nowX] += siz[vir];
    if (siz[nowX] > maxx) {
      maxx = siz[nowX];
      Sson[nowX] = vir;
    }
  }
}
void DFS2(long long nowX, long long ftop) {
  top[nowX] = ftop;
  ++cntNODE;
  ID[nowX] = cntNODE;
  if (!Sson[nowX]) {
    return;
  }
  DFS2(Sson[nowX], ftop);
  for (int i = head[nowX]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa[nowX] || vir == Sson[nowX]) {
      continue;
    }
    DFS2(vir, vir);
  }
}
struct Node {
  long long l, r;
  long long val0, val1;
  long long tag0, tag1;
  Node *lch, *rch;
  void pushup() {
    val0 = lch->val0 + rch->val0;
    val1 = lch->val1 + rch->val1;
  }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag0 = 0;
    tag1 = 0;
    if (l == r) {
      val0 = 1;
      val1 = 0;
      lch = rch = NULL;
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  void maketag(bool w) {
    if (w) {
      if (tag0) {
        tag0 = 0;
      }
      tag1 = 1;
      val1 = (r - l + 1);
      val0 = 0;
    } else {
      if (tag1) {
        tag1 = 0;
      }
      tag0 = 1;
      // tag0=1;
      val1 = 0;
      val0 = (r - l + 1);
    }
  }
  void pushdown() {
    if (!tag0 && !tag1) {
      return;
    }
    if (tag1) {
      lch->maketag(true);
      rch->maketag(true);
    } else {
      lch->maketag(false);
      rch->maketag(false);
    }
    tag0 = tag1 = 0;
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (l > R) || (L > r); }
  void update(long long L, long long R, bool w) {
    if (INrange(L, R)) {
      maketag(w);
    } else if (!OUTrange(L, R)) {
      pushdown();
      lch->update(L, R, w);
      rch->update(L, R, w);
      pushup();
    }
  }
  long long query(long long L, long long R, bool typ) {
    if (INrange(L, R)) {
      if (typ) {
        return val1;
      } else {
        return val0;
      }
    }
    if (OUTrange(L, R)) {
      return 0;
    }
    pushdown();
    return lch->query(L, R, typ) + rch->query(L, R, typ);
  }
};

Node *rot;

void updRange(long long L, long long R, bool typ) {
  // long long nowANS=0;
  while (top[L] != top[R]) {
    if (dep[top[L]] < dep[top[R]]) {
      swap(L, R);
    }
    rot->update(ID[top[L]], ID[L], typ);
    L = fa[top[L]];
  }
  if (dep[L] < dep[R]) {
    swap(L, R);
  }
  rot->update(ID[R], ID[L], typ);
}

long long qRange(long long L, long long R, bool typ) {
  long long nowANS = 0;
  while (top[L] != top[R]) {
    if (dep[top[L]] < dep[top[R]]) {
      swap(L, R);
    }
    nowANS += rot->query(ID[top[L]], ID[L], typ);
    L = fa[top[L]];
  }
  if (dep[L] < dep[R]) {
    swap(L, R);
  }
  nowANS += rot->query(ID[R], ID[L], typ);
  return nowANS;
}

void updTree(long long x, bool typ) {
  rot->update(ID[x], ID[x] + siz[x] - 1, typ);
}
long long qTree(long long x, bool typ) {
  return rot->query(ID[x], ID[x] + siz[x] - 1, typ);
}

string opt;

int main() {
  freopen("P2146_2.in", "r", stdin);
  freopen("ans.ans", "w", stdout);
  totN = read();
  for (int i = 2, u; i <= totN; ++i) {
    u = read() + 1;
    add_edge(u, i);
  }
  DFS1(1, 0);
  DFS2(1, 1);
  rot = new Node(1, totN);
  totQ = read();
  for (int i = 1, x; i <= totQ; ++i) {
    // if (!(i % 5000)) {
    //   cerr << "OK!5000Passed" << endl;
    // }
    cin >> opt;
    x = read() + 1;
    if (opt == "install") {
      write(qRange(1, x, false));
      putchar('\n');
      updRange(0, x, true);
    } else {
      write(qTree(x, true));
      putchar('\n');
      updTree(x, false);
    }
  }
  return 0;
} // Thomitics Code