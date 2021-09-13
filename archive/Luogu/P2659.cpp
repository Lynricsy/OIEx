/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
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
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

const long long maxN = 20090;
long long totANS = -1;
struct Node {
  long long id;
  long long num;
} nums[maxN], sta[maxN];
long long totN;
long long top;

int main() {
  totN = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i].num = read();
    nums[i].id = i;
  }
  for (int i = 1; i <= totN; ++i) {
    if (!top) {
      sta[++top] = nums[i];
    } else {
      while (sta[top].num > nums[i].num) {
        totANS = max(totANS, sta[top].num * (i - sta[top - 1].id - 1));
        --top;
      }
      sta[++top] = nums[i];
    }
  }
  for (int i = 1; i <= top; ++i) {
    totANS = max(totANS, sta[i].num * (totN - sta[i - 1].id));
  }
  write(totANS);
  return 0;
} // Thomitics Code