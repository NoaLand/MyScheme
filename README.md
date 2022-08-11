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
