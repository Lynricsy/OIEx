/**************************************************************
 * Problem: Luogu P7411
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm: 模拟
 **************************************************************/
#include <bits/stdc++.h>
#include <utility>
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

const long long maxN = 190;
int mapp[maxN][maxN];
long long totN;
vector<pair<int, int>> V;
int delt[5][2] = {{0, 0}, {1, 0}, {-1, 0}, {0, 1}, {0, -1}};

bool check(int x, int y) {
  if (!mapp[x][y]) {
    return false;
  }
  long long ans = 0;
  for (int i = 1, tx, ty; i <= 4; ++i) {
    tx = x + delt[i][0];
    ty = y + delt[i][1];
    if (mapp[tx][ty]) {
      ++ans;
    }
  }
  return (ans == 3);
}
long long totANS;

void fake(long long x, long long y) {
  for (int i = 1, tx, ty; i <= 4; ++i) {
    tx = x + delt[i][0];
    ty = y + delt[i][1];
    if (!mapp[tx][ty]) {
      mapp[tx][ty] = 2;
      ++totANS;
      if (check(tx, ty)) {
        fake(tx, ty);
      }
      for (int j = 1, xx, yy; j <= 4; ++j) {
        xx = tx + delt[j][0];
        yy = ty + delt[j][1];
        if (check(xx, yy)) {
          fake(xx, yy);
        }
      }
    }
  }
}

int main() {
  totN = read();
  for (int i = 1, x, y; i <= totN; ++i) {
    x = read() + 3;
    y = read() + 3;
    V.push_back(make_pair(x, y));
  }
  for (auto i : V) {
    if (mapp[i.first][i.second] == 2) {
      --totANS;
    }
    mapp[i.first][i.second] = 1;
    if (check(i.first, i.second)) {
      fake(i.first, i.second);
    }
    for (int j = 1, xx, yy; j <= 4; ++j) {
      xx = i.first + delt[j][0];
      yy = i.second + delt[j][1];
      if (check(xx, yy)) {
        fake(xx, yy);
      }
    }
    write(totANS, '\n', 1);
  }
  return 0;
} // Thomitics Code