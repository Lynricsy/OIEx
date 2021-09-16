/**************************************************************
 * Problem: Luogu P7527
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm: 树状数组
 **************************************************************/
#include <bits/stdc++.h>
#define lowbit(x) x & -x;
#define int long long
#define N 400010
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
int n, ans;
int a[N], f[N];
int tree[N];
int ask(int x) {
  int sum = 0;
  while (x > 0) {
    sum += tree[x];
    x -= lowbit(x);
  }
  return sum;
}
void add(int x, int k) {
  while (x <= 2 * n) {
    tree[x] += k;
    x += lowbit(x);
  }
}
signed main() {
  n = read();
  for (int i = 1; i <= n; i++) {
    a[i] = read();
    f[i] = n + 1;
  }
  for (int i = n; i >= 1; i--) {
    ans += ask(f[a[i]] - 1);
    add(f[a[i]], -1);
    f[a[i]] = i;
    add(f[a[i]], 1);
  }
  cout << ans << endl;
}
