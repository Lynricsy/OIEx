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