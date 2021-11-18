/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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
long long totQ;

long long nums[maxN];

struct Node {
  long long l, r;
  long long val;
  long long tagC;
  long long tagA;
  Node *lch, *rch;
  void pushup() { val = max(lch->val, rch->val); }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tagC = INF;
    tagA = 0;
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
  void makeCtag(long long w) {
    tagA = 0;
    val = w;
    tagC = w;
  }
  void makeAtag(long long w) {
    tagA += w;
    val += w;
  }
  void pushdown() {
    if (tagC != INF) {
      lch->makeCtag(tagC);
      rch->makeCtag(tagC);
      tagC = INF;
    }
    if (tagA) {
      lch->makeAtag(tagA);
      rch->makeAtag(tagA);
      tagA = 0;
    }
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (l > R) || (L > r); }
  void update(long long L, long long R, long long w, bool typ) {
    if (INrange(L, R)) {
      if (typ) {
        makeCtag(w);
      } else {
        makeAtag(w);
      }
    } else if (!OUTrange(L, R)) {
      pushdown();
      lch->update(L, R, w, typ);
      rch->update(L, R, w, typ);
      pushup();
    }
  }
  long long query(long long L, long long R) {
    if (INrange(L, R)) {
      return val;
    } else if (OUTrange(L, R)) {
      return -INF;
    } else {
      pushdown();
      return max(lch->query(L, R), rch->query(L, R));
    }
  }
};

int main() {
  totN = read();
  totQ = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  Node *rot = new Node(1, totN);
  for (long long i = 1, l, r, x, opt; i <= totQ; ++i) {
    opt = read();
    l = read();
    r = read();
    if (opt == 1) {
      x = read();
      rot->update(l, r, x, true);
    } else if (opt == 2) {
      x = read();
      rot->update(l, r, x, false);
    } else if (opt == 3) {
      write(rot->query(l, r), '\n', 1);
    }
  }
  return 0;
} // Thomitics Code