/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <map>
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
template <typename T> inline void write(T x) {
  if (x < 0ll) {
    putchar('-');
    x = -x;
  }
  if (x > 9ll)
    write(x / 10ll);
  putchar(x % 10ll + '0');
}

long long totT;
map<string, long long> Fs;
vector<vector<long long>> Parent;
bool vis[2090];
bool cmp(long long a, long long b) { return a > b; }

bool checkOUT(string str, vector<string> Rk) {
  long long totM = Fs.size();
  if (Fs.count(str)) {
    return false;
  }
  for (auto st : Rk) {
    if (!Fs.count(st)) {
      return false;
    }
  }
  vector<long long> nowR;
  for (auto i : Rk) {
    nowR.push_back(Fs[i]);
  }
  sort(nowR.begin(), nowR.end(), cmp);
  memset(vis, 0, sizeof vis);
  for (auto i : nowR) {
    if (vis[i]) {
      continue;
    } else {
      for (auto j : Parent[i]) {
        if (vis[j]) {
          return false;
        }
        vis[j] = true;
      }
      // vis[i] = true;
    }
  }
  Fs[str] = totM;
  Parent.push_back(vector<long long>());
  for (auto i : nowR) {
    vis[i] = true;
  }
  // for (auto i : nowR) {
  //   Parent[totM].push_back(i);
  // }
  for (int i = 0; i < totM; ++i) {
    if (vis[i]) {
      Parent[totM].push_back(i);
    }
  }
  return true;
}

int main() {
  totT = read();
  while (totT--) {
    string fstr;
    cin >> fstr;
    string trash;
    cin >> trash;
    string par;
    cin >> par;
    vector<string> pp;
    while (par != ";") {
      pp.push_back(par);
      cin >> par;
    }
    if (checkOUT(fstr, pp)) {
      puts("ok");
    } else {
      puts("greska");
    }
  }
  return 0;
} // Thomitics Code