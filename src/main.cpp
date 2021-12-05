#include <bits/stdc++.h>
#define INF 0x3f3f3f3f3f3f3f3f
#define IINF 0x3f3f3f3f

using namespace std;

inline long long read() {
  long long x = 0ll;
  long long f = 1ll;
  char ch = getchar();
  while (ch < '0' || ch > '9') {
    if (ch == '-') {
      f = -1;
    }
    ch = getchar();
  }
  while (ch >= '0' && ch <= '9') {
    x = (x << 1) + (x << 3) + (ch ^ 48);
    ch = getchar();
  }
  return x * f;
}

const long long maxN = 10090;
const long long MOD = 998244353;
long long totN;
long long totM;
long long totK;
long long V[maxN];

long long popcount(long long x) {
  long long ret = 0;
  while (x) {
    if (x & 1) {
      ++ret;
    }
    x >>= 1;
  }
  return ret;
}
long long quick_pow(long long a, long long b) {
  if (!b) {
    return 1ll;
  }
  long long base = a;
  long long res = 1;
  while (b) {
    if (b & 1) {
      res *= base;
      res %= MOD;
    }
    base *= base;
    base %= MOD;
    b >>= 1;
  }
  return res;
}

long long totANS;
long long nums[maxN];

void work(long long x, long long nowSUM, long long op) {
  if (x == totN + 1) {
    if (nowSUM == op) {
      long long nowres = 1;
      for (int i = 1; i <= totN; ++i) {
        nowres *= V[nums[i]];
        nowres %= MOD;
      }
      totANS += nowres;
      totANS %= MOD;
    }
    return;
  }
  for (int i = 0; i <= totM; ++i) {
    nums[x] = i;
    work(x + 1, nowSUM + quick_pow(2, i), op);
  }
}

int main() {
  totN = read();
  totM = read();
  totK = read();
  for (int i = 0; i <= totM; ++i) {
    V[i] = read();
  }
  for (int i = totN; i <= totN * quick_pow(2, totM); ++i) {
    if (popcount(i) <= totK) {
      //			printf("%lld\n",i);
      work(1, 0, i);
    }
  }
  printf("%lld\n", totANS % MOD);
  //	printf("%lld",popcount(totN));
  return 0;
}