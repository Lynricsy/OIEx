/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <csetjmp>
#include <cstdint>
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

const long long maxN = 1090;

long long totT;
long long totN;
long long A[maxN];
long long Au[maxN];
long long B[maxN];
long long D[maxN];
long long raw[maxN];
long long DP[maxN][maxN];

struct Node {
  long long l, r;
  Node *lch, *rch;
  long long val;
  void pushup() { val = max(lch->val, rch->val); }
  Node(long long L, long long R) {
    l = L;
    r = R;
    if (l == r) {
      lch = rch = NULL;
      val = D[l];
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
  }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (L > r) || (l > R); }
  long long query(long long L, long long R) {
    if (INrange(L, R)) {
      return val;
    }
    if (OUTrange(L, R)) {
      return -INF;
    }
    return max(lch->query(L, R), rch->query(L, R));
  }
};

int main() {
  totT = read();
  while (totT--) {
    for (int i = 1; i <= totN; ++i) {
      A[i] = read();
      Au[i * 2] = A[i];
      B[i] = read();
      Au[i + 1] = B[i];
      D[i] = read();
    }
    Node *rot = new Node(1, totN);
    sort(Au + 1, Au + 2 * totN + 1);
    long long tmpT = unique(Au + 1, Au + 2 * totN + 1) - Au - 1;
    for (int i = 1; i <= totN; ++i) {
      A[i] = lower_bound(Au + 1, Au + tmpT + 1, A[i]) - Au - 1;
      B[i] = lower_bound(Au + 1, Au + tmpT + 1, B[i]) - Au - 1;
    }
    for (int len = 2; len <= totN; ++len) {
      for (int i = 1; i + len - 1 <= totN; ++i) {
        long long j = i + len - 1;
        for (int k = i; k <= j; ++k) {
          DP[i][j] = max(DP[i][j], DP[i][k] + DP[k + 1][j] + rot->query(i, j));
        }
      }
    }
  }
  return 0;
} // Thomitics Code