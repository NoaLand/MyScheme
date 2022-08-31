#include "runnable_the_little_schemer//scheme_use_case.h"

class CarFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(CarGroup,
                         CarFunctionGroupTest,
                         testing::Values(
                                 UseCase<atom>("(car (a b c))", "a"),
                                 UseCase<list<atom>>("(car ((a b c) x y z))", "( a b c )"),
                                 UseCase<list<atom>>("(car (((hotdogs)) (and) (pickle) relish))", "( ( hotdogs ) )"),
                                 UseCase<list<atom>>("(car (car (((hotdogs)) (and))))", "( hotdogs )"),
                                 UseCase<list<atom>>("(car hotdog)", "should throw! car is only for list", true),
                                 UseCase<list<atom>>("(car ())", "should throw! car is only for list", true)
                         ));

TEST_P(CarFunctionGroupTest, should_return_expected_car_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class CdrFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(CdrGroup,
                         CdrFunctionGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(cdr ((a b c) x y z))", "( x y z )"),
                                 UseCase<list<integer>>("(cdr (hamburger))", "( )"),
                                 UseCase<list<atom>>("(cdr ((x) t r))", "( t r )"),
                                 UseCase<list<atom>>("(cdr hotdogs)", "should throw! cdr is only for list", true),
                                 UseCase<list<atom>>("(cdr ())", "should throw! cdr is only for list", true)
                         ));

TEST_P(CdrFunctionGroupTest, should_return_expected_cdr_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class CarCdrFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(CarCdrGroup,
                         CarCdrFunctionGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(car (cdr ((b) (x y) (c))))", "( x y )"),
                                 UseCase<list<atom>>("(cdr (cdr ((b) (x y) ((c)))))", "( ( ( c ) ) )"),
                                 UseCase<list<atom>>("(cdr (car (a (b (c)) d)))", "should throw! car should take a list!", true)
                         ));

TEST_P(CarCdrFunctionGroupTest, should_return_expected_mix_car_cdr_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class ConsFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(ConsGroup,
                         ConsFunctionGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(cons peanut (butter and jelly))", "( peanut butter and jelly )"),
                                 UseCase<list<s_expression>>("(cons (banana and) (peanut butter and jelly))", "( ( banana and ) peanut butter and jelly )"),
                                 UseCase<list<s_expression>>("(cons ((help) this) (is very ((hard) to learn)))", "( ( ( help ) this ) is very ( ( hard ) to learn ) )"),
                                 UseCase<list<s_expression>>("(cons (a b (c)) ())", "( ( a b ( c ) ) )"),
                                 UseCase<list<atom>>("(cons a ())", "( a )"),
                                 UseCase<list<atom>>("(cons ((a b c)) b)", "should throw! cons second param needs a list type!", true),
                                 UseCase<list<atom>>("(cons a b)", "should throw! cons second param needs a list type", true),
                                 UseCase<list<atom>>("(cons a (car ((b) c d)))", "( a b )"),
                                 UseCase<list<atom>>("(cons a (cdr ((b) c d)))", "( a c d )")
                         ));

TEST_P(ConsFunctionGroupTest, should_return_expected_cons_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class IsNullFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsNullGroup,
                         IsNullFunctionGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(null? ())", "#t"),
                                 UseCase<boolean>("(null? (a b c))", "#f"),
                                 UseCase<boolean>("(null? spaghetti)", "should throw! null? take a list as param", true)
                         ));

TEST_P(IsNullFunctionGroupTest, should_return_expected_is_null_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class AddTupGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(AddTupGroup,
                         AddTupGroupTest,
                         testing::Values(
                                 UseCase<integer>("(addtup (3 5 2 8))", "18"),
                                 UseCase<integer>("(addtup (15 6 7 12 3))", "43")
                         ));

TEST_P(AddTupGroupTest, should_return_expected_add_tup_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class TupAddGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(TupAddGroup,
                         TupAddGroupTest,
                         testing::Values(
                                 UseCase<list<integer>>("(tup+ (3 6 9 11 4) (8 5 2 0 7))", "( 11 11 11 11 11 )"),
                                 UseCase<list<integer>>("(tup+ (2 3) (4 6))", "( 6 9 )"),
                                 UseCase<list<integer>>("(tup+ (3 7) (4 6))", "( 7 13 )"),
                                 UseCase<list<integer>>("(tup+ (3 7) (4 6 8 1))", "should throw! tup+ need tuples and has same size!", true)
                         ));

TEST_P(TupAddGroupTest, should_return_expected_add_tup_res_from_scheme_interpreter) {
    function_define("+", "(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))");
    function_define("tup+", "(define tup+ (lambda (tup1 tup2) (cond ((and? (null? tup1) (null? tup2)) ()) (else (cons (+ (car tup1) (car tup2)) (tup+ (cdr tup1) (cdr tup2)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}
