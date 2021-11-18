/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cmath>
#include <cstddef>
#include <shared_mutex>
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
template <typename T>
inline void write(initializer_list<T> WRITE_NUMS, char ch) {
  for (auto i : WRITE_NUMS) {
    write(i);
    putchar(ch);
  }
}

const long long maxN = 1090;
long long totN;
long long totM;
long long nums[maxN];

struct Node {
  long long val;
  long long l, r;
  Node *lch, *rch;
  long long tag;
  void pushup() { val = lch->val + rch->val; }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag = 0;
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
    tag += w;
    val += (r - l + 1) * w;
  }
  void pushdown() {
    if (!tag) {
      return;
    }
    lch->maketag(tag);
    rch->maketag(tag);
    tag = 0;
  }
  bool INrange(long long L, long long R) { return (l >= L) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (r < L) || (R < l); }
  void update(long long L, long long R, long long w) {
    if (INrange(L, R)) {
      maketag(w);
      return;
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
      return 0;
    } else {
      pushdown();
      return lch->query(L, R) + rch->query(L, R);
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
  for (long long i = 1, opt, l, r, x; i <= totM; ++i) {
    opt = read();
    l = read();
    r = read();
    if (l > r) {
      swap(l, r);
    }
    if (opt == 1) {
      x = read();
      rot->update(l, r, x);
    } else {
      write(rot->query(l, r), '\n', 1);
    }
  }
  return 0;
} // Thomitics Code