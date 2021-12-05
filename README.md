# OIEx
My OI workspace.

已经有

![计数](https://count.getloli.com/get/@thomitics-luogu?theme=moebooru-h)

人来这里爆踩了我，嘤嘤嘤

[![](https://chat.getloli.com/room/@thomitics/svg?width=600&height=280&limit=20&theme=light&fontSize=13&title=%E8%8A%8A%E6%9E%AB%E7%9A%84%E8%81%8A%E5%A4%A9%E5%AE%A4%EF%BC%8C%E7%82%B9%E5%87%BB%E5%8F%AF%E4%BB%A5%E5%8F%91%E8%A8%80:%20~)](https://chat.getloli.com/room/@thomitics?title=%E8%8A%8A%E6%9E%AB%E7%9A%84%E8%81%8A%E5%A4%A9%E5%AE%A4)

# Nothing last forever……それでも、わたしは。

![](https://upload-bbs.mihoyo.com/upload/2021/05/25/159922380/e12b45cb79b5f9ab7654c643c63d149d_6077329167235459581.gif?x-oss-process=image/resize,s_600/quality,q_80/auto-orient,0/interlace,1/format,gif)

![](https://ipcounter.ihcr.top/?mode=2&mail=i@foxex.cn&qq=2188955531&gh=Thomitics&lg=%E8%8A%8A%E6%9E%ABThomitics&pic=Miku&str=Nothing%20Last%20Forever.)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)
![](http://啧.tk/gz)


------------

![](https://pic.imgdb.cn/item/60e111c25132923bf8fcb72f.jpg)

![](https://pic.imgdb.cn/item/60e2efcd5132923bf814e064.png)
![](https://i.loli.net/2021/07/06/7QONEjW3nZa51ve.png)
![](https://i.loli.net/2021/07/06/Yc73sQTl4tGXWdN.png)
![](https://i.loli.net/2021/07/06/qDcpk27ly894dub.png)
![](https://i.loli.net/2021/07/06/WQSUmT1ywOzb7aq.png)

[fangke](http://192.168.25.100:8080/PortalServer/customize_new/1573638657062/pc/auth.jsp?ssid=guest)

------------

[一号仓](https://www.luogu.com.cn/paste/60erm1s6)

[二号仓](https://www.luogu.com.cn/user/315398)

[三号仓](https://www.luogu.com.cn/paste/ejpwsu2g)


[doge]


------------

codeforces:


![codeforces](https://img.shields.io/badge/Thomitics-Legendary%20GrandMaster%203372-ff0000.svg?style=for-the-badge&logo=Codeforces)


勉强算是一个V家P主吧……

单推fbk(^・ω・^§)ﾉ （脑补玉米）

（凪白みと大法好！！）（小声）



------------


确实是一个旅行者

![](https://genshin-card.himiku.com/1/256908286.png)



------------


[我的blog](https://blog.foxex.cn)




------------
谁还不是个人呢

![](https://pic.imgdb.cn/item/60e2ae225132923bf8c392f7.png)
------------
谁还没有点人类的基本需求呢

![](https://s1.ax1x.com/2020/07/02/NbSfXj.png)
![](https://s1.ax1x.com/2020/07/02/Nbp08U.png)


------------
谁还不会显现出人类的本质呢

![](https://s1.ax1x.com/2020/07/02/NbE1nU.png)
------------

![](https://api.r10086.com/%E6%98%8E%E6%97%A5%E6%96%B9%E8%88%9F2.php)
------------

个人码风：
```cpp

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

int main() { return 0; } // Shirakami Ling Code
```

火车头：

```cpp
#ifdef ONLINE_JUDGE
#pragma GCC optimize(2)
#pragma GCC diagnostic error "-std=c++11"
#pragma GCC target("avx")
#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-ffast-math")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-funroll-loops")
#pragma GCC optimize("-fwhole-program")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-fstrict-overflow")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-skip-blocks")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("no-stack-protector")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("-funsafe-loop-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma GCC optimize(3)
#endif // ONLINE_JUDGE
```


------------
感谢以下企业/组织为我的OI学习提供了便利：

- [Microsoft中国](https://www.microsoft.com/zh-cn/)
- [Jetbrains中国](https://www.jetbrains.com/zh-cn/)
- [腾讯](https://www.tencent.com/)
- [火绒](https://www.huorong.cn/)
- [洛谷](https://www.luogu.com.cn/)
- [百度](https://www.baidu.com/)
- [Google](https://www.google.com/)
- [bilibili](https://www.bilibili.com/)
- [GitHub](https://www.github.com/)
- [开源中国](https://www.oschina.net/)
- [Vercel](https://vercel.com/)


------------
![迷迭香](https://p.pstatp.com/origin/fe710002fbf9f70d4eac)