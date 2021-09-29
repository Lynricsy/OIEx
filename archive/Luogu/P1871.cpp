/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
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
template <typename T>
inline void write(initializer_list<T> WRITE_NUMS, char ch) {
  for (auto i : WRITE_NUMS) {
    write(i);
    putchar(ch);
  }
}

const long long maxN = 1090;
long long totN;
long long totM;
long long primes[maxN];
bool isprime[maxN];
long long cntPRIME;
bool OPEN[maxN];
long long hav[maxN];
long long yin[maxN];

void prefix() {
  for (int i = 1; i <= totN; ++i) {
    isprime[i] = true;
  }
  // ++cntPRIME;
  // primes[cntPRIME] = 2;
  // isprime[2] = true;
  for (int i = 2; i <= totN; ++i) {
    if (isprime[i]) {
      ++cntPRIME;
      primes[cntPRIME] = i;
      yin[i] = cntPRIME;
    }
    for (int j = 1; j <= cntPRIME && i * primes[j] <= totN; ++j) {
      isprime[i * primes[j]] = false;
      yin[i * primes[j]] = j;
      if (!i % primes[j]) {
        break;
      }
    }
  }
}

int main() {
  totN = read();
  totM = read();
  prefix();
  getchar();
  for (int i = 1; i <= totM; ++i) {
    char ch = getchar();
    while (ch != '+' && ch != '-') {
      ch = getchar();
    }
    long long num = read();
    if (ch == '+') {
      if (OPEN[num]) {
        puts("Already on");
      } else {
        long long x = num;
        while (x > 1) {
          if (hav[yin[x]]) {
            break;
          }
          x /= primes[yin[x]];
        }
        if (x != 1) {
          printf("Conflict with %lld\n", hav[yin[x]]);
        } else {
          OPEN[num] = true;
          x = num;
          while (x > 1) {
            hav[yin[x]] = num;
            x /= primes[yin[x]];
          }
          puts("Success");
        }
      }
    } else {
      if (!OPEN[num]) {
        puts("Already off");
      } else {
        OPEN[num] = false;
        long long x = num;
        while (x > 1) {
          hav[yin[x]] = 0;
          x /= primes[yin[x]];
        }
        puts("Success");
      }
    }
    // getchar();
  }
  return 0;
} // Thomitics Code