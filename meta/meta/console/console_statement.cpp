//
//  console_statement.cpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#include "console_statement.hpp"
#include "console_register.hpp"

using namespace meta::console;

void Statement::push(const Reg & reg) {
    if (reg.type == INSTRUCTION) {
        
    }
    _reg_stack.push(reg);
}

Reg & Statement::pop() {
    Reg & r = _reg_stack.top();
    _reg_stack.pop();
    return r;
}

size_t Statement::size() const {
    return _reg_stack.size();
}
