/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
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
char sta[maxN];
long long top;
char ch;
char str[maxN];
long long totANS;

int main() {
  scanf("%s", str + 1);
  long long len = strlen(str + 1);
  for (int i = 1; i <= len; ++i) {
    if (str[i] == 'P' && sta[top] == 'A') {
      top--;
    } else {
      ++top;
      sta[top] = str[i];
    }
  }
  totANS = top;
  if (sta[1] == 'A') {
    write(totANS);
    return 0;
  }
  long long i = 1;
  while (sta[i] == 'P') {
    ++i;
  }
  i -= 1;
  if (i & 1) {
    i -= 1;
  }
  totANS -= i;
  write(totANS);
  return 0;
} // Thomitics Code