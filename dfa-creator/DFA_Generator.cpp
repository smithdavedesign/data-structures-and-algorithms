#include "DFA_Generator.h"

/*******************************************************************
//Constructor for DFA_Gen class
/********************************************************************/
DFA_Generator::DFA_Generator()
{
  //strings for each function
  begin_sub = "";
  end_sub = "";
  contain_sub = ""; 
  begin_sub_odd_or_even = "";
  k = 0;  //for the (least most and exactly) function

  combine_string = "";
  //for the 4 functions
  begin_substring = false;
  end_substring = false;
  contains_sub_least_most_exactly = false;
  contain_even_odd = false;
  beg_accept = false;
  end_accept = false;
  even_accept = false;
  contain_accept = false;
  combine =false;
  combine_result = false;
  odd =false;//boolean flag for even odd function
}

/*******************************************************************
/********************************************************************/
DFA_Generator::~DFA_Generator()
{

}

/*******************************************************************
// DFA Creator for the substring begin
/********************************************************************/
void DFA_Generator::begin_Substring(string s) //f
{
  int accepting_state = s.length();
  int fail_state = -1;
  int how_many_states = s.length() + 1; 

  if(combine == true && accepting_states.size() > 0)
    {
      for(int i =0; i < accepting_states.size(); i++)
	{
	  accepting_states.pop_back();
	}
    }
  
  accepting_states.push_back(accepting_state); //accepting statevector
  int dfa [how_many_states][alphabet.size()];
  
  for(int l = 0; l <  how_many_states; l++)
    {
      for(int j = 0; j < alphabet.size(); j++)
	{
	  if(l == accepting_state)
	    {
	      dfa[l][j]= accepting_state;
	    }
	  else
	    {
	      if(s[l] == alphabet[j])
		{
		  dfa [l][j] = l + 1;
		}
	      else if(s[l] != alphabet[j])
		{
		  dfa[l][j] = -1;
		}
	    }
	}
    }
  // string_Check(dfa);//checks the dfa with user inputed strings
  /////**************/////
  ///// Testing   //////
  /////////////////////
  bool end = false;
  bool after_evaluate = false;
  cout << "here is your transition table: " << endl;
  for (int i = 0; i < how_many_states; i++)
    {
      for(int j = 0; j < alphabet.size(); j++)
	cout << dfa[i][j] << " ";
      cout << endl;
    }

  while(end == false)
    {
      string input = "";
      if(combine == true)
	{
	  cout << "You entered this string to test: " << combine_string << endl;
	  input = combine_string;
	}
      else
	{
	  cout << "enter a string you believe should be in the language" << endl;
	  cin >> input;
	}
      int old_state = 0;
      int next_state = 0;
      //////Check to see if the string passes the dfa the user specified///////
      ///testing the dfa///////
      for(int i = 0; i < input.length(); i++)
	{
	  if(old_state == -1)
	    {
	      after_evaluate = false;
	      cout << "this is not in your language "<<endl;
	      break;
	    }
	  next_state = dfa[old_state][column_Finder(input[i])];
	  //checks the value of the character in are alphabet. maps it using the old state so now we know where are next state is
	  old_state = next_state;
	  if(old_state == -1)
	    {
	      after_evaluate = false;
	      cout << "this is not in your language "<< endl;
	      break;
	    }
	}

      for(int k=0; k < accepting_states.size(); k++)
	{
	  if(old_state == accepting_states[k])//check to see if are final state was an accepting one
	    {
	      after_evaluate = true;
	    }
	}

      if(after_evaluate == true)
	{
	  cout << "yes " << input << " is in the Language and ends in a accepting state " << endl;
	  cout << "accepting states are: ";
	  for(int i =0; i< accepting_states.size(); i++)
	    {
	      cout << accepting_states[i] << " ";
	    }
	  cout << "current_state: "<< next_state <<endl;
	  beg_accept= true;
	  if(combine ==true)
	    {
	      return;
	    }
	}
      else
	{
	  cout << "no " << input << " is not in the Language and ends in"
	       << " a non accepting state " << endl;
	  cout << "accepting states are: ";
	  for(int i =0; i< accepting_states.size(); i++)
	    {
	      cout << accepting_states[i] << " ";
	    }
	  cout << "current_state: "<< next_state <<endl;
	  if(combine ==true)
	    {
	      beg_accept= false;
	      return;
	    }
	}
      after_evaluate = false;
      cout << "try another string? enter 1 for yes and 2 for no " << endl;
      int keep_going = 0;
      cin >> keep_going;
      if(keep_going == 2)
	{
	  end = true;
	}
    }
  return;
}

 


