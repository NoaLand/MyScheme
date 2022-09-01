#include "core/token.h"


std::string serialize_token_list(const std::vector<Token>& token_list) {
    std::string deserialized_body;
    for(const auto& ele : token_list) {
        deserialized_body += ele.value + " ";
    }

    return deserialized_body;
}
