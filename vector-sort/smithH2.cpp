//Program: sum of floats.
//File: smithHW2.cpp
//Author:David Smith
//Date: feb 10th 2017
//Description:this program stores a files values into a vector then proceeds to sort thte vector
//and calculate the sum after the sort arbitrary precision.
#include<iostream>
#include<fstream>
#include<ostream>
#include<vector>
#include<iomanip>
#include<algorithm>

using namespace std;

void function(std::fstream &stream);

int main(int argc, char **argv)
{
  std::fstream input1 (argv[1]);
  function(input1);
}


void function(std::fstream &stream)
{
  float sum = 0;
  float desending = 0;
  float ascending = 0;
  float v = 0;
  vector<float> floatVector; //my vector to store values of file

  while(stream >> v)//while there is stuff in the file push it one by one onto v
    {
      floatVector.push_back(v);//push the files contents onto my vector
    }
  
  ////////////////////////////////////////////////////////////////////////////////////////
  //for the sum of the unsorted vector
 
  for(int i = 0; i < floatVector.size(); i++)
    {
      sum += floatVector[i];

    }
  cout << "The sum of the unsorted values is: "<< fixed << setprecision(5)  << sum << endl;
  /////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////////////////////////////////////////////////////////////
  //sort in descending
  sort(floatVector.rbegin(), floatVector.rend());

  for(int i = 0; i < floatVector.size(); i++)
    {
      desending += floatVector[i];

    }
   cout << "The sum of the descending values is: "<< fixed << setprecision(5)  << desending <<endl;
   ////////////////////////////////////////////////////////////////////////////////////////
   
   ///////////////////////////////////////////////////////////////////////////////////////////////
   //sort in ascending
   sort(floatVector.begin(), floatVector.end());
  for(int i = 0; i < floatVector.size(); i++)
    {
      ascending += floatVector[i];

    }  
  cout << "The sum of the ascending values is: "<< fixed << setprecision(5)  << ascending << endl;

 
  //////////////////////////////////////////////////////////////////////////////////////////////

    for(int i = 0; i < floatVector.size(); i++)
    {
      cout << floatVector[i] << '\n';
    }
  
}

