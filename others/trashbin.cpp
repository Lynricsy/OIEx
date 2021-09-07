#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
using namespace std;
struct alien {
  int a, b, d;
} aaa[550];
int n, cnt, j, id, dp[2000][2000], quchong[10050];
int main() {
  int t;
  scanf("%d", &t);
  while (t) {
    cnt = 0;
    t--;
    memset(quchong, 0, sizeof(quchong));
    memset(dp, 0, sizeof(dp));
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
      scanf("%d%d%d", &aaa[i].a, &aaa[i].b, &aaa[i].d);
      quchong[aaa[i].a] = 1;
      quchong[aaa[i].b] = 1;
    }
    for (int i = 1; i <= 10000; i++)
      if (quchong[i])
        quchong[i] = ++cnt;
    for (int i = 1; i <= n; i++)
      aaa[i].a = quchong[aaa[i].a], aaa[i].b = quchong[aaa[i].b];
    for (int len = 1; len < cnt; len++)
      for (int i = 1; i + len <= cnt; i++) {
        j = i + len;
        id = -1;
        for (int q = 1; q <= n; q++)
          if (aaa[q].a >= i && aaa[q].b <= j &&
              (id == -1 || aaa[q].d > aaa[id].d))
            id = q;
        if (id == -1)
          continue;
        dp[i][j] = 0x3f3f3f3f;
        for (int k = aaa[id].a; k <= aaa[id].b; k++)
          dp[i][j] = min(dp[i][k - 1] + dp[k + 1][j] + aaa[id].d, dp[i][j]);
      }
    printf("%d\n", dp[1][cnt]);
  }
}