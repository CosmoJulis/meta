//
//  test_reflection_ts.cpp
//  meta
//
//  Created by Cosmo Julis on 1/26/22.
//

// https://cplusplus.github.io/reflection-ts/draft.pdf
// https://en.cppreference.com/w/cpp/keyword/reflexpr


/*
#include <experimental/reflect>
#include <iostream>
#include <string>

class Person {
public:
    int age;
    int name;
    void set_age(int age) {
        std::cout << "set_age(" << age << ")" << std::endl;
    }
    void set_name(std::string name) {
        std::cout << "set_name(" << name << ")" << std::endl;
    }
};



template <auto begin, auto end, typename ObjectSequence>
void constexpr_for(Person * p) {
    if constexpr (begin < end) {
        using namespace std::experimental::reflect;
        using meta_func = get_element_t<begin, ObjectSequence>;

        auto func_name = get_display_name_v<meta_func>;
        std::cout << begin << ": " << func_name << std::endl;

        auto funcPtr = get_pointer_v<meta_func>;
        if constexpr (std::is_same_v<decltype(funcPtr), decltype(&Person::set_age)>) {
            (p->*funcPtr)(18);
        } else {
            (p->*funcPtr)("Girl");
        }
        constexpr_for<begin + 1, end, ObjectSequence>(p);
    }
}

void init_reflect(Person * p) {
    using namespace std::experimental::reflect;
    using meta_info_t = reflexpr(Person);
    using meta_funcs_seq = get_public_member_functions_t<meta_info_t>;
    constexpr auto funcs_size = get_size_v<meta_funcs_seq>;
    std::cout << "member func count = " << funcs_size << std::endl;
    constexpr_for<0, funcs_size, meta_funcs_seq>(p);
}



int main() {
    Person p;
    init_reflect(&p);


    


    return 0;
}

*/
