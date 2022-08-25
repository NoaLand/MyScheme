#include "nor_logic_family.h"

boolean* or_logic::execute() {
    if(left->val()) {
        return new boolean{true};
    }
    return new boolean{right->val()};
}

boolean *and_logic::execute() {
    auto left_val = dynamic_cast<boolean*>(left)->val();
    auto right_val = dynamic_cast<boolean*>(right)->val();
    return new boolean(left_val && right_val);
}
