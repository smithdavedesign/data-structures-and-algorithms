#include "largeNum.h"
#include <vector>
#include <iostream>

largeNum::largeNum()
{
  negative = false;
}

largeNum::largeNum(std::string a)
{
  if(a[0] == '-')
    {
      negative = true;
      a.erase(a.begin());
    }
  else
    {
      negative = false;
    }
  int length = a.length() - 1;
  for(int i = length; i >= 0; i--)
    {
      num.push_back(a[i] - '0');
    }
}

largeNum::largeNum(std::vector<int> n, bool neg)
{
  num = n;
  negative = neg;
}

largeNum *largeNum::sum(largeNum *b)
{
  std::vector<int> sum;
  bool neg = false;
  int carry = 0;
  if(negative)
    {
      negative = false;
      largeNum *temp = b->diff(this);
      if(b->isNegative() || isLarger(b))
	{
	  temp->setNegative(true);
	}
      negative = true;
      return temp;
    }
  else if(b->isNegative())
    {
      b->setNegative(false);
      largeNum *temp = diff(b);
      if(!isLarger(b))
	{
	  temp->setNegative(true);
	}
      b->setNegative(true);
      return temp;
    }
  else
    {
      equalizeSize(b);

      for(int i = 0; i < num.size(); i++)
	{
	  int tempSum = num[i] + b->getAtPos(i) + carry;
	  if(tempSum > 9)
	    {
	      tempSum -= 10;
	      carry = 1;
	    }
	  else
	    {
	      carry = 0;
	    }
	  sum.push_back(tempSum);
	}
      if(carry)
	{
	  sum.push_back(carry);
	}
    }
  
  return new largeNum(sum, neg);
}

//returns this - b
largeNum *largeNum::diff(largeNum *b)
{
  std::vector<int> diff;
  int borrow = 0;

  if(negative)
    {
      negative = false;
      
      largeNum *temp = sum(b);
      if(b->isNegative())
	{
	  negative = true;
	  if(!isLarger(b))
	    {
	      temp->setNegative(true);
	    }
	  else
	    {
	      temp->setNegative(false);
	    }
	  return temp;
	}
      else
	{
	  temp->setNegative(true);
	}
      negative = true;
      return temp;
    }
  else if(b->isNegative())
    {
      b->setNegative(false);
      largeNum *temp = sum(b);
      temp->setNegative(false);
      b->setNegative(true);
      return temp;
    }
  else if(!isLarger(b))
    {
      largeNum *temp = b->diff(this);
      temp->setNegative(true);
      return temp;
    }
  else
    {
      for(int i = 0; i < num.size(); i++)
	{
	  int tempDiff = num[i] - b->getAtPos(i) - borrow;
	  if(tempDiff < 0)
	    {
	      for(int j = i + 1; j < num.size(); j++)
		{
		  if(num[j] != 0)
		    {
		      tempDiff += 10;
		      borrow = 1;
		      break;
		    }
		}
	    }
	  else
	    {
	      borrow = 0;
	    }
	  diff.push_back(tempDiff);
	} 
    }
      
  return new largeNum(diff, false);
}


void largeNum::setLength(int l)
{
  while(l > num.size())
    {
      num.push_back(0);
    }
    
}

void largeNum::setNum(std::vector<int> newNum)
{
  num = newNum;
}

void largeNum::print()
{
  bool leadingZero = true;
  if(negative)
    {
      std::cout << "-";
    }
  for(int i = num.size() - 1; i >= 0; i--)
    {
      if(num[i] != 0 || !leadingZero)
	{
	  std::cout << num[i];
	  leadingZero = false;
	}
    }
  std::cout << std::endl;
}

int largeNum::size()
{
  return num.size();
}

int largeNum::getAtPos(int i)
{
  return num[i];
}

void largeNum::setNegative(bool a)
{
  negative = a;
}

bool largeNum::isNegative()
{
  return negative;
}

//return true if this is larger than b
bool largeNum::isLarger(largeNum *b)
{
  equalizeSize(b);
  if(negative && !b->isNegative())
    {
      return false;
    }
  if(!negative && b->isNegative())
    {
      return true;
    }
  for(int i = num.size() - 1; i >=0; i--)
    {
      if(num[i] > b->getAtPos(i))
	{
	  if(negative)
	    {
	      return false;
	    }
	  return true;
	}
      else if(num[i] < b->getAtPos(i))
	{
	  if(negative)
	    {
	      return true;
	    }
	  return false;
	}
    }
  return false;
}

void largeNum::equalizeSize(largeNum *b)
{
  if(b->size() > num.size())
    {
      setLength(b->size());
    }
  else
    {
      b->setLength(num.size());
    }
}


int largeNum::exponentiation(int base, int exp_num){
  if(exp_num == 0)
    {
      return 1;
    }
  if(exp_num % 2 == 0)
    {
      return exponentiation(base, (exp_num/2))^2; //times the number by itself
      //so call mult func with two params which are a and a
    }
  else
    {
      return  base * (exponentiation(base,  (exp_num-1 / 2)));
      // use multiplication function for the recursive times a.  
    }
      
}