/*******************************************************************
// DFA gen for substring end
/********************************************************************/
void DFA_Generator::end_Substring(string s)
{
  int accepting_state = s.length();
  char char_start_state = s[0];
  int first_state = 1;
  int how_many_states = s.length() +1;
  int dfa[how_many_states][alphabet.size()];  //initalize your dfa/trasition table

  if(combine == true && accepting_states.size() > 0)
    {
      for(int i =0; i < accepting_states.size(); i++)
	{
	  accepting_states.pop_back();
	}
    }
  accepting_states.push_back(accepting_state);
  
  for(int l = 0; l <  how_many_states; l++)
    {
      for(int j = 0; j < alphabet.size(); j++)
	{
	  //cout << s[subcounter] << " " << alphabet[j] << " " << char_start_state << int_super_start_state << int_final_state << endl;
	  if(l == accepting_state)
	    {
	      if(alphabet[j] == char_start_state)
		{
		  dfa[l][j] = first_state;
		}
	      else
		dfa [l][j] = 0;
	    }
	  if(s[l] == alphabet[j])
	    {
	      dfa [l][j] = l + 1;
	    }
	  else if(alphabet[j] == char_start_state)
	    {
	      dfa[l][j] = first_state;
	    }
	  else
	    dfa[l][j] = 0;
	}
    }
  
  /////**************/////
  ///// Testing   //////
  /////////////////////
  bool end = false;
  bool after_evaluate = false;
  cout << "here is your transition table: " << endl;
  for (int i = 0; i < how_many_states; i++)
    {
      for(int j = 0; j < alphabet.size(); j++)
	cout << dfa[i][j] << " ";
      cout << endl;
    }

  while(end == false)
    {
      string input = "";
      if(combine == true)
	{
	  cout << "You entered this string to test: " << combine_string << endl;
	  input = combine_string;
	}
      else
	{
	  cout << "enter a string you believe should be in the language" << endl;
	  cin >> input;
	}
      
      int old_state = 0;
      int next_state = 0;
      //////Check to see if the string passes the dfa the user specified///////
      ///testing the dfa///////
      for(int i = 0; i < input.length(); i++)
	{
	  if(old_state == -1)
	    {
	      after_evaluate = false;
	      cout << "this is not in your language "<<endl;
	      break;
	    }
	  next_state = dfa[old_state][column_Finder(input[i])];
	  //checks the value of the character in are alphabet. maps it using the old state so now we know where are next state is
	  old_state = next_state;
	  if(old_state == -1)
	    {
	      after_evaluate = false;
	      cout << "this is not in your language "<< endl;
	      break;
	    }
	}

      for(int k=0; k < accepting_states.size(); k++)
	{
	  if(next_state == accepting_states[k])//check to see if are final state was an accepting one
	    {
	      after_evaluate = true;
	    }
	}

      if(after_evaluate == true)
	{
	  cout << "yes " << input << " is in the Language and ends in a accepting state " << endl;
	  cout << "accepting states are: ";
	  for(int i =0; i< accepting_states.size(); i++)
	    {
	      cout << accepting_states[i] << " ";
	    }
	  cout << "current_state: "<< next_state <<endl;
	  end_accept =true;
	  if(combine ==true)
	    {
	      return;
	    }
	}
      else
	{
	  cout << "no " << input << " is not in the Language and ends in"
	       << " a non accepting state " << endl;
	  cout << "accepting states are: ";
	  for(int i =0; i< accepting_states.size(); i++)
	    {
	      cout << accepting_states[i] << " ";
	    }
	  cout << "current_state: "<< next_state <<endl;
	  if(combine ==true)
	    {
	      end_accept =false;
	      return;
	    }
	}
      after_evaluate = false;
      cout << "try another string? enter 1 for yes and 2 for no " << endl;
      int keep_going = 0;
      cin >> keep_going;
      if(keep_going == 2)
	{
	  end = true;
	}
    }


  return;
}

