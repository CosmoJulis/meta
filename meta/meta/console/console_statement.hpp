//
//  console_statement.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_statement_hpp
#define console_statement_hpp

#include <iostream>
#include <queue>
#include "console_code.hpp"
#include "arg.hpp"

namespace meta::console {

template <typename T>
static constexpr bool NumberSupportType =
    meta::arg::is::any_same_v<T,
                                bool,
                                short,
                                int,
                                long,
                                float,
                                double>;


union Number {
    int64_t integer_m;
    double float_m;
    
    operator int() const {
        if (integer_m != 0) {
            return (int)integer_m;
        } else {
            return float_m;
        }
    }
    
    operator float() const {
        if (float_m != 0) {
            return float_m;
        } else {
            return integer_m;
        }
    }
    
    operator double() const {
        if (float_m != 0) {
            return float_m;
        } else {
            return integer_m;
        }
    }
    
    Number() {
        
    }
    
    Number(int n) {
        integer_m = n;
    }
    
    Number(float n) {
        float_m = n;
    }
    
    Number(double n) {
        float_m = n;
    }
    
    friend std::ostream & operator<<(std::ostream & os, const Number & n) {
        if (n.integer_m != 0) {
            os << n.integer_m;
        } else {
            os << n.float_m;
        }
        return os;
    }
};

enum Type {
    NONE,
    INSTRUCTION,
    NODE,
    NUMBER,
    STRING,
};

//struct Statement;
struct Reg {

    Type type;
    
    union {
        Code code;
        Number number;
    };
    
    std::string string;    // property or value
    
//    Statement statement;
//
//    Reg(const Statement & st);
    
    Reg(const Code & c) : type(INSTRUCTION), code(c) { }
    
    Reg(const Number & n) : type(NUMBER), number(n) { }
    Reg(const int & i) : Reg(Number(i)) { }
    Reg(const float & f) : Reg(Number(f)) { }
    
    Reg(const char * s) : type(STRING), string(s) { }
    Reg(const std::string & str) : type(STRING), string(str) { }
    
    Reg() : type(NONE) { }
    
    friend std::ostream & operator<<(std::ostream & os, const Reg & r) {
        switch (r.type) {
            case NONE:
                os << "null";
                break;
            case INSTRUCTION:
                os << r.code;
                break;
            case NUMBER:
                os << r.number;
                break;
            case STRING:
                os << r.string;
                break;
            default:
                os << "unknown";
                break;
        }
        return os;
    }
    
    //    friend std::ostream & operator<<(std::ostream & os, const Reg & r) {
    //        os << "type: ";
    //        switch (r.type) {
    //            case NONE:
    //                os << "none, value: null";
    //                break;
    //            case INSTRUCTION:
    //                os << "instruction, value: " << r.code;
    //                break;
    //            case NUMBER:
    //                os << "number, value: " << r.number;
    //                break;
    //            case STRING:
    //                os << "string, value: " << r.string;
    //                break;
    //            default:
    //                os << "unknown, value: unknown";
    //                break;
    //        }
    //        return os;
    //    }
        
};


class Statement {
public:
    
    Code code;

    Statement(const Code & c = NOP) : code(c) {

    }

    template <typename T>
    void push(const T & t) {

    }

//    Reg & pop() {
//        Reg & r = _reg_queue.front();
//        _reg_queue.pop();
//        return r;
//    }
//
//    size_t size() const {
//        return _reg_queue.size();
//    }
    
private:
    
    int inst_branch = 0;
    
//    std::queue<Reg> _reg_queue;
};



//Reg::Reg(const Statement & st) : type(NODE), statement(st) { }



}

#endif /* console_statement_hpp */
