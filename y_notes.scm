(define lendef
  (lambda (li)
    (cond
     ((null? li) 0)
     (else (+ 1 (lendef (cdr li)))))))

(define bottom
  (lambda (x) (bottom x)))

((lambda (li)
   (cond
    ((null? li) 0)
    (else
     (+ 1
        ((lambda (li)
           (cond
            ((null? li) 0)
            (else
             (+ 1
                ((lambda (li)
                   (cond
                    ((null? li) 0)
                    (else
                     (+ 1
                        (bottom li)))))
                 (cdr li))))))
         (cdr li))))))
 '(1 2))


;; Cleanup
(((lambda (lenf)
    (lambda (li)
      (cond
       ((null? li) 0)
       (else (+ 1 (lenf (cdr li)))))))
  ((lambda (lenf)
     (lambda (li)
       (cond
        ((null? li) 0)
        (else (+ 1 (lenf (cdr li)))))))
  bottom))
 '(1 2))

;; Factor make-lenf and apply manually
(((lambda (mk-lenf)
    (mk-lenf
     (mk-lenf
      (mk-lenf bottom))))
 (lambda (lenf)
   (lambda (li)
     (cond
      ((null? li) 0)
      (else
       (+ 1
          (lenf (cdr li))))))))
 '(1 2))

;; Let function use mk-lenf
(((lambda (mk-lenf)
    (mk-lenf mk-lenf))
  (lambda (mk-lenf)
    (lambda (li)
      (cond
       ((null? li) 0)
       (else
        (+ 1
           ((mk-lenf bottom)
            (cdr li))))))))
 '(1))

;; Use "recursively" and we have solution
(((lambda (mk-lenf)
    (mk-lenf mk-lenf))
  (lambda (mk-lenf)
    (lambda (li)
      (cond
       ((null? li) 0)
       (else
        (+ 1
           ((mk-lenf mk-lenf)
            (cdr li))))))))
 '(1 2 3 4))

;; Can we factor "length" function out? Remove need to create length func?
(((lambda (mk-lenf)
    (mk-lenf mk-lenf))
  (lambda (mk-lenf)
    (lambda (li)
      (cond
       ((null? li) 0)
       (else
        (+ 1
           ((lambda (x)
              ((mk-lenf mk-lenf) x))
            (cdr li))))))))
 '(1 2 3 4))

;; Use mk-lenf and pass in recursive lenf
(((lambda (mk-lenf)
    (mk-lenf mk-lenf))
  (lambda (mk-lenf)
    ((lambda (lenf)
       (lambda (li)
         (cond
          ((null? li) 0)
          (else
           (+ 1 (lenf (cdr li)))))))
     (lambda (x)
       ((mk-lenf mk-lenf) x)))))
 '(1 2 3 4))

;; Extract length function from out of between the helpers
(((lambda (lenf-applyer)
    ((lambda (mk-lenf)
       (mk-lenf mk-lenf))
     (lambda (mk-lenf)
       (lenf-applyer
        (lambda (li)
          ((mk-lenf mk-lenf) li))))))
  (lambda (lenf)
    (lambda (li)
      (cond
       ((null? li) 0)
       (else (add1 (lenf (cdr li))))))))
 '(1 2 3 4))

;; Does this pattern have a name?
(define Y
  (lambda (lf)
    ((lambda (f) (f f))
     (lambda (f)
       (lf (lambda (x)
             ((f f) x)))))))

;; Nice
((Y
  (lambda (lenf)
    (lambda (li)
      (cond
       ((null? li) 0)
       (else (+ 1 (lenf (cdr li))))))))
 '(1 2 3 4))


(define length-y
  (Y
   (lambda (lenf)
     (lambda (li)
       (cond
        ((null? li) 0)
        (else (+ 1 (lenf (cdr li)))))))))

(length-y '(1 2 3 4 5))
