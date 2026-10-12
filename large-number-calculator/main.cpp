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
      largeNum *a = new largeNum(var);

      std::cout << "input first variable: ";
      std::cin >> var;
      largeNum *b = new largeNum(var);
      std::cout << "a is ";
      a->print();
      std::cout << "b is ";
      b->print();
      largeNum *sum = a->sum(b);
      largeNum *diff = a->diff(b);

      std::cout << "a + b = ";
      sum->print();
      std::cout << " a - b = ";
      diff->print();


      std::cin >> end;
      
    }
  return 0;
}

int exponentiation(int base, int exp_num){
  if(exp_num == 0)
    {
      return 1;
    }
  if(exp_num % 2 == 0)
    {
      return exponentiation(base, (exp_num/2)) * base; //times the number by itself
      //so call mult func with two params which are a and a
    }
  else
    {
      return  base * (exponentiation(base,  (exp_num-1 / 2)));
      // use multiplication function for the recursive times a.
    }

}
