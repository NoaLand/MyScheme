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
    - others:
        - quote class:
            (quote any) -> atom
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
-> list: (apple plum grape bean)

(firsts ((a b) (c d) (e f)))
-> list: (a c e)

(firsts ((five plums) (four) (eleven green oranges)))
-> list: (five four eleven)

(firsts (((five plums) four) (eleven green oranges) ((no) more)))
-> list: ((five plums) eleven (no))

(firsts ())
-> list: ()
```

### 2. insertR
```scheme
(define insertR (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons old (cons new (cdr lat)))) (else (cons (car lat) (insertR new old (cdr lat)))))))
```
```text
# test cases
(insertR topping fudge (ice cream with fudge for dessert))
-> list: ( ice cream with fudge topping for dessert )

(insertR jalapeno and (tacos tamales and salsa))
-> list: ( tacos tamales and jalapeno salsa )

(insertR e d (a b c d f g d h))
-> list: ( a b c d e f g d h )
```

### 3. insertL
```scheme
(define insertL (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons new lat)) (else (cons (car lat) (insertL new old (cdr lat)))))))
```
```text
# test cases
(insertL topping fudge (ice cream with fudge for dessert))
-> list: ( ice cream with topping fudge for dessert )

(insertL jalapeno and (tacos tamales and salsa))
-> list: ( tacos tamales jalapeno and salsa )

(insertL e d (a b c d f g d h))
-> list: ( a b c e d f g d h )
```

### 4. subst
```scheme
(define subst (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons new (cdr lat))) (else (cons (car lat) (subst new old (cdr lat)))))))
```
```text
# test cases
(subst topping fudge (ice cream with fudge for dessert))
-> list: ( ice cream with topping for dessert )

(subst jalapeno and (tacos tamales and salsa))
-> list: ( tacos tamales jalapeno salsa )

(subst e d (a b c d f g d h))
-> list: ( a b c e f g d h )
```

### 5. subst2
```scheme
(define subst2 (lambda (new o1 o2 lat) (cond ((null? lat) (())) ((or? (eq? o1 (car lat)) (eq? o2 (car lat))) (cons new (cdr lat))) (else (cons (car lat) (subst new o1 o2 (cdr lat)))))))
```
```text
# test cases
(subst2 vanilla chocolate banana (banana ice cream with chocolate topping))
-> list: ( vanilla ice cream with chocolate topping ) 
```

### 6. multirember
```scheme
(define multirember (lambda (a lat) (cond ((null? lat) ()) ((eq? a (car lat)) (multirember a (cdr lat))) (else (cons (car lat) (multirember a (cdr lat)))))))
```
```text
# test cases
(multirember cup (coffee cup tea cup and hick cup))
-> list: ( coffee tea and hick )
```

### 7. multiinsertR
```scheme
(define multiinsertR (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons old (cons new (multiinsertR new old (cdr lat))))) (else (cons (car lat) (multiinsertR new old (cdr lat)))))))
```
```text
# test cases
(multiinsertR topping fudge (ice cream with fudge for fudge dessert))
-> list: ( ice cream with fudge topping for fudge topping dessert )

(multiinsertR jalapeno and (tacos and tamales and salsa))
-> list: ( tacos and jalapeno tamales and jalapeno salsa )

(multiinsertR e d (a b c d f g d h))
-> list: ( a b c d e f g d e h )
```

### 8. multiinsertL
```scheme
(define multiinsertL (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons new (cons old (multiinsertL new old (cdr lat))))) (else (cons (car lat) (multiinsertL new old (cdr lat)))))))
```
```text
# test cases
(multiinsertL fried fish (chips and fish or fish and fried))
-> list: ( chips and fried fish or fried fish and fried )
```

### 9. multisubst
```scheme
(define multisubst (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons new (multisubst new old (cdr lat)))) (else (cons (car lat) (multisubst new old (cdr lat)))))))
```
```text
# test cases
(multisubst topping fudge (ice cream with fudge for dessert and fudge tacos))
-> list: ( ice cream with topping for dessert and topping tacos )
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
-> tuple: ( 11 11 11 11 11 )

(tup+ (2 3) (4 6))
-> tuple: ( 6 9 )

(tup+ (3 7) (4 6))
-> tuple: ( 7 13 )

