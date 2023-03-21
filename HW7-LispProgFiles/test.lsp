;; CS471 Yoshii - for learning various features

(setf (get 'spot 'age) 7)
(setf (get 'spot 'color) 'tan)


(defun func1 (L)
  (cond ((null L) L)
        (T   (print (car L))     (func1 (cdr L)))))

(defun abc (L)
  (cond ((null L)  0  )
        ((atom L)  1    )
        (T  (print "hi")(+ 1 (abc (cdr L))) )
  )
)  

(defun main ()
 (prog (x l l2 y)
  l (print "enter anything")
    (setq x (read))
    (print (car x))
    (if (equal (car x) 'bye) (go l2))
    (go l)
 l2
 )
)
