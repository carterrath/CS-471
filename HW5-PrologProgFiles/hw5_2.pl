% the top level goal is find
find(Who) :- wings(Who), write('The answer is: '), write(Who).

wings(X) :- fly(X).

eagle(bill).

airplane(dc10).


fly(mary).
fly(X) :- airplane(X).
fly(Y) :- bird(Y).

bird(Z) :- eagle(Z).
