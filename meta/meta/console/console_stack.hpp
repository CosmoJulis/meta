//
//  console_stack.hpp
//  meta
//
//  Created by Cosmo Julis on 1/25/22.
//

#ifndef console_stack_hpp
#define console_stack_hpp

#include <stack>
#include "console_instruction.hpp"

namespace meta::console {

class Stack {
public:

    static Stack & get_manager() {
        static Stack * ps = new Stack();
        return *ps;
    }
    
    std::stack<Reg> reg_stack;
    
    void push(const Reg & reg) {
        reg_stack.push(reg);
    }

//    void push(const std::string & s) {
//        push(s);
//    }
    
    Reg & pop() {
        Reg & r = reg_stack.top();
        reg_stack.pop();
        return r;
    }
};


}

#endif /* console_stack_hpp */
