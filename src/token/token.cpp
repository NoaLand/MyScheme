#include "token/token.h"


std::string serialize_token_list(const std::vector<Token>& token_list) {
    std::string deserialized_body;
    for(const auto& ele : token_list) {
        if(ele.type == '(' || ele.type == ')') {
            deserialized_body += ele.type;
            deserialized_body += " ";
        } else if(ele.type == 'N') {
            deserialized_body += std::to_string(ele.integer_value) + " ";
        } else if(ele.type == 'P') {
            deserialized_body += "$" + ele.value + "$" + " ";
        } else {
            deserialized_body += ele.value + " ";
        }
    }

    return deserialized_body;
}
