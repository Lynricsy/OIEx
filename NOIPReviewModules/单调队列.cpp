/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <deque>
#include <queue>
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
long long totK;

struct Node {
  long long tim;
  long long num;
};
deque<Node> AQ;
deque<Node> IQ;
long long nums[maxN];

void GetMax() {
  // AQ.push_back({1, nums[1]});
  for (int i = 1; i <= totN; ++i) {
    while (!AQ.empty() && AQ.back().num < nums[i]) {
      AQ.pop_back();
    }
    AQ.push_back({i, nums[i]});
    if (AQ.front().tim <= i - totK) {
      AQ.pop_front();
    }
    if (i >= totK) {
      write(AQ.front().num, ' ', 1);
    }
  }
  putchar('\n');
}
void GetMin() {
  // IQ.push_back({1, nums[1]});
  for (int i = 1; i <= totN; ++i) {
    while (!IQ.empty() && IQ.back().num > nums[i]) {
      IQ.pop_back();
    }
    IQ.push_back({i, nums[i]});
    if (IQ.front().tim <= i - totK) {
      IQ.pop_front();
    }
    if (i >= totK) {
      write(IQ.front().num, ' ', 1);
    }
  }
  putchar('\n');
}

int main() {
  totN = read();
  totK = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  GetMin();
  GetMax();
  return 0;
} // Thomitics Code