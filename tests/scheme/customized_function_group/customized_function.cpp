#include "scheme/scheme_use_case.h"

class IsLatListGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsLatGroup,
                         IsLatListGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(lat? (Jack Sprat could eat no chicken fat))", "#t"),
                                 UseCase<boolean>("(lat? ((Jack) Sprat could eat no chicken fat))", "#f"),
                                 UseCase<boolean>("(lat? (Jack (Sprat could) eat no chicken fat))", "#f"),
                                 UseCase<boolean>("(lat? ())", "#t"),
                                 UseCase<boolean>("(lat? (bacon and eggs))", "#t"),
                                 UseCase<boolean>("(lat? (bacon (and eggs)))", "#f"),
                                 UseCase<boolean>("(lat? (((tomato sauce)) ((bean) sauce) (and ((flying)) sauce)))", "#f")
                         ));

TEST_P(IsLatListGroupTest, should_return_expected_list_from_scheme_interpreter) {
    function_define("lat?", "(define lat? (lambda (l) (cond ((null? l) #t) ((atom? (car l)) (lat? (cdr l))) (else #f))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}
