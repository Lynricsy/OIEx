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
long long nums[maxN];
long long totN;

long long DFS(long long l, long long r, long long cl, long long cr) {
  if (r - l <= 1) {
    return 0;
  }
  long long nowANS = INF;
  for (int i = l + 1; i <= r - 1; ++i) {
    nowANS = min(nowANS, DFS(l, i, cl, cl + cr) + DFS(i, r, cl + cr, cr) +
                             nums[i] * (cl + cr));
  }
  return nowANS;
}

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  write(nums[1] + nums[totN] + DFS(1, totN, 1, 1));
  return 0;
} // Thomitics Code