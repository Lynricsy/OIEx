/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <new>
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
long long totK;
long long nums[maxN];
long long nowANS;

// struct Node {
//   long long val;
//   long long tag;
//   bool hav;
//   long long l, r;
//   Node *lch, *rch;
//   void pushup() {
//     val = lch->val + rch->val;
//     hav = lch->val | rch->val;
//   }
//   Node(long long L, long long R) {
//     tag = 0;
//     l = L;
//     r = R;
//     if (l == r) {
//       val = nums[l];
//       lch = rch = NULL;
//       return;
//     }
//     long long Mid = (L + R) >> 1;
//     lch = new Node(L, Mid);
//     rch = new Node(Mid + 1, R);
//     pushup();
//   }

// };

int main() {
  totK = read();
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  for (int i = 1; i <= totN; ++i) {
    if (nums[i] == i) {
      ++nowANS;
    }
  }
  if (nowANS) {
    puts("YES");
  } else {
    puts("NO");
  }
  for (int i = 1, l, r, c; i <= totK - 1; ++i) {
    l = read();
    r = read();
    c = read();
    nowANS = 0;
    for (int i = l; i <= r; ++i) {
      nums[i] += c;
    }
    for (int i = 1; i <= totN; ++i) {
      if (nums[i] == i) {
        ++nowANS;
      }
    }
    if (nowANS) {
      puts("YES");
    } else {
      puts("NO");
    }
  }
  return 0;
} // Thomitics Code