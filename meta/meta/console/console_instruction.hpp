//
//  console_instruction.hpp
//  meta
//
//  Created by Cosmo Julis on 1/21/22.
//

#ifndef console_instruction_hpp
#define console_instruction_hpp

#include <iostream>
#include "console_register.hpp"
#include "console_code.hpp"
#include "console_manager.hpp"

namespace meta::console {


struct Inst {

    Code code;
    
    Inst() { }
    Inst(std::stack<Reg> & sr) { }
    
    virtual void execute() { }
};

struct Set : Inst {
    Reg id;
    Reg property;
    Reg value;
    
    Set(std::stack<Reg> & sr) {
        if (sr.size() != 3) {
            throw "arg count not match";
        }
        id = sr.top();
        sr.pop();
        property = sr.top();
        sr.pop();
        value = sr.top();
        sr.pop();
    }
    
    void execute() override {
        // TEST:
        std::cout << "set " << id << "." << property << " " << value << std::endl;
    }
};

struct Get : Inst {
    Reg id;
    Reg property;

    Get(std::stack<Reg> & sr) {
        if (sr.size() != 2) {
            throw "arg count not match";
        }
        id = sr.top();
        sr.pop();
        property = sr.top();
        sr.pop();
    }
    
    void execute() override {
        // TEST:
        std::cout << "get " << id << "." << property << std::endl;
        Stack & s = Manager::shared().currentStack();
        s.push("hello");
    }

};

struct Show : Inst {
    Reg value;
    
    Show(std::stack<Reg> & sr) {
        if (sr.size() != 1) {
            throw "arg count not match";
        }
        value = sr.top();
        sr.pop();
    }
    
    void execute() override {
        // TEST:
        std::cout << "show ";
        std::cout << value << std::endl;
    }
};

struct Repeat : Inst {
    Reg count;
    Stack stack;
    
    Repeat(std::stack<Reg> & sr) {
        if (sr.size() != 2) {
            throw "arg count not match";
        }
        count = sr.top();
        sr.pop();
//        stack = sr.top();
//        sr.pop();
    }
    
    void execute() override {
        int n = count.number;
        for (int i = 0; i < n; i++) {
            
        }
    }
};



}

#endif /* console_instruction_hpp */
