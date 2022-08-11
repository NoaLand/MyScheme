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
    # function can be enclosed with () or not, they are the same
    - assertion: every function return atom(#t/#f)
        - assertion s_expression -> bool(#t/#f)
    - s_expression family:
        - is_atom class:
            atom? s_expression -> bool(#t/#f)
        - is_eq class:    
            eq? s_expression s_expression -> bool(#t/#f)
    - list family:
        - car class:
            car list -> s_expression
            (car list) -> s_expression
        - cdr class:
            cdr list -> list
            (cdr list) -> list
        - cons class:
            cons s_expression list -> list
        - is_null class:
            null? list -> bool(#t/#f)
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
s_expression:
    list
    atom
    bool
list:
    # let's say these items can be in any order
    (atom, atom, ...)
    (list, list, ...)
    (list, atom, ...)
atom:
    a string of characters
bool:
    #t
    #f
```

Now you can define any lambda like below:
```lisp
(define lat? (lambda (l) (cond ((null? l) #t) ((atom? (car l)) (lat? (cdr l))) (else #f))))
```

And you'll get result like this:
```
---- func ----
-> name: lat?
-> var: ( l )
-> body: (cond ( ( null? l ) #t ) ( ( atom? ( car l ) ) ( lat? ( cdr l ) ) ) ( else #f ) ) 
```

Then you can call this lambda with parameters:
```
(lat? (Jack Sprat could eat no chicken fat))
```

And you'll get the process of calculation and result:
```
-> null? return type: bool, with value: #f
-> car return type: s_expression, with value: Jack
-> atom? return type: bool, with value: #t
-> cdr return type: list, with value: ( Sprat could eat no chicken fat )
-> null? return type: bool, with value: #f
-> car return type: s_expression, with value: Sprat
-> atom? return type: bool, with value: #t
-> cdr return type: list, with value: ( could eat no chicken fat )
-> null? return type: bool, with value: #f
-> car return type: s_expression, with value: could
-> atom? return type: bool, with value: #t
-> cdr return type: list, with value: ( eat no chicken fat )
-> null? return type: bool, with value: #f
-> car return type: s_expression, with value: eat
-> atom? return type: bool, with value: #t
-> cdr return type: list, with value: ( no chicken fat )
-> null? return type: bool, with value: #f
-> car return type: s_expression, with value: no
-> atom? return type: bool, with value: #t
-> cdr return type: list, with value: ( chicken fat )
-> null? return type: bool, with value: #f
-> car return type: s_expression, with value: chicken
-> atom? return type: bool, with value: #t
-> cdr return type: list, with value: ( fat )
-> null? return type: bool, with value: #f
-> car return type: s_expression, with value: fat
-> atom? return type: bool, with value: #t
-> cdr return type: list, with value: ( )
-> null? return type: bool, with value: #t
bool: #t
```
