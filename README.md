# My Scheme

This is a project to implement my own Scheme compiler, since client network cannot work.

Basically, I'll define term according to 'The Little Schemer'.

So we can just start from the begining of this book.

## Term
- atom: a string of characters
- l: a l contains multiple atoms -- ( atom, atom, ... )

## Grammar
```
expression:
    # expression can be enclosed with () or not, they are the same
    - car class:
        car list -> list
        (car list) -> list
list:
    # let's say these items can be in any order
    (atom, atom, ...)
    (list, list, ...)
    (list, atom, ...)
atom:
    a string of characters
```
