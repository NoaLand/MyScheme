#include "nor_logic_family.h"

boolean* or_logic::execute() {
    if(dynamic_cast<boolean*>(left)->val()) {
        return new boolean{true};
    }
    auto final_res = dynamic_cast<boolean*>(right)->val();
    return new boolean{final_res};
}

boolean *and_logic::execute() {
    auto left_val = dynamic_cast<boolean*>(left)->val();
    auto right_val = dynamic_cast<boolean*>(right)->val();
    return new boolean(left_val && right_val);
}
