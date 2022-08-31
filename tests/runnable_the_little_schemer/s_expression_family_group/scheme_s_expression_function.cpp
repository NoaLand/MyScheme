#include "runnable_the_little_schemer/scheme_use_case.h"

class IsAtomGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsAtomGroup,
                         IsAtomGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(atom? Harry)", "#t"),
                                 UseCase<boolean>("(atom? (Harry ahd a heap of apples))", "#f"),
                                 UseCase<boolean>("(atom? (car (Harry had a heap of apples)))", "#t"),
                                 UseCase<boolean>("(atom? (cdr (Harry had a heap of apples)))", "#f"),
                                 UseCase<boolean>("(atom? (cdr (Harry)))", "#f"),
                                 UseCase<boolean>("(atom? (car (cdr (swing low sweet cherry oat))))", "#t"),
                                 UseCase<boolean>("(atom? (car (cdr (swing (low sweet) cherry oat))))", "#f"),
                                 UseCase<boolean>("(atom? 14)", "#t")
                         ));

TEST_P(IsAtomGroupTest, should_return_expected_is_atom_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class IsEqGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsEqGroup,
                         IsEqGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(eq? Harry Harry)", "#t"),
                                 UseCase<boolean>("(eq? margarine butter)", "#f"),
                                 UseCase<boolean>("(eq? () (strawberry))", "#f"),
                                 UseCase<boolean>("(eq? 6 7)", "#f"),
                                 UseCase<boolean>("(eq? (car (Mary had a little lamb chop)) Mary)", "#t"),
                                 UseCase<boolean>("(eq? (cdr (soured milk)) milk)", "#f"),
                                 UseCase<boolean>("(eq? (car (beans beans we need jelly beans))"
                                                 "(car (cdr (beans beans we need jelly beans))))", "#t")
                         ));

TEST_P(IsEqGroupTest, should_return_expected_is_eq_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}

class IsNumberGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsNumberGroup,
                         IsNumberGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(number? tomato)", "#f"),
                                 UseCase<boolean>("(number? 76)", "#t")
                         ));

TEST_P(IsNumberGroupTest, should_return_expected_is_number_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
