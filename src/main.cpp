/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <map>
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
const int maxN = 4e5 + 10;

int totN;
int nums[maxN], aims[maxN];
long long ta[maxN], tb[maxN];
long long sa, sb;
long long tot = 0, date[maxN], fa[maxN];
map<long long, bool> ti;

int find(int x) { return fa[x] == x ? fa[x] : fa[x] = find(fa[x]); }
void unionn(int x, int y) { fa[x] = y; }

int main() {
  totN = read();
  for (int i = 1; i <= totN; i++)
    nums[i] = read(), sa ^= nums[i];
  nums[totN + 1] = sa;
  for (int i = 1; i <= totN; i++)
    aims[i] = read(), sb ^= aims[i];
  aims[totN + 1] = sb;
  totN++;
  memcpy(ta, nums, sizeof(nums));
  memcpy(tb, aims, sizeof(aims));
  sort(ta + 1, ta + totN + 1);
  sort(tb + 1, tb + totN + 1);
  for (int i = 1; i <= totN - 1; i++)
    if (ta[i] != tb[i])
      return puts("-1"), 0;

  int ans = 0, num = 0;
  for (int i = 1; i <= totN; i++)
    if (nums[i] != aims[i] || (i == totN)) {
      date[++num] = nums[i];
      date[++num] = aims[i];
      if (i < totN)
        ans++;
    }
  if (ans == 0)
    return puts("0"), 0;

  sort(date + 1, date + num + 1);
  num = unique(date + 1, date + num + 1) - date - 1;
  for (int i = 1; i <= num; i++)
    fa[i] = i;
  for (int i = 1; i <= totN; i++)
    if (nums[i] != aims[i]) {
      nums[i] = lower_bound(date + 1, date + num + 1, nums[i]) - date,
      aims[i] = lower_bound(date + 1, date + num + 1, aims[i]) - date;
      if (!ti[nums[i]])
        ti[nums[i]] = 1;
      if (!ti[aims[i]])
        ti[aims[i]] = 1;
      unionn(find(nums[i]), find(aims[i]));
    }

  for (int i = 1; i <= num; i++)
    if (fa[i] == i)
      ans++;
  write(ans - 1);
  return 0;
}