/*******************************************************************
// DFA gen substring of least or most or exact length k
/********************************************************************/
void DFA_Generator::contains_Substring_Least_Most_Exactly_K(string s, bool most, bool least, bool exact, int k) // seperate constructor
{
  char char_start_state = s[0];
  //loop through transition table
  int int_super_start_state = 0;
  int int_final_state = s.length() - 1; // for checking when the next dfa is technically starting in the dfa states
  //num loop is how manny times were gonna repeat the given dfa with another of the same dfa
  int num_loop = 0;
  //accepting state
  int accepting_state = 0;
  //the substring is at least k
  //  enum alphabet_state_values {alphabet[i] =1,
  if(combine == true && accepting_states.size() > 0)
    {
      for(int i =0; i < accepting_states.size(); i++)
	{
	  accepting_states.pop_back();
	}

    }
 
  if(least == true)
    {
      num_loop = k;
      accepting_state = s.length() * num_loop;
      accepting_states.push_back(accepting_state);
    }
  else if(most == true)
    {
      num_loop = k + 1;
      int fail_state = s.length() * num_loop;
      // accepting_state = s.length() * num_loop;
      for(int i =0; i < num_loop * s.length(); i++)
	accepting_states.push_back(i);
      
    }
  else if(exact == true)
    {
      num_loop = k + 1;
      accepting_state = s.length() * k;
      for(int i =0; i < s.length(); i++)
	{
	  accepting_states.push_back(accepting_state + i);
	}
    }

  for(int i = 0; i < alphabet.size(); i++)
    cout << alphabet[i] << endl;
  cout << endl;
  
  //how manny states we will have
  int how_manny_states = s.length() * num_loop + 1;
  //initalize your dfa/trasition table
  int dfa[how_manny_states][alphabet.size()];
  //  dfa = new int*[];
  int subcounter = 0;
  for(int l = 0; l <  how_manny_states; l++)
    {
      for(int j = 0; j < alphabet.size(); j++)
	{
	  if(s[subcounter] == alphabet[j])
	    {
	      if(l == (how_manny_states - 1))
		dfa[l][j] = l;
	      else
		dfa [l][j] = l + 1;
	    }
	  else if(alphabet[j] == char_start_state)
	    {
	      dfa[l][j] = int_super_start_state + 1;
	    }
	  else
	    dfa[l][j] = int_super_start_state;
	}
      if(subcounter == (s.length() - 1))
	subcounter = 0;
      else
	subcounter++;
      if((l == int_final_state) && (num_loop != 0))
	{
	  int_final_state = int_final_state + s.length();
	  int_super_start_state = int_super_start_state + s.length();
	  num_loop--;
	}
    }

  /////**************/////
  ///// Testing   //////
  /////////////////////
  bool end = false;
  bool after_evaluate = false;
  cout << "here is your transition table: " << endl;
  for (int i = 0; i < how_manny_states; i++)
    {
      for(int j = 0; j < alphabet.size(); j++)
	cout << dfa[i][j] << " ";
      cout << endl;
    }

  while(end == false)
    {
      string input = "";
      
      if(combine == true)
	{
	  cout << "You entered this string to test: " << combine_string << endl;
	  input = combine_string;
	}
      else
	{
	  cout << "enter a string you believe should be in the language" << endl;
	  cin >> input;
	}
      int old_state = 0;
      int next_state = 0;
      //////Check to see if the string passes the dfa the user specified///////
      ///testing the dfa///////
      for(int i = 0; i < input.length(); i++)
	{
	  if(old_state == -1)
	    {
	      after_evaluate = false;
	      cout << "this is not in your language "<<endl;
	      break;
	    }
	  next_state = dfa[old_state][column_Finder(input[i])];

	  //checks the value of the character in are alphabet. maps it using the old state so now we know where are next state is
	  old_state = next_state;
	  if(old_state == -1)
	    {
	      after_evaluate = false;
	      cout << "this is not in your language "<< endl;
	      break;
	    }
	}

      for(int k=0; k < accepting_states.size(); k++)
	{
	  if(old_state == accepting_states[k])//check to see if are final state was an accepting one
	    {
	      after_evaluate = true;
	    }
	}

      if(after_evaluate == true)
	{
	  cout << "yes " << input << " is in the Language and ends in a accepting state " << endl;
	  cout << "accepting states are: ";
	  for(int i =0; i< accepting_states.size(); i++)
	    {
	      cout << accepting_states[i] << " ";
	    }
	  cout << "current_state: "<< next_state <<endl;
	  even_accept =true;
	  if(combine ==true)
	    {
	      return;
	    }
	}
      else
	{
	  cout << "no " << input << " is not in the Language and ends in"
	       << " a non accepting state " << endl;
	  cout << "accepting states are: ";
	  for(int i =0; i< accepting_states.size(); i++)
	    {
	      cout << accepting_states[i] << " ";
	    }
	  cout << "current_state: "<< next_state <<endl;
	  if(combine ==true)
	    {
	      even_accept =false;
	      return;
	    }
	}
      after_evaluate = false;
      cout << "try another string? enter 1 for yes and 2 for no " << endl;
      int keep_going = 0;
      cin >> keep_going;
      if(keep_going == 2)
	{
	  end = true;
	  exit(0);
	}
    }

   return;
}

