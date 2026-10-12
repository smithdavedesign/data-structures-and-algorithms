#include <iostream>
#include "largeNum.h"

using namespace std;

int exponentiation(int base, int exp_num); 
int main()
{
  std::string var;
  char end = 'y';
   int result = exponentiation(4, 3);
   cout <<"EX result : "<< result << endl;
  while(end == 'y')
    {
      std::cout << "input first variable: ";
      std::cin >> var;
      largeNum a(var);

      std::cout << "input second variable: ";
      std::cin >> var;
      largeNum b(var);
      std::cout << "a is ";
      a.print();
      std::cout << "b is ";
      b.print();
      largeNum *sum = a.sum(&b);    // sum() and diff() return new objects: free them below
      largeNum *diff = a.diff(&b);

      std::cout << "a + b = ";
      sum->print();
      std::cout << " a - b = ";
      diff->print();
      delete sum;
      delete diff;
      std::cout << "another? (y/n) ";


      std::cin >> end;
      
    }
  return 0;
}

int exponentiation(int base, int exp_num){
  // Exponentiation by squaring: b^n = (b^(n/2))^2, times b once more when n is odd.
  // (Fixed in 2026: `exp_num-1 / 2` parsed as `exp_num - 0`, so odd exponents recursed forever.)
  if(exp_num == 0)
    {
      return 1;
    }
  int half = exponentiation(base, exp_num / 2);
  return exp_num % 2 == 0 ? half * half : half * half * base;
}
