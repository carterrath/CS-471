;; F22 Yoshii - recursion example in Lisp
;; Try (interleave '(a b c) '(x y z))

;; interleaves two lists x and y
(defun interleave (x y)
  (cond ((and (null x)(null y)) nil)
        (t (cons (car x) (cons (car y) (interleave (cdr x) (cdr y)))))))


