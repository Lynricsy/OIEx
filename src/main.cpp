/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstring>
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
long long totW;
long long INmax;
long long L, R;
long long Mid = 114514;
long long nums[maxN];
long long cha[maxN];
long long deal[maxN];
long long nowM;
long long nowSUM;
struct Node {
  long long l, r;
  Node *lch, *rch;
  long long tag;
  long long val;
  void pushup() { val = min(lch->val, rch->val); }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag = 0;
    if (l == r) {
      lch = rch = NULL;
      val = nums[l];
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
  bool OUTrange(long long L, long long R) { return (l > R) || (L > r); }
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
    }
    if (OUTrange(L, R)) {
      return INF;
    }
    pushdown();
    return min(lch->query(L, R), rch->query(L, R));
  }
};

Node *rot;

bool check(long long x) {
  nowSUM = 0;
  nowM = totM;
  memset(deal, 0, sizeof deal);
  for (int i = 1; i <= totN; ++i) {
    if (nowSUM < x) {
      deal[i + totW] -= x - nowSUM;
      nowM -= x - nowSUM;
      write(x - nowSUM, '\n', 1);
      nowSUM = x;
    }
    if (nowM < 0) {
      return false;
    }
  }
  if (nowM < 0) {
    return false;
  }
  return true;
}

int main() {
  totN = read();
  totM = read();
  totW = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
    cha[i] = nums[i] - nums[i - 1];
    INmax = max(nums[i], INmax);
  }
  // rot = new Node(1, totN);
  L = 0;
  R = INmax + totM;
  while (L <= R) {
    Mid = (L + R) >> 1;
    if (check(Mid)) {
      L = Mid + 1;
    } else {
      R = Mid - 1;
    }
  }
  write(Mid);
  return 0;
} // Thomitics Code