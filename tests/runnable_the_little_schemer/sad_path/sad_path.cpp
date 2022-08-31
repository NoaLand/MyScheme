#include "runnable_the_little_schemer//scheme_use_case.h"

class SadPathGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(SadPathGroup,
                         SadPathGroupTest,
                         testing::Values(
                                 UseCase<atom>("car (a)", "should throw! function can only call in closure", true),
                                 UseCase<atom>("cdr (a)", "should throw! function can only call in closure", true),
                                 UseCase<atom>("define x (lambda l) (= n 1)", "should throw! function define can only call in closure", true),
                                 UseCase<atom>("(eq 10 11 12)", "should throw! wrong params number!", true),
                                 UseCase<atom>("(wrong (a b c))", "should throw! cond condition must return bool!", true)
                         ));

TEST_P(SadPathGroupTest, should_throw_syntax_err_exception_from_scheme_interpreter) {
    function_define("=", "(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))");
    function_define("eq", "(define eq (lambda (n m) (= n m)))");
    function_define("wrong", "(define wrong (lambda (n) (cond ((car n) (cdr n)) (else (car n)))))");
    UseCase use_case = GetParam();
    scheme(use_case);
}
