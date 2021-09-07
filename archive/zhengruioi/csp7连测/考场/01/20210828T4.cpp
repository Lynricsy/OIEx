#define fastcall __attribute__((optimize("-O3")))
#pragma GCC optimize(2)
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define INF 0x4f4f4f4f4f4f4f4f
#define swap(x, y) x ^= y, y ^= x, x ^= y;

inline ll read() {
  ll x = 0, f = 0;
  char ch = getchar();
  while (!isdigit(ch))
    f |= (ch == '-'), ch = getchar();
  while (isdigit(ch))
    x = (x << 1) + (x << 3) + (ch ^= 48), ch = getchar();
  return f ? -x : x;
}

void write(ll x) {
  if (x < 0)
    putchar('-'), x = -x;
  if (x > 9)
    write(x / 10);
  putchar(x % 10 + 48);
}

const ll mod = 2148473647, N = 1e7 + 5;
ll totN;

ll dp[N];
bool isprime[N];
ll prime[N], top, fn;

void Prime(ll n) {
  top = 0;
  memset(isprime, true, sizeof(isprime));
  for (int i = 2; i < n; i++) {
    if (isprime[i])
      prime[top++] = i;
    for (int k = 0; k < top && i * prime[k] < n; k++) {
      isprime[i * prime[k]] = false;
      if (i % prime[k] == 0)
        break;
    }
  }
}

ll quickpow(ll m, ll n) {
  ll b = 1;
  while (n) {
    if (n & 1)
      b = (b * m) % mod;
    n = n >> 1;
    m = (m * m) % mod;
  }
  return b;
}

void fracacsa(ll n) {
  ll len = -1;
  while (prime[++len] <= n) {
    ll sum = 0;
    dp[prime[len]] = 0;
    ll num = prime[len];
    while (num <= n) {
      sum += n / num;
      num = num * prime[len];
    }
    dp[prime[len]] += sum;
  }
}

void fracacsb(ll n) {
  ll len = -1;
  while (prime[++len] <= n) {
    ll sum = 0;
    ll num = prime[len];
    while (num <= n) {
      sum += n / num;
      num = num * prime[len];
    }
    dp[prime[len]] -= sum;
  }
}

long long quick_pow(long long a, long long b) {
  long long ans = 1;
  while (b) {
    if (b & 1)
      ans = (ans * a) % mod;
    b >>= 1;
    a = (a * a) % mod;
  }
  return ans;
}

inline void Pint(ll a, ll b) {
  ll ans = quick_pow(b, mod - 2);
  ans = (ans * a) % mod;
  printf("%lld\n", ans);
}

inline ll frac(ll x) {
  ll ans = 1;
  for (int i = 1; i <= x; ++i)
    ans = (ans * i) % mod;
  return ans % mod;
}

inline void pre_fix() {
  Prime(10000000);
  if (totN == 1) {
    fn = 1;
    return;
  }
  fracacsa(2 * totN);
  fracacsb(totN);
  fracacsb(totN + 1);
  ll resl = 1;
  for (int i = 0; prime[i] <= 2 * totN; i++) {
    if (dp[prime[i]])
      resl = (resl * quickpow(prime[i], dp[prime[i]])) % mod;
  }
  fn = resl;
}
int main() {
  totN = read();
  pre_fix();
  ll p, q;
  p = frac(2 * (totN - 1)) % mod;
  ll ret = frac(totN - 1) % mod;
  q = ((fn * ret) % mod * ret) % mod;
  Pint(p, q);
  return 0;
}