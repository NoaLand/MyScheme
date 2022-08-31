#include "runnable_the_little_schemer//scheme_use_case.h"

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

TEST_P(IsLatListGroupTest, should_return_expected_list_is_atom_res_from_scheme_interpreter) {
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

TEST_P(IsMemberGroupTest, should_return_expected_member_boolean_res_from_scheme_interpreter) {
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

TEST_P(RememberGroupTest, should_return_expected_rember_list_from_scheme_interpreter) {
    function_define("rember", "(define rember (lambda (a lat) (cond ((null? lat) ()) (else (cond ((eq? (car lat) a) (cdr lat)) (else (cons (car lat) (rember a (cdr lat)))))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class FirstGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(FirstGroup,
                         FirstGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(firsts ((apple peach pumpkin)"
                                                                "(plum pear cherry)"
                                                                "(grape raisin pea)"
                                                                "(bean carrot eggplant)))", "( apple plum grape bean )"),
                                 UseCase<list<atom>>("(firsts ((a b) (c d) (e f)))", "( a c e )"),
                                 UseCase<list<integer>>("(firsts ())", "( )"),
                                 UseCase<list<atom>>("(firsts ((five plums)"
                                                                "(four)"
                                                                "(eleven green oranges)))", "( five four eleven )"),
                                 UseCase<list<s_expression>>("(firsts (((five plums) four)"
                                                                        "(eleven green oranges)"
                                                                        "((no) more)))", "( ( five plums ) eleven ( no ) )")
                         ));

TEST_P(FirstGroupTest, should_return_expected_first_res_from_scheme_interpreter) {
    function_define("firsts", "(define firsts (lambda (l) (cond ((null? l) ()) (else (cons (car (car l)) (firsts (cdr l)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class InsertRGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(InsertRGroup,
                         InsertRGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(insertR topping fudge (ice cream with fudge for dessert))", "( ice cream with fudge topping for dessert )"),
                                 UseCase<list<atom>>("(insertR jalapeno and (tacos tamales and salsa))", "( tacos tamales and jalapeno salsa )"),
                                 UseCase<list<atom>>("(insertR e d (a b c d f g d h))", "( a b c d e f g d h )")
                         ));

TEST_P(InsertRGroupTest, should_return_expected_insertR_res_from_scheme_interpreter) {
    function_define("insertR", "(define insertR (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons old (cons new (cdr lat)))) (else (cons (car lat) (insertR new old (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class InsertLGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(InsertLGroup,
                         InsertLGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(insertL topping fudge (ice cream with fudge for dessert))", "( ice cream with topping fudge for dessert )"),
                                 UseCase<list<atom>>("(insertL jalapeno and (tacos tamales and salsa))", "( tacos tamales jalapeno and salsa )"),
                                 UseCase<list<atom>>("(insertL e d (a b c d f g d h))", "( a b c e d f g d h )")
                         ));

TEST_P(InsertLGroupTest, should_return_expected_insertL_res_from_scheme_interpreter) {
    function_define("insertL", "(define insertL (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons new lat)) (else (cons (car lat) (insertL new old (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class SubstGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(SubstGroup,
                         SubstGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(subst topping fudge (ice cream with fudge for dessert))", "( ice cream with topping for dessert )"),
                                 UseCase<list<atom>>("(subst jalapeno and (tacos tamales and salsa))", "( tacos tamales jalapeno salsa )"),
                                 UseCase<list<atom>>("(subst e d (a b c d f g d h))", "( a b c e f g d h )")
                         ));

TEST_P(SubstGroupTest, should_return_expected_subst_res_from_scheme_interpreter) {
    function_define("subst", "(define subst (lambda (new old lat) (cond ((null? lat) (())) ((eq? old (car lat)) (cons new (cdr lat))) (else (cons (car lat) (subst new old (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class Subst2GroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(Subst2Group,
                         Subst2GroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(subst2 vanilla chocolate banana (banana ice cream with chocolate topping))", "( vanilla ice cream with chocolate topping )")
                         ));

TEST_P(Subst2GroupTest, should_return_expected_subst2_res_from_scheme_interpreter) {
    function_define("subst2", "(define subst2 (lambda (new o1 o2 lat) (cond ((null? lat) (())) ((or? (eq? o1 (car lat)) (eq? o2 (car lat))) (cons new (cdr lat))) (else (cons (car lat) (subst new o1 o2 (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class MultiRemberGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(MultiRemberGroup,
                         MultiRemberGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(multirember cup (coffee cup tea cup and hick cup))", "( coffee tea and hick )")
                         ));

TEST_P(MultiRemberGroupTest, should_return_expected_multirember_res_from_scheme_interpreter) {
    function_define("multirember", "(define multirember (lambda (a lat) (cond ((null? lat) ()) ((eq? a (car lat)) (multirember a (cdr lat))) (else (cons (car lat) (multirember a (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class MultiInsertRGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(MultiInsertRGroup,
                         MultiInsertRGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(multiinsertR topping fudge (ice cream with fudge for fudge dessert))", "( ice cream with fudge topping for fudge topping dessert )"),
                                 UseCase<list<atom>>("(multiinsertR jalapeno and (tacos and tamales and salsa))", "( tacos and jalapeno tamales and jalapeno salsa )"),
                                 UseCase<list<atom>>("(multiinsertR e d (a b c d f g d h))", "( a b c d e f g d e h )")
                         ));

TEST_P(MultiInsertRGroupTest, should_return_expected_multiinsertR_res_from_scheme_interpreter) {
    function_define("multiinsertR", "(define multiinsertR (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons old (cons new (multiinsertR new old (cdr lat))))) (else (cons (car lat) (multiinsertR new old (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class MultiInsertLGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(MultiInsertLGroup,
                         MultiInsertLGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(multiinsertL fried fish (chips and fish or fish and fried))", "( chips and fried fish or fried fish and fried )")
                         ));

TEST_P(MultiInsertLGroupTest, should_return_expected_multiinsertL_res_from_scheme_interpreter) {
    function_define("multiinsertL", "(define multiinsertL (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons new (cons old (multiinsertL new old (cdr lat))))) (else (cons (car lat) (multiinsertL new old (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class MultiSubstGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(MultiSubstLGroup,
                         MultiSubstGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(multisubst topping fudge (ice cream with fudge for dessert and fudge tacos))", "( ice cream with topping for dessert and topping tacos )")
                         ));

TEST_P(MultiSubstGroupTest, should_return_expected_multisubst_res_from_scheme_interpreter) {
    function_define("multisubst", "(define multisubst (lambda (new old lat) (cond ((null? lat) ()) ((eq? old (car lat)) (cons new (multisubst new old (cdr lat)))) (else (cons (car lat) (multisubst new old (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class NoNumsGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(NoNumsGroup,
                         NoNumsGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(no-nums (5 pears 6 prunes 9 dates))", "( pears prunes dates )")
                         ));

TEST_P(NoNumsGroupTest, should_return_expected_no_nums_res_from_scheme_interpreter) {
    function_define("no-nums", "(define no-nums (lambda (lat) (cond ((null? lat) ()) ((number? (car lat)) (no-nums (cdr lat))) (else (cons (car lat) (no-nums (cdr lat)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class AllNumsGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(AllNumsGroup,
                         AllNumsGroupTest,
                         testing::Values(
                                 UseCase<list<integer>>("(all-nums (5 pears 6 prunes 9 dates))", "( 5 6 9 )")
                         ));

TEST_P(AllNumsGroupTest, should_return_expected_all_nums_res_from_scheme_interpreter) {
    function_define("all-nums", "(define all-nums (lambda (lat) (cond ((null? lat) ()) ((number? (car lat)) (cons (car lat) (all-nums (cdr lat)))) (else (all-nums (cdr lat))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}