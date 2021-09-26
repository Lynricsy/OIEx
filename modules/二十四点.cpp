#include <bits/stdc++.h>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;

const double PRECISION = 1E-6;
const int COUNT_OF_NUMBER = 4;
const int NUMBER_TO_BE_CAL = 24;

double number[COUNT_OF_NUMBER];
string expression[COUNT_OF_NUMBER];

bool Search(int n) {
  if (n == 1) {
    if (fabs(number[0] - NUMBER_TO_BE_CAL) < PRECISION) {
      cout << expression[0] << endl;
      return true;
    } else {
      return false;
    }
  }

  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      double a, b;
      string expa, expb;

      a = number[i];
      b = number[j];
      number[j] = number[n - 1];

      expa = expression[i];
      expb = expression[j];
      expression[j] = expression[n - 1];

      expression[i] = '(' + expa + '+' + expb + ')';
      number[i] = a + b;
      if (Search(n - 1))
        return true;

      expression[i] = '(' + expa + '-' + expb + ')';
      number[i] = a - b;
      if (Search(n - 1))
        return true;

      expression[i] = '(' + expb + '-' + expa + ')';
      number[i] = b - a;
      if (Search(n - 1))
        return true;

      expression[i] = '(' + expa + '*' + expb + ')';
      number[i] = a * b;
      if (Search(n - 1))
        return true;

      if (b != 0) {
        expression[i] = '(' + expa + '/' + expb + ')';
        number[i] = a / b;
        if (Search(n - 1))
          return true;
      }
      if (a != 0) {
        expression[i] = '(' + expb + '/' + expa + ')';
        number[i] = b / a;
        if (Search(n - 1))
          return true;
      }

      number[i] = a;
      number[j] = b;
      expression[i] = expa;
      expression[j] = expb;
    }
  }
  return false;
}

int main() {
  for (int i = 0; i < COUNT_OF_NUMBER; i++) {
    char buffer[20];
    int x;
    cin >> x;
    number[i] = x;
    sprintf(buffer, "%d", x);
    expression[i] = buffer;
  }

  if (Search(COUNT_OF_NUMBER)) {
    cout << "Success." << endl;
  } else {
    cout << "Fail." << endl;
  }
  return 0;
}