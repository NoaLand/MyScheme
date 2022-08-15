# My Scheme

This is a project to implement my own Scheme compiler, since client network cannot work.

Basically, I'll define term according to 'The Little Schemer'.

So we can just start from the begining of this book.

## Grammar
```
customized function:
    # I do not care about customized function's return type
    (define atom
        (lambda (atom)
            (function)
        )
    )
function:
    # function must be enclosed with (), they are the same
    - math family:
        - integer class:
            - (zero? integer) -> bool(#t/#f)
            - (add1 integer) -> integer
            - (sub1 integer) -> integer
    - nor logic family:
        - or_logic class:
            (or? s_expression s_expression) -> bool(#t/#f)
    - s_expression family:
        - is_atom class:
            (atom? s_expression) -> bool(#t/#f)
        - is_eq class:    
            (eq? s_expression s_expression) -> bool(#t/#f)
    - list family:
        - car class:
            (car list) -> s_expression
        - cdr class:
            (cdr list) -> list
        - cons class:
            (cons s_expression list) -> list
        - is_null class:
            (null? list) -> bool(#t/#f)
        - add_tuple class:
            (addtup tuple) -> integer
    - condition family:
        - cond class:
            (lambda (s_expression)
                (cond
                    (assertion s_expression)
                    (assertion s_expression)
                    (assertion s_expression)
                    ...
                    (else s_expression)
                )
            )
    # function basic type
    - assertion: every function return atom(#t/#f)
        - (assertion s_expression) -> bool(#t/#f)
s_expression:
    list
    atom
    bool
list:
    # let's say these items can be in any order
    (atom atom ...)
    (list list ...)
    (list atom ...)
    - tuple
        (integer integer ...)
atom:
    - a string of characters
    - bool:
        - #t
        - #f
    - nonnegative integer
```

Now you can define any lambda like below:
```scheme
(define lat? (lambda (l) (cond ((null? l) #t) ((atom? (car l)) (lat? (cdr l))) (else #f))))
```

And you'll get result like this:
```text
---- func ----
-> name: lat?
-> var: ( l )
-> body: (cond ( ( null? l ) #t ) ( ( atom? ( car l ) ) ( lat? ( cdr l ) ) ) ( else #f ) ) 
```

Then you can call this lambda with parameters:
```scheme
(lat? (Jack Sprat could eat no chicken fat))
```

And you'll get the process of calculation and result:
```text
-> null? -> bool [#f]
-> car -> s_expression [Jack]
-> atom? -> bool [#t]
-> cdr -> list [( Sprat could eat no chicken fat )]
-> null? -> bool [#f]
-> car -> s_expression [Sprat]
-> atom? -> bool [#t]
-> cdr -> list [( could eat no chicken fat )]
-> null? -> bool [#f]
-> car -> s_expression [could]
-> atom? -> bool [#t]
-> cdr -> list [( eat no chicken fat )]
-> null? -> bool [#f]
-> car -> s_expression [eat]
-> atom? -> bool [#t]
-> cdr -> list [( no chicken fat )]
-> null? -> bool [#f]
-> car -> s_expression [no]
-> atom? -> bool [#t]
-> cdr -> list [( chicken fat )]
-> null? -> bool [#f]
-> car -> s_expression [chicken]
-> atom? -> bool [#t]
-> cdr -> list [( fat )]
-> null? -> bool [#f]
-> car -> s_expression [fat]
-> atom? -> bool [#t]
-> cdr -> list [( )]
-> null? -> bool [#t]
bool: #t
```

## Functions in Scheme
### 1. firsts
```scheme
(define firsts (lambda (l) (cond ((null? l) ()) (else (cons (car (car l)) (firsts (cdr l)))))))
```
```text
# test cases
(firsts ((apple peach pumpkin) (plum pear cherry) (grape raisin pea) (bean carrot eggplant)))
-> output: (apple plum grape bean)

(firsts ((a b) (c d) (e f)))
-> output: (a c e)

(firsts ((five plums) (four) (eleven green oranges)))
-> output: (five four eleven)

(firsts (((five plums) four) (eleven green oranges) ((no) more)))
-> output: ((five plums) eleven (no))

(firsts ())
-> output: ()
```

