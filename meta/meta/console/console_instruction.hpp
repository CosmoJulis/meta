//
//  console_instruction.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_instruction_hpp
#define console_instruction_hpp

#include <iostream>
#include "console_code.hpp"
//#include "console_statement.hpp"

namespace meta::console {

class Instruction {
public:
    
    Instruction() { std::cout << "Instruction\n"; }
    
    Instruction(const Code & c) : code(c) { std::cout << "Instruction " << c << std::endl; }
    
    ~Instruction() { std::cout << "~Instruction\n"; }
    
    template <typename T>
    void push(const T & t) {
//        if constexpr (std::is_same_v<T, int>) {
//            
//        }
//        else if constexpr (std::is_same_v<T, Number>) {
//
//        }
//        else if constexpr (std::is_same_v<T, std::string>) {
//
//        }
//        else {
//            std::cout << meta::arg::list_log<T> << std::endl;
//            throw "Type not match.";
//        }
        branch++;
    }
    
    void pop();
    
    void execute() {
        switch (code) {
            case SET:
                
                break;
            case GET:
                
                break;
            case SHOW:
                
                break;
            case REPEAT:
                
                break;
                
            case PAUSE:
                
                break;
            default:
                break;
        }
    }
    
    int branchCount() const {
        switch (code) {
            case SET:
                return 3;
            case GET:
                return 2;
            case SHOW:
                return 1;
            case REPEAT:
                return 2;
            case PAUSE:
                return 0;
            default:
                return 0;
        }
    }
    
    bool isFullBranch() const {
        return branch == branchCount();
    }
    
protected:
    
    int branch = 0;
    Code code;
    
};

}

#endif /* console_instruction_hpp */
