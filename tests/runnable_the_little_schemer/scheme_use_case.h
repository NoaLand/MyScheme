#ifndef MYSCHEME_SCHEME_USE_CASE_H
#define MYSCHEME_SCHEME_USE_CASE_H

#include <base_test.h>

#include <utility>
#include <concepts>

#include "core/interpreter.h"

template <typename T>
requires std::derived_from<T, s_expression>
class UseCase {
public:
    UseCase(std::string&& i, std::string&& e, bool exception = false): input(std::move(i) + "\n"), handle_throw(exception) {
        // TODO: ugly code, this is solve list<X> is list and list<integer> is tuple, this condition indicates that list implementation needs to be improved
        if(!std::is_abstract_v<T>) {
            if constexpr (std::is_same_v<T, list<atom>>
                || std::is_same_v<T, list<boolean>>
                || std::is_same_v<T, list<function_declaration>>
                || std::is_same_v<T, list<param>>
                || std::is_same_v<T, list<s_expression>>) {
                expected_output = "list: " + std::move(e);
            } else {
                mem = std::make_shared<T>();
                expected_output = reinterpret_cast<s_expression*>(mem.get())->get_indicator() + ": " + std::move(e);
            }
        }
    };

    template<typename D> explicit UseCase(const UseCase<D>& u) {
        handle_throw = std::move(u.handle_throw);
        input = std::move(u.input);
        expected_output = std::move(u.expected_output);
        mem = std::move(u.mem);
    }

    bool handle_throw;
    std::string input;
    std::string expected_output;
    std::shared_ptr<T> mem;
};

class SchemeUseCaseBaseTest: public BaseTest,
                             public testing::WithParamInterface<UseCase<s_expression>> {
protected:
    interpreter inter{ts};

    inline void function_define(const std::string& func_name, const std::string& func_definition) {
        is.str(func_definition + "\n");
        inter.scheme();
        ASSERT_TRUE(context.is_in(func_name));
    }

    inline void scheme(UseCase<s_expression>& use_case) {
        std::string expression = use_case.input;
        is.str(expression);

        if(use_case.handle_throw) {
            ASSERT_ANY_THROW(inter.scheme());
            std::cout << use_case.expected_output << std::endl;
        } else {
            inter.scheme();
            ASSERT_THAT(os.str(), HasSubstr(use_case.expected_output));
        }
    }
};

#endif //MYSCHEME_SCHEME_USE_CASE_H
