#include "runnable_the_little_schemer/scheme_use_case.h"

class SelfAddGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(SelfAddGroup,
                         SelfAddGroupTest,
                         testing::Values(
                                 UseCase<integer>("(add1 67)", "68"),
                                 UseCase<integer>("(add1 x)", "should throw! add1 is only for integer", true)
                         ));

TEST_P(SelfAddGroupTest, should_return_expected_self_add_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class SelfSubGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(SelfSubGroup,
                         SelfSubGroupTest,
                         testing::Values(
                                 UseCase<integer>("(sub1 5)", "4"),
                                 UseCase<integer>("(sub1 0)", "-1"),
                                 UseCase<integer>("(sub1 -1)", "should throw! sub1 is only for [0, 1, 2 ...)", true)
                         ));

TEST_P(SelfSubGroupTest, should_return_expected_self_sub_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class IsZeroGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsZeroGroup,
                         IsZeroGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(zero? 0)", "#t"),
                                 UseCase<boolean>("(zero? 1492)", "#f")
                         ));

TEST_P(IsZeroGroupTest, should_return_expected_is_zero_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class AddGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(AddGroup,
                         AddGroupTest,
                         testing::Values(
                                 UseCase<integer>("(+ 46 12)", "58"),
                                 UseCase<integer>("(+ 10 2)", "12")
                         ));

TEST_P(AddGroupTest, should_return_expected_add_res_from_scheme_interpreter) {
    function_define("+", "(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class MinusGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(MinusGroup,
                         MinusGroupTest,
                         testing::Values(
                                 UseCase<integer>("(- 14 3)", "11"),
                                 UseCase<integer>("(- 10 2)", "8"),
                                 UseCase<integer>("(- 17 9)", "8"),
                                 UseCase<integer>("(- 18 25)", "-7")
                         ));

TEST_P(MinusGroupTest, should_return_expected_minus_res_from_scheme_interpreter) {
    function_define("-", "(define - (lambda (n m) (cond ((zero? m) n) (else (sub1 (- n (sub1 m)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class TimeGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(TimeGroup,
                         TimeGroupTest,
                         testing::Values(
                                 UseCase<integer>("(* 12 3)", "36"),
                                 UseCase<integer>("(* 10 10)", "100")
                         ));

TEST_P(TimeGroupTest, should_return_expected_minus_res_from_scheme_interpreter) {
    function_define("+", "(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))");
    function_define("*", "(define * (lambda (n m) (cond ((zero? m) 0) (else (+ n (* n (sub1 m)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class GreaterThanGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(GreaterThanGroup,
                         GreaterThanGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(> 12 133)", "#f"),
                                 UseCase<boolean>("(> 120 11)", "#t"),
                                 UseCase<boolean>("(> 10 10)", "#f")
                         ));

TEST_P(GreaterThanGroupTest, should_return_expected_minus_res_from_scheme_interpreter) {
    function_define(">", "(define > (lambda (n m) (cond ((zero? n) #f) ((zero? m) #t) (else (> (sub1 n) (sub1 m))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class LessThanGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(LessThanGroup,
                         LessThanGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(< 4 6)", "#t"),
                                 UseCase<boolean>("(< 8 3)", "#f"),
                                 UseCase<boolean>("(< 6 6)", "#f")
                         ));

TEST_P(LessThanGroupTest, should_return_expected_minus_res_from_scheme_interpreter) {
    function_define("<", "(define < (lambda (n m) (cond ((zero? m) #f) ((zero? n) #t) (else (< (sub1 n) (sub1 m))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}