/*******************************************************************
// DFA gen substring that is even or odd
/********************************************************************/
void DFA_Generator::contains_Substring_Odd_Even(string s, bool odd)
{
  bool odd_half =false;
  //accepting state
  int accept_state = s.length();
  if(combine == true && accepting_states.size() > 0)
    {
      for(int i =0; i < accepting_states.size(); i++)
	{
	  accepting_states.pop_back();
	}
      
    }
  
  if(odd == true)
    {
      for(int i =0; i < s.length(); i++)
	{
	  if(s.length() == 1)
	    {
	      accepting_states.push_back(1);
	    }
	  else
	    accepting_states.push_back(accept_state + i);
	}
    }
  else
    {
      for(int i=0; i < s.length(); i++)
	{
	  if(s.length() == 1)
	    {
	      accepting_states.push_back(0);
	    }
	  else
	    accepting_states.push_back(i);
	}
    }


  int count = 0;
  char char_start_state = s[0];
  //loop through transition table
  int int_super_start_state = 0;
  int int_final_state = s.length() - 1; // for checking when the next dfa is technically starting in the dfa states
  //num loop is how manny times were gonna repeat the given dfa with another of the same dfa
  int num_loop = 1;
  //accepting state
  int accepting_state = 0;
  //the substring is at least k
  //  enum alphabet_state_values {alphabet[i] =1,
  int final_transition = s.length() *2;
  //how manny states we will have
  int how_manny_states = s.length() * 2;
  //initalize your dfa/trasition table
  int dfa [how_manny_states][alphabet.size()];

  int subcounter = 0;
  for(int l = 0; l <  how_manny_states; l++)
    {
      for(int j = 0; j < alphabet.size(); j++)
	{
	  //cout << s.length() << " " << l << endl;

	  //cout << s[subcounter] << " " << alphabet[j] << " " << char_start_state << int_super_start_state << int_final_state << endl;
	  if(s[subcounter] == alphabet[j])
	    {
	      if(l == (how_manny_states - 1))
		dfa[l][j] = l;
	      else

		{
		  dfa [l][j] = l + 1;
		}
	    }
	  else if(alphabet[j] == char_start_state)
	    {
	      dfa[l][j] = int_super_start_state + 1;
	    }
	  else
	    {
	      dfa[l][j] = int_super_start_state;
	    }
	  if(s[s.length() - 1] == alphabet[j] && l == how_manny_states -1)
	    {
	      dfa[l][j] = 0;
	    }
	}

      if(subcounter == (s.length() - 1))
	subcounter = 0;
      else
	subcounter++;
      if((l == int_final_state) && (num_loop != 0))
	{
	  if(count == 2)
	    {
	      int_final_state = 0;
	      int_super_start_state = 0;
	    }
	  else
	    {
	      int_final_state = int_final_state + s.length();
	      int_super_start_state = int_super_start_state + s.length();
	      num_loop--;
	      count ++;
	    }
	}

    }

  /////**************/////
  ///// Testing   //////
  /////////////////////
  bool end = false;
  bool after_evaluate = false;
  cout << "here is your transition table: " << endl;
  for (int i = 0; i < how_manny_states; i++)
    {
      for(int j = 0; j < alphabet.size(); j++)
	cout << dfa[i][j] << " ";
      cout << endl;
    }

  while(end == false)
    {
      string input = "";
      if(combine == true)
	{
	  cout << "You entered this string to test: " << combine_string << endl;
	  input = combine_string;
	}
      else
	{
	  cout << "enter a string you believe should be in the language" << endl;
	  cin >> input;
	}
      int old_state = 0;
      int next_state = 0;
      //////Check to see if the string passes the dfa the user specified///////
      ///testing the dfa///////
      for(int i = 0; i < input.length(); i++)
	{
	  next_state = dfa[old_state][column_Finder(input[i])];
	  //checks the value of the character in are alphabet. maps it using the old state so now we know where are next state is
	  old_state = next_state;
	}
      
      for(int k=0; k < accepting_states.size(); k++)
	{
	  //  cout << old_state << endl;
	  // cout << accepting_states[k] << endl;
	  if(old_state == accepting_states[k])//check to see if are final state was an accepting one
	    {
	      after_evaluate = true;
	    }
	}

      if(after_evaluate == true)
	{
	  cout << "yes " << input << " is in the Language and ends in a accepting state " << endl;
	  cout << "accepting states are: ";
	  for(int i =0; i< accepting_states.size(); i++)
	    {
	      cout << accepting_states[i] << " ";
	    }
	  cout << "current_state: "<< next_state <<endl;
	  contain_accept = true;
	  if(combine ==true)
	    {
	      return;
	    }
	}
      else
	{
	  cout << "no " << input << " is not in the Language and ends in "
	       << "a non accepting state " << endl;
	  cout << "the state is: " << old_state << endl;
	  cout << "accepting states are: ";
	  for(int i =0; i< accepting_states.size(); i++)
	    {
	      cout << accepting_states[i] << " ";
	    }
	  if(combine ==true)
	    {
	      contain_accept = false;
	      return;
	    }
	}
      after_evaluate = false;
      cout << "try another string? enter 1 for yes and 2 for no " << endl;
      int keep_going = 0;
      cin >> keep_going;
      if(keep_going == 2)
	{
	  end = true;
	}
    }

  
  return;
}

