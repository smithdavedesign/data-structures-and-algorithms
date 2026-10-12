#ifndef LARGENUMBER
#define LARGENUMBER
#include <vector>
#include <string>

class largeNum
{
 public:
  largeNum();
  largeNum(std::string a);
  largeNum(std::vector<int> n, bool neg);
  largeNum *sum(largeNum *b);
  largeNum *diff(largeNum *b);
  void setNum(std::vector<int> newNum);
  void print();
  void setLength(int l);
  int size();
  int getAtPos(int i);
  void setNegative(bool a);
  bool isNegative();
  bool isLarger(largeNum *b);
  void equalizeSize(largeNum *b);
  int exponentiation(int base, int exp_num);
 private:
  std::vector<int> num;
  bool negative;
  
};

#endif