### 2. insertR
```scheme
(define insertR (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons old (cons new (cdr lat)))) (else (cons (car lat) (insertR new old (cdr lat)))))))
```
```text
# test cases
(insertR topping fudge (ice cream with fudge for dessert))
-> output: ( ice cream with fudge topping for dessert )

(insertR jalapeno and (tacos tamales and salsa))
-> output: ( tacos tamales and jalapeno salsa )

(insertR e d (a b c d f g d h))
-> output: ( a b c d e f g d h )
```

### 3. insertL
```scheme
(define insertL (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons new lat)) (else (cons (car lat) (insertL new old (cdr lat)))))))
```
```text
# test cases
(insertL topping fudge (ice cream with fudge for dessert))
-> output: ( ice cream with topping fudge for dessert )

(insertL jalapeno and (tacos tamales and salsa))
-> output: ( tacos tamales jalapeno and salsa )

(insertL e d (a b c d f g d h))
-> output: ( a b c e d f g d h )
```

### 4. subst
```scheme
(define subst (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons new (cdr lat))) (else (cons (car lat) (subst new old (cdr lat)))))))
```
```text
# test cases
(subst topping fudge (ice cream with fudge for dessert))
-> output: ( ice cream with topping for dessert )

(subst jalapeno and (tacos tamales and salsa))
-> output: ( tacos tamales jalapeno salsa )

(subst e d (a b c d f g d h))
-> output: ( a b c e f g d h )
```

### 5. subst2
```scheme
(define subst2 (lambda (new o1 o2 lat) (cond ((null? lat) (())) ((or? (eq? o1 (car lat)) (eq? o2 (car lat))) (cons new (cdr lat))) (else (cons (car lat) (subst new o1 o2 (cdr lat)))))))
```
```text
# test cases
(subst2 vanilla chocolate banana (banana ice cream with chocolate topping))
-> output: ( vanilla ice cream with chocolate topping ) 
```

### 6. multirember
```scheme
(define multirember (lambda (a lat) (cond ((null? lat) ()) ((eq? a (car lat)) (multirember a (cdr lat))) (else (cons (car lat) (multirember a (cdr lat)))))))
```
```text
# test cases
(multirember cup (coffee cup tea cup and hick cup))
-> output: ( coffee tea and hick )
```

### 7. multiinsertR
```scheme
(define multiinsertR (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons old (cons new (multiinsertR new old (cdr lat))))) (else (cons (car lat) (multiinsertR new old (cdr lat)))))))
```
```text
# test cases
(multiinsertR topping fudge (ice cream with fudge for fudge dessert))
-> output: ( ice cream with fudge topping for fudge topping dessert )

(multiinsertR jalapeno and (tacos and tamales and salsa))
-> output: ( tacos and jalapeno tamales and jalapeno salsa )

(multiinsertR e d (a b c d f g d h))
-> output: ( a b c d e f g d e h )
```

### 8. multiinsertL
```scheme
(define multiinsertL (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons new (cons old (multiinsertL new old (cdr lat))))) (else (cons (car lat) (multiinsertL new old (cdr lat)))))))
```
```text
# test cases
(multiinsertL fried fish (chips and fish or fish and fried))
-> output: ( chips and fried fish or fried fish and fried )
```

### 9. multisubst
```scheme
(define multisubst (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons new (multisubst new old (cdr lat)))) (else (cons (car lat) (multisubst new old (cdr lat)))))))
```
```text
# test cases
(multisubst topping fudge (ice cream with fudge for dessert and fudge tacos))
-> output: ( ice cream with topping for dessert and topping tacos )
```

### 10. +
```scheme
(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))
```
```text
# test cases
(+ 10 2)
---
-> output:
-> is_zero -> bool [#f]
-> sub1 -> integer [1]
-> is_zero -> bool [#f]
-> sub1 -> integer [0]
-> is_zero -> bool [#t]
-> add1 -> integer [11]
-> add1 -> integer [12]
integer: 12
```

### 11. -
```scheme
(define - (lambda (n m) (cond ((zero? m) n) (else (sub1 (- n (sub1 m)))))))
```
```text
# test cases
(- 10 2)
---
-> output:
-> is_zero -> bool [#f]
-> sub1 -> integer [1]
-> is_zero -> bool [#f]
-> sub1 -> integer [0]
-> is_zero -> bool [#t]
-> sub1 -> integer [9]
-> sub1 -> integer [8]
integer: 8
```