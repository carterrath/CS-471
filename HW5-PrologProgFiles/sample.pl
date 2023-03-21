
parent(pam, bob).
parent(X,Y) :- offspring(Y,X).

offspring(bob,pam).

