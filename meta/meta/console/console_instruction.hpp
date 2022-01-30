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

namespace meta::console {

class Instruction {
public:
    
    Instruction(Code c) : code(c) { }
    
    template <typename T>
    void push(const T & t) {
        // TODO:
        branch++;
    }
    
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
    
    bool isBranchFull() const {
        return branch == branchCount();
    }
    
protected:
    
    int branch;
    Code code;
    
};




//struct Set :
//    Reg id;
//    Reg property;
//    Reg value;
//
//    Set(Statement & st) {
////        if (sr.size() < 3) {
////            throw "arg count not match";
////        }
////        id = sr.top();
////        sr.pop();
////        property = sr.top();
////        sr.pop();
////        value = sr.top();
////        sr.pop();
//    }
//
//    void execute() override {
//        // TEST:
////        std::cout << "set " << id << "." << property << " " << value << std::endl;
//    }
//};


//struct Get : Instruction<2> {
//    Reg id;
//    Reg property;
//
//    Get(Statement & st) {
////        if (sr.size() < 2) {
////            throw "arg count not match";
////        }
////        id = sr.top();
////        sr.pop();
////        property = sr.top();
////        sr.pop();
//    }
//
//    void execute() override {
//        // TEST:
////        std::cout << "get " << id << "." << property << std::endl;
////        Stack & s = Manager::shared().currentStatement();
////        s.push("name");
//    }
//
//};

//struct Show : Instruction<1> {
//    Reg value;
//
//    Show(Statement & st) {
////        if (sr.size() < 1) {
////            throw "arg count not match";
////        }
////        value = sr.top();
////        sr.pop();
//    }
//
//    void execute() override {
//        // TEST:
////        std::cout << "show ";
////        std::cout << value << std::endl;
//    }
//};

//struct Repeat : Instruction<2> {
//    Reg count;
//
//    Repeat(Statement & st) {
////        if (sr.size() != 2) {
////            throw "arg count not match";
////        }
////        count = sr.top();
////        sr.pop();
//    }
//
//    void execute() override {
////        int n = count.number;
////        for (int i = 0; i < n; i++) {
////
////        }
//    }
//};


}

#endif /* console_instruction_hpp */
