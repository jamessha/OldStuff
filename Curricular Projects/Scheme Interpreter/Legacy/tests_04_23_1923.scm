;;; Test Cases for the Scheme Project 

;; To run all tests:
;;     python3 scheme_test.py tests.scm
;;


;; The following should work for the initial files.

3
; expect 3

-123
; expect -123

1.25
; expect 1.25

#t
; expect #t

#f
; expect #f

)
; expect Error

;; In the following sections, you should provide test cases, so that by 
;; running 
;;     python3 scheme_test.py tests.scm
;; you can test the portions of the project you've completed.  In fact, 
;; you might consider writing these tests BEFORE tackling the associated
;; problem!

; Problem 1  (the reader)
;   Initially, the project skeleton simply reads and prints the expressions
;   entered.  Later on, it starts evaluating them.  You may therefore need
;   to modify the tests you initially provide for this section when you get
;   to later sections.  For example, initially, entering the symbol x will
;   simply cause the evaluator to print "x" rather than attempting to evaluate
;   it (and getting an error).  Therefore, you may later have to modify
;   x to (e.g.) 'x

; YOUR TEST CASES HERE


; Problem A2 and B2 (symbol evaluation and simple defines)

+
; expect <primitive procedure..at somewhere>

(define x 3)
x
; expect 3


; Problem 3 (primitive function calls)

(+ 1 2)
; expect 3

(- 3 9)
; expect -6

(boolean? 4)
; expect #f

(boolean? #t)
; expect #t


; Problem A4, B4, A5, B5, and 6 (calls on user-defined functions)

(define square (lambda (x) (* x x)))
(square 2)
; expect 4

(define square2 (lambda (x) (* x x) (- x x)))
(square2 2)
; expect 0

(define multi (lambda (x y) (* x y)))
(multi 3 4)
; expect 12

(define x 6)
(define (setter) (define x 2))
x
; expect 6


; Problem 7 (set!)

(set! x 9)
x
; expect 9

(define x 7)
(define setter (lambda () (set! x 2)))
(setter)
x
; expect 2

; Problem A8 (if, and)

(and (< 2 3) (< 2 3))
; expect #t

(and (< 2 3) (> 2 3))
; expect #f

(and (< 2 3) (< 2 3) (> 2 3))
; expect #f

(and (< 2 3) (< 2 3) (< 2 3))
; expect #t

(and 2 3)
; expect 3

(and (< 2 3) 3)
; expect 3

(and (> 2 3) 3)
; expect #f

; Problem B8 (cond, or)

(or 2 3)
; expect 2

(or (> 2 3) (< 2 3))
; expect #t

(cond ((> 2 3) 5) (else 6))
; expect 6

(cond ((and 1 2 3) => square) (else #f))
; expect 9


; Problem 9 (let)

(define x 3)
(define y 10)
(let ((x y) (y (+ x 5))) (set! x (+ x 1)) (list x y))
; expect (11 8)

(list x y)
; expect (3 10)

; Extra Credit 1 (let*)

(let* ((x y) (y (+ x 5)))
	(set! x (+ x 1))
	(list x y))
; expect (11 15)

; Extra Credit 2 (case)

(case (* 2 3)
	((2 3 5 7) 'prime)
	((1 4 6 8 9) 'composite)
	)
; expect composite

(case (car '(c d)) 
	((a e i o u) 'vowel) 
	((w y) 'semivowel) (else 'consonant)
	)
; expect consonant

(case (car '(+ * /)) 
	((+ add) (+ x y)) 
	((* mult) (* x y)) 
	((/ div) (/ x y))
	)
; expect 13

; Problem A10

;; The subsequence of list S for which F outputs a true value (i.e., one
;; other than #f), computed destructively
(define (filter! f s)
	(define (filter1 f s l)
		(cond ((null? (cdr s)) (cond ((null? l) l) 
					((f (car l)) l)
					(else (cdr l))
					)
				)
			((not (f (cadr s))) (set-cdr! s (cddr s)) (filter1 f s l))
			(else (filter1 f (cdr s) l))
			)
		)
	(filter1 f s s)
	)
(define (big x) (> x 5))
(define ints (list 1 10 3 8 4 7))
(define ints1 (cdr ints))
(define filtered-ints (filter! big ints))
filtered-ints
; expect (10 8 7)

(eq? filtered-ints ints1)
; expect #t

; Problem B10

;; Reverse list L destructively, creating no new pairs.  May modify the 
;; cdrs of the items in list L.

;Non-Destructive Method 
;(define (reverse! L)
    ;(cond ( (null? L) ())
        ;(else (append (reverse! (cdr L)) (list (car L))))
    ;)    
;)

(define (reverse! L)
    (define (reverse2 item L)
        (set-cdr! L (cdr(butlast L)))
        (cond ((= (length L) 1) (append (list item) L))
            (else (append (list item) (reverse2 (last L) L)))
        )
    )
    (cond ((null? L) ())
        (else (reverse2 (last L) L))  
    )
)
(define L (list 1 2 3 4))
(define LR (reverse! L))
LR
; expect (4 3 2 1)

(eq? L (list-tail LR 3))
; expect #t


; Problem A11.

;; The number of ways to change TOTAL with DENOMS
;; At most MAX-COINS total coins can be used.
(define (count-change total denoms max-coins)
	(cond ((= total 0) 1)
		((= max-coins 0) 0)
		((null? denoms) 0)
		((>= total (car denoms)) (+ (count-change total (cdr denoms) max-coins) (count-change (- total (car denoms)) denoms (- max-coins 1))))
		(else (count-change total (cdr denoms) max-coins))
		)
) 
(define us-coins '(50 25 10 5 1))
(count-change 20 us-coins 18)
; expect 8


; Problem B11

;; The number of ways to partition TOTAL, where 
;; each partition must be at most MAX-VALUE
(define (count-partitions total max-value)
	(define (maker total parts)
		(cond ((= total 0) 1)
			((null? parts) 0)
			((>= total (car parts)) (+ (maker (- total (car parts)) parts) (maker total (cdr parts))))
			(else (maker total (cdr parts))
				)
			)
		)
	(define (range low high)
		(cond ((> low high) '())
			(else (append (list low) (range (+ low 1) high)))
			)
		)
	(maker total (range 1 max-value))
)

(count-partitions 5 3)
; expect 5
; Note: The 5 partitions are [[3 2] [3 1 1] [2 2 1] [2 1 1 1] [1 1 1 1 1]]

; Problem 12

;; A list of all ways to partition TOTAL, where  each partition must 
;; be at most MAX-VALUE and there are at most MAX-PIECES partitions.
(define (list-partitions total max-pieces max-value)
	(define (maker total parts l max-pieces)
		(cond ((= total 0) (list l))
			((null? parts) '())
			((= max-pieces 0) '())
			((>= total (car parts)) (append (maker (- total (car parts)) parts (append l (list (car parts))) (- max-pieces 1)) (maker total (cdr parts) l max-pieces)))
			(else (maker total (cdr parts) l max-pieces))
			)
		)
	(define (range low high)
		(cond ((> low high) '())
			(else (append (list low) (range (+ low 1) high)))
			)
		)
	(maker total (range 1 max-value) '() max-pieces)
	)

(list-partitions 5 2 4)
; expect ((1 4) (2 3))
(list-partitions 7 3 5)
; expect ((1 1 5) (1 2 4) (1 3 3) (2 2 3) (2 5) (3 4))



