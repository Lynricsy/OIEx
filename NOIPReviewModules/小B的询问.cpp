/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cmath>
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
long long totK;
long long totANS;

long long nums[maxN];
long long cnt[maxN];
long long ans[maxN];

long long SIZE;

long long inB(const long long &x) { return x / SIZE; }
struct Query {
  long long l, r;
  long long ID;
} queries[maxN];

bool operator<(const Query &a, const Query &b) {
  if (inB(a.l) != inB(b.l)) {
    return a.l < b.l;
  } else {
    return (inB(a.l)) & 1 ? a.r < b.r : a.r > b.r;
  }
}

void add(const long long &x) {
  totANS += cnt[x] * 2 + 1;
  ++cnt[x];
}
void del(const long long &x) {
  totANS -= cnt[x] * 2 - 1;
  --cnt[x];
}

int main() {
  totN = read();
  totQ = read();
  totK = read();
  SIZE = (long long)sqrt(totN);
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  for (int i = 1; i <= totQ; ++i) {
    queries[i].l = read();
    queries[i].r = read();
    queries[i].ID = i;
  }
  sort(queries + 1, queries + totQ + 1);
  for (long long i = 1, l = 1, r = 0; i <= totQ; ++i) {
    while (l > queries[i].l) {
      add(nums[--l]);
    }
    while (r < queries[i].r) {
      add(nums[++r]);
    }
    while (l < queries[i].l) {
      del(nums[l++]);
    }
    while (r > queries[i].r) {
      del(nums[r--]);
    }
    ans[queries[i].ID] = totANS;
  }
  for (int i = 1; i <= totQ; ++i) {
    write(ans[i], '\n', 1);
  }
  return 0;
} // Thomitics Code