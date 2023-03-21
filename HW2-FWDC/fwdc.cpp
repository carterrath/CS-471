#include<string>
#include<vector>
#include<iostream>
#include<stdlib.h>  /* to use exit */
using namespace std;

// FALL22
// Update this file for HW2 FWDC (Yoshii)
// Read the main() first and write down all the functions it calls!
// Then, look for *** using control-S and add code.
// ** always marks where you need to change!
//--------------------------------------------------
// YOUR NAME: Carter Rath
// Tested on Empress using g++
//--------------------------------------------------

// State description class.
// Could have used struct.
// Items here is a string of L or R for FWDC
//    e.g. RRRR for the initial state
class state{
  public:
    string items;  // made up of L and R going from RRRR to LLLL
    string camefrom; // the parent on the solution path
    int g;   // cost so far
    int h;   // estimated cost to the goal
    int f;   // g+h
};

// Major data structures:
vector<state> frontier;  // Frontier nodes - will pick one of these to expand
vector<state> beenThere; // already expanded nodes

// ========== Utility Functions ===================

// utility to add x to the beenthere
void addtoBeenThere(state x){  
  beenThere.push_back(x);                     
}

// utility to add x to the frontier
void addtoFrontier(state x){  
  frontier.push_back(x); 
}

// to remove state x from the frontier when it has been expanded
void removefromFrontier(state x){
  vector<state> newfrontier;
  for (int k = 0; k < frontier.size(); k++){    // loop through frontier vector
    if (frontier[k].items != x.items){          // if items of k state is not equal to x state items
      newfrontier.push_back(frontier[k]);       // add state to new frontier vector
    }
  }
  frontier = newfrontier;                       // over write the current frontier vector with the new frontier vector
}

// Check to see if next items is already in beenThere and return true or false
bool inBeenThere(state next) {
    for (int k = 0; k < beenThere.size(); k++){ // loop through beenThere vector
        if (beenThere[k].items == next.items){  // if items of k state is the same as the next state
            return true;                        // return true, already been at this state
        }
    }
    return false;                               // loop is done, state was not found in beenThere, return false
}

// check to see if next items is a safe state and return true or false
bool isUnSafe(state next){
  if (next.items == "LRRR"){                    // duck is alone with corn and wolf is alone with duck
    return true;                                // return true, unsafe!
    }
  else if (next.items == "LLRR"){               // duck is alone with corn
    return true;                                // return true, unsafe!
    }
  else if (next.items == "LRRL"){               // wolf is alone with duck
    return true;                                // return true, unsafe!
    }
  else if (next.items == "RLLR"){               // wolf is alone with duck
    return true;                                // return true, unsafe!
    }
  else if(next.items == "RRLL"){                // duck is alone with corn
    return true;                                // return true, unsafe!
    }
  else{
    return false;                               // return false, safe!
    }
   
}

//============= At the Very End ====================

// Trace and display the solution path from goal to initial.
// Note that camefrom of each state should be used. (called from generate)
void tracePath(state goal)
{
  // *** add code here to display the path from goal to initial
  // using cameFrom's  -- recursion is useful to not to depend on a particular order of state in Been There!
  if(goal.items == "RRRR"){                     // base case, initial state has been reached
    return;                                     // return to exit recursions
  }
  else{                                         // initial state not reached, continue tracing
    state parent;                               // to store parent state
    cout << "came from" << endl;
    cout << goal.camefrom << endl;              // goal state's parent
    for(int i = 0; i < beenThere.size(); i++){  // loop through beenThere vector
      if(goal.camefrom == beenThere[i].items){  // if the goal state's parent is equal to the items of i state
        parent = beenThere[i];                  // the parent of goal has been found in beenThere, store in parent variable
      }
    }
    tracePath(parent);                          // recursive call on the parent
  }
}// end of tracePath

//======= For Generating a new state to add to Frontier  =============

// Check to see if next's items is already in frontier and return true or false.
//   If it is already in frontier,
//   and if the next's f is better,
//   update the frontier node to next.  (called from generate)
bool inFrontier(state next){
  // **** add code here, possibly updating
  // the same frontier node with next if f is better.
  // Please cout a message in that case.
  // Return true or false.
    for (int k = 0; k < frontier.size(); k++){  // loop through frontier vector
        if (frontier[k].items == next.items){   // if items of k state is equal to items of next state
            if(frontier[k].f > next.f){         // if f of the k state is greater than the f of next state
                removefromFrontier(frontier[k]);// remove k state from frontier 
                addtoFrontier(next);            // add next state to frontier because it has a smaller f
                return true;                    // return true because next state was found in frontier vector
            }
            else{                               // f is not better
                cout << "Already in the Frontier" << endl;
                cout << "f not better" << endl;
                return true;                    // return true because next state was found in frontier vector
            }
        }
    }
    return false;                               // loop is over, so next state was not found in the frontier vector. Return false!
}// end of inFrontier


