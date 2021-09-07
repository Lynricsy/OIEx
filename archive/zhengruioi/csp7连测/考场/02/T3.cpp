/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <iostream>
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

const long long maxN = 1090;
long long totN;
// map<string, set<string>> anc;
set<string> ply;
set<string> tmpa;

int main() {
  totN = read();
  for (long long i = 1; i <= totN; i++) {
    string st;
    cin >> st;
    if (ply.find(st) == ply.end()) {
      // ply.insert(st);
    } else {
      puts("greska");
      while (st != ";") {
        cin >> st;
      }
      getchar();
      continue;
    }
    string s;
    cin >> s;
    cin >> s;
    while (s != ";") {
      if (ply.find(s) == ply.end()) {
        puts("greska");
        while (st != ";") {
          cin >> st;
        }
        // tmpa.clear();
        goto outer;
      } else {
        // tmpa.insert(s);
      }
      cin >> s;
    }
    // anc[st] = tmpa;
    ply.insert(st);
    puts("ok");
  outer:
    getchar();
  }
  return 0;
} // Thomitics Code