(define not-one?
  (lambda (c)
    (and
     (char? c)
     (not (eq? #\1 c)))))

(define valid-digit?
  (lambda (d)
    (and
     (not-one? d)
     (char-numeric? d))))

(define base-case?
  (lambda (s cleaned)
    (or
     (null? s)
     (= 10 (length cleaned)))))

(define clean-list-do
  (lambda (s cleaned)
    (cond
     ((base-case? s cleaned) (reverse cleaned))
     ((valid-digit? (car s))
      (clean-list-do
       (cdr s) (cons (car s) cleaned)))
     (else (clean-list-do (cdr s) cleaned)))))

(define clean-list
  (lambda (s)
    (clean-list-do s '())))

(define cleanup-phone
  (lambda (s)
    (list->string (clean-list (string->list s)))))

;; (display (cleanup "12345"))
;; (newline)
;; (display (cleanup "1 2-345"))
;; (newline)
