% Yoshii - Missionary and Cannibals example in Prolog

membr(X,[X|L]).
membr(X,[Z|L]) :- membr(X,L).

% The top level goal is path.
% path(initial state, goal state, list to accumulate the path). 
% Note that intially, you have 3 and 3 on the left side. You want 3 and 3 on the right side at the end.  See what a state looks like in the rules. 

% ----------------------------------

% When we have reached the goal, display the path.
path(Goal,Goal,Path) :- write(Path).

% It starts here.
% Move to the Next stete.
% If Next has not been visited yet and Next is not bad,
% add Next to the Path.
path(State,Goal,Sofar) :-
   move(State,Next),
   \+ membr(Next,Sofar),
   \+ bad(Next),
    write([Next|Sofar]),
   path(Next,Goal,[Next|Sofar]).

% Note that a state is in the following format: state(Lm, Lc, Rm, Rc, B)
% where Lm is the number of missionaries on the left, Lc is the number of
%    canibals on the left, Rm is the number of missionaies on the right, and
%    Rc is the number of canibals on the right. B is where the boat is 
%    i.e. l or r   
% Thus the initial state is state(3,3,0,0,l) and the goal is state(0,0,3,3,r).
%---------------------------------------------
% Move rules follow:

%
move(state(Lm,Lc,Rm,Rc,l),state(Lma,Lc,Rma,Rc,r)) :-
   member(X,[1,2]), Lma is Lm-X, Lma >= 0, Rma is Rm + X.

%
move(state(Lm,Lc,Rm,Rc,r),state(Lma,Lc,Rma,Rc,l)) :-
   member(X,[1,2]), Rma is Rm-X, Rma >= 0, Lma is Lm + X.

%
move(state(Lm,Lc,Rm,Rc,l),state(Lm,Lca,Rm,Rca,r)) :-
   member(X,[1,2]), Lca is Lc-X, Lca >= 0, Rca is Rc + X.

%
move(state(Lm,Lc,Rm,Rc,r),state(Lm,Lca,Rm,Rca,l)) :-
   member(X,[1,2]), Rca is Rc-X, Rca >= 0, Lca is Lc + X.

%
move(state(Lm,Lc,Rm,Rc,l),state(Lma,Lca,Rma,Rca,r)) :-
   Lc > 0, Lm > 0, Lca is Lc-1, Lma is Lm-1, Rca is Rc + 1, Rma is Rm + 1.

%
move(state(Lm,Lc,Rm,Rc,r),state(Lma,Lca,Rma,Rca,l)) :-
   Rc > 0, Rm > 0, Rca is Rc-1, Rma is Rm-1, Lca is Lc + 1, Lma is Lm + 1.

% Bad if the number of cannibals > missionaries on one side
bad(state(Lm,Lc,Rm,Rc,_)) :- Lc > Lm, Lm > 0.
bad(state(Lm,Lc,Rm,Rc,_)) :- Rc > Rm, Rm > 0.

