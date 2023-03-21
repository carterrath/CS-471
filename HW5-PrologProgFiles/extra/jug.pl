
% Yoshii - Water Jug Program in Prolog

% Member function definition as two rules.
membr(X,[X|L]).
membr(X,[Z|L]) :- membr(X,L).

% Top level goal is path.
% path(initial state, goal state, list to accumulate the path).
% e.g. Invoke it by saying path(state(0,0), state(_,2), [state(0,0)]).

% ------------------------------------

% When we have reached the goal state, display the Path
path(Goal,Goal,Path) :- write(Path), nl.

% To find a path from State to Goal accumulating the visited states in Sofar,
%    move from State to Next and
%    if Next has not been visited, 
%    find a path from Next to Goal. (note: Next is added to SoFar
%       but in front of Sofar.)
path(State,Goal,Sofar) :-
   move(State,Next),
   \+ membr(Next,Sofar),
   path(Next,Goal,[Next|Sofar]).

% Notice that each state is in the following format: state(X,Y)
% where X is the gallons in the smaller jug and Y is the gallons in
% the larget jug.  Initial state is thus state(0,0) and the goal 
% state is state(_, 2) meaning we do not care about X.

% ------------------------------------------------------

% Here are the move rules.  
% move(current state, next state).
% Note that X is for the 3 gallon jug. Y is for the 4 gallon jug.

% rule 1: Dump the 4 gallon jug
move(state(X,Y),state(X,0)).

% rule 2: Dump the 3 gallon jug
move(state(X,Y),state(0,Y)).

% rule 3: Fill the 3 gallon jug  
move(state(X,Y),state(3,Y)).

% rule 4: Fill the 4 gallon jug
move(state(X,Y),state(X,4)).

% rule 5: If 4 gallon jug is not full, and 3 gallon jug has
%    enough water to fill the 4 gallon jug, do so
move(state(X,Y),state(X1,4)) :-
   A is 4-Y, A > 0, X1 is X-A, X1 >= 0.

% rule 6: Pour all water in the 3 gallon jug into 4 gallon jug
%         if doing so will not overflow the 4 gallon jug
move(state(X,Y),state(0,Y1)) :-
   Y1 is Y+X, Y1 =< 4.

% rule 7: If 3 gallon jug is not full, and 4 gallon jug has
%   enough water to fill the 3 gallon jug, do so
move(state(X,Y),state(3,Y1)) :-
   A is 3-X, A >0, Y1 is Y-A,Y1 >= 0.

% rule 8: Pour all water in the 4 gallon jug into 3 gallon jug
%         if doing so will not overflow the 3 gallon jug 
move(state(X,Y),state(X1,0)) :-
   X1 is X+Y, X1 =< 3.






