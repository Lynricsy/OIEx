/*---------------------------------
 *Author: EdisonBa
 *Title number: Luogu
 *Creation date: 2021.9
 *Tips: CSP-S NOIP 2021 RP++!
 *-------------------------------*/
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>
#define Ba 0
using namespace std;
typedef long long ll;
#define Edison return
#define rint register int
#define ull unsigned long long
#define INF 9223372036854775800

#define Timeok ((double)clock() / CLOCKS_PER_SEC < MAX_TIME)
const double MAX_TIME = 1.0 - 0.0032;

// char xch, xB[1 << 15], *xS = xB, *xTT = xB;
// #define Getc() (xS == xTT && (xTT = (xS = xB) + fread(xB, 1, 1 << 15, stdin),
// xS == xTT) ? 0 : *xS++) #ifndef ONLINE_JUDGE
#define Getc() getchar()
// #endif

inline ll read() {
  ll x = Ba, f = Ba;
  char ch = Getc();
  while (!isdigit(ch))
    f |= (ch == '-'), ch = Getc();
  while (isdigit(ch))
    x = (x << 1) + (x << 3) + (ch ^= 48), ch = Getc();
  return f ? -x : x;
}

void write(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + 48);
}

/*------------C-O-D-E------------*/

const ll mod = 1e9;
ll n, m;
ll t[10000000];
ll a[10000000][3], tot, ans;

ll st[10000000][3], top;

void dfs() {
  // for(int i = 1; i <= m; ++i)
  //     printf("%lld ", t[i]);
  // puts("");

  for (int i = 1; i <= m; ++i) {
    st[++top][1] = a[t[i]][1];
    st[top][2] = a[t[i]][2];
  }
  ll minn = 12567123687, maxn = -1263123123;
  for (int i = 1; i <= top; ++i) {
    minn = min(minn, min(st[i][1], st[i][2]));
    maxn = max(maxn, max(st[i][1], st[i][2]));
  }
  bool ok = 1;
  for (int i = 2; i <= n; ++i) {
    if ((minn >= i and maxn >= i) || (minn < i and maxn < i)) {
      ok = 0;
      break;
    }
  }
  if (ok == 1)
    ++ans;
  // if(ok == 1)
  // {
  //     for(int i = 1; i <= top; ++i)
  //         printf("%lld %lld\n", st[i][1], st[i][2]);
  //     puts("");
  // }
  if (ans >= mod)
    ans -= mod;

  top = 0;
  ok = 1;
  for (int i = m; i >= 1; --i) {
    if (t[i] != tot - m + i) {
      ++t[i];
      for (int j = i + 1; j <= m; ++j)
        t[j] = t[j - 1] + 1;
      ok = 0;
      break;
    }
  }
  if (ok == 1)
    return; // all ok
  dfs();
}

int main() {
  n = read();
  for (int i = 1; i <= n - 1; ++i) {
    for (int j = i + 1; j <= n; ++j) {
      if (__gcd(i, j) == 1)
        a[++tot][1] = i, a[tot][2] = j;
    }
  }
  for (int i = 1; i <= tot; ++i) {
    for (int j = 1; j <= i; ++j)
      t[j] = j;
    m = i;
    dfs();

    for (int j = 1; j <= tot; ++j)
      t[j] = 0;
  }

  printf("%lld\n", ans);
  return 0;
}