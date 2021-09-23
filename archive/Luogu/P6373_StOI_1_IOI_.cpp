/**************************************************************
 * Problem: OJ ProID
 * Author: 芊枫
 * Date: 2021 Sept 16
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
char str[maxN];
long long totN;
long long totM;

struct Node {
  long long IOI;
  long long I, O, OI, IO;
  // vector<long long> tag;
  Node *lch, *rch;
  long long l, r;
  void pushup(Node *la, Node *ra) {
    I = la->I + ra->I;
    O = la->O + ra->O;
    OI = la->OI + ra->OI + la->O * ra->I;
    IO = la->IO + ra->IO + la->I * ra->O;
    IOI = la->I * ra->OI + la->IO * ra->I + la->IOI + ra->IOI;
  }
  Node(long long L, long long R) {
    l = L;
    r = R;
    if (L == R) {
      lch = rch = NULL;
      if (str[l] == 'I') {
        I = 1;
        O = 0;
      }
      if (str[l] == 'O') {
        O = 1;
        I = 0;
      }
      return;
    }
    long long Mid = (L + R) >> 1;
    lch = new Node(L, Mid);
    rch = new Node(Mid + 1, R);
    pushup(lch, rch);
  }
  Node() { IOI = OI = IO = I = O = 0; }
  bool INrange(long long L, long long R) { return (L <= l) && (r <= R); }
  bool OUTrange(long long L, long long R) { return (l > R) || (L > r); }
};
void update(Node *thi, long long pos, char ch) {
  if (thi->l == pos && thi->r == pos) {
    if (ch == 'I') {
      thi->I = 1;
      thi->O = 0;
    }
    if (ch == 'O') {
      thi->O = 1;
      thi->I = 0;
    }
    return;
  }
  if (pos >= thi->rch->l) {
    update(thi->rch, pos, ch);
  } else {
    update(thi->lch, pos, ch);
  }
  thi->pushup(thi->lch, thi->rch);
}
Node *query(Node *thi, long long L, long long R) {
  if (thi->INrange(L, R)) {
    return thi;
  }
  if (thi->rch->OUTrange(L, R)) {
    return query(thi->lch, L, R);
  }
  if (thi->lch->OUTrange(L, R)) {
    return query(thi->rch, L, R);
  }
  Node *tmp = new Node();
  tmp->pushup(query(thi->lch, L, R), query(thi->rch, L, R));
  return tmp;
}

int main() {
  totN = read();
  totM = read();
  scanf("%s", str + 1);
  Node *rot = new Node(1, totN);
  for (int i = 1, x; i <= totM; ++i) {
    x = read();
    if (x == 2) {
      long long l = read();
      long long r = read();
      write(query(rot, l, r)->IOI, '\n', 1);
    }
    if (x == 1) {
      long long po = read();
      char ch = getchar();
      update(rot, po, ch);
    }
  }
  return 0;
} // Thomitics Code