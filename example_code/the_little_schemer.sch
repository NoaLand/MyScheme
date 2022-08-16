(define insertR
    (lambda (new old lat)
        (cond
            ((null? lat) (()))
            ((eq? old (car lat)) (cons old (cons new (cdr lat))))
            (else (cons (car lat) (insertR new old (cdr lat))))
        )
    )
)
(insertR topping fudge (ice cream with fudge for dessert))
(insertR jalapeno and (tacos tamales and salsa))
(insertR e d (a b c d f g d h))

(define insertL
    (lambda (new old lat)
        (cond
            ((null? lat) ())
            ((eq? old (car lat)) (cons new lat))
            (else (cons (car lat) (insertL new old (cdr lat))))
        )
    )
)
(insertL topping fudge (ice cream with fudge for dessert))
(insertL jalapeno and (tacos tamales and salsa))
(insertL e d (a b c d f g d h))

(define insert
    (lambda (l)
        (cond
            (l (insertL topping fudge (ice cream with fudge for dessert)))
            (else (insertR topping fudge (ice cream with fudge for dessert)))
        )
    )
)

(define subst
    (lambda (new old lat)
        (cond
            ((null? lat) (()))
            ((eq? old (car lat)) (cons new (cdr lat)))
            (else (cons (car lat) (subst new old (cdr lat))))
        )
    )
)
(subst topping fudge (ice cream with fudge for dessert))

(define subst2
    (lambda (new o1 o2 lat)
        (cond
            ((null? lat) (()))
            ((or (eq? o1 (car lat)) (eq? o2 (car lat))) (cons new (cdr lat)))
            (else (cons (car lat) (subst new o1 o2 (cdr lat))))
        )
    )
)
(subst2 vanilla chocolate banana (banana ice cream with chocolate topping))

(define multirember
    (lambda (a lat)
        (cond
            ((null? lat) ())
            ((eq? a (car lat)) (multirember a (cdr lat)))
            (else (cons (car lat) (multirember a (cdr lat))))
        )
    )
)
(multirember cup (coffee cup tea cup and hick cup))

(define multiinsertR
    (lambda (new old lat)
        (cond
            ((null? lat) ())
            ((eq? old (car lat)) (cons old (cons new (multiinsertR new old (cdr lat)))))
            (else (cons (car lat) (insertR new old (cdr lat))))
        )
    )
)
(multiinsertR topping fudge (ice cream with fudge for fudge dessert))
(multiinsertR jalapeno and (tacos and tamales and salsa))
(multiinsertR e d (a b c d f g d h))

(define multiinsertL
    (lambda (new old lat)
        (cond
            ((null? lat) ())
            ((eq? old (car lat)) (cons new (cons old (multiinsertL new old (cdr lat)))))
            (else (cons (car lat) (multiinsertL new old (cdr lat))))
        )
    )
)
(define multiinsertL (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons new (cons old (multiinsertL new old (cdr lat))))) (else (cons (car lat) (multiinsertL new old (cdr lat)))))))
(multiinsertL fried fish (chips and fish / fish and fried))

(define multisubst
    (lambda (new old lat)
        (cond
            ((null? lat) (()))
            ((eq? old (car lat)) (cons new (multisubst new old (cdr lat))))
            (else (cons (car lat) (multisubst new old (cdr lat))))
        )
    )
)
(define multisubst (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons new (multisubst new old (cdr lat)))) (else (cons (car lat) (multisubst new old (cdr lat)))))))
(multisubst topping fudge (ice cream with fudge for dessert and fudge tacos))

(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))
(define - (lambda (n m) (cond ((zero? m) n) (else (sub1 (- n (sub1 m)))))))
(define * (lambda (n m) (cond ((zero? m) 0) (else (+ n (* n (sub1 m)))))))

