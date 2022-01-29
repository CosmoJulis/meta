//
//  console_stack.hpp
//  meta
//
//  Created by Cosmo Julis on 1/25/22.
//

#ifndef console_stack_hpp
#define console_stack_hpp

#include <stack>
#include "console_register.hpp"

namespace meta::console {

class Stack {
public:
    
    
    void push(const Reg & reg) {
        _reg_stack.push(reg);
    }
    
    Reg & pop() {
        Reg & r = _reg_stack.top();
        _reg_stack.pop();
        return r;
    }
    
    size_t size() const {
        return _reg_stack.size();
    }
    
private:
    
    std::stack<Reg> _reg_stack;
};


}

#endif /* console_stack_hpp */