// Try to add next to frontier but stop if LLLL (called from generateAll)
void generate(state next)
{
  cout << "Trying to add: " << next.items;

  if (next.items  == "LLLL")                    // the goal is reached
    { cout << "\n>>Reached: " << next.items << endl;
      tracePath(next);                          // display the solution path
      exit(0); }                                // done

  // *** if been there before, do not add to frontier.
  // You may write a utility function check been-there and call it
  else if (inBeenThere(next) == true){          // check if next state is in beenThere vector
    cout << " been there already" << endl;
  }
  // *** if unsafe, do not add to frontier.
  // You may write a function to check unsafe and call it
  else if (isUnSafe(next) == true){             // check if next state is an unsafe state
    cout << " unsafe!" << endl;
  }
  else {                                        // it is safe and not in beenThere
    cout << " safe!" << endl;
    // else compute h and then f for next
    int h = 0;                                  // start point for h; g is already set
    // ** update h and then f
    for (int i = 1; i < next.items.size(); i++){// loop through next state's items string starting at wolf
      if(next.items[i] == 'R'){                 // if item is on right side of river
        h++;                                    // increment h
      }
    }
    next.h = h;                                 // set calculated h equal to next state's h
    next.f = next.g + next.h;                   // calculate f by adding g + h = total path from initial state to goal state
    if (!inFrontier(next)){                     // check if next state is already in frontier
      cout << "Not in Frontier yet" << endl;
      addtoFrontier(next);                      // add next to Frontier
    }
  }
}// end of generate

// Generate all new states from current (called from main)
void generateAll(state current){
  state next;                                    // a generated one

  // each next will be modified from current for ease
  current.g = current.g + 1;                     // to update g to be used for next
  current.camefrom = current.items;              // storing the parent so that we can produce the solution path

  // check all possibilities as follows..

  // move F alone to L
  next = current;                                // starting point of next is current
  if (current.items[0] == 'R'){ 
    next.items[0]='L'; 
    generate(next);
  }

  next = current;                                // starting point of next is current
  // move F alone to R
  if (current.items[0] == 'L'){ 
    next.items[0]='R'; 
    generate(next);
  }

  next = current;                                 // starting point of next
  // move FW to L
  if (current.items[0] == 'R' && current.items[1] == 'R'){ 
    next.items[0]='L'; 
    next.items[1] = 'L'; 
    generate(next);
  }

  next = current;                                 // starting point of next
  // move FW to R
  if (current.items[0] == 'L' && current.items[1] == 'L'){ 
    next.items[0]='R'; 
    next.items[1] = 'R'; 
    generate(next);
  }

  next = current;                                 // starting point of next
  // move FD to L
  if (current.items[0] == 'R' && current.items[2] == 'R'){ 
    next.items[0]='L'; 
    next.items[2] = 'L'; 
    generate(next);
  }

  next = current;                                 // starting point of next
  // move FD to R
  if (current.items[0] == 'L' && current.items[2] == 'L'){ 
    next.items[0]='R'; 
    next.items[2] = 'R'; 
    generate(next);
  }

  next = current;                                 // starting point of next
  // move FC to L
  if (current.items[0] == 'R' && current.items[3] == 'R'){ 
    next.items[0]='L'; 
    next.items[3] = 'L'; 
    generate(next);
  }

  next = current;                                 // starting point of next
  // move FC to R
  if (current.items[0] == 'L' && current.items[3] == 'L'){ 
    next.items[0]='R'; 
    next.items[3] = 'R'; 
    generate(next);
  }

}// end of generateAll


// Find the best f state out of the frontier and return it (called from main)
state bestofFrontier(){
    state best;                                // state variable to store best state of frontier
    for(int k = 0; k < frontier.size(); k++){     // loop through frontier vector
        if(k == 0){                               
            best = frontier[0];                   // set first state in frontier as best, may be temporary
        }
        else{
            if(best.f > frontier[k].f){           // if f of k state is smaller than f of best
                best = frontier[k];               // set k state as best
            }
        }
    }
    return best;                                  // return best state of frontier, meaning it has the smallest f
}//end of bestofFrontier

// Display the states in the frontier  (called from main)
void displayFrontier(){
  for (int k = 0; k < frontier.size(); k++){ 
    cout << frontier[k].items << " ";
    cout << "g = " <<frontier[k].g << " ";
    cout << "h = " <<frontier[k].h << " ";
    cout << "f = " <<frontier[k].f << endl;
  }
}// end of displayFrontier

//================= Main ===========================

int main(){

  state  current = {"RRRR","", 0, 3, 3};           // initial
  addtoFrontier(current);

  char ans;
  while ( ans != 'n'){
      removefromFrontier(current);
      addtoBeenThere(current);

      cout << ">>>Expand:" << current.items << endl;
      generateAll(current);                        // new states are added to frontier

      cout << "Frontier is:" << endl;
      displayFrontier();
      
      current = bestofFrontier();                  // pick the best state out of frontier
      cout << "Best is: " << current.items << endl;
      cin >> ans;

    }// end while
}//end of main
