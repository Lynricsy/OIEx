/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Mon Date
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
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

vector<char> PV[20];
vector<char> RV[20];
vector<char> SV[20];
long long Sn[20][4];
long long Pn[20][4];
long long Rn[20][4];
long long totT;
long long r, p, s;
long long nowN;

int main() {
  PV[1].push_back('P');
  RV[1].push_back('R');
  SV[1].push_back('S');
  for (int i = 2; i <= 16; ++i) {
    for (int jj = 0; jj < PV[i - 1].size(); ++jj) {
      char j = PV[i - 1][jj];
      if (j == 'P') {
        PV[i].push_back('P');
        PV[i].push_back('R');
      } else if (j == 'R') {
        PV[i].push_back('R');
        PV[i].push_back('S');
      } else if (j == 'S') {
        PV[i].push_back('P');
        PV[i].push_back('S');
      }
      if (jj & 1) {
        if (PV[i - 1][jj] == 'S' && PV[i - 1][jj - 1] == 'R') {
          PV[i].pop_back();
          PV[i].pop_back();
          PV[i].pop_back();
          PV[i].pop_back();
          PV[i].push_back('P');
          PV[i].push_back('S');
          PV[i].push_back('R');
          PV[i].push_back('S');
        }
      }
    }
  }
  for (int i = 2; i <= 16; ++i) {
    for (int jj = 0; jj < RV[i - 1].size(); ++jj) {
      char j = RV[i - 1][jj];
      if (j == 'P') {
        RV[i].push_back('P');
        RV[i].push_back('R');
      } else if (j == 'R') {
        RV[i].push_back('R');
        RV[i].push_back('S');
      } else if (j == 'S') {
        RV[i].push_back('P');
        RV[i].push_back('S');
      }
      if (jj & 1) {
        if (RV[i - 1][jj] == 'S' && RV[i - 1][jj - 1] == 'R') {
          RV[i].pop_back();
          RV[i].pop_back();
          RV[i].pop_back();
          RV[i].pop_back();
          RV[i].push_back('P');
          RV[i].push_back('S');
          RV[i].push_back('R');
          RV[i].push_back('S');
        }
      }
    }
  }
  for (int i = 2; i <= 16; ++i) {
    for (int jj = 0; jj < SV[i - 1].size(); ++jj) {
      char j = SV[i - 1][jj];
      if (j == 'P') {
        SV[i].push_back('P');
        SV[i].push_back('R');
      } else if (j == 'R') {
        SV[i].push_back('R');
        SV[i].push_back('S');
      } else if (j == 'S') {
        SV[i].push_back('P');
        SV[i].push_back('S');
      }
      if (jj & 1) {
        if (SV[i - 1][jj] == 'S' && SV[i - 1][jj - 1] == 'R') {
          SV[i].pop_back();
          SV[i].pop_back();
          SV[i].pop_back();
          SV[i].pop_back();
          SV[i].push_back('P');
          SV[i].push_back('S');
          SV[i].push_back('R');
          SV[i].push_back('S');
        }
      }
    }
  }
  // for (int i = 2; i <= 16; ++i) {
  //   for (auto j : RV[i - 1]) {
  //     if (j == 'P') {
  //       RV[i].push_back('P');
  //       RV[i].push_back('R');
  //     } else if (j == 'R') {
  //       RV[i].push_back('R');
  //       RV[i].push_back('S');
  //     } else if (j == 'S') {
  //       RV[i].push_back('P');
  //       RV[i].push_back('S');
  //     }
  //   }
  // }
  // for (int i = 2; i <= 16; ++i) {
  //   for (auto j : SV[i - 1]) {
  //     if (j == 'P') {
  //       SV[i].push_back('P');
  //       SV[i].push_back('R');
  //     } else if (j == 'R') {
  //       SV[i].push_back('R');
  //       SV[i].push_back('S');
  //     } else if (j == 'S') {
  //       SV[i].push_back('P');
  //       SV[i].push_back('S');
  //     }
  //   }
  // }
  for (int i = 1; i <= 16; ++i) {
    for (auto j : PV[i]) {
      if (j == 'P') {
        ++Pn[i][1];
      } else if (j == 'R') {
        ++Pn[i][2];
      } else if (j == 'S') {
        ++Pn[i][3];
      }
    }
  }
  for (int i = 1; i <= 16; ++i) {
    for (auto j : RV[i]) {
      if (j == 'P') {
        ++Rn[i][1];
      } else if (j == 'R') {
        ++Rn[i][2];
      } else if (j == 'S') {
        ++Rn[i][3];
      }
    }
  }
  for (int i = 1; i <= 16; ++i) {
    for (auto j : SV[i]) {
      if (j == 'P') {
        ++Sn[i][1];
      } else if (j == 'R') {
        ++Sn[i][2];
      } else if (j == 'S') {
        ++Sn[i][3];
      }
    }
  }
  totT = read();
  while (totT--) {
    r = read();
    p = read();
    s = read();
    nowN = 1;
    long long ncnt = 1;
    while (nowN != (r + p + s)) {
      nowN <<= 1;
      ++ncnt;
    }
    if (p == Pn[ncnt][1] && r == Pn[ncnt][2] && s == Pn[ncnt][3]) {
      for (auto ch : PV[ncnt]) {
        putchar(ch);
      }
      putchar('\n');
      continue;
    }
    if (p == Rn[ncnt][1] && r == Rn[ncnt][2] && s == Rn[ncnt][3]) {
      for (auto ch : RV[ncnt]) {
        putchar(ch);
      }
      putchar('\n');
      continue;
    }
    if (p == Sn[ncnt][1] && r == Sn[ncnt][2] && s == Sn[ncnt][3]) {
      for (auto ch : SV[ncnt]) {
        putchar(ch);
      }
      putchar('\n');
      continue;
    }
    puts("-1");
  }
  return 0;
} // Thomitics Code