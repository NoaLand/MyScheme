# My Scheme

This is a project to implement my own Scheme compiler, since client network cannot work.

Basically, I'll define term according to 'The Little Schemer'.

So we can just start from the begining of this book.

## Term
- atom: a string of characters
- l: a l contains multiple atoms -- ( atom, atom, ... )

## Grammar
```
function:
    # function can be enclosed with () or not, they are the same
    - s_expression family:
        - is_atom class:
            atom? s_expression -> atom(#t/#f)
        - is_eq class:    
            eq? s_expression s_expression -> atom(#t/#f)
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
            null? list -> atom(#t/#f)
s_expression:
    list
    atom
list:
    # let's say these items can be in any order
    (atom, atom, ...)
    (list, list, ...)
    (list, atom, ...)
atom:
    a string of characters
```
