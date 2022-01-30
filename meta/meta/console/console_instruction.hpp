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
#include "console_statement.hpp"
#include "console_register.hpp"

namespace meta::console {

struct Instruction {
    
    Code code;
    
    Instruction() { }
    
    virtual void execute() { }
};

struct Set : Instruction {
    Reg id;
    Reg property;
    Reg value;
    
    Set(Statement & st) {
//        if (sr.size() < 3) {
//            throw "arg count not match";
//        }
//        id = sr.top();
//        sr.pop();
//        property = sr.top();
//        sr.pop();
//        value = sr.top();
//        sr.pop();
    }
    
    void execute() override {
        // TEST:
//        std::cout << "set " << id << "." << property << " " << value << std::endl;
    }
};

struct Get : Instruction {
    Reg id;
    Reg property;

    Get(Statement & st) {
//        if (sr.size() < 2) {
//            throw "arg count not match";
//        }
//        id = sr.top();
//        sr.pop();
//        property = sr.top();
//        sr.pop();
    }
    
    void execute() override {
        // TEST:
//        std::cout << "get " << id << "." << property << std::endl;
//        Stack & s = Manager::shared().currentStatement();
//        s.push("name");
    }

};

struct Show : Instruction {
    Reg value;
    
    Show(Statement & st) {
//        if (sr.size() < 1) {
//            throw "arg count not match";
//        }
//        value = sr.top();
//        sr.pop();
    }
    
    void execute() override {
        // TEST:
//        std::cout << "show ";
//        std::cout << value << std::endl;
    }
};

struct Repeat : Instruction {
    Reg count;
    
    Repeat(Statement & st) {
//        if (sr.size() != 2) {
//            throw "arg count not match";
//        }
//        count = sr.top();
//        sr.pop();
    }
    
    void execute() override {
//        int n = count.number;
//        for (int i = 0; i < n; i++) {
//            
//        }
    }
};


}

#endif /* console_instruction_hpp */
