/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
// #include <bits/stdc++.h>
#include <cstdio>
#include <ctime>
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
long long nums[maxN];

struct Pusher {
  long long maxM;
  long long maxL, maxR;
  long long sum;
};
void Ppushup(Pusher &S, Pusher lch, Pusher rch) {
  S.sum = lch.sum + rch.sum;
  S.maxL = max(lch.maxL, lch.sum + rch.maxL);
  S.maxR = max(rch.maxR, rch.sum + lch.maxR);
  // if (rch->maxL<0&&lch->maxR<0) {
  //   maxM
  // }
  S.maxM = max({lch.maxM, rch.maxM, lch.maxR, rch.maxL, rch.maxL + lch.maxR});
}
struct Node {
  // long long val;
  Node *lch, *rch;
  long long l, r;
  long long sum;
  long long maxL, maxR;
  long long maxM;
  void pushup() {
    sum = lch->sum + rch->sum;
    maxL = max(lch->maxL, lch->sum + rch->maxL);
    maxR = max(rch->maxR, rch->sum + lch->maxR);
    // if (rch->maxL<0&&lch->maxR<0) {
    //   maxM
    // }
    maxM = max(
        {lch->maxM, rch->maxM, lch->maxR, rch->maxL, rch->maxL + lch->maxR});
  }
  Node() {}
  Node(long long L, long long R) {
    l = L;
    r = R;
    if (l == r) {
      sum = maxM = maxL = maxR = nums[l];
      lch = rch = NULL;
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (L > r) || (l > R); }
  void update(long long pos, long long w) {
    if (pos > r || pos < l) {
      return;
    }
    if (l == r) {
      sum = maxM = maxL = maxR = w;
      return;
    }
    lch->update(pos, w);
    rch->update(pos, w);
    pushup();
  }
  Pusher query(long long L, long long R) {
    if (INrange(L, R)) {
      return {maxM, maxL, maxR, sum};
    }
    // if (OUTrange(L, R)) {
    //   return {-INF, -INF, -INF, -INF};
    // }
    if (R <= lch->r) {
      return lch->query(L, R);
    }
    if (L >= rch->l) {
      return rch->query(L, R);
    }
    Pusher tmp;
    Ppushup(tmp, lch->query(L, R), rch->query(L, R));
    return tmp;
  }
};

int main() {
  totN = read();
  totM = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  Node *rot = new Node(1, totN);
  for (int i = 1, opt, x, y; i <= totM; ++i) {
    opt = read();
    x = read();
    y = read();
    if (opt == 1) {
      if (x > y) {
        swap(x, y);
      }
      write(rot->query(x, y).maxM);
      putchar('\n');
    }
    if (opt == 2) {
      rot->update(x, y);
    }
  }
  return 0;
} // Thomitics Code