//
//  console_statement.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_statement_hpp
#define console_statement_hpp

#include <stack>

namespace meta::console {

struct Reg;
class Statement {
public:
    
    void push(const Reg & reg);
    
    Reg & pop();
    
    size_t size() const;
    
private:
    
    std::stack<Reg> _reg_stack;
};

}

#endif /* console_statement_hpp */
