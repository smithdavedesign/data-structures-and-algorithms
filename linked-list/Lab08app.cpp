// Lab 08 application program
// Data: Spring 2012
// Description: This program is designed to test the LList class.

#include <iostream>
#include <fstream>
#include <cstdlib>
#include "LList.h"

using namespace std;

int main (int argc, char * argv[])
{
   // Test for existence of file name argument
   if (argc < 2)
   {
      cerr << "Usage: " << argv[0] << " <file-name>\n";
      exit (1);
   }
   // Test to see if file was opened
   ifstream ins (argv[1]);
   if (ins.fail ())
   {
      cerr << "No file " << argv[1] << " found\n";
      exit (2);
   }
   LList LL;
   char action;
   int value;
   while (ins >> action)
      switch (action)
      {
         case 'D' : 
            if (LL.DeleteFirst ())
               cout << "First value deleted from list\n";
            else
               cout << "First value not deleted from list\n";
            break;
         case 'E' : 
            if (LL.DeleteLast ())
               cout << "Last value deleted from list\n";
            else
               cout << "Last value not deleted from list\n";
            break;
         case 'I' : ins >> value;
            if (LL.InsertFirst (value))
               cout << value << " inserted at front of list\n";
            else
               cout << value << " not inserted at front of list\n";
            break;
         case 'J' : 
            ins >> value;
            if (LL.InsertLast (value))
               cout << value << " inserted at end of list\n";
            else
               cout << value << " not inserted at end of list\n";
            break;
         case 'S' : cout << LL.Size() << endl;
            break;
         case 'W' : cout << LL << endl;
            break;
         default : cout << action << " is not a valid option\n";
      }
      return 0;
}

