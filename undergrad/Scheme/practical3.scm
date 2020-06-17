(define dictionary '((a . 1)(b . "hello")(c .(123)))
;(write dictionary)

(new-environment)
(env-declare! env var)
(env-get env var)
(env-put! env var val)