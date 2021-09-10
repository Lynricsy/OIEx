/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
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

const long long maxN = 100090;
const long long MOD = 1E8 - 3;

long long totN;
struct Node {
  long long loca;
  long long num;
} a[maxN], b[maxN];
long long totANS;
bool operator<(Node as, Node bs) { return as.num < bs.num; }

long long c[maxN];
long long tre[maxN];

long long lowbit(long long x) { return (-x) & (x); }
void add(long long x, long long w) {
  for (; x <= totN; x += lowbit(x)) {
    tre[x] += w;
    tre[x] %= MOD;
  }
}
long long query(long long x) {
  long long ret = 0;
  for (; x; x -= lowbit(x)) {
    ret += tre[x];
    ret %= MOD;
  }
  return ret;
}

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    a[i].num = read();
    a[i].loca = i;
  }
  for (int i = 1; i <= totN; ++i) {
    b[i].num = read();
    b[i].loca = i;
  }
  sort(a + 1, a + totN + 1);
  sort(b + 1, b + totN + 1);
  for (int i = 1; i <= totN; ++i) {
    c[a[i].loca] = b[i].loca;
  }
  for (int i = 1; i <= totN; ++i) {
    add(c[i], 1);
    totANS += i - query(c[i]);
    totANS %= MOD;
  }
  write(totANS);
  return 0;
} // Thomitics Code