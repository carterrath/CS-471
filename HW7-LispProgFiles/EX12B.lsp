;;Name: Carter Rath
;;WEEK 12B IN CLASS EX 12B - LISP PROGRAM
;;In a file, use setfs to set the property list of Spot
;;Write a function main with PROG to ask the user for a property name and display the get value for it. Loop until the user enters done as a property name
(setf (get 'Spot 'species) 'dog)
(setf (get 'Spot 'age) 7)
(setf (get 'Spot 'color) 'tan)
(setf (get 'Spot 'sex) 'male)

(defun main()
  (prog (property) ;;local variable property
	(setq x 1)
	loop(princ "Enter a property name for Spot or done to quit ")
	    (setq property (read))
	    (cond
	        ((equal property 'done) (setq x 0) (princ "Goodbye"))
		((null (get 'Spot property)) (princ "property not found"))
		(t (princ (get 'Spot property)))) (terpri)
	        (if(equal x 1) (go loop))))

	
