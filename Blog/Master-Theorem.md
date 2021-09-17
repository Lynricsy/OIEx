---
title: 主定理简洁结论
date: 2021-09-17
tags:
 - 初赛
categories: 初赛
description: 主定理，直接上结论！
top_img: https://api.dujin.org/bing/1920.php
cover: https://article.biliimg.com/bfs/article/c133f6366b1c376d289197967788f521f62efcd6.jpg
---
## 前言

首先，众所周知，主定理是一个根据复杂度递推式子计算出实际复杂度的定理。

网上有不少讲解主定理的文章，但是我感觉可能对于一部分人来说还是太长了（毕竟就出一道题，看什么证明![qq_emoji: ww](https://z3.ax1x.com/2021/05/30/2VYiTA.png))

所以我就写一个直接说结果的博客吧。

## 直接上结论

假设复杂度递推式子是

$T(n)=aT(\frac{n}{b})+O(n^d)$

那么

如果$\dfrac{a}{b^d}<1$：

复杂度为

$O(n^d)$

如果$\dfrac{a}{b^d}>1$：

复杂度为

$O(n^{\log_ba})$

如果$\dfrac{a}{b^d}=1$：

复杂度为

$O(n^{d}\log_bn)$

嗯，到这里就结束了！![qq_emoji: xy](https://xn--9zr.tk/xyx)