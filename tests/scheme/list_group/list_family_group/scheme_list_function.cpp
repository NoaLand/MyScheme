#include "scheme/scheme_use_case.h"

class CarFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(CarGroup,
                         CarFunctionGroupTest,
                         testing::Values(
                                 UseCase("(car (a b c))", "atom: a"),
                                 UseCase("(car ((a b c) x y z))", "list: ( a b c )"),
                                 UseCase("(car (((hotdogs)) (and) (pickle) relish))", "list: ( ( hotdogs ) )"),
                                 UseCase("(car (car (((hotdogs)) (and))))", "list: ( hotdogs )"),
                                 UseCase("(car hotdog)", "should throw! car is only for list", true),
                                 UseCase("(car ())", "should throw! car is only for list", true)
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
                                 UseCase("(cdr ((a b c) x y z))", "list: ( x y z )"),
                                 UseCase("(cdr (hamburger))", "tuple: ( )"),
                                 UseCase("(cdr ((x) t r))", "list: ( t r )"),
                                 UseCase("(cdr hotdogs)", "should throw! cdr is only for list", true),
                                 UseCase("(cdr ())", "should throw! cdr is only for list", true)
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
                                 UseCase("(car (cdr ((b) (x y) (c))))", "list: ( x y )"),
                                 UseCase("(cdr (cdr ((b) (x y) ((c)))))", "list: ( ( ( c ) ) )"),
                                 UseCase("(cdr (car (a (b (c)) d)))", "should throw! car should take a list!", true)
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
                                 UseCase("(cons peanut (butter and jelly))", "list: ( peanut butter and jelly )"),
                                 UseCase("(cons (banana and) (peanut butter and jelly))", "list: ( ( banana and ) peanut butter and jelly )"),
                                 UseCase("(cons ((help) this) (is very ((hard) to learn)))", "list: ( ( ( help ) this ) is very ( ( hard ) to learn ) )"),
                                 UseCase("(cons (a b (c)) ())", "list: ( ( a b ( c ) ) )"),
                                 UseCase("(cons a ())", "list: ( a )"),
                                 UseCase("(cons ((a b c)) b)", "should throw! cons second param needs a list type!", true),
                                 UseCase("(cons a b)", "should throw! cons second param needs a list type", true),
                                 UseCase("(cons a (car ((b) c d)))", "list: ( a b )"),
                                 UseCase("(cons a (cdr ((b) c d)))", "list: ( a c d )")
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
                                 UseCase("(null? ())", "bool: #t"),
                                 UseCase("(null? (a b c))", "bool: #f"),
                                 UseCase("(null? spaghetti)", "should throw! null? take a list as param", true)
                         ));

TEST_P(IsNullFunctionGroupTest, should_return_expected_is_null_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
