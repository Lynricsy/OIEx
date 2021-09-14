/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <set>
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

const long long maxN = 2000090;
long long totN;
char str[maxN];
double sum[maxN];
multiset<double> S;
set<double> see;
long long totANS;

int main() {
  freopen("bridge.in", "r", stdin);
  freopen("bridge.out", "w", stdout);
  totN = read();
  scanf("%s", str + 1);
  for (int i = 1; i <= totN; ++i) {
    if (str[i] == '+') {
      sum[i] = sum[i - 1] - 0.5;
    } else if (str[i] == '-') {
      sum[i] = sum[i - 1] + 0.5;
    } else if (str[i] == 'L') {
      sum[i] = sum[i - 1] - 1.0;
    } else if (str[i] == 'R') {
      sum[i] = sum[i - 1] + 1.0;
    }
  }
  for (int i = 1; i <= totN; ++i) {
    S.insert(sum[i]);
    see.insert(sum[i]);
  }
  for (auto i : see) {
    totANS += (S.count(i) - 1) * (S.count(i)) / 2;
  }
  write(totANS + S.count(0));
  // putchar('\n');
  // write(S.count(0));
  return 0;
} // Thomitics Code