/*******************************************************************
// Sets the alphabet for the desired DFA
/********************************************************************/
void DFA_Generator::set_Alphabet(int how_many)
{
  alphabet.clear();
  string alphabet_string = "";
  alphabet_map[how_many];
  
  cout << "enter your alphabet all in one line, for example if you wanted 0 and 1 in your alphabet you would enter 01 . " << endl;
  cin >> alphabet_string;
  for(int i = 0; i < how_many; i++)
    {
      alphabet.push_back(alphabet_string[i]);
    }
  
  
  return;
}

/*******************************************************************
// This function calls all the needed functions to set up are input for are DFA
// creating functions.
/********************************************************************/
void DFA_Generator::user_Choice_Set()
{
  int alphabet_Size = 0;
  int decision = 0;
  
  /////////////// what alphabet do they want /////////////////////////////
  cout << "Enter how many characters you would like in your alphabet " << endl
       << "For example: if you want 0 and 1 in your alphabet you would enter 2." << endl;
  cin >> alphabet_Size;
  set_Alphabet(alphabet_Size);  
  cout << "Here are your options..." << endl
       << "1. begining substring " << endl
       << "2. ending substring. " << endl
       << "3. contains substring of certain size" << endl
       << "4. contains a substring of even or odd length. " << endl
       << "5. combine two languages. " << endl
       << "choose one of the 4 options, enter 1 , 2 , 3 , 4, or 5 " << endl;
   
  /////////////// set rules for dfa up /////////////////////////////
  cin >> decision;
  int rule_chosen = user_Choice(decision);

  //moved
  
  ////////////// create the dfa using the data the user gave ///////////////////////////////
  DFA_Function_Caller();

  
  return;
}

