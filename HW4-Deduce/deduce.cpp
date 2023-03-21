#include<iostream>
#include<fstream>
#include<string>
using namespace std;

//  FALL22 Yoshii - HW4 EC for Inferences
//   Given two facts and one implies rule
//   see what you can deduce.
//   Each fact has a true or false value
//   The condition part of the implication rule
//   may use AND or OR.
// Look for ** to complete.
-----------------------------------------
// YOUR NAME: Carter Rath
// Tested on Empress using g++
//----------------------------------------

// Each fact is a word e.g. RAINING
// Each fact is followed by either true or false
string facts[2][2];

// a rule
struct rule
{
  string p1; // a condition
  string op; // op is AND or OR
  string p2; // the second condition
  string concl; // the conclusion
};


// for the current KB
rule myrule; // the rule  
int num;     // number of conditions in the rule

// ========= Functions follow ==============


// check to see if a condition is notted
bool isnotted(string s)
{ 
  if (s[0] == '~') return true; else return false;
}

// read in the contents of a kb file
// and display them
void readin()
{ string kb;
  cout << "Enter the KB name: ";
  cin >> kb;
  ifstream fin (kb.c_str(), ios::in);

  fin >> num;  // how many facts or conditions

  //** for each fact
    // ** read the fact word
    // ** read true or false
 
  // ** display the facts

  // ** read the rule condition(s) 
  // ** read the operator
  // ** read the implies symbol 
  // ** read the conclusion
  // ** display them

}// end of reading the kb   

// deduce based on one condition
string deduceOne()
{
  // ** check the notted condition vs. false fact
  // ** check the unnotted condition vs. true fact
  // ** check the conclusion vs. false fact 
  else
    return "nothing";
}

// deduce based on two conditions
// Think: when is a condition true?
 string deduceTwo()
 { 
   // ** check to see if the first condition is true
   // ** check to see if the second condition is true
   // ** check the operator to decide if the conclusion is true
   else return "error";
 }

// =============== THE MAIN =================

 int main()
 {
   cout << "Reading the KB..." << endl;
   readin();
   cout << "DEDUCED:" << endl;
   if (num == 1) cout << deduceOne() << endl;
   else cout << deduceTwo() << endl;
 }
