/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <vector>
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
bool nprime[maxN];
// long long primes[maxN];
long long totN;
long long totQ;
long long x;
vector<long long> Primes;

void GetPrime() {
  for (int i = 2; i <= totN; ++i) {
    if (!nprime[i]) {
      Primes.push_back(i);
    }
    for (auto j : Primes) {
      if (j * i > totN) {
        break;
      }
      nprime[i * j] = true;
      if (!(i % j)) {
        break;
      }
    }
  }
}

int main() {
  totN = read();
  totQ = read();
  GetPrime();
  for (int i = 1; i <= totQ; ++i) {
    x = read();
    write(Primes[x - 1], '\n', 1);
  }
  return 0;
} // Thomitics Code