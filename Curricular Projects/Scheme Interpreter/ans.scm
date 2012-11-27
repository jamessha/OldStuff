; 10A
(define (big x) (> x 5))

(define ints (list 1 10 3 8 4 7))
(define ints1 (cdr ints))

(define (filter! f s)
	(define (filter1 f s l)
		(cond ((null? (cdr s)) (cdr l))
			((not (f (cadr s))) (set-cdr! s (cddr s)) (filter1 f s l))
			(else (filter1 f (cdr s) l))
			)
		)
	(filter1 f s s)
	)

; 11A
(define (count-change total denoms max-coins)
	(cond ((eq? total 0) 1)
		((eq? max-coins 0) 0)
		((null? denoms) 0)
		((>= total (car denoms)) (+ (count-change total (cdr denoms) max-coins) (count-change (- total (car denoms)) denoms (- max-coins 1))))
		(else (count-change total (cdr denoms) max-coins))
		)
)

; 12
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

(define L (list 1 2 3 4))
; expect l
(define LR (reverse! L))
; expect lr
LR
; expect (4 3 2 1)

(eq? L (list-tail LR 3))
; expect #t

(define (reverse! L)
   (define (helper l to-return)
   	   (cond (= (length l) 1) to-return)
   	   (else (set-cdr! L 
)
