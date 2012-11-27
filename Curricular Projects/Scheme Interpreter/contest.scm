;;; Your entry for the Scheme contest
;;;
;;; Title: 
;;;   Do Fractal Dragons dream of Complex Snow?
;;;
;;; Description:
;;;   Dragon in his den
;;;   Picture turtle on a pen
;;;   Fractals you shall dream
;;;
;;;
;;;	NOTE: TO USE: LET: 1 = X-Axis, 2 = Y-Axis, 3 = Forward, 4 = Turn Right, 5 = Turn Left
;;; ALSO NOTE: I found an algorithm for the generation of fractals in python, which I modified to allow drawing as the instructions are calculated and ported to scheme.
;;; Credit: http://code.activestate.com/recipes/576982-dragon-fractal-curve/



(define (draw-fractal len ang lev init target repl target2 repl2)
	(define (range low high)
		(cond ((> low high) '())
			(else (append (list low) (range (+ low 1) high)))
		)
	)
	(define (state-builder init state target target2 repl repl2)
				(cond ((null? init) (draw state) state)
					((= (car init) (car target)) (state-builder (cdr init) (append state repl) target target2 repl repl2))
					((= (car init) (car target2)) (state-builder (cdr init) (append state repl2) target target2 repl repl2))
					(else (state-builder (cdr init) (append state (list (car init))) target target2 repl repl2))
				)
	)
	(define (depth-creater range init state target target2 repl repl2 lev)
		(cond ((= lev (car range))) 
			(else (define init (state-builder init state target target2 repl repl2)) (depth-creater (cdr range) init state target target2 repl repl2 lev))
		)
	)
	(define (draw final_instructions)
		(cond ((null? final_instructions))
			((= (car final_instructions) 3) (forward len) (draw (cdr final_instructions)))
			((= (car final_instructions) 4) (right ang) (draw (cdr final_instructions)))
			((= (car final_instructions) 5) (left ang) (draw (cdr final_instructions)))
			(else (draw (cdr final_instructions)))
		)
	)
	(depth-creater (range 0 lev) init '() target target2 repl repl2 lev)
)

(define (dragon lvl) 
	;1 = X-Axis, 2 = Y-Axis, 3 = Forward, 4 = Turn Right, 5 = Turn Left
	(draw-fractal 5 90 lvl '(3 1) '(1) '(1 4 2 3 4) '(2) '(5 3 1 5 2))
)

(define (koch-snowflake lvl)
	;1 = X-Axis, 2 = Y-Axis, 3 = Forward, 4 = Turn Right, 5 = Turn Left
	(draw-fractal 1 60 lvl '(1 4 4 1 4 4 1) '(1) '(3 1 5 3 1 4 4 1 3 5 1 3) '(0) '(0))
)

(define (cesaro lvl)
	;1 = X-Axis, 2 = Y-Axis, 3 = Forward, 4 = Turn Right, 5 = Turn Left
	(draw-fractal 2 75 lvl '(3 1) '(1) '(1 5 3 1 4 4 3 1 5 3 1) '(0) '(0))
)

(define (quadratic-koch lvl)
	;1 = X-Axis, 2 = Y-Axis, 3 = Forward, 4 = Turn Right, 5 = Turn Left
	(setheading 180)
	(draw-fractal 1 90 lvl '(1 4 1 4 1 4 1) '(1) '(3 1 5 3 1 4 3 1 4 3 1 3 1 3 1 5 3 1 5 3 1 4 3 1) '(0) '(0))
)

(define (start)
	(st)
	(speed 0)
	(hideturtle)
	(penup)
	(setposition -300 175)
	(pendown)
	(setheading 180)
	(cesaro 5)
	(penup)
	(setposition 250 -175)
	(pendown)
	(setheading 0)
	(cesaro 5)
	(penup)
	(setposition -200 -200)
	(pendown)
	(setheading 90)
	(cesaro 5)
	(penup)
	(setposition 200 200)
	(pendown)
	(setheading 270)
	(cesaro 5)
	(penup)
	(setposition 50 0)
	(setheading 0)
	(pendown)
	(color 'blue)
	(koch-snowflake 4)
	(penup)
	(setposition -90 -45)
	(setheading 0)
	(pendown)
	(color 'red)
	(dragon 10)
	(exitonclick)
)

(start)
	