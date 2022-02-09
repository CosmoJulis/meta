//
//  console_instruction.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_instruction_hpp
#define console_instruction_hpp

#include <iostream>
#include <vector>
#include "console_code.hpp"


namespace meta::console {

class Reg {
public:
    
    static Reg & PLACE() {
        static Reg * r = new Reg();
        return *r;
    };

    
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
    
    int _inst_id = -1;
    Number _number;
    std::string _string;
    
    Type _type = NONE;
};

class Instruction {
public:
    
    Instruction() { }
    
    Instruction(const Code & c) : code(c) { }
    
    ~Instruction() { }
    
    template <typename T>
    void push(const T & t) {
        auto b = Reg();
        b.set(t);
        _branchs.push_back(b);
    }

    void pop();

    
    Reg execute();
    
    bool isFullBranch() const {
        return _branchs.size() == CodeBranch(code);
    }
    
    void setID(int inst_id) {
        _id = inst_id;
    }
    
protected:

    Code code;
    
    std::vector<Reg> _branchs;
    
    int _id = -1;
    

};

}

#endif /* console_instruction_hpp */
