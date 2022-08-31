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

class IsMemberGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsMemberGroup,
                         IsMemberGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(member? meat (mashed potatoes and meat gravy))", "#t"),
                                 UseCase<boolean>("(member? liver ())", "#f"),
                                 UseCase<boolean>("(member? liver (bagels and lox))", "#f")
                         ));

TEST_P(IsMemberGroupTest, should_return_expected_list_from_scheme_interpreter) {
    function_define("member?", "(define member?  (lambda (a lat) (cond ((null? lat) #f) (else (or? (eq? (car lat) a) (member? a (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class RememberGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(RememberGroup,
                         RememberGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(rember mint (lamb chops and mint jelly))", "( lamb chops and jelly )"),
                                 UseCase<list<atom>>("(rember mint (lamb chops and mint flavored mint jelly))", "( lamb chops and flavored mint jelly )"),
                                 UseCase<list<atom>>("(rember toast (bacon lettuce and tomato))", "( bacon lettuce and tomato )"),
                                 UseCase<list<atom>>("(rember cup (coffee cup tea cup and hick cup))", "( coffee tea cup and hick cup )"),
                                 UseCase<list<atom>>("(rember bacon (bacon lettuce and tomato))", "( lettuce and tomato )"),
                                 UseCase<list<atom>>("(rember and (bacon lettuce and tomato))", "( bacon lettuce tomato )"),
                                 UseCase<list<atom>>("(rember sauce (soy sauce and tomato sauce))", "( soy and tomato sauce )")
                         ));

TEST_P(RememberGroupTest, should_return_expected_list_from_scheme_interpreter) {
    function_define("rember", "(define rember (lambda (a lat) (cond ((null? lat) ()) (else (cond ((eq? (car lat) a) (cdr lat)) (else (cons (car lat) (rember a (cdr lat)))))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class FirstGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(FirstGroup,
                         FirstGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(firsts ((apple peach pumpkin) (plum pear cherry) (grape raisin pea) (bean carrot eggplant)))", "( apple plum grape bean )")
                         ));

TEST_P(FirstGroupTest, should_return_expected_first_res_from_scheme_interpreter) {
    function_define("firsts", "(define firsts (lambda (l) (cond ((null? l) ()) (else (cons (car (car l)) (firsts (cdr l)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}