#include "nor_logic_family.h"

boolean* or_logic::execute() {
    if(left->get_indicator() != "bool") {
        throw std::runtime_error("or need take bool as input");
    }
    if(((boolean*)left)->val()) {
        return new boolean{true};
    }
    bool final_res = ((boolean*)right)->val();
    return new boolean{final_res};
}
