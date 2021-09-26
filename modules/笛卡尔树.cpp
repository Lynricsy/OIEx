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

const long long maxN = 1090;
struct Node {
  long long lch;
  long long rch;
} nodes[maxN];
long long nums[maxN];
long long totN;
long long Sta[maxN << 1];
long long top;
long long pos;
long long L;
long long R;

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    pos = top;
    while (pos && nums[Sta[pos]] > nums[i]) {
      --pos;
    }
    nodes[Sta[pos]].rch = i;
    if (pos < top) {
      nodes[i].lch = Sta[pos + 1];
    }
    top = pos + 1;
    Sta[top] = i;
  }
  for (int i = 1; i <= totN; ++i) {
    L ^= i * (nodes[i].lch + 1);
    R ^= i * (nodes[i].rch + 1);
  }
  write(L, ' ', 1);
  write(R);
  return 0;
} // Thomitics Code