/*******************************************************************
//takes the user choice of operations/rules and stores them so we can make a DFA
//with the data they have chosen.
/********************************************************************/
int DFA_Generator::user_Choice(int decision)
{
  if(decision == 1)
    {
      begin_substring = true;
      cout << "enter a substring that will be at the begining "
	   << "of all accepted strings in your DFA" << endl;
      cin >> begin_sub;
      return decision;
    }
  if(decision == 2)
    {
      end_substring = true;
      cout << "enter a substring that will be at the ending "
	   << "of all accepted strings in your DFA" << endl;
      cin >> end_sub;
      return decision;
    }
  if(decision == 3)
    {
      int input = 0;
      contains_sub_least_most_exactly = true;
      cout << "enter a substring that will be anywhere in your "
	   << "accepted strings in your DFA" << endl;
      cin >> begin_sub;
      cout << "now enter 1: substring at most k,"
	   <<  "2: substring at least k, 3: substring  exactly k" << endl;
      cin >> input;
      if(input == 1)
	{
	  most = true;
	}
      if(input == 2)
	{
	  least = true;
	}
      if(input == 3)
	{
	  exact = true;
	}
      cout << "enter a amount for k: " << endl;
      cin >> k;
      return decision;
    }
  if(decision == 4)
    {
      char input = ' ';
      contain_even_odd = true;
      cout << "enter a substring that will be anywhere in your "
	   << "accepted strings in your DFA But will be an even or odd amount of times " << endl << endl;
      cin >> begin_sub_odd_or_even;
      cout << "enter e for even amount of substrings or o for odd amount of substrings " << endl;
      cin >> input;
      if(input  == 'o')
	{
	  odd = true;
	}
      else
	{
	  odd = false;
	}
      return decision;
    }

  if(decision == 5)
    {
      combine =true;      
      cout << "Enter the two languages you like to combine 1: begin  2: end  3: contains  4: even/odd ...enter 1,2,3 or 4" << endl;
      cout << " for example if you want end substring and contain substring you would enter 1 3 " << endl;
      cin >> first;
      cin >> seccond;

      if(first == 1 || seccond == 1)
	{
	  begin_substring = true;
	  cout << "enter a substring that will be at the begining "
	       << "of all accepted strings in your DFA" << endl;
	  cin >> begin_sub;
	}
      if(first == 2 || seccond == 2)
	{
	  end_substring = true;
	  cout << "enter a substring that will be at the ending "
	       << "of all accepted strings in your DFA" << endl;
	  cin >> end_sub;
	}
      if(first == 3 || seccond == 3)
	{
	  int input = 0;
	  contains_sub_least_most_exactly = true;
	  cout << "enter a substring that will be anywhere in your "
	       << "accepted strings in your DFA" << endl;
	  cin >> begin_sub;
	  cout << "now enter 1: substring at most k,"
	       <<  "2: substring at least k, 3: substring  exactly k" << endl;
	  cin >> input;
	  if(input == 1)
	    {
	      most = true;
	    }
	  if(input == 2)
	    {
	      least = true;
	    }
	  if(input == 3)
	    {
	      exact = true;
	    }
	  cout << "enter a amount for k: " << endl;
	  cin >> k;
	}
      if(first == 4 || seccond == 4)
	{
	  char input = ' ';
	  contain_even_odd = true;
	  cout << "enter a substring that will be anywhere in your "
	       << "accepted strings in your DFA But will be an even or odd amount of times " << endl << endl;
	  cin >> begin_sub_odd_or_even;
	  cout << "enter e for even amount of substrings or o for odd amount of substrings " << endl;
	  cin >> input;
	  if(input  == 'o')
	    {
	      odd = true;
	    }
	  else
	    {
	      odd = false;
	    }
	}
      return decision;
    }
}

