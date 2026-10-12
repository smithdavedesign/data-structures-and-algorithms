#ifndef DFA_GENERATOR_H
#define DFA_GENERATOR_H
#include<iostream>
#include<vector>
using namespace std;

class DFA_Generator
{
 public:
  DFA_Generator();
  ~DFA_Generator();

  //helperfunctions
  int user_Choice(int);
  void user_Choice_Set();
  void DFA_Function_Caller();
  // void string_check(const int dfa_table[][]);
  
  
 private:
  int column_Finder(char input);
  void begin_Substring(string);
  void end_Substring(string);
  void contains_Substring_Least_Most_Exactly_K(string, bool, bool, bool, int);
  void contains_Substring_Odd_Even(string, bool);
  void string_Check();
  void set_Alphabet(int);
 
  string combine_string;
  string begin_sub;
  string end_sub;
  string contain_sub;
  string begin_sub_odd_or_even;
  bool contains_sub_least_most_exactly;
  bool end_substring;
  bool begin_substring;
  bool contain_even_odd;
  bool odd;
  bool most;
  bool least;
  bool exact;

  bool beg_accept;
  bool end_accept;
  bool even_accept;
  bool contain_accept;

  bool combine;
  bool combine_result;
  int k;
  int first;
  int seccond;
  
  vector <char> alphabet;
  vector <int> accepting_states;
  int alphabet_map[];
};
#endif
