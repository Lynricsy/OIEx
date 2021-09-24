/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
#include <cstdio>
#include <cstring>
#include <queue>
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

const long long maxN = 1090;
long long LEN;
char str[maxN];
long long ch[maxN][27];
long long lst[27];
long long rot;
bool vis[maxN];
long long pre[maxN];
vector<char> ans;
long long raw[maxN];
long long tANS;
queue<long long> Q;

void build(char *s) {
  long long nlen = strlen(s + 1);
  // rot = maxN - 17;
  rot = 588;
  for (int i = nlen; i; --i) {
    memcpy(ch[i], lst, sizeof(lst));
    lst[s[i] - 'a' + 1] = i;
  }
  memcpy(ch[rot], lst, sizeof(lst));
}

void BFS() {
  pre[rot] = raw[rot] = 0;
  Q.push(rot);
  while (!Q.empty()) {
    long long nowX = Q.front();
    Q.pop();
    for (int i = 1; i <= 26; ++i) {
      long long vir = ch[nowX][i];
      if (!vir) {
        pre[vir] = nowX;
        raw[vir] = i;
        long long ptr = vir;
        while (ptr != rot) {
          ans.push_back(raw[ptr] + 'a' - 1);
          ptr = pre[ptr];
        }
        for (auto i : ans) {
          putchar(i);
        }
        exit(0);
      }
      if (vis[vir]) {
        continue;
      }
      vis[vir] = true;
      pre[vir] = nowX;
      raw[vir] = i;
      Q.push(vir);
    }
  }
}

int main() {
  scanf("%s", str + 1);
  LEN = strlen(str + 1);
  build(str);
  BFS();
  return 0;
} // Thomitics Code