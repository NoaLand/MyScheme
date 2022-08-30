#include "scheme/scheme_use_case.h"

class DISABLED_IsLatListGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsLatGroup,
                         DISABLED_IsLatListGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(lat? (Jack Sprat could eat no chicken fat))", "#t")
                         ));

TEST_P(DISABLED_IsLatListGroupTest, should_return_expected_list_from_scheme_interpreter) {
    function_define("lat?", "(define lat? (lambda (l) (cond ((null? l) #t) ((atom? (car l)) (lat? (cdr l))) (else #f))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}
