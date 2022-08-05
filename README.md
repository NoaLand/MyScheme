# My Scheme

This is a project to implement my own Scheme compiler, since client network cannot work.

Basically, I'll define term according to 'The Little Schemer'.

So we can just start from the begining of this book.

## Term
- atom: a string of characters
- list: a list contains multiple atoms -- ( atom, atom, ... )

## Grammar
```
list:
    # let's say these items can be in any order
    (atom, atom, ...)
    (list, list, ...)
    (list, atom, ...)
atom:
    a string of characters
```
