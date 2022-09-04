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

class EqanGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(EqanGroup,
                         EqanGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(eqan? (1 2 a (b c)) (1 2 a (b c)))", "#t"),
                                 UseCase<boolean>("(eqan? (2 c) (2 c b d))", "#f")
                         ));

TEST_P(EqanGroupTest, should_return_expected_eqan_res_from_scheme_interpreter) {
    function_define("=", "(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))");
    function_define("eqan?", "(define eqan?  (lambda (a1 a2) (cond ((and? (number? a1) (number? a2)) (= a1 a2)) ((or? (number? a1) (number? a2)) #f) (else (eq? a1 a2)))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class OccurGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(OccurGroup,
                         OccurGroupTest,
                         testing::Values(
                                 UseCase<integer>("(occur bc (abc bc cd cb bc a (bc)))", "2"),
                                 UseCase<integer>("(occur (bc) (abc bc cd cb bc a (bc)))", "1"),
                                 UseCase<integer>("(occur nothing (abc bc c))", "0")
                         ));

TEST_P(OccurGroupTest, should_return_expected_occur_res_from_scheme_interpreter) {
    function_define("occur", "(define occur (lambda (a lat) (cond ((null? lat) 0) ((eq? a (car lat)) (add1 (occur a (cdr lat)))) (else (occur a (cdr lat))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class RememberStarGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(RememberStarGroup,
                         RememberStarGroupTest,
                         testing::Values(
                                 UseCase<list<s_expression>>("(rember* cup ((coffee) cup ((tea) cup) (and (hick)) cup))", "( ( coffee ) ( ( tea ) ) ( and ( hick ) ) )"),
                                 UseCase<list<s_expression>>("(rember* sauce (((tomato sauce)) ((bean) sauce) (and ((flying)) sauce)))", "( ( ( tomato ) ) ( ( bean ) ) ( and ( ( flying ) ) ) )")
                         ));

TEST_P(RememberStarGroupTest, should_return_expected_remberstar_list_from_scheme_interpreter) {
    function_define("rember*", "(define rember* (lambda (a l) (cond ((null? l) ()) ((atom? (car l)) (cond ((eq? a (car l)) (rember* a (cdr l))) (else (cons (car l) (rember* a (cdr l)))))) (else (cons (rember* a (car l)) (rember* a (cdr l)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class InsertRStarGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(InsertRStarGroup,
                         InsertRStarGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(insertR* roast chuck ((how much (wood)) could ((a (wood) chuck)) (((chuck))) (if (a) ((wood chuck))) could chuck wood))",
                                                   "( ( how much ( wood ) ) could ( ( a ( wood ) chuck roast ) ) ( ( ( chuck roast ) ) ) ( if ( a ) ( ( wood chuck roast ) ) ) could chuck roast wood )")
                         ));

TEST_P(InsertRStarGroupTest, should_return_expected_insertRstar_res_from_scheme_interpreter) {
    function_define("insertR*", "(define insertR* (lambda (new old l) (cond ((null? l) ()) ((atom? (car l)) (cond ((eq? (car l) old) (cons old (cons new (insertR* new old (cdr l))))) (else (cons (car l) (insertR* new old (cdr l)))))) (else (cons (insertR* new old (car l)) (insertR* new old (cdr l)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class OccurStarGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(OccurStarGroup,
                         OccurStarGroupTest,
                         testing::Values(
                                 UseCase<integer>("(occur* banana ((banana) (split ((((banana ice))) (cream (banana)) sherbet)) (banana) (bread) (banana brandy)))", "5")
                         ));

TEST_P(OccurStarGroupTest, should_return_expected_occurstar_res_from_scheme_interpreter) {
    function_define("+", "(define + (lambda (n m) (cond ((zero? m) n) (else (add1 (+ n (sub1 m)))))))");
    function_define("occur*", "(define occur* (lambda (a l) (cond ((null? l) 0) ((atom? (car l)) (cond ((eq? a (car l)) (add1 (occur* a (cdr l)))) (else (occur* a (cdr l))))) (else (+ (occur* a (car l)) (occur* a (cdr l)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class SubstStarGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(SubstStarGroup,
                         SubstStarGroupTest,
                         testing::Values(
                                 UseCase<list<s_expression>>("(subst* orange banana ((banana) (split ((((banana ice))) (cream (banana)) sherbet)) (banana) (bread) (banana brandy)))", "( ( orange ) ( split ( ( ( ( orange ice ) ) ) ( cream ( orange ) ) sherbet ) ) ( orange ) ( bread ) ( orange brandy ) )")
                         ));

TEST_P(SubstStarGroupTest, should_return_expected_subststar_res_from_scheme_interpreter) {
    function_define("subst*", "(define subst* (lambda (new old l) (cond ((null? l) ()) ((atom? (car l)) (cond ((eq? old (car l)) (cons new (subst* new old (cdr l)))) (else (cons (car l) (subst* new old (cdr l)))))) (else (cons (subst* new old (car l)) (subst* new old (cdr l)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class InsertLStarGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(InsertLStarGroup,
                         InsertLStarGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(insertL* pecker chuck ((how much (wood)) could ((a (wood) chuck)) (((chuck))) (if (a) ((wood chuck))) could chuck wood))", "( ( how much ( wood ) ) could ( ( a ( wood ) pecker chuck ) ) ( ( ( pecker chuck ) ) ) ( if ( a ) ( ( wood pecker chuck ) ) ) could pecker chuck wood )")
                         ));

TEST_P(InsertLStarGroupTest, should_return_expected_insertL_res_from_scheme_interpreter) {
    function_define("insertL*", "(define insertL* (lambda (new old l) (cond ((null? l) ()) ((atom? (car l)) (cond ((eq? old (car l)) (cons new (cons old (insertL* new old (cdr l))))) (else (cons (car l) (insertL* new old (cdr l)))))) (else (cons (insertL* new old (car l)) (insertL* new old (cdr l)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class IsMemberStarGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsMemberStarGroup,
                         IsMemberStarGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(member* chips ((potato) (chips ((with) fish) (chips))))", "#t")
                         ));

TEST_P(IsMemberStarGroupTest, should_return_expected_memberstar_boolean_res_from_scheme_interpreter) {
    function_define("member*", "(define member* (lambda (a l) (cond ((null? l) #f) ((atom? (car l)) (cond ((eq? a (car l)) #t) (else (or? #f (member* a (cdr l)))))) (else (or? (member* a (car l)) (member* a (cdr l)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class IsMemberStarImprovementGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsMemberStarImprovementGroup,
                         IsMemberStarImprovementGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(member* (chips) ((potato) (chips ((with) fish) (chips))))", "#t"),
                                 UseCase<boolean>("(member* (chips a b) ((potato) (chips ((with) fish) (chips a b))))", "#t"),
                                 UseCase<boolean>("(member* (chips a b) ((potato) (chips a b ((with) fish) (chips))))", "#f")
                         ));

TEST_P(IsMemberStarImprovementGroupTest, should_return_expected_memberstar_improvement_boolean_res_from_scheme_interpreter) {
    function_define("member*", "(define member* (lambda (a l) (cond ((atom? a) (cond ((null? l) #f) ((atom? (car l)) (cond ((eq? a (car l)) #t) (else (or? #f (member* a (cdr l)))))) (else (or? (member* a (car l) (member* a (cdr l))))))) (else (cond ((null? l) #f) ((atom? (car l)) (member* a (cdr l))) (else (cond ((eq? a (car l)) #t) (else (or? (member* a (car l)) (member* a (cdr l)))))))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class LeftmostGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(LeftMostGroup,
                         LeftmostGroupTest,
                         testing::Values(
                                 UseCase<atom>("(leftmost ((potato) (chips ((with) fish) (chips))))", "potato"),
                                 UseCase<atom>("(leftmost (((hot) (tuna (and))) cheese))", "hot"),
                                 UseCase<atom>("(leftmost (((() four)) 17 (seventeen)))", "should throw! leftmost cannot get a null list!", true),
                                 UseCase<atom>("(leftmost (()))", "should throw! leftmost cannot get a null list!", true)
                         ));

TEST_P(LeftmostGroupTest, should_return_expected_leftmost_boolean_res_from_scheme_interpreter) {
    function_define("leftmost", "(define leftmost (lambda (l) (cond ((atom? (car l)) (car l)) (else (leftmost (car l))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class IsSeroGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(IsSeroGroup,
                         IsSeroGroupTest,
                         testing::Values(
                                 UseCase<boolean>("(sero? ())", "#t"),
                                 UseCase<boolean>("(sero? (()))", "#f"),
                                 UseCase<boolean>("(sero? (() ()))", "#f")
                         ));

TEST_P(IsSeroGroupTest, should_return_expected_issero_boolean_res_from_scheme_interpreter) {
    function_define("sero?", "(define sero? (lambda (n) (null? n)))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class Edd1GroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(Edd1Group,
                         Edd1GroupTest,
                         testing::Values(
                                 UseCase<list<s_expression>>("(edd1 ())", "( ( ) )"),
                                 UseCase<list<s_expression>>("(edd1 (() ()))", "( ( ) ( ) ( ) )")
                         ));

TEST_P(Edd1GroupTest, should_return_expected_edd1_res_from_scheme_interpreter) {
    function_define("edd1", "(define edd1 (lambda (n) (cons () n)))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class Zub1GroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(Zub1Group,
                         Zub1GroupTest,
                         testing::Values(
                                 UseCase<list<integer>>("(zub1 (()))", "( )"),
                                 UseCase<list<s_expression>>("(zub1 (() ()))", "( ( ) )")
                         ));

TEST_P(Zub1GroupTest, should_return_expected_zub1_res_from_scheme_interpreter) {
    function_define("zub1", "(define zub1 (lambda (n) (cdr n)))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class ParenthesesAddGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(ParenthesesAddGroup,
                         ParenthesesAddGroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(+ (()()()) (()()()()))", "( ( ) ( ) ( ) ( ) ( ) ( ) ( ) )")
                         ));

TEST_P(ParenthesesAddGroupTest, should_return_expected_parenthesesadd_res_from_scheme_interpreter) {
    function_define("sero?", "(define sero? (lambda (n) (null? n)))");
    function_define("edd1", "(define edd1 (lambda (n) (cons () n)))");
    function_define("zub1", "(define zub1 (lambda (n) (cdr n)))");

    function_define("+", "(define + (lambda (n m) (cond ((sero? m) n) (else (edd1 (+ n (zub1 m)))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class RememberFGroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(RememberFGroup,
                         RememberFGroupTest,
                         testing::Values(
                                 UseCase<list<integer>>("(rember-f = 5 (6 2 5 3))", "( 6 2 3 )"),
                                 UseCase<list<atom>>("(rember-f eq? jelly (jelly beans are good))", "( beans are good )"),
                                 UseCase<list<atom>>("(rember-f eq? (pop corn) (lemonade (pop corn) and (cake)))", "( lemonade and ( cake ) )")
                         ));

TEST_P(RememberFGroupTest, should_return_expected_remberf_list_from_scheme_interpreter) {
    function_define("=", "(define = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m))))))");
    function_define("rember-f", "(define rember-f (lambda (test? a l) (cond ((null? l) ()) (else (cond ((test? (car l) a) (cdr l)) (else (cons (car l) (rember-f test? a (cdr l)))))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}

class DISABLED_RememberFV2GroupTest: public SchemeUseCaseBaseTest {
};

INSTANTIATE_TEST_SUITE_P(RememberFV2Group,
                         DISABLED_RememberFV2GroupTest,
                         testing::Values(
                                 UseCase<list<atom>>("(rember-f (function = (lambda (n m) (cond ((and? (zero? n) (zero? m)) #t) ((or? (zero? n) (zero? m)) #f) (else (= (sub1 n) (sub1 m)))))) 5 (6 2 5 3))", "( 6 2 3 )")
                         ));

TEST_P(DISABLED_RememberFV2GroupTest, should_return_expected_remberf_v2_list_from_scheme_interpreter) {
    function_define("rember-f", "(define rember-f (lambda (test? a l) (cond ((null? l) ()) (else (cond ((test? (car l) a) (cdr l)) (else (cons (car l) (rember-f test? a (cdr l)))))))))");

    UseCase use_case = GetParam();
    scheme(use_case);
}
