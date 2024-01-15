#ifndef MYSCHEME_FUNCTION_FACTORY_H
#define MYSCHEME_FUNCTION_FACTORY_H
#include <vector>
#include <unordered_map>

#include "core/token.h"
#include "s_expression/function_declaration.h"

class function_instance {
public:
    function_instance(std::shared_ptr<function_declaration> func, std::shared_ptr<list<s_expression>> input) {
        func_name = func->get_name();
        body = func->get_body();
        param_list = func->get_params();
        for(int index = 0; index < param_list->size_of(); index++) {
            param_hashmap[param_list->get(index)->get_value()] = input->get(index);
            if(input->get(index)->get_indicator() == "customized_function") {
                auto f = dynamic_pointer_cast<function_declaration>(input->get(index));
                local_function_hashmap[f->get_name()] = f;
            }
        }
    }

    std::string func_name;
    std::unordered_map<std::string, std::shared_ptr<s_expression>> param_hashmap;
    std::unordered_map<std::string, std::shared_ptr<function_declaration>> local_function_hashmap;
    std::vector<Token> body;
    std::shared_ptr<list<param>> param_list;
};

#endif //MYSCHEME_FUNCTION_FACTORY_H
