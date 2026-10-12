#include <iostream>
#include <string>
#include <algorithm>
#include "../Real.h"
using namespace std;
int main() {
  string a, op, b;
  while (cin >> a >> op >> b) {
    Real x(a), y(b);
    if (op == "+") cout << (x + y) << "\n";
    else if (op == "-") cout << (x - y) << "\n";
    else if (op == "*") cout << (x * y) << "\n";
    else if (op == "/") { if (y == Real(0)) cout << "DIV0\n"; else cout << (x / y) << " " << max(x.precision(), y.precision()) + Real::DIVISION_DIGITS << "\n"; }
    else if (op == "<") cout << (x < y) << "\n";
    else if (op == "==") cout << (x == y) << "\n";
    cout.flush();
  }
}
