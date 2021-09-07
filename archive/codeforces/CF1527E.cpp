/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstring>
// #define INF 0x3f3f3f3f3f3f3f3f
#define INF 0x3f3f3f3f

using namespace std;

inline int read() {
  int x = 0;
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

const int maxN = 35090;
int nums[maxN];
int totN;
int totK;
int DP[maxN][109];
int last[maxN];
int totANS = INF;

struct Node {
  int l, r;
  Node *lch, *rch;
  int val;
  int tag;
  void pushup() { val = min(lch->val, rch->val); }
  Node(int L, int R) {
    l = L;
    r = R;
    tag = 0;
    if (l == r) {
      val = 0;
      lch = rch = NULL;
      return;
    }
    int Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  void maketag(int w) {
    tag += w;
    val += w;
  }
  bool INrange(int L, int R) { return (L <= l) && (r <= R); }
  bool OUTrange(int L, int R) { return (L > r) || (l > R); }
  void pushdown() {
    if (!tag) {
      return;
    }
    lch->maketag(tag);
    rch->maketag(tag);
    tag = 0;
  }
  void update(int L, int R, int w) {
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
  int query(int L, int R) {
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
Node *rot[109];

int main() {
  totN = read();
  totK = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  memset(DP, 0x3f, sizeof(DP));
  DP[0][0] = 0;
  for (int i = 1; i <= totK; ++i) {
    rot[i] = new Node(1, totN);
  }
  for (int i = 1; i <= totN; ++i) {
    for (int j = 1; j <= min(totK, (int)i); ++j) {
      rot[j]->update(i, i, DP[i - 1][j - 1]);
      if (last[nums[i]]) {
        rot[j]->update(1, last[nums[i]], i - last[nums[i]]);
      }
      DP[i][j] = rot[j]->query(1, i);
    }
    last[nums[i]] = i;
  }
  for (int i = 1; i <= totK; ++i) {
    totANS = min(totANS, DP[totN][i]);
  }
  write(totANS);
  return 0;
} // Thomitics Code