(tup+ (3 7) (4 6 8 1))
-> no answer
```
#### v2 -- support for tuples with diff sizes
```scheme
(define tup+ (lambda (tup1 tup2) (cond ((null? tup1) tup2) ((null? tup2) tup1) (else (cons (+ (car tup1) (car tup2)) (tup+ (cdr tup1) (cdr tup2)))))))
```
```text
# test cases
(tup+ (3 7) (4 6 8 1))
-> tuple: ( 7 13 8 1 )
```

### 13. >
```scheme
(define > (lambda (n m) (cond ((zero? n) #f) ((zero? m) #t) (else (> (sub1 n) (sub1 m))))))
```
```text
# test cases
(> 12 133)
-> bool: #f

(> 120 11)
-> bool: #t

(> 10 10)
-> bool: #f
```

### 14. <
```scheme
(define < (lambda (n m) (cond ((zero? m) #f) ((zero? n) #t) (else (< (sub1 n) (sub1 m))))))
```
```text
# test cases
(< 4 6)
-> bool: #t

(< 8 3)
-> bool: #f

(< 6 6)
-> bool: #f
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
-> bool: #t

(= 9 10)
-> bool: #f

(= 10 9)
-> bool: #f
```

### 16. ^
```scheme
(define ^ (lambda (n m) (cond ((zero? m) 1) (else (* n (^ n (sub1 m)))))))
```
```text
# test cases
(^ 1 1)
-> integer: 1

(^ 2 3)
-> integer: 8

(^ 5 3)
-> integer: 125
```

### 17. /
```scheme
(define / (lambda (n m) (cond ((< n m) 0) (else (add1 (/ (- n m) m))))))
```
```text
# test cases
(/ 15 4)
-> integer: 3
```

### 18. length
```scheme
(define length (lambda (lat) (cond ((null? lat) 0) (else (add1 (length (cdr lat)))))))
```
```text
# test cases
(length (hotdogs with mustard sauerkraut and pickles))
-> integer: 6

(length (ham and cheese on rye))
-> integer: 5
```

### 19. pick
```scheme
(define pick (lambda (n lat) (cond ((zero? (sub1 n)) (car lat)) (else (pick (sub1 n) (cdr lat))))))
```
```text
# test cases
(pick 4 (lasagna spaghetti ravioli macaroni meatball))
-> atom: macaroni

(pick 0 (lasagna spaghetti ravioli macaroni meatball))
-> no answer
```

### 20. rempick
#### v1 -- use (zero? (sub1 n))
```scheme
(define rempick (lambda (n lat) (cond ((zero? (sub1 n)) (cdr lat)) (else (cons (car lat) (rempick (sub1 n) (cdr lat)))))))
```
#### v2 -- use (one? n) directly
```scheme
(define rempick (lambda (n lat) (cond ((one? n) (cdr lat)) (else (cons (car lat) (rempick (sub1 n) (cdr lat)))))))
```
```text
# test cases
(rempick 3 (hotdogs with hot mustard))
-> list: ( hotdogs with mustard )
```

### 21. no-nums
```scheme
(define no-nums (lambda (lat) (cond ((null? lat) ()) ((number? (car lat)) (no-nums (cdr lat))) (else (cons (car lat) (no-nums (cdr lat)))))))
```
```text
# test cases
(no-nums (5 pears 6 prunes 9 dates))
-> list: ( pears prunes dates )
```

### 22. all-nums
```scheme
(define all-nums (lambda (lat) (cond ((null? lat) ()) ((number? (car lat)) (cons (car lat) (all-nums (cdr lat)))) (else (all-nums (cdr lat))))))
```
```text
# test cases
(all-nums (5 pears 6 prunes 9 dates))
-> tuple: ( 5 6 9 )
```

### 23. eqan?
```scheme
(define eqan?  (lambda (a1 a2) (cond ((and? (number? a1) (number? a2)) (= a1 a2)) ((or? (number? a1) (number? a2)) #f) (else (eq? a1 a2)))))
```
```text
# test cases
(eqan? (1 2 a (b c)) (1 2 a (b c)))
-> bool: #t

(eqan? (2 c) (2 c b d))
-> bool: #f
```

### 24. occur
```scheme
(define occur (lambda (a lat) (cond ((null? lat) 0) ((eq? a (car lat)) (add1 (occur a (cdr lat)))) (else (occur a (cdr lat))))))
```
```text
# test cases
(occur bc (abc bc cd cb bc a (bc)))
-> integer: 2

(occur (bc) (abc bc cd cb bc a (bc)))
-> integer: 1

(occur nothing (abc bc c))
-> integer: 0
```

### 25. one?
#### v1 -- with cond
```scheme
(define one?  (lambda (n) (cond (else (= n 1)))))
```
#### v2 -- simplify
```scheme
(define one?  (lambda (n) (= n 1)))
```
```text
# test cases
(one? 1)
-> bool: #t

(one? 2)
-> bool: #f
```

### 26. rember*
```scheme
(define rember*
    (lambda (a l)
        (cond
            ((null? l) ())
            ((atom? (car l))
                (cond
                    ((eq? a (car l)) (rember* a (cdr l)))
                    (else (cons (car l) (rember* a (cdr l))))
                )
            )
            (else (cons (rember* a (car l)) (rember* a (cdr l))))
        )
    )
)
```
```text
# test cases
(rember* cup ((coffee) cup ((tea) cup) (and (hick)) cup))
-> list: ( ( coffee ) ( ( tea ) ) ( and ( hick ) ) )

(rember* sauce (((tomato sauce)) ((bean) sauce) (and ((flying)) sauce)))
-> list: ( ( ( tomato ) ) ( ( bean ) ) ( and ( ( flying ) ) ) )
```

### 27. insertR*
```scheme
(define insertR*
    (lambda (new old l)
        (cond
            ((null? l) ())
            ((atom? (car l))
                (cond
                    ((eq? (car l) old) (cons old (cons new (insertR* new old (cdr l)))))
                    (else (cons (car l) (insertR* new old (cdr l))))
                )
            )
            (else (cons (insertR* new old (car l)) (insertR* new old (cdr l))))
        )
    )
)
```
```text
# test cases
(insertR* roast chuck ((how much (wood)) could ((a (wood) chuck)) (((chuck))) (if (a) ((wood chuck))) could chuck wood))
-> list: ( ( how much ( wood ) ) could ( ( a ( wood ) chuck roast ) ) ( ( ( chuck roast ) ) ) ( if ( a ) ( ( wood chuck roast ) ) ) could chuck roast wood )
```

### 28. occur*
```scheme
(define occur*
    (lambda (a l)
        (cond
            ((null? l) 0)
            ((atom? (car l)) (cond
                ((eq? a (car l)) (add1 (occur* a (cdr l))))
                (else (occur* a (cdr l)))
            ))
            (else (+ (occur* a (car l)) (occur* a (cdr l))))
        )
    )
)
```
```text
# test cases
(occur* banana ((banana) (split ((((banana ice))) (cream (banana)) sherbet)) (banana) (bread) (banana brandy)))
-> integer: 5
```

### 29. subst*
```scheme
(define subst*
    (lambda (new old l)
        (cond
            ((null? l) ())
            ((atom? (car l)) (cond
                ((eq? old (car l)) (cons new (subst* new old (cdr l))))
                (else (cons (car l) (subst* new old (cdr l))))
            ))
            (else (cons (subst* new old (car l)) (subst* new old (cdr l))))
        )
    )
)
```
```text
# test cases
(subst* orange banana ((banana) (split ((((banana ice))) (cream (banana)) sherbet)) (banana) (bread) (banana brandy)))
-> list: ( ( orange ) ( split ( ( ( ( orange ice ) ) ) ( cream ( orange ) ) sherbet ) ) ( orange ) ( bread ) ( orange brandy ) )
```

### 30. insertL*
```scheme
(define insertL*
    (lambda (new old l)
        (cond
            ((null? l) ())
            ((atom? (car l)) (cond
                ((eq? old (car l)) (cons new (cons old (insertL* new old (cdr l)))))
                (else (cons (car l) (insertL* new old (cdr l))))
            ))
            (else (cons (insertL* new old (car l)) (insertL* new old (cdr l))))
        )
    )
)
```
```text
# test cases
(insertL* pecker chuck ((how much (wood)) could ((a (wood) chuck)) (((chuck))) (if (a) ((wood chuck))) could chuck wood))
-> list: ( ( how much ( wood ) ) could ( ( a ( wood ) pecker chuck ) ) ( ( ( pecker chuck ) ) ) ( if ( a ) ( ( wood pecker chuck ) ) ) could pecker chuck wood )
```

### 31. member*
#### v1 -- this version only word when a is an atom
```scheme
(define member*
    (lambda (a l)
        (cond
            ((null? l) #f)
            ((atom? (car l)) (cond
                ((eq? a (car l)) #t)
                (else (or? #f (member* a (cdr l))))
            ))
            (else (or? (member* a (car l)) (member* a (cdr l))))
        )
    )
)
```
```text
# test cases
(member* chips ((potato) (chips ((with) fish) (chips))))
-> bool: #t
```
#### v2 -- this version will work when a is a list as well
```scheme
(define member*
    (lambda (a l)
        (cond
            ((atom? a) (cond
                ((null? l) #f)
                ((atom? (car l)) (cond
                    ((eq? a (car l)) #t)
                    (else (or? #f (member* a (cdr l))))
                ))
                (else (or? (member* a (car l) (member* a (cdr l)))))
            ))
            (else (cond
                ((null? l) #f)
                ((atom? (car l)) (member* a (cdr l)))
                (else (cond
                    ((eq? a (car l)) #t)
                    (else (or? (member* a (car l)) (member* a (cdr l))))
                ))
            ))
        )
    )
)
```
```text
# test cases
(member* (chips) ((potato) (chips ((with) fish) (chips))))
-> bool: #t

(member* (chips a b) ((potato) (chips ((with) fish) (chips a b))))
-> bool: #t

(member* (chips a b) ((potato) (chips a b ((with) fish) (chips))))
-> bool: #f
```

### 32. leftmost
```scheme
(define leftmost (lambda (l) (cond ((atom? (car l)) (car l)) (else (leftmost (car l))))))
```
```text
# test cases
(leftmost ((potato) (chips ((with) fish) (chips))))
-> atom: potato

(leftmost (((hot) (tuna (and))) cheese))
-> atom: hot

(leftmost (((() four)) 17 (seventeen)))
-> no answer

(leftmost (()))
-> no answer
```

# Let's use () as zero, (()) as 1, (() ()) as 2, (() () ()) as 3 ...
### 33. pzero?
```scheme
(define pzero? (lambda (n) (null? n)))
```
```text
# test cases
(pzero? ())
-> bool: #t

(pzero? (() ()))
-> bool: #f
```