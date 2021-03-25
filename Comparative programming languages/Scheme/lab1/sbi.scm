#!/afs/cats.ucsc.edu/courses/cse112-wm/usr/racket/bin/mzscheme -qr
;SBI.SCM
;David Grim
;CSE112
;Assignment 1

(define *stderr* (current-error-port))
(define *label-table* (make-hash))
(define *function-table* (make-hash))
(define *variable-table* (make-hash))


(define (get_Lable key)
(hash-ref *label-table* key '()))
    
(define (Put_Lable! key val)
(hash-set! *label-table* key val ))

(define (get_Var key)
(hash-ref *variable-table* key '(no such key in variable-table)))

(define (put_var! key val)
(hash-set! *variable-table* key val))

(define (Get_Function key)
(hash-ref *function-table* key '(no such key in function-table)))

(define (Put_Function! key val)
(hash-set! *function-table* key val))
   

  
;given run file function
(define *run-file*
    (let-values
        (((dirpath basepath root?)
            (split-path (find-system-path 'run-file))))
        (path->string basepath))
)

;given die function
(define (die list)
    (for-each (lambda (item) (display item *stderr*)) list)
    (newline *stderr*)
    (exit 0)
)

;given function for reading input sbir file
(define (readlist-from-inputfile filename)
    (let ((inputfile (open-input-file filename)))
      (if (not (input-port? inputfile))
        (die 
         `(,*run-file* ": " ,filename ": failed to open input file"))
           (let ((program (read inputfile)))(close-input-port inputfile)
            program))
))
 
;print the physical hash table       
(define (printHashTable x)   
 (hash-for-each x
        (lambda (key value)(printf "~s :  = ~s~n" key  value))))

;for input in sbir  
(define (sbir_input . x)
  (put_var! 'inputcount 0)
  (define (get_Input x)
     (when (not (null? (car x)))
        (put_var! (car x) (void))
        (let ((object (read)))
      (cond ((eof-object? object)(put_var! 'inputcount -1))
       ((number? object)(sb_let (car x) object)
        (put_var! 'inputcount (+ (get_Var 'inputcount) 1)))
          (else (begin (printf "invalid number: ~a~n" object))))) 
         (when (not (null? (cdr x)))
     (get_Input (cdr x)))
   ))
  (get_Input x)
)

;for dim in sbir
(define (sb_Dim x)
   (hash-set! *variable-table*(car x)
     (make-vector (caddr x)(exact-round 0.0))))

;factorial definition
(define fact (lambda(x)
    (if (= x 0) 1
      (* x (factorial (- x 1))))))

;The table
(for-each
    (lambda (item)
            (Put_Function! (car item) (car(cdr item))))
    `(
    (exp, exp)
    (sin, sin) 
    (asin, asin)
    (cos, cos) 
    (acos, acos)
    (tan, tan)
    (atan,(lambda(x)(atan (if (equal? x 0) 0.0 x))))
    (factorial, fact)
    (sqrt, sqrt)
    (+, +)
    (-, -) 
    (*, *)
    (/, (lambda (x y)  (sbir_divide x y)))
    (% , (lambda (x y) (- x (* (div x y) y))))
    (quot, (lambda (x y) (truncate (/ x y))))
    (abs, abs) 
    (<, <)
    (>, >)
    (<>,(lambda (x y) (not (equal? x y))))
    (=, (lambda (x y) (eqv? x y)))
    (<=, (lambda (x y) (<= x y)))
    (>=, (lambda (x y) (>= x y)))
    (!=,(lambda (x y) (not (equal? x y))))
    (^ ,(lambda (x y) (expt x y)))
    (log, (lambda(x)(log (if (equal? x 0) 0.0 x))))
    (floor, floor)
    (ceiling, ceiling) 
    (round, round)
    (print,(lambda x (sb_print x)))
    (dim,sb_Dim)
    (let, (lambda (x y) (sb_let x y)))
    (input, (lambda (x) (sb_let x (read)) (size (get_Var x))))
    (goto, (lambda (x) (get_Lable x)))
    (log10   ,(lambda (x) (/ (log x) (log 10.0))))  
    ;(log10_2 0.301029995663981195213738894724493026768189881)
    (e 2.7182818284590452353602874713526624977572470)
    (pi 3.141592653589793238462643383279502884197169)
    (inputcount 1)
    ))

;sbir definition of print in scheme
(define (sb_print x)
  (for-each (lambda (item)
  (if (pair? item)
    (cond((equal?(length x )1)
    (display (vector-ref (get_Var (car(car x))) (-(car(cdr(car x)))1))))
          ((equal? (length x)4)  
           (display (vector-ref (get_Var (car(car(cdr(cdr(cdr x)))))) 
             (-(car(cdr(car(cdr(cdr(cdr x))))))1)))
    ))
  (display item))) x)
    (newline)
)

;sbir definition of divide in scheme
(define (sbir_divide x y)
  (if (= y 0)
    (if (= x 0) "NAN"
      (if (> x 0) "+Infinity" "-Infinity"))
       (/ x y)))



;sbir definition of let in scheme
(define (sb_let var val)
  (if (var? val) (sb_let variable (get_Var val))
    (if (list? var)
      (if (var? (car(cdr var))) 
        (vector-set! (get_Var (car var)) 
         (-(get_Var (car(cdr var)))1) val)
        (vector-set! (get_Var (car var)) 
         (-(car(cdr var))1)val)
      )
      (put_var! var val))
    )
)

(define (size x)
  (cond ((< x 0) (sb_let 'inputcount (- 1)))
      ((= x 0) (sb_let 'inputcount 0)) (else 
        (define (size_ x len)
          (if (>= x 1)
            (size_ (/ x 10) (+ len 1)) 
            (sb_let 'inputcount len)))
            (size_ x 0)       
        )
    )
)

;set the label
(define (set_label program)
  (define (set_label_ x)
    (cond  ((null? x) x)                  
           ((null? (cdr(car x)))(set_label_ (cdr x)))        
           ((list? (car(cdr(car x)))) (set_label_ (cdr x)))
           (else (Put_Lable!(car(cdr(car x))) x)
        (set_label_ (cdr x)))
    ))
    (set_label_ program))

;definition of starting the file reading and interpretting process
(define (start filename program)
    (set_label program)
  (interpret program) 
)

(define (input? x)
  (if (equal? (car x) 'input) #t #f)
)

(define (var? x)
  (if (number? (get_Var x )) #t #f)
)   
 
(define (func? x)
  (if (list? x)
  (if (procedure? (Get_Function (car x))) #t #f)#f)
) 

 ;evaluate the expression
(define (evaluate_expression x)
  (cond ((null? x) x)
     ((number? x) x)
     ((string? x) x)
     ((var? x) (get_Var x))
     ((func? x) (cond((equal? (car x) 'let)
       (sb_let (car(cdr x)) 
        (evaluate_expression (car(cdr(cdr x))))))
     ((input? x)(apply sbir_input(cdr x)))
           (else (apply(Get_Function (car x)) 
             (map evaluate_expression (cdr x))))))
      ((pair? x) (map evaluate_expression x))
      (else x)))

;modified if for use in interpret function
(define (if_ x y z)
  (if (evaluate_expression x) (get_Lable y) (cdr z))
)

;Program interpreter
(define (interpret program)
  (define (interpret_ x)
     (cond  ((null? x) x)            
            ((null? (cdr(car x))) (interpret_ (cdr x))) 
            ((list? (car(cdr(car x))))
              (cond ((equal? 'goto (car(car(cdr(car x))))) 
            (interpret_ (evaluate_expression (car(cdr(car x))))))
              ((equal? 'if (car(car(cdr(car x))))) 
               (interpret_ (if_ (car(cdr(car(cdr(car x))))) 
                 (car(cdr (cdr(car(cdr(car x))))))x)))
              (else (evaluate_expression (car(cdr(car x)))) 
                    (interpret_ (cdr x)))))
             ((null? (cdr(cdr(car x)))) (interpret_ (cdr x))) (else 
             (cond((equal? 'goto (car(car(cdr(cdr(car x)))))) 
               (interpret_ (evaluate_expression 
                    (car(cdr(cdr(car x))))))) 
                ((equal? 'if (car (car(cdr(cdr(car x)))))) 
                    (interpret_ (if_ (cadr (car(cdr(cdr(car x))))) 
                      (car(cdr(cdr(car(cdr(cdr(car x)))))))x))) 
              (else (evaluate_expression (car(cdr(cdr(car x)))))
                (interpret_ (cdr x)))
            )
          )
      ) 
    )
    (interpret_ program))


;given main function
(define (main arglist)
    (if (or (null? arglist) (not (null? (cdr arglist))))
        (usage-exit)
        (let* ((sbprogfile (car arglist))
               (program (readlist-from-inputfile sbprogfile)))
              (start sbprogfile program))))

;actual driver for main
(main (vector->list (current-command-line-arguments)))
