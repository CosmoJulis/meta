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

class Register {
public:
    
    template <typename T>
    void set(const T & t) {
        if constexpr (std::is_same_v<T, int>) {
            _type = INSTRUCTION;
            _inst_id = t;
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
            _type = NONE;
            std::cout << meta::arg::list_log<T> << std::endl;
            throw "Type not match.";
        }
    }
    
    Type type() const {
        return _type;
    }
    
    int get_inst_id() const {
        return _inst_id;
    }
    
    Number get_number() const {
        return _number;
    }
    
    std::string get_string() const {
        return _string;
    }
    
private:
    
    int _inst_id;
    Number _number;
    std::string _string;
    
    Type _type;
};

class Instruction {
public:
    
    Instruction() { }
    
    Instruction(const Code & c) : code(c) { }
    
    ~Instruction() { }
    
    template <typename T>
    void push(const T & t) {
        auto reg = Register();
        reg.set(t);
        _regs.push_back(reg);
//        branch++;
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
        return _regs.size() == branchCount();
    }
    
protected:
    
//    int branch = 0;
    Code code;
    
    std::vector<Register> _regs;
    
};

}

#endif /* console_instruction_hpp */
