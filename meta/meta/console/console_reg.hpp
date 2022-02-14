//
//  console_reg.hpp
//  meta
//
//  Created by Cosmo Julis on 2/10/22.
//

#ifndef console_reg_hpp
#define console_reg_hpp

#include <iostream>
#include "console_type.hpp"

namespace meta::console {

using ID = instruction::ID;

class Reg {
public:
    
    enum Type {
        NONE,
        INSTRUCTION,
        NUMBER,
        STRING,
    };
    
    friend std::ostream & operator<<(std::ostream & os, const Type & t) {
        switch (t) {
            case NONE:
                os << "none";
                break;
            case INSTRUCTION:
                os << "instruction";
                break;
            case NUMBER:
                os << "number";
                break;
            case STRING:
                os << "string";
                break;
            default:
                os << "unknown";
                break;
        }
        return os;
    }
    
    Reg() { }
    
    template <typename T>
    Reg(const T & t) {
        if constexpr (std::is_same_v<T, ID>) {
            _type = INSTRUCTION;
            _inst = t;
        }
        else if constexpr (std::is_same_v<T, Number>) {
            _type = NUMBER;
            _number = t;
        }
        else if constexpr (std::is_same_v<T, std::string>) {
            _type = STRING;
            _string = t;
        }
        else {
            std::cout << meta::arg::list_log<T> << std::endl;
            throw "Type not match.";
        }
    }
    
    Type type() const {
        return _type;
    }
    
    ID get_inst() const {
        return _inst;
    }
    
    Number get_number() const {
        return _number;
    }
    
    std::string get_string() const {
        return _string;
    }
    
private:
    
    ID _inst;
    Number _number;
    std::string _string;
    
    Type _type = NONE;
};


    
}


#endif /* console_reg_hpp */
