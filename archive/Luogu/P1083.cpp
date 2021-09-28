/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
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
long long nums[maxN];

struct Order {
  long long num;
  long long st;
  long long ed;
} orders[maxN];

struct Node {
  long long l, r;
  long long val;
  long long tag;
  bool _tag;
  Node *lch, *rch;
  void pushup() { val = min(lch->val, rch->val); }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag = 0;
    _tag = false;
    if (l == r) {
      val = nums[l];
      lch = rch = NULL;
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  void maketag(long long w) {
    val += w;
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
  bool OUTrange(long long L, long long R) { return (L > r) || (l > R); }
  void update(long long L, long long R, long long w) {
    if (INrange(L, R)) {
      maketag(w);
    } else if (!OUTrange(L, R)) {
      pushdown();
      lch->update(L, R, w);
      rch->update(L, R, w);
      pushup();
    }
  }
  long long query(long long L, long long R) {
    if (INrange(L, R)) {
      return val;
    } else if (OUTrange(L, R)) {
      return INF;
    } else {
      pushdown();
      return min(lch->query(L, R), rch->query(L, R));
    }
  }
};

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  Node *rot = new Node(1, totN);
  for (int i = 1, x, l, r; i <= totM; ++i) {
    x = read();
    l = read();
    r = read();
    rot->update(l, r, -x);
    if (rot->query(1, totN) < 0) {
      puts("-1");
      write(i);
      return 0;
    }
  }
  puts("0");
  return 0;
} // Thomitics Code