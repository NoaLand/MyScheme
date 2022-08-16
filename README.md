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
        - and_logic class:
            (and? s_expression s_expression) -> bool(#t/#f)
    - s_expression family:
        - is_atom class:
            (atom? s_expression) -> bool(#t/#f)
        - is_eq class:    
            (eq? s_expression s_expression) -> bool(#t/#f)
        - is_number class:
            (number? s_expression) -> bool(#t/#f)
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

### 12. tup+
#### v1
```scheme
(define tup+ (lambda (tup1 tup2) (cond ((and? (null? tup1) (null? tup2)) ()) (else (cons (+ (car tup1) (car tup2)) (tup+ (cdr tup1) (cdr tup2)))))))
```
```text
# test cases
(tup+ (3 6 9 11 4) (8 5 2 0 7))
-> output: tuple: ( 11 11 11 11 11 )

(tup+ (2 3) (4 6))
-> output: tuple: ( 6 9 )

(tup+ (3 7) (4 6))
-> output: tuple: ( 7 13 )

(tup+ (3 7) (4 6 8 1))
-> output: no answer
```
#### v2 -- support for tuples with diff sizes
```scheme
(define tup+ (lambda (tup1 tup2) (cond ((null? tup1) tup2) ((null? tup2) tup1) (else (cons (+ (car tup1) (car tup2)) (tup+ (cdr tup1) (cdr tup2)))))))
```
```text
# test cases
(tup+ (3 7) (4 6 8 1))
-> output: tuple: ( 7 13 8 1 )
```

### 13. >
```scheme
(define > (lambda (n m) (cond ((zero? n) #f) ((zero? m) #t) (else (> (sub1 n) (sub1 m))))))
```
```text
# test cases
(> 12 133)
-> output: bool: #f

(> 120 11)
-> output: bool: #t

(> 10 10)
-> output: bool: #f
```

### 14. <
```scheme
(define < (lambda (n m) (cond ((zero? m) #f) ((zero? n) #t) (else (< (sub1 n) (sub1 m))))))
```
```text
# test cases
(< 4 6)
-> output: bool: #t

(< 8 3)
-> output: bool: #f

(< 6 6)
-> output: bool: #f
```

### 15. =
#### use zero?, sub1
```scheme
(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))
```
#### use >, < function
```scheme
(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))
```

```text
# test cases
(= 10 10)
-> output: bool: #t

(= 9 10)
-> output: bool: #f

(= 10 9)
-> output: bool: #f
```

### 16. ^
```scheme
(define ^ (lambda (n m) (cond ((zero? m) 1) (else (* n (^ n (sub1 m)))))))
```
```text
# test cases
(^ 1 1)
-> output: integer: 1

(^ 2 3)
-> output: integer: 8

(^ 5 3)
-> output: integer: 125
```

### 17. /
```scheme
(define / (lambda (n m) (cond ((< n m) 0) (else (add1 (/ (- n m) m))))))
```
```text
# test cases
(/ 15 4)
-> output: integer: 3
```

### 18. length
```scheme
(define length (lambda (lat) (cond ((null? lat) 0) (else (add1 (length (cdr lat)))))))
```
```text
# test cases
(length (hotdogs with mustard sauerkraut and pickles))
-> output: integer: 6

(length (ham and cheese on rye))
-> output: integer: 5
```

### 19. pick
```scheme
(define pick (lambda (n lat) (cond ((zero? (sub1 n)) (car lat)) (else (pick (sub1 n) (cdr lat))))))
```
```text
# test cases
(pick 4 (lasagna spaghetti ravioli macaroni meatball))
-> output: atom: macaroni

(pick 0 (lasagna spaghetti ravioli macaroni meatball))
-> output: no answer
```

### 20. rempick
```scheme
(define rempick (lambda (n lat) (cond ((zero? (sub1 n)) (cdr lat)) (else (cons (car lat) (rempick (sub1 n) (cdr lat)))))))
```
```text
# test cases
(rempick 3 (hotdogs with hot mustard))
-> output: list: ( hotdogs with mustard )
```

### 21. no-nums
```scheme
(define no-nums (lambda (lat) (cond ((null? lat) ()) ((number? (car lat)) (no-nums (cdr lat))) (else (cons (car lat) (no-nums (cdr lat)))))))
```
```text
# test cases
(no-nums (5 pears 6 prunes 9 dates))
-> output: list: ( pears prunes dates )
```

### 22. all-nums
```scheme
(define all-nums (lambda (lat) (cond ((null? lat) ()) ((number? (car lat)) (cons (car lat) (all-nums (cdr lat)))) (else (all-nums (cdr lat))))))
```
```text
# test cases
(all-nums (5 pears 6 prunes 9 dates))
-> output: tuple: ( 5 6 9 )
```

### 23. eqan?
```scheme
(define eqan?  (lambda (a1 a2) (cond ((and? (number? a1) (number? a2)) (= a1 a2)) ((or? (number? a1) (number? a2)) #f) (else (eq? a1 a2)))))
```
```text
# test cases
(eqan? (1 2 a (b c)) (1 2 a (b c)))
-> output: bool: #t

(eqan? (2 c) (2 c b d))
-> output: bool: #f
```

### 24. occur
```scheme
(define occur (lambda (a lat) (cond ((null? lat) 0) ((eq? a (car lat)) (add1 (occur a (cdr lat)))) (else (occur a (cdr lat))))))
```
```text
# test cases
(occur bc (abc bc cd cb bc a (bc)))
-> output: integer: 2

(occur (bc) (abc bc cd cb bc a (bc)))
-> output: integer: 1

(occur nothing (abc bc c))
-> output: integer: 0
```

### 25. one?
```scheme
(define one?  (lambda (n) (cond (else (= n 1)))))
```
```text
# test cases
(one? 1)
-> output: bool: #t

(one? 2)
-> output: bool: #f
```