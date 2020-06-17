;; The first three lines of this file were inserted by DrScheme. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-advanced-reader.ss" "lang")((modname ass3part2) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #t #t none #f ())))
;creates a new environment
(define (new-environment) (make-hash-table))

;declares a new variable in the environment
(define (env-declare! env var)
  ;declares a new variable in the environment with a null value
  (hash-table-put! env var '()))

;gets a variable in the environment
(define (env-get env var)
  ;gets a variable in the environment
  (hash-table-get env var 'ERROR))

;gives a value to a variable
(define (env-put! env var val)
  ;puts a value into the environment, only if the variable was previously declared
  (if (eq? (env-get env var) 'ERROR)
      'ERROR
      (hash-table-put! env var val)))