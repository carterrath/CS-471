//  Yoshii FALL22 - HW3EC: Binary MiniMAX tree
// Change this to make it tri-nary
// I tried to mark all binary parts with **
//-------------------------------------------
// YOUR NAME: **
// Tested on Empress using g++
//-------------------------------------------

#include "mmtree.h"

mmtree::mmtree()
{  count = 0; lastinternal = 0; maxlevel = 0;  // data members
}

mmtree::~mmtree() 
{ // nothing to do 
}

// displays the path of operators down to slot i leaf
void mmtree::displaypath(int i)
{
 do 
    {
      cout << Q[i].op << "<-";
      if (!even(i)) i = (i-1)/2; else i = (i-2)/2;  // **
    }
  while (i >= 0);
}

// assign utility values to the terminal nodes
// at the max level ; starting at slot i of Q
void mmtree::getUtilityValues(int i)
{
  int leaves = pow(2, maxlevel);  // the number of leaves at maxlevel **
  cout << "There are " << leaves << " leaves.. " << endl;
  
  // Normally the values are determined by
  // examining the states' features but here
  // we will let the user enter the values. 

  cout << "Please enter the value of each leaf (left to right)." << endl;

  int v;  // node value
  
  for (int k = 1; k <= leaves; k++) // for each leaf
    { // first store the operation name **
      if (!even(i)) Q[i].op = "L"; else Q[i].op = "R";
      displaypath(i);
      // then store the value
      cout << "value: "; cin >> v; 
      Q[i].value = v;      
      // level number is stored
      Q[i].level = maxlevel;
      i++; // next slot
    }
  count = i--;   // count slots have been used
}

// this function builds a game tree to the
//  maxlevel (0...maxlevel)
void mmtree::build(int ml)
{
  maxlevel = ml;  // set the data member maxlevel

  int i = 0;  // current index into array Q
  int l = 0;  // current tree level

  // First the internal structure is built

  while (l < maxlevel)  // one level at a time
    {
      // binary tree has 2^l nodes at level l **
      for (int k = 1; k <= pow(2,l); k++) // for the current level nodes
	{ // Q index tells us if L or R child **
	  if (!even(i)) 
            Q[i].op = "L"; else Q[i].op = "R"; // op is stored **
	  Q[i].value = 0;  // no value yet
	  Q[i].level = l;  // tree level is stored
          i++; // next slot in Q
	}
      l++;  // next level
    }

  // Now assign the node values to leaves

  lastinternal  = i-1;  // the last internal node is at Q's i-1 so the next leaf goes to slot i 

  // get values for the leaf nodes
  getUtilityValues(i);
}


// ----- for doing MinMax --------------------------

// this function does the minMAX value computation
// recursively bottom up
int mmtree::minMaxDFS(int x)
{ int v1, v2;

  if (x > lastinternal) return (Q[x].value);  // reached leaf
  // otherwise recursively go to the children **
  v1 = minMaxDFS(2*x+1);  // left child **
  v2 = minMaxDFS(2*x+2);  // right child **
  // now for the parent..
  if (evenLevel(x)) // MAX level
      Q[x].value = maxof(v1,v2); **
  else // MIN level
      Q[x].value = minof(v1,v2); **
  return Q[x].value;

}  

// --------------- utility functions ----------------

// to determine MIN or MAX level (MIN is odd)
bool mmtree::evenLevel(int x)
{
  if ((Q[x].level % 2) == 0) return true; else return false;
}

// ** the following work for binary trees

int mmtree::maxof(int a, int b)
{  if (a > b) return a; else return b; }

int mmtree::minof(int a, int b)
{  if (a > b) return b; else return a; }

// ** To determine which branch
bool mmtree::even(int x)
{
  if (x%2 == 0) return true; else return false; // ** left or right
}


// ---  to display the tree ------------------

// to display blanks 10-level times
void mmtree::blanks(int level)
{ for (int i = 1; i <= 10-level; i++) cout << " "; }

// to display the game tree
void mmtree::displayAll()
{ 
  cout << "MAX:";
  blanks(0); cout << Q[0].value << endl;
  // the root

  int i = 1; // slot in Q 
  for (int d =1 ; d <= Q[count-1].level; d++)
    {   // current level is d  
      int num = 1; // number of nodes per level
      int starti = i; // start i for the level
      cout << "    ";
      blanks(d);
      while (num <= pow(2,d)) //**
	{
	  cout << Q[i].op ;
 	  i++; num++;
	}  
      cout << endl;
      num = 1; i = starti; 
      if (even(d)) cout << "MAX:"; else cout << "MIN:"; 
      blanks(d);
      while (num <= pow(2,d)) //**
	{
	  cout << Q[i].value;
	  num++; i++;
	}
      cout << endl;  
    } 
} 