/*******************************************************************
// This function calls the functions to create the DFAs by using previous boolenas then will call the tester function
/********************************************************************/
void DFA_Generator::DFA_Function_Caller()
{

  if(combine == true)
    {

      cout << "Enter an input string you are going to run through both DFAs ." << endl;
      cin >> combine_string;
      if(first == 1 && seccond == 2)
	{
	  begin_Substring(begin_sub);
	  end_Substring(end_sub);
	  cout << "The result of your input string for both langauges is: ";
	  if(beg_accept == true && end_accept ==true)
	    cout << "The string is in both languages!" << endl;
	  else
	    cout << "Not in one or both of the languages"<< endl;
	  return;
	}
      if(first == 1 && seccond == 3)
	{
	  begin_Substring(begin_sub);
	  contains_Substring_Least_Most_Exactly_K(begin_sub, most, least, exact, k);
	  
	  cout << "The result of your input string for both langauges is: ";
	  if(beg_accept == true && contain_accept ==true)
	    cout << "The string is in both languages!" <<endl;
	  else
	    cout << "Not in one or both of the languages"<< endl;
	  return;
	}
      if(first == 1 && seccond == 4)
	{
	  begin_Substring(begin_sub);
	  contains_Substring_Odd_Even(begin_sub_odd_or_even, odd);//creates the dfa
	  
	  cout << "The result of your input string for both langauges is: ";
	  if(beg_accept == true && even_accept ==true)
	    cout << "The string is in both languages!" <<endl;
	  else
	    cout << "Not in one or both of the languages"<< endl;
	  return;
	}
      if(first == 2  && seccond == 3)
	{
	  end_Substring(end_sub);
	  contains_Substring_Least_Most_Exactly_K(begin_sub, most, least, exact, k);
	  cout << "The result of your input string for both langauges is: ";
	  if(end_accept == true && contain_accept ==true)
	    cout << "The string is in both languages!" <<endl;
	  else
	    cout << "Not in one or both of the languages"<< endl;
	  return;
	}
      if(first == 2 && seccond == 4)
	{
	  end_Substring(end_sub);
	  contains_Substring_Odd_Even(begin_sub_odd_or_even, odd);//creates the dfa
	  cout << "The result of your input string for both langauges is: ";
	  if(end_accept == true && even_accept ==true)
	    cout << "The string is in both languages!" <<endl;
	  else
	    cout << "Not in one or both of the languages"<< endl;
	  return;
	}
      if(first == 3 && seccond == 4)
	{
	  contains_Substring_Least_Most_Exactly_K(begin_sub, most, least, exact, k);	  
	  contains_Substring_Odd_Even(begin_sub_odd_or_even, odd);//creates the dfa
	  cout << "The result of your input string for both langauges is: ";
	  if(contain_accept == true && even_accept ==true)
	    cout << "The string is in both languages!" <<endl;
	  else
	    cout << "Not in one or both of the languages"<< endl;
	  return;
	}
    }

 
 if(begin_substring == true)//1
   {
     begin_Substring(begin_sub);
     return;
   }
 
 if(end_substring == true)//2
   {
     end_Substring(end_sub);
     return;
   }
 
 if(contains_sub_least_most_exactly == true)//3
   {
     contains_Substring_Least_Most_Exactly_K(begin_sub, most, least, exact, k);
     return;
   }
 
 if(contain_even_odd = true)//4
   {
     contains_Substring_Odd_Even(begin_sub_odd_or_even, odd);//creates the dfa
     return;
   }
 
 return;
}

/*******************************************************************
// This function calls the functions to create the DFAs by using previous boolenas
/********************************************************************/
void DFA_Generator::string_Check()
{
  return;
}

int DFA_Generator::column_Finder(char input)
{
  int counter =0;
  for(int i =0; i < alphabet.size(); i++)
    {
      if(input == alphabet[i])
	return counter;
      else
	counter ++;
    }
  return counter;
}

