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

TEST_P(TimeGroupTest, should_return_expected_times_res_from_scheme_interpreter) {
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

TEST_P(GreaterThanGroupTest, should_return_expected_greater_than_res_from_scheme_interpreter) {
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

TEST_P(LessThanGroupTest, should_return_expected_less_than_res_from_scheme_interpreter) {
    function_define("<", "(define < (lambda (n m) (cond ((zero? m) #f) ((zero? n) #t) (else (< (sub1 n) (sub1 m))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class EqualGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(EqualGroup,
                         EqualGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(= 10 10)", "#t"),
                                 UseCase<boolean>("(= 9 10)", "#f"),
                                 UseCase<boolean>("(= 10 9)", "#f")
                         ));

TEST_P(EqualGroupTest, should_return_expected_equal_res_from_scheme_interpreter) {
    function_define("=", "(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

TEST_P(EqualGroupTest, should_return_expected_equal_v2_res_from_scheme_interpreter) {
    function_define(">", "(define > (lambda (n m) (cond ((zero? n) #f) ((zero? m) #t) (else (> (sub1 n) (sub1 m))))))");
    function_define("<", "(define < (lambda (n m) (cond ((zero? m) #f) ((zero? n) #t) (else (< (sub1 n) (sub1 m))))))");
    function_define("=", "(define = (lambda (n m) (cond ((> n m) #f) ((< n m) #f) (else #t))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class ExptGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(ExptGroup,
                         ExptGroupTest,
                         testing::Values(
                                 UseCase<integer>("(^ 1 1)", "1"),
                                 UseCase<integer>("(^ 2 3)", "8"),
                                 UseCase<integer>("(^ 5 3)", "125")
                         ));

TEST_P(ExptGroupTest, should_return_expected_expt_res_from_scheme_interpreter) {
    function_define("+", "(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))");
    function_define("*", "(define * (lambda (n m) (cond ((zero? m) 0) (else (+ n (* n (sub1 m)))))))");
    function_define("^", "(define ^ (lambda (n m) (cond ((zero? m) 1) (else (* n (^ n (sub1 m)))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class DivisionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(DivisionGroup,
                         DivisionGroupTest,
                         testing::Values(
                                 UseCase<integer>("(/ 15 4)", "3")
                         ));

TEST_P(DivisionGroupTest, should_return_expected_division_res_from_scheme_interpreter) {
    function_define("-", "(define - (lambda (n m) (cond ((zero? m) n) (else (sub1 (- n (sub1 m)))))))");
    function_define("<", "(define < (lambda (n m) (cond ((zero? m) #f) ((zero? n) #t) (else (< (sub1 n) (sub1 m))))))");
    function_define("/", "(define / (lambda (n m) (cond ((< n m) 0) (else (add1 (/ (- n m) m))))))");
    UseCase use_case = GetParam();

    scheme(use_case);
}

class IsOneGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsOneGroup,
                         IsOneGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(one? 1)", "#t"),
                                 UseCase<boolean>("(one? 2)", "#f")
                         ));

TEST_P(IsOneGroupTest, should_return_expected_is_one_res_from_scheme_interpreter) {
    function_define("=", "(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))");
    function_define("one?", "(define one?  (lambda (n) (= n 1)))");
    UseCase use_case = GetParam();

    scheme(use_case);
}
