;; Yoshii F22 - Eliza Example -- call (main) to start 
;; Eliza is a fake psycho therapist.
;; Look for ** to complete
;; ===================================================


(setf (get 'mary 'age) 40)
(setf (get 'mary 'MS)  'married)
(setf (get 'mary 'kids) 3)
;; ** add 1 more patient here
(setf (get 'corey 'age) 21)
(setf (get 'corey 'MS) 'single)
(setf (get 'corey 'kids) 5)
(defun main ()
  (prog  (L1 client ans count L2)

   (princ "Hi. My name is eliza. What is yours? ")
   (setq client (read))

   (princ "Looking at my records you are ")
   ;; new client?
   (cond ((null (get client 'age))
                (princ  " new. ") (go L))
   )
   (princ (get client 'age)) (princ " and ")
   (princ (get client 'MS))
   (terpri)
   (princ "And you have ")
   (princ (get client 'kids))(princ " children.")
   (terpri)

L
    (princ "So tell me what is bothering you today: ")
    (princ '(enclose your answer in parentheses))
    (terpri)
    (setq count 0) 
   
L1  (setq ans (read))
    (setq count (+ count 1))
    (if (eq count 10) (go L2)) ;; to end
    
    (princ (response-to ans))
    (terpri)
    (go L1)

L2 (princ '(Oops our time is up. See you next week    ))
 )
)           


;; key words we look for
(setq key-words '(sad mad depressed angry tired))

;; produce a response for the answer a
;; Checks these in order:
;; keywords found
;; have been found
;; I am found
;; why found
;; what found
;; how found
;; because found
;; and the conditions you add..
(defun response-to (a)
  (cond 
    ((intersection a key-words) 
        (append '(Why are you) (switchthem (member (car (intersection a key-words)) a))))
    ((member 'been (member 'have a))
        (append '(How long have you) (switchthem (member 'been a))))
    ((member 'am (member 'I a))
          (subst 'are 'am (subst 'You 'I (subst 'me 'you a))))
    ( (member 'why a) '(why do you think?))
    ( (member 'what a) '(that is a difficult question)) 
    ( (member 'how a) '(how? Hmm))
    ( (eq (car a) 'because) '(I see. Interesting.)) 
 ;; ** add another condition here that is not covered by the above 
    ( (member 'where a) '(anywhere you want))
    ( (member 'who a) '(whoever you think))
    ( (member 'you (member 'are a))
        (subst 'am 'are (subst 'I 'you a)))  
   (T '(Tell me more about it))
   )
)


;; switch YOU and I pronouns in the response given the answer a
(defun switchthem (a)
(cond ((member 'your a) ( subst 'my 'your a))
      ((member 'my a) (subst 'your 'my a))
      ((member 'myself a) (subst 'yourself 'myself a))
      (t a))) 
