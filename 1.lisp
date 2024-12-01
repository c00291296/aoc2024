(defun solve1 (l1 l2)
  (reduce #'+
	  (mapcar #'abs
		  (mapcar #'- 
			  (sort l1 #'<)
			  (sort l2 #'<)))))

(defun solve2 (l1 l2)
  (reduce #'+
	  (mapcar (lambda (a)
		    (* a (count a l2)))
		  l1)))
;assume instead of 2 columns we have 1 big list
(defun split (l result)
  (if l
    (split (cdr l) (cons (cons (car l) (cdr result))
			 (car result)))
    result))
;just copy and paste the input file inside '(FILE), split it and feed
;the lists into the solution.
