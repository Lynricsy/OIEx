/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
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
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

const int maxN = 1000090;
int totN;
int totM;
int fst[maxN];
bool Cflag;

struct Node {
  int l, r;
  int val;
  int tag;
  Node *lch, *rch;
  void pushup() {
    val = 0;
    if (lch) {
      val += lch->val;
    }
    if (rch) {
      val += rch->val;
    }
  }
  Node(int L, int R) {
    l = L;
    r = R;
    tag = 0;
    if (l == r) {
      val = fst[l];
      lch = rch = NULL;
      return;
    }
    int Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  bool INrange(int L, int R) { return (L <= l) && (r <= R); }
  bool OUTrange(int L, int R) { return (L > r) || (l > R); }
  void update(int pos) {
    if (pos < l || pos > r) {
      return;
    }
    if (l == r && l == pos) {
      ++val;
      pushup();
      return;
    }
    lch->update(pos);
    rch->update(pos);
    pushup();
  }
  void del(int K) {
    if (l == r) {
      --val;
      return;
    }
    if (lch->val >= K) {
      lch->del(K);
      pushup();
      return;
    }
    if (lch->val + 1 == K) {
      rch->ldel();
      pushup();
      return;
    }
    K -= (lch->val);
    rch->del(K);
    pushup();
  }
  void ldel() {
    if (l == r) {
      --val;
      return;
    }
    lch->ldel();
    pushup();
  }
  int edt() {
    if (!val) {
      return 0;
    }
    if (l == r && val) {
      return l;
    }
    if (lch->val) {
      return lch->edt();
    }
    return rch->edt();
  }
};

int main() {
  totN = read();
  totM = read();
  for (int i = 1, x; i <= totN; ++i) {
    x = read();
    ++fst[x];
  }
  Node *rot = new Node(1, totN);
  for (int i = 1, x; i <= totM; ++i) {
    x = read();
    if (x < 0) {
      x = -x;
      if (rot->val < x) {
        continue;
      }
      rot->del(x);
    } else {
      rot->update(x);
    }
  }
  write(rot->edt());
  return 0;
} // Thomitics Code