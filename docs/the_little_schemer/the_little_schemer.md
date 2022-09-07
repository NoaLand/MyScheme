## Functions in The Little Schemer
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
(define = (lambda (n m) (cond ((> n m) #f) ((< n m) #f) (else #t))))
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
### 33. sero?
```scheme
(define sero? (lambda (n) (null? n)))
```
```text
# test cases
(sero? ())
-> bool: #t

(sero? (() ()))
-> bool: #f
```

### 34. edd1
```scheme
(define edd1 (lambda (n) (cons () n)))
```
```text
# test cases
(edd1 ())
-> list: (())

(edd1 (() ()))
-> list: (() () ())
```

### 35. zub1
#### v1
```scheme
(define zub1 (lambda (n) (cdr n)))
```
```text
# test cases
(zub1 (()))
-> tuple: ()

(zub1 (() ()))
-> list: (())
```

### 36. p+
```scheme
(define p+
    (lambda (n m)
        (cond
            ((sero? m) n)
            (else (edd1 (p+ n (zub1 m))))
        )
    )
)
```
```text
# test cases
(p+ (()()()) (()()()()))
-> list: ( ( ) ( ) ( ) ( ) ( ) ( ) ( ) )

(p+ (()()()()()) (()()()()))
-> list: ( ( ) ( ) ( ) ( ) ( ) ( ) ( ) ( ) ( ) )
```

### 37. set?
```scheme
(define set?
    (lambda (lat)
        (cond
            ((null? lat) #t)
            ((member? (car lat) (cdr lat)) #f)
            (else (set? (cdr lat)))
        )
    )
)
```
```text
# test cases
(set? (apple peaches apple plum))
-> bool: #f

(set? (apple peaches pears plums))
-> bool: #t

(set? ())
-> bool: #t

(set? (apple 3 pear 4 9 apple 3 4))
-> bool: #f
```

### 38. makeset
#### v1
```scheme
(define makeset
    (lambda (lat)
        (cond
            ((null? lat) ())
            ((member? (car lat) (cdr lat)) (makeset (cdr lat)))
            (else (cons (car lat) (makeset (cdr lat))))
        )
    )
)
```
```text
# test cases
(makeset (apple peach pear peach plum apple lemon peach))
-> list: ( pear plum apple lemon peach )
```
#### v2
```scheme
(define makeset (lambda (lat) (cond ((null? lat) ()) (else (cons (car lat) (makeset (multirember (car lat) (cdr lat))))))))
```
```text
# test cases
(makeset (apple peach pear peach plum apple lemon peach))
-> list: ( apple peach pear plum lemon )

(makeset (apple 3 pear 4 9 apple 3 4))
-> list: ( apple 3 pear 4 9 )
```

### 39. subset?
#### v1
```scheme
(define subset?
    (lambda (set1 set2)
        (cond
            ((null? set1) #t)
            ((member? (car set1) set2) (subset? (cdr set1) set2))
            (else #f)
        )
    )
)
```
#### v2 -- use and?
```scheme
(define subset?
    (lambda (set1 set2)
        (cond
            ((null? set1) #t)
            (else
                (and? (member? (car set1) set2)
                      (subset? (cdr set1) set2))
            )
        )
    )
)
```
```text
# test cases
(subset? (5 chicken wings) (5 hamburgers 2 pieces fried chicken and light duckling wings))
-> bool: #t

(subset? (4 pounds of horseradish) (four pounds chicken and 5 ounces horseradish))
-> bool: #f
```

### 40. eqset?
```scheme
(define eqset?
    (lambda (set1 set2)
        (and? (subset? set1 set2) (subset? set2 set1))
    )
)
```
```text
# test cases
(eqset? (6 large chickens with wings) (6 chickens with large wings))
-> bool: #t
```

### 41. intersect?
```scheme
(define intersect?
    (lambda (set1 set2)
        (cond
            ((null? set1) #f)
            (else (or? (member? (car set1) set2) (intersect? (cdr set1) set2)))
        )
    )
)
```
```text
# test cases
(intersect? (stewed tomatoes and macaroni) (macaroni and cheese))
-> bool: #t
```

### 42. intersect
```scheme
(define intersect
    (lambda (set1 set2)
        (cond
            ((null? set1) ())
            ((member? (car set1) set2) (cons (car set1) (intersect (cdr set1) set2)))
            (else (intersect (cdr set1) set2))
        )
    )
)
```
```text
# test cases
(intersect (stewed tomatoes and macaroni) (macaroni and cheese))
-> list: ( and macaroni )
```

### 43. union
```scheme
(define union
    (lambda (set1 set2)
        (cond
            ((null? set1) set2)
            ((member? (car set1) set2) (union (cdr set1) set2))
            (else (cons (car set1) (union (cdr set1) set2)))
        )
    )
)
```
```text
# test cases
(union (stewed tomatoes and macaroni casserole) (macaroni and cheese))
-> list: ( stewed tomatoes casserole macaroni and cheese )
```

### 44. diff
```scheme
(define diff
    (lambda (set1 set2)
        (cond
            ((null? set1) ())
            ((member? (car set1) set2) (diff (cdr set1) set2))
            (else (cons (car set1) (diff (cdr set1) set2)))
        )
    )
)
```
```text
# test cases
(diff (stewed tomatoes and macaroni casserole) (macaroni and cheese))
-> list: ( stewed tomatoes casserole )
```

### 45. intersectall
```scheme
(define intersectall
    (lambda (l-set)
        (cond
            ((null? (cdr l-set)) (car l-set))
            (else (intersect (car l-set) (intersectall (cdr l-set))))
        )
    )
)
```
```text
# test cases
(intersectall ((a b c) (c a d e) (e f g h a b)))
-> list: ( a )

(intersectall ((6 pears and) (3 peaches and 6 peppers) (8 pears and 6 plums) (and 6 prunes with some apples)))
-> list: ( 6 and )
```

### 46. a-pair?
```scheme
(define a-pair?
    (lambda (x)
        (cond
            ((atom? x) #f)
            ((null? x) #f)
            ((null? (cdr x)) #f)
            ((null? (cdr (cdr x))) #t)
            (else #f)
        )
    )
)
```
```text
# test cases
(a-pair? (pear pear))
-> bool: #t

(a-pair? (3 7))
-> bool: #t

(a-pair? ((2) (pair)))
-> bool: #t

(a-pair? (full house))
-> bool: #t

(a-pair? (a))
-> bool: #f

(a-pair? (a b c))
-> bool: #f
```

### 47. first
```scheme
(define first (lambda (p) (car p)))
```
```text
# test cases
(first (a b))
-> atom: a

(first ((a) b))
-> list: ( a )

(first ((a b) (c d)))
-> list: ( a b )
```

### 48. second
```scheme
(define second (lambda (p) (car (cdr p))))
```
```text
# test cases
(second (a b))
-> atom: b

(second ((a) b))
-> list: b

(second ((a b) (c d)))
-> list: ( c d )
```

### 49. third
```scheme
(define third (lambda (l) (car (cdr (cdr l)))))
```
```text
# test cases
(third (a b c))
-> atom: c

(third (a b (c d)))
-> list: ( c d )
```

### 50. build
```scheme
(define build (lambda (s1 s2) (cons s1 (cons s2 ()))))
```
```text
# test cases
 (build a b)
 -> list: ( a b )
 
 (build (a) b)
 -> list: ( ( a ) b )
 
 (build (a b) (c d))
 -> list: ( ( a b ) ( c d ) )
```

### 51. fun?
```scheme
(define fun? (lambda (rel) (set? (firsts rel))))
```
```text
# test cases
(fun? ((8 3) (4 2) (7 6) (6 2) (3 4)))
-> bool: #t

(fun? ((d 4) (b 0) (b 9) (e 5) (g 4)))
-> bool: #f
```

### 52. revrel
```scheme
(define revrel
    (lambda (rel)
        (cond
            ((null? rel) ())
            (else (cons (build (second (car rel)) (first (car rel))) (revrel (cdr rel))))
        )
    )
)
```
```text
# test cases
(revrel ((8 a)(pumpkin pie)(got sick)))
-> list: ( ( a 8 ) ( pie pumpkin ) ( sick got ) )
```

### 52. revpair
```scheme
(define revpair
    (lambda (pair)
        (build (second pair) (first pair))
    )
)
```
#### we can then, use revpair to rewrite revrel, and now, revrel could be like this
```scheme
(define revrel
    (lambda (rel)
        (cond
            ((null? rel) ())
            (else (cons (revpair (car rel)) (revrel (cdr rel))))
        )
    )
)
```
```text
# test cases
(revrel ((8 a)(pumpkin pie)(got sick)))
-> list: ( ( a 8 ) ( pie pumpkin ) ( sick got ) )
```

### 53. one-to-one?
You can then use functions defined above to write a more complicated function -- one-to-one?
```scheme
(define member?  (lambda (a lat) (cond ((null? lat) #f) (else (or? (eq? (car lat) a) (member? a (cdr lat)))))))
(define set? (lambda (lat) (cond ((null? lat) #t) ((member? (car lat) (cdr lat)) #f) (else (set? (cdr lat))))))
(define firsts (lambda (l) (cond ((null? l) ()) (else (cons (car (car l)) (firsts (cdr l)))))))
(define fun? (lambda (rel) (set? (firsts rel))))
(define first (lambda (p) (car p)))
(define second (lambda (p) (car (cdr p))))
(define build (lambda (s1 s2) (cons s1 (cons s2 ()))))
(define revrel (lambda (rel) (cond ((null? rel) ()) (else (cons (build (second (car rel)) (first (car rel))) (revrel (cdr rel)))))))

(define one-to-one? (lambda (fun) (fun? (revrel fun))))
```
```text
# test cases
(one-to-one? ((8 3) (4 2) (7 6) (6 2) (3 4)))
-> bool: #f

(one-to-one? ((8 3) (4 8) (7 6) (6 2) (3 4)))
-> bool: #t

(one-to-one? ((grape raisin) (plum prune) (stewed prune)))
-> bool: #f

(one-to-one? ((grape raisin) (plum prune) (stewed grape)))
-> bool: #t

(one-to-one? ((chocolate chip) (doughy cookie)))
-> bool: #t
```

### 54. rember-f
```scheme
(define rember-f
    (lambda (test? a l)
        (cond
            ((null? l) ())
            (else (cond
                ((test? (car l) a) (cdr l))
                (else (cons (car l) (rember-f test? a (cdr l))))
            ))
        )
    )
)
```
```text
# test cases
(rember-f = 5 (6 2 5 3))
-> tuple: ( 6 2 3 )

(rember-f eq? jelly (jelly beans are good))
-> list: ( beans are good )

(rember-f eq? (pop corn) (lemonade (pop corn) and (cake)))
-> list: ( lemonade and ( cake ) )

# you can also do something like below:
(rember-f (function = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m)))))) 5 (6 2 5 3))
-> tuple: ( 6 2 3 )

(rember-f (function e? (lambda (n m) (eq? n m))) jelly (jelly beans are good))
-> list: ( beans are good )

(rember-f (function e? (lambda (n m) (eq? n m))) (pop corn) (lemonade (pop corn) and (cake)))
-> list: ( lemonade and ( cake ) )
```

### 55. insertL-f
```scheme
(define insertL-f (lambda (test? new old lat) (cond ((null? lat) (())) ((test? old (car lat)) (cons new lat)) (else (cons (car lat) (insertL-f test? new old (cdr lat)))))))
```
```text
# test cases
(insertL-f eq? topping fudge (ice cream with fudge for dessert))
-> list: ( ice cream with topping fudge for dessert )

(insertL-f eq? jalapeno and (tacos tamales and salsa))
-> list: ( tacos tamales jalapeno and salsa )

(insertL-f eq? e d (a b c d f g d h))
-> list: ( a b c e d f g d h )
```

### 56. insertR-f
```scheme
(define insertR-f (lambda (test? new old lat) (cond ((null? lat) (())) ((test? old (car lat)) (cons old (cons new (cdr lat)))) (else (cons (car lat) (insertR-f test? new old (cdr lat)))))))
```
```text
# test cases
(insertR-f eq? topping fudge (ice cream with fudge for dessert))
-> list: ( ice cream with fudge topping for dessert )

(insertR-f eq? jalapeno and (tacos tamales and salsa))
-> list: ( tacos tamales and jalapeno salsa )

(insertR-f eq? e d (a b c d f g d h))
-> list: ( a b c d e f g d h )
```

### 57 - 59. seqL, seqR, insert-g
```scheme
(define seqL (lambda (new old l) (cons new (cons old l))))

(define seqR (lambda (new old l) (cons old (cons new l))))

(define insert-g (lambda (seq new old l) (cond ((null? l) ()) ((eq? (car l) old) (seq new old (cdr l))) (else (cons (car l) (insert-g seq new old (cdr l)))))))

; TODO: after implement lambda anonymous function, you can write something like this:
(define insertL (insert-g seqL))
(define insertR (insert-g seqR))
; but for now, it's not OK
```
```text
# test cases
(insert-g seqR topping fudge (ice cream with fudge for dessert))
-> list: ( ice cream with fudge topping for dessert )

(insert-g seqR jalapeno and (tacos tamales and salsa))
-> list: ( tacos tamales and jalapeno salsa )

(insert-g seqR e d (a b c d f g d h))
-> list: ( a b c d e f g d h )

(insert-g seqL topping fudge (ice cream with fudge for dessert))
-> list: ( ice cream with topping fudge for dessert )

(insert-g seqL jalapeno and (tacos tamales and salsa))
-> list: ( tacos tamales jalapeno and salsa )

(insert-g seqL e d (a b c d f g d h))
-> list: ( a b c e d f g d h )
```

### 60. subst in insert-g and seqS
```scheme
(define seqS (lambda (new old l) (cons new l)))

(define insert-g (lambda (seq new old l) (cond ((null? l) ()) ((eq? (car l) old) (seq new old (cdr l))) (else (cons (car l) (insert-g seq new old (cdr l)))))))
```
```text
# test cases
(insert-g seqS topping fudge (ice cream with fudge for dessert))
-> list: ( ice cream with topping for dessert )

(insert-g seqS jalapeno and (tacos tamales and salsa))
-> list: ( tacos tamales jalapeno salsa )

(insert-g seqS e d (a b c d f g d h))
-> list: ( a b c e f g d h )
```
