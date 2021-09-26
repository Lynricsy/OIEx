#include <bits/stdc++.h>

using namespace std;

//#define int long long
//#define INF 1ll<<30
#define pb emplace_back

template <typename _T> inline void read(_T &x) {
  x = 0;
  char s = getchar();
  int f = 1;
  while (s < '0' || s > '9') {
    f = 1;
    if (s == '-')
      f = -1;
    s = getchar();
  }
  while ('0' <= s && s <= '9') {
    x = (x << 3) + (x << 1) + s - '0';
    s = getchar();
  }
  x *= f;
}

const int np = 2e5 + 5;
int n, m;
int head[np], ver[np * 2], nxt[np * 2];
int tit, in[np], typ[np * 2];
int r[np], g[np], b[np];
int now[np], lu[np], ans[np];
vector<int> vec[np];

inline void add(int x, int y, int id) {
  ver[++tit] = y;
  typ[tit] = id;
  nxt[tit] = head[x];
  head[x] = tit;
}

inline int check(int x) {
  if (r[x] <= b[x] && r[x] <= g[x])
    return 1;
  if (g[x] <= r[x] && g[x] <= b[x])
    return 2;
  if (b[x] <= r[x] && b[x] <= g[x])
    return 3;
}

queue<int> q;

namespace subtask {
inline void Main() {
  for (int i = 1, a, b; i <= m; i++) {
    read(a), read(b);
    ans[i] = rand() % 3 + 1;
  }
  for (int i = 1; i <= m; i++) {
    if (ans[i] == 1) {
      putchar('R');
      putchar('\n');
    }
    if (ans[i] == 2) {
      putchar('G');
      putchar('\n');
    }
    if (ans[i] == 3) {
      putchar('B');
      putchar('\n');
    }
  }
  return;
}
} // namespace subtask

signed main() {
  freopen("C.in", "r", stdin);
  freopen("my.out", "w", stdout);
  //	srand(time(0));
  read(n), read(m);
  printf("%d %d\n", n, m);
  //	if(n <= 200)
  //	{
  //	subtask::Main();
  //	return 0;
  //	}
  for (int i = 1, a, b; i <= m; i++) {
    read(a), read(b);
    printf("%d %d\n", a, b);
    add(a, b, i);
    in[b]++;
    vec[b].pb(i);
  }
  for (int i = 1; i <= n; i++)
    if (!in[i])
      q.push(i), now[i] = i % 3 + 1;

  while (q.size()) {
    int x = q.front();
    q.pop();
    if (!now[x])
      now[x] = check(x);
    for (int i = head[x], v; i; i = nxt[i]) {
      v = ver[i];
      switch (now[x]) {
      case 1: {
        r[v] = max(r[v], r[x] + 1);
        break;
      }
      case 2: {
        g[v] = max(g[v], g[x] + 1);
        break;
      }
      case 3: {
        b[v] = max(b[v], b[x] + 1);
        break;
      }
      }
      in[v]--;
      if (!in[v])
        q.push(v);
    }
  }
  for (int i = 1; i <= n; i++) {
    for (auto q : vec[i])
      ans[q] = now[i];
  }
  for (int i = 1; i <= m; i++) {
    if (ans[i] == 1)

    {
      putchar('R');
      putchar('\n');
    }
    if (ans[i] == 2) {
      putchar('G');
      putchar('\n');
    }
    if (ans[i] == 3) {
      putchar('B');
      putchar('\n');
    }
  }
  //	printf("%d\n",ans[i]);
}
