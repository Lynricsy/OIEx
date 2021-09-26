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
long long totN;
long long nums[maxN];
long long cnt[3];
bool ONEflag;
long long nowGCD;

bool WORKit() {
  memset(cnt, 0, sizeof(cnt));
  for (int i = 1; i <= totN; ++i) {
    if (nums[i] & 1) {
      nums[i] -= 1;
      break;
    }
  }
  nowGCD = nums[1];
  for (int i = 2; i <= totN; ++i) {
    nowGCD = __gcd(nowGCD, nums[i]);
  }
  for (int i = 1; i <= totN; ++i) {
    nums[i] /= nowGCD;
  }
  for (int i = 1; i <= totN; ++i) {
    ++cnt[nums[i] & 1];
    if (nums[i] == 1) {
      ONEflag = 1;
    }
  }
  if (cnt[0] & 1) {
    return true;
  }
  if (ONEflag && cnt[0] == totN - 1) {
    if (cnt[0] & 1) {
      //   puts("First");
      return true;
    } else {
      //   puts("Second");
      return false;
    }
  }
  if ((!(cnt[0] & 1)) && cnt[1] > 1) {
    // puts("Second");
    return false;
  }
  return WORKit() ^ 1;
}

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
    ++cnt[nums[i] & 1];
    if (nums[i] == 1) {
      ONEflag = 1;
    }
  }
  if (cnt[0] & 1) {
    puts("First");
    return 0;
  }
  if (ONEflag && cnt[0] == totN - 1) {
    if (cnt[0] & 1) {
      puts("First");
      return 0;
    } else {
      puts("Second");
      return 0;
    }
  }
  if ((!(cnt[0] & 1)) && cnt[1] > 1) {
    puts("Second");
    return 0;
  }
  puts(WORKit() ^ 1 ? "First" : "Second");
  return 0;
} // Thomitics Code