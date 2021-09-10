/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <map>
#include <set>
#include <utility>
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
long long totN, totM, totQ;
long long at[maxN];
map<long long, bool> H;
long long room[maxN];
set<long long> S;
long long ha[maxN];
long long siz[maxN];
long long nowANS;

long long mkCHAOS() {
  return (rand() % 2039483) * 384 + (rand() % 39445583 - 83494) * 2 - 9384;
}

int main() {
  srand(time(0));
  totN = read();
  totM = read();
  totQ = read();
  for (int i = 1; i <= totN; ++i) {
    at[i] = 1;
    ha[i] = mkCHAOS();
    room[1] ^= ha[i];
  }
  siz[1] = totN;
  S.insert(1);
  for (int i = 1; i <= totQ; ++i) {
    char ch = getchar();
    long long x = read();
    long long y = read();
    if (ch == 'C') {
      if (at[x] == y) {
        continue;
      }
      S.erase(at[x]);
      S.erase(y);
      --siz[at[x]];
      ++siz[y];
      room[at[x]] ^= ha[x];
      room[y] ^= ha[x];
      if (!H[room[at[x]]]) {
        S.insert(at[x]);
      }
      if (!H[room[y]]) {
        S.insert(y);
      }
      at[x] = y;
    } else {
      nowANS = 0;
      auto it = S.lower_bound(x);
      for (; it != S.end() && *it <= y; it = S.lower_bound(x)) {
        H[room[*it]] = true;
        nowANS += siz[*it];
        S.erase(it);
      }
      write(nowANS);
      putchar('\n');
    }
  }
  return 0;
} // Thomitics Code
  // P2087