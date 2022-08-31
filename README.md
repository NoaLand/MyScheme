# My Scheme -- A Runnable The Little Schemer
[![My-Scheme-CI](https://github.com/NoaLand/MyScheme/actions/workflows/build_and_test.yml/badge.svg?branch=master)](https://github.com/NoaLand/MyScheme/actions/workflows/build_and_test.yml)

This is a project to implement my own Scheme compiler, since client network cannot work.

Basically, I'll define term according to 'The Little Schemer'.

So we can just start from the begining of this book.

## TODO
- [x] refactor implementation of function instantiate -- use stack/list instead of string/replace
- [x] add automation test according to docs
- [ ] use **smart pointer** to refactor this codebase, since last 8 refactor commit introduce memory bugs when declare customized function
- [ ] refactor architecture
  - [x] refactor to basic structure
  - [x] extract function out of repl
  - [ ] separate interpreter.cpp into several factories
- [ ] refactor code smell -- 50%

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
            (quote s_expression) -> atom
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