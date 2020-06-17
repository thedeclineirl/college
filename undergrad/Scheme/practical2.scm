(define list_a '(6))

(define (mergesort l)
   (let((split l)
       (merge l))
     display l 
         )
      
) 

;splitting method
(define (split a)
 (if (null? cdr(a))
     (merge a)
     (split a)
  )
 )
 
 

;merge method
(define (merge b)
  
  )

;tester method
(define (test x)
  (let (display x))
)

(echo list_a)
(mergesort list_a)