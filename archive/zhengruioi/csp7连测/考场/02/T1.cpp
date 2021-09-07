/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

using namespace std;

inline __int128_t read() {
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

__int128_t a[10];
bool flag = false;
char str[190];
long long len;
long long now = 1;
bool nflag = 0;

//(__int128_t)

int main() {
  scanf("%s", str + 1);
  len = strlen(str + 1);
  for (int i = 1; i <= len; ++i) {
    if (str[i] >= '0' && str[i] <= '9') {
      a[now] = a[now] * (__int128_t)10ll + (__int128_t)str[i] - (__int128_t)'0';
    } else if (str[i] == '.') {
      if (str[i - 1] >= '0' && str[i - 1] <= '9') {
        now++;
      }
    } else {
      flag = true;
      if (str[i - 1] >= '0' && str[i - 1] <= '9') {
        now++;
      }
    }
  }
  for (int i = 1; i <= len; ++i) {
    if (str[i] == '.' && str[i - 1] == '.') {
      flag = true;
    }
  }
  if (a[1] > (__int128_t)255) {
    a[1] = (__int128_t)255;
    flag = true;
  }
  if (a[2] > (__int128_t)255) {
    a[2] = (__int128_t)255;
    flag = true;
  }
  if (a[3] > (__int128_t)255) {
    a[3] = (__int128_t)255;
    flag = true;
  }
  if (a[4] > (__int128_t)255) {
    a[4] = (__int128_t)255;
    flag = true;
  }
  if (flag) {
    puts("NO");
  } else {
    puts("YES");
    return 0;
  }
  write(a[1]);
  putchar('.');
  write(a[2]);
  putchar('.');
  write(a[3]);
  putchar('.');
  write(a[4]);
  return 0;
} // Thomitics Code