## 2021-09-13

### P3398 仓鼠找sugar

`dis(a,y)+dis(y,b)`写成`dis(a,y)+dis(y,x)`。

```c++
if (dis(x, c) + dis(x, d) == dis(c, d) ||
        dis(y, a) + dis(y, b) == dis(a, b)) {
      puts("Y");
    } else {
      puts("N");
    }
```

## 2021-09-15

### P4981 父子

多组数据输出忘记换行。呜

### P4430 小猴打架

又TM是结论题，预处理忘取模了![qq_emoji: wul](https://z3.ax1x.com/2021/05/30/2VJfJ0.png)

```cpp
void prefix() {
  fac[0] = 1;
  for (int i = 1; i <= totN - 1; ++i) {
    fac[i] = fac[i - 1] * i % MOD;
  }
}
```

## 2021-09-17

### P1986

草，循环嵌套内部数组又用错了！

```c++
for (int j = nodes[i].r; j >= nodes[i].l; --j) {
  if (x >= nodes[i].x) {
    break;
  }
  if (!nav[i]) {
           ^
            应该是j
    nav[i] = true;
        ^
          应该是j
    ++x;
  }
}
```