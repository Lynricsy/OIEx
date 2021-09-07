/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <vector>
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
vector<short> nums[26];
long long totN;
long long lstcnt;

void proc(long long x) {
  long long nowNUM;
  long long nowCNT;
  nowNUM = nums[x - 1][0];
  nowCNT = 1;
  for (int i = 1; i < nums[x - 1].size(); ++i) {
    if (nums[x - 1][i] == nowNUM) {
      ++nowCNT;
    } else {
      nums[x].push_back(nowCNT);
      nums[x].push_back(nowNUM);
      nowNUM = nums[x - 1][i];
      nowCNT = 1;
    }
  }
  nums[x].push_back(nowCNT);
  nums[x].push_back(nowNUM);
}

int main() {
  totN = read();
  nums[1].push_back(1);
  for (int i = 2; i <= totN; ++i) {
    proc(i);
  }
  for (int i = 0; i < nums[totN].size(); ++i) {
    write(nums[totN][i]);
  }
  return 0;
} // Thomitics Code