(define tup+
    (lambda (tup1 tup2)
        (cond
            ((null? tup1) tup2)
            ((null? tup2) tup1)
            (else (cons (+ (car tup1) (car tup2)) (tup+ (cdr tup1) (cdr tup2))))
        )
    )
)
(define tup+ (lambda (tup1 tup2) (cond ((null? tup1) tup2) ((null? tup2) tup1) (else (cons (+ (car tup1) (car tup2)) (tup+ (cdr tup1) (cdr tup2)))))))
(tup+ (3 6 9 11 4) (8 5 2 0 7))
(tup+ (2 3) (4 6))
(tup+ (3 7) (4 6))
(tup+ (3 7) (4 6 8 1))

(define >
    (lambda (n m)
        (cond
            ((zero? n) #f)
            ((zero? m) #t)
            (else (> (sub1 n) (sub1 m)))
        )
    )
)
(define > (lambda (n m) (cond ((zero? n) #f) ((zero? m) #t) (else (> (sub1 n) (sub1 m))))))
(> 12 133)
(> 120 11)

(define <
    (lambda (n m)
        (cond
            ((zero? m) #f)
            ((zero? n) #t)
            (else (< (sub1 n) (sub1 m)))
        )
    )
)
(define < (lambda (n m) (cond ((zero? m) #f) ((zero? n) #t) (else (< (sub1 n) (sub1 m))))))
(< 4 6)
(< 8 3)
(< 6 6)

(define =
    (lambda (n m)
        (cond
            ((and? (zero? n) (zero? m)) #t)
            ((or? (zero? n) (zero? m)) #f)
            (else (= (sub1 n) (sub1 m)))
        )
    )
)
(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))

(define =
    (lambda (n m)
        (cond
            ((> n m) #f)
            ((< n m) #f)
            (else #t)
        )
    )
)
(define = (lambda (n m) (cond ((> n m) #f) ((< n m) #f) (else #t))))
(= 10 10)
(= 9 10)
(= 10 9)

(define ^
    (lambda (n m)
        (cond
            ((zero? m) 1)
            (else (* n (^ n (sub1 m))))
        )
    )
)
(define ^ (lambda (n m) (cond ((zero? m) 1) (else (* n (^ n (sub1 m)))))))
(^ 1 1)
(^ 2 3)
(^ 5 3)

(define /
    (lambda (n m)
        (cond
            ((< n m) 0)
            (else (add1 (/ (- n m) m)))
        )
    )
)
(define / (lambda (n m) (cond ((< n m) 0) (else (add1 (/ (- n m) m))))))
(/ 15 4)

(define length
    (lambda (lat)
        (cond
            ((null? lat) 0)
            (else (add1 (length (cdr lat))))
        )
    )
)
(define length (lambda (lat) (cond ((null? lat) 0) (else (add1 (length (cdr lat)))))))
(length (hotdogs with mustard sauerkraut and pickles))
(length (ham and cheese on rye))

(define pick
    (lambda (n lat)
        (cond
            ((zero? (sub1 n)) (car lat))
            (else (pick (sub1 n) (cdr lat)))
        )
    )
)
(define pick (lambda (n lat) (cond ((zero? (sub1 n)) (car lat)) (else (pick (sub1 n) (cdr lat))))))
(pick 4 (lasagna spaghetti ravioli macaroni meatball))
(pick 0 (lasagna spaghetti ravioli macaroni meatball))

(define rempick
    (lambda (n lat)
        (cond
            ((zero? (sub1 n)) (cdr lat))
            (else (cons (car lat) (rempick (sub1 n) (cdr lat))))
        )
    )
)
(define rempick (lambda (n lat) (cond ((one? n) (cdr lat)) (else (cons (car lat) (rempick (sub1 n) (cdr lat)))))))
(define rempick (lambda (n lat) (cond ((zero? (sub1 n)) (cdr lat)) (else (cons (car lat) (rempick (sub1 n) (cdr lat)))))))
(rempick 3 (hotdogs with hot mustard))

(define no-nums
    (lambda (lat)
        (cond
            ((null? lat) ())
            ((number? (car lat)) (no-nums (cdr lat)))
            (else (cons (car lat) (no-nums (cdr lat))))
        )
    )
)
(define no-nums (lambda (lat) (cond ((null? lat) ()) ((number? (car lat)) (no-nums (cdr lat))) (else (cons (car lat) (no-nums (cdr lat)))))))
(no-nums (5 pears 6 prunes 9 dates))

(define all-nums
    (lambda (lat)
        (cond
            ((null? lat) ())
            ((number? (car lat)) (cons (car lat) (all-nums (cdr lat))))
            (else (all-nums (cdr lat)))
        )
    )
)
(define all-nums (lambda (lat) (cond ((null? lat) ()) ((number? (car lat)) (cons (car lat) (all-nums (cdr lat)))) (else (all-nums (cdr lat))))))
(all-nums (5 pears 6 prunes 9 dates))

(define eqan?
    (lambda (a1 a2)
        (cond
            ((and? (number? a1) (number? a2)) (= a1 a2))
            ((or? (number? a1) (number? a2)) #f)
            (else (eq? a1 a2))
        )
    )
)
(define eqan?  (lambda (a1 a2) (cond ((and? (number? a1) (number? a2)) (= a1 a2)) ((or? (number? a1) (number? a2)) #f) (else (eq? a1 a2)))))
(eqan? (1 2 a (b c)) (1 2 a (b c)))
(eqan? (2 c) (2 c b d))

(define occur
    (lambda (a lat)
        (cond
            ((null? lat) 0)
            ((eq? a (car lat)) (add1 (occur a (cdr lat))))
            (else (occur a (cdr lat)))
        )
    )
)
(define occur (lambda (a lat) (cond ((null? lat) 0) ((eq? a (car lat)) (add1 (occur a (cdr lat)))) (else (occur a (cdr lat))))))
(occur bc (abc bc cd cb bc a (bc)))
(occur (bc) (abc bc cd cb bc a (bc)))
(occur nothing (abc bc c))

(define one?
    (lambda (n)
        (cond
            (else (= n 1))
        )
    )
)
(define one?  (lambda (n) (cond (else (= n 1)))))
(one? 1)
(one? 2)
(define one?
    (lambda (n)
        (= n 1)
    )
)
(define one?  (lambda (n) (= n 1)))
(one? 1)
(one? 2)

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
(define rember* (lambda (a l) (cond ((null? l) ()) ((atom? (car l)) (cond ((eq? a (car l)) (rember* a (cdr l))) (else (cons (car l) (rember* a (cdr l)))))) (else (cons (rember* a (car l)) (rember* a (cdr l)))))))
(rember* cup ((coffee) cup ((tea) cup) (and (hick)) cup))
(rember* sauce (((tomato sauce)) ((bean) sauce) (and ((flying)) sauce)))

(lat? (((tomato sauce)) ((bean) sauce) (and ((flying)) sauce)))
(atom? (car (((tomato sauce)) ((bean) sauce) (and ((flying)) sauce))))

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
(define insertR* (lambda (new old l) (cond ((null? l) ()) ((atom? (car l)) (cond ((eq? (car l) old) (cons old (cons new (insertR* new old (cdr l))))) (else (cons (car l) (insertR* new old (cdr l)))))) (else (cons (insertR* new old (car l)) (insertR* new old (cdr l)))))))
(insertR* roast chuck ((how much (wood)) could ((a (wood) chuck)) (((chuck))) (if (a) ((wood chuck))) could chuck wood))

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
(define occur* (lambda (a l) (cond ((null? l) 0) ((atom? (car l)) (cond ((eq? a (car l)) (add1 (occur* a (cdr l)))) (else (occur* a (cdr l))))) (else (+ (occur* a (car l)) (occur* a (cdr l)))))))
(occur* banana ((banana) (split ((((banana ice))) (cream (banana)) sherbet)) (banana) (bread) (banana brandy)))