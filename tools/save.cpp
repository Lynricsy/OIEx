#include <cstdlib>

int main() {
  long long n = 1;
  switch (n) {
  case 1:
    system("cp ~/OIEx/src/main.cpp ~/OIEx/archive/Luogu/P3227.cpp");
    break;
  }
  // 自动清空 work.cpp
  // return 0;
  system("rm ~/OIEx/src/main.cpp");
  system("cp ~/OIEx/std/std.cpp ~/OIEx/src/main.cpp");
  return 0;
}