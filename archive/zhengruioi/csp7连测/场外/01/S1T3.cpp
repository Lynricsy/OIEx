/**************************************************************
 * Problem: Luogu P2709
 * Author: 芊枫
 * Date: 2021 July 06
 * Algorithm: 莫队
 **************************************************************/
#include <algorithm>
#include <bits/stdc++.h>
#include <unordered_map>
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
void write(const long long &x) {
  if (!x) {
    putchar('0');
    return;
  }
  char f[100];
  long long tmp = x;
  if (tmp < 0) {
    tmp = -tmp;
    putchar('-');
  }
  long long s = 0;
  while (tmp > 0) {
    f[s++] = tmp % 10 + '0';
    tmp /= 10;
  }
  while (s > 0) {
    putchar(f[--s]);
  }
}

const long long maxN = 100090;
long long SIZE;
long long inB(long long nowX) { return nowX / SIZE; }
struct Quest {
  long long l;
  long long r;
  long long ID;
} quests[maxN];
bool operator<(const Quest &a, const Quest &b) {
  if (inB(a.l) != inB(b.l)) {
    return a.l < b.l;
  }
  return (inB(a.l)) & 1 ? a.r < b.r : a.r > b.r;
}
// bool operator<(Quest a, Quest b) {
//   if (inB(a.l) != inB(b.l)) {
//     return a.l < b.l;
//   } else {
//     return a.r < b.r;
//   }
// }

long long totN;
long long totM;
long long nums[maxN];
long long cnt[maxN];
long long nowANS;
long long ans[maxN];
// long long raw[maxN];
// long long nnums[maxN];
// unordered_map<long long, long long> M;
// set<long long> S;

void add(long long nowX) {
  ++cnt[nowX];
  if (cnt[nowX] & 1) {
    ++nowANS;
  } else {
    --nowANS;
  }
}
void del(long long nowX) {
  if (cnt[nowX] & 1) {
    --nowANS;
  } else {
    ++nowANS;
  }
  --cnt[nowX];
}

int main() {
  totN = read();
  SIZE = (long long)sqrt(totN);
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
    // nnums[i] = nums[i];
    // if (S.find(nums[i]) == S.end()) {
    //   S.insert(nums[i]);
    //   M[nums[i]] = S.size();
    // }
  }
  // sort(nnums + 1, nnums + totN + 1);
  // long long uniqnums = unique(nnums + 1, nnums + totN + 1) - nnums - 1;
  // for (int i=1; i<=uniqnums; ++i) {
  //   raw[i]=nnums[i];
  // }
  totM = read();
  for (int i = 1; i <= totM; ++i) {
    quests[i].l = read();
    quests[i].r = read();
    quests[i].ID = i;
  }
  sort(quests + 1, quests + totM + 1);
  for (long long i = 1, l = 1, r = 0; i <= totM; ++i) {
    while (l > quests[i].l) {
      add(nums[--l]);
    }
    while (r < quests[i].r) {
      add(nums[++r]);
    }
    while (l < quests[i].l) {
      del(nums[l++]);
    }
    while (r > quests[i].r) {
      del(nums[r--]);
    }
    ans[quests[i].ID] = nowANS;
  }
  for (int i = 1; i <= totM; ++i) {
    write(ans[i]);
    putchar('\n');
  }
  return 0;
} // Thomitics Code