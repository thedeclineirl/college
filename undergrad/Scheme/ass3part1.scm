;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname ass3part1) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ())))
;creates a new environment
(define (new-environment) '(()))

;declares a new variable in the environment
(define (env-declare! env var)
  ;declares a var if its not already in the list
  (if (eq? (env-get env var) 'ERROR)
      ;goes through the list until we find where to insert the var
      (cond ((null? (car env))(set-car! env (cons var '())))
            ((null? (cdr env))(set-cdr! env (cons (cons var '()) '())))
            (else (env-declare! (cdr env) var)))
      'ERROR))

;gets a variable in the environment
(define (env-get env var)
  ;return ERROR if var is not there
  (cond ((or (null? env) (null? (car env))) 'ERROR)
        ;returns value of variable, if the variable is found
        ((eq? var (car (car env)))(cdr (car env)))
        (else (env-get (cdr env) var))))

;gives a value to a variable
(define (env-put! env var val)
  ;returns ERROR if var is not there
  (cond ((or (null? env) (null? (car env))) 'ERROR)
        ;assigns value to variable, if variable is found
        ((eq? var (car (car env)))(set-cdr! (car env) val))
        (else (env-put! (cdr env) var val))))