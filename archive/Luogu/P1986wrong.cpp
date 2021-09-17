/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdlib>
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

struct Node {
  long long l, r;
  long long tag;
  long long val;
  Node *rch, *lch;
  void pushup() { val = lch->val + rch->val; }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag = 0;
    if (l == r) {
      val = 0;
      lch = rch = NULL;
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  void maketag(long long w) {
    val += (r - l + 1) * w;
    tag += w;
  }
  void pushdown() {
    if (!tag) {
      return;
    }
    lch->maketag(tag);
    rch->maketag(tag);
    tag = 0;
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (l > R) || (L > r); }
  void update(long long L, long long R) {
    if (INrange(L, R)) {
      maketag(1);
      return;
    } else if (!OUTrange(L, R)) {
      pushdown();
      lch->update(L, R);
      rch->update(L, R);
      pushup();
    }
  }
  long long query(long long L, long long R) {
    if (INrange(L, R)) {
      return val;
    } else if (OUTrange(L, R)) {
      return 0;
    } else {
      pushdown();
      return lch->query(L, R) + rch->query(L, R);
    }
  }
};

struct Query {
  long long a;
  long long b;
  long long c;
} Q[maxN];
bool operator<(Query a, Query b) {
  if (a.a == b.a) {
    return a.b < b.b;
  }
  return a.a < b.a;
}

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totM; ++i) {
    Q[i].a = read();
    Q[i].b = read();
    Q[i].c = read();
  }
  Node *rot = new Node(1, totN);
  sort(Q + 1, Q + totM + 1);
  for (int i = 1; i <= totM; ++i) {
    long long nowC = rot->query(Q[i].a, Q[i].b);
    if (nowC < Q[i].c) {
      rot->update(Q[i].b - (Q[i].c - nowC) + 1, Q[i].b);
    }
  }
  write(rot->query(1, totN));
  return 0;
} // Thomitics Code