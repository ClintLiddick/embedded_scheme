(import
 ;; bitwise operations
 (srfi 33))

(define square
  (lambda (sq)
    (arithmetic-shift 1 (- sq 1))))

