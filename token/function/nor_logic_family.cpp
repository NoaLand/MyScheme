#include "nor_logic_family.h"

boolean* or_logic::execute() {
    if(left->val()) {
        return new boolean{true};
    }
    return new boolean{right->val()};
}

boolean* and_logic::execute() {
    return new boolean(left->val() && right->val());
}
