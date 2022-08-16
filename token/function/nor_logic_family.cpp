#include "nor_logic_family.h"

boolean* or_logic::execute() {
    if(((boolean*)left)->val()) {
        return new boolean{true};
    }
    bool final_res = ((boolean*)right)->val();
    return new boolean{final_res};
}

boolean *and_logic::execute() {
    auto left_val = ((boolean*)left)->val();
    auto right_val = ((boolean*)right)->val();
    return new boolean(left_val && right_val);
}
