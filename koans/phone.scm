(define clean-list
  (lambda (s)
    (cond
     ((null? s) '())
     ((char-numeric? (car s)) (cons (car s) (clean-list (cdr s))))
     (else (clean-list (cdr s))))))

(define cleanup
  (lambda (s)
    (list->string (clean-list (string->list s)))))

(display (cleanup "12345"))
(newline)
(display (cleanup "1 2-345"))
(newline)
