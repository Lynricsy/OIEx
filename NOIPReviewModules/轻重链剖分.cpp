/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
 * Algorithm:
 **************************************************************/
#include <bits/stdc++.h>
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
long long MOD;

long long totN;
long long totM;
long long totS;

struct Edge {
  long long to;
  long long nxt;
} edges[maxN];
long long cnt_edges;
long long head[maxN];
void add_edge(long long u, long long v) {
  ++cnt_edges;
  edges[cnt_edges].nxt = head[u];
  head[u] = cnt_edges;
  edges[cnt_edges].to = v;
}

long long fath[maxN];
long long top[maxN];
long long depth[maxN];
long long Sson[maxN];
long long siz[maxN];
long long nums[maxN];
long long num[maxN];
long long ID[maxN];

long long cntNODE;

void DFS1(long long x, long long fa) {
  siz[x] = 1;
  fath[x] = fa;
  depth[x] = depth[fa] + 1;
  for (int i = head[x]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == fa) {
      continue;
    }
    DFS1(vir, x);
    siz[x] += siz[vir];
    if (siz[vir] > siz[Sson[x]]) {
      Sson[x] = vir;
    }
  }
}
void DFS2(long long x, long long ftop) {
  ++cntNODE;
  ID[x] = cntNODE;
  num[cntNODE] = nums[x];
  top[x] = ftop;
  if (!Sson[x]) {
    return;
  }
  DFS2(Sson[x], ftop);
  for (int i = head[x]; i; i = edges[i].nxt) {
    long long vir = edges[i].to;
    if (vir == Sson[x] || vir == fath[x]) {
      continue;
    }
    DFS2(vir, vir);
  }
}
struct Node {
  long long val;
  long long l, r;
  Node *lch, *rch;
  long long tag;
  void pushup() { val = lch->val + rch->val; }
  Node(long long L, long long R) {
    l = L;
    r = R;
    tag = 0;
    if (l == r) {
      val = num[l] % MOD;
      lch = rch = NULL;
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup();
  }
  void maketag(long long w) {
    tag += w;
    tag %= MOD;
    val += (r - l + 1) * w;
    val %= MOD;
  }
  void pushdown() {
    if (!tag) {
      return;
    }
    lch->maketag(tag);
    rch->maketag(tag);
    tag = 0;
  }
  bool INrange(long long L, long long R) { return (l >= L) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (r < L) || (R < l); }
  void update(long long L, long long R, long long w) {
    if (INrange(L, R)) {
      maketag(w);
      return;
    } else if (!OUTrange(L, R)) {
      pushdown();
      lch->update(L, R, w);
      rch->update(L, R, w);
      pushup();
    }
  }
  long long query(long long L, long long R) {
    if (INrange(L, R)) {
      return val;
    } else if (OUTrange(L, R)) {
      return 0;
    } else {
      pushdown();
      return (lch->query(L, R) + rch->query(L, R)) % MOD;
    }
  }
};

Node *rot;

long long qRANGE(long long x, long long y) {
  long long nowANS = 0;
  while (top[x] != top[y]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    nowANS += rot->query(ID[top[x]], ID[x]);
    x = fath[top[x]];
  }
  if (depth[x] < depth[y]) {
    swap(x, y);
  }
  nowANS += rot->query(ID[y], ID[x]);
  return nowANS % MOD;
}
long long qTREE(long long x) {
  return rot->query(ID[x], ID[x] + siz[x] - 1) % MOD;
}
void updRANGE(long long x, long long y, long long w) {
  while (top[x] != top[y]) {
    if (depth[top[x]] < depth[top[y]]) {
      swap(x, y);
    }
    rot->update(ID[top[x]], ID[x], w);
    x = fath[top[x]];
  }
  if (depth[x] < depth[y]) {
    swap(x, y);
  }
  rot->update(ID[y], ID[x], w);
}
void updTREE(long long x, long long w) {
  rot->update(ID[x], ID[x] + siz[x] - 1, w);
}

int main() {
  totN = read();
  totM = read();
  totS = read();
  MOD = read();
  for (int i = 1; i <= totN; ++i) {
    nums[i] = read();
  }
  for (int i = 1, u, v; i <= totN - 1; ++i) {
    u = read();
    v = read();
    add_edge(u, v);
    add_edge(v, u);
  }
  DFS1(totS, 0);
  DFS2(totS, totS);
  rot = new Node(1, totN);
  for (long long i = 1, x, y, w, opt; i <= totM; ++i) {
    opt = read();
    x = read();
    if (opt == 1) {
      y = read();
      w = read();
      updRANGE(x, y, w);
    } else if (opt == 2) {
      y = read();
      write(qRANGE(x, y), '\n', 1);
    } else if (opt == 3) {
      w = read();
      updTREE(x, w);
    } else if (opt == 4) {
      write(qTREE(x), '\n', 1);
    }
  }
  return 0;
} // Thomitics Code