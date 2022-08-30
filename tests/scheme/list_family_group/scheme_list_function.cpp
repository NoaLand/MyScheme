#include "scheme/scheme_use_case.h"

class CarFunctionGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(CarGroup,
                         CarFunctionGroupTest,
                         testing::Values(
                                 UseCase("(car (a b c))", "atom: a"),
                                 UseCase("(car ((a b c) x y z))", "list: ( a b c )"),
                                 UseCase("(car (((hotdogs)) (and) (pickle) relish))", "list: ( ( hotdogs ) )"),
                                 UseCase("(car (car (((hotdogs)) (and))))", "list: ( hotdogs )")
                         ));

TEST_P(CarFunctionGroupTest, should_return_expected_car_res_from_scheme_interpreter) {
    UseCase use_case = GetParam();

    scheme(use_case);
}
