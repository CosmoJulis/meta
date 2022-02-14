//
//  console_code.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_code_hpp
#define console_code_hpp

#include <iostream>
#include "../template/arg.hpp"

namespace meta::console {

enum Code {
    NOP,
    SET,
    GET,
    SHOW,
    REPEAT,
    
    // Math
    ADD,
    SUB,
    MUL,
    DIV,
    
    // Operator
    EQUAL,
    LESS,
    GREATER,
    NOT,
//    AND,
//    OR,
//    XOR,

    // Type Cast

    
    
    PAUSE,  // Need Impl
//        play,
//        step,
//        clear,
//        push,
//        pop,
    SLEEP,  // Need Impl
};

std::ostream & operator<<(std::ostream & os, const Code & c);


int CodeBranch(const Code & c);

bool CodeBranchReduce(const Code & c);





enum Type {
    NONE,
    INSTRUCTION,
    NUMBER,
    STRING,
};

std::ostream & operator<<(std::ostream & os, const Type & t);


template <typename T>
static constexpr bool NumberSupportType =
    meta::arg::is::any_same_v<T,
                                bool,
                                int,
                                long,
                                float,
                                double>;

class Number {
public:
    
    operator bool() const {
        switch (_type) {
            case EMPTY:
                throw "Add number uninitialized.";
            case BOOL:
                return _bool;
            case INT:
                return _int;
            case LONG:
                return _long;
            case FLOAT:
                return _float;
            case DOUBLE:
                return _double;
        }
    }
    
    operator int() const {
        switch (_type) {
            case EMPTY:
                throw "Add number uninitialized.";
            case BOOL:
                return _bool;
            case INT:
                return _int;
            case LONG:
                return int(_long);
            case FLOAT:
                return _float;
            case DOUBLE:
                return _double;
        }
    }
    
    operator long() const {
        switch (_type) {
            case EMPTY:
                throw "Add number uninitialized.";
            case BOOL:
                return _bool;
            case INT:
                return _int;
            case LONG:
                return _long;
            case FLOAT:
                return _float;
            case DOUBLE:
                return _double;
        }
    }
    
    operator float() const {
        switch (_type) {
            case EMPTY:
                throw "Add number uninitialized.";
            case BOOL:
                return _bool;
            case INT:
                return _int;
            case LONG:
                return _long;
            case FLOAT:
                return _float;
            case DOUBLE:
                return _double;
        }
    }
    
    operator double() const {
        switch (_type) {
            case EMPTY:
                throw "Add number uninitialized.";
            case BOOL:
                return _bool;
            case INT:
                return _int;
            case LONG:
                return _long;
            case FLOAT:
                return _float;
            case DOUBLE:
                return _double;
        }
    }
    
    Number() { }
    
    Number(const bool & n) : _type(BOOL), _bool(n) { }
    
    Number(const int32_t & n) : _type(INT), _int(n) { }
    
    Number(const int64_t & n) : _type(LONG), _long(n) { }
    
    Number(const float & n) : _type(FLOAT), _float(n) { }
    
    Number(const double & n) : _type(DOUBLE), _double(n) { }
    
    friend std::ostream & operator<<(std::ostream & os, const Number & n) {
        switch (n._type) {
            case EMPTY:
                os << "Uninitialized";
                break;
            case BOOL:
                os << "B(" << (n._bool ? "true" : "false") << ")";
                break;
            case INT:
                os << "I(" << n._int << ")";
                break;
            case LONG:
                os << "L(" << n._long << ")";
                break;
            case FLOAT:
                os << "F(" << n._float << ")";
                break;
            case DOUBLE:
                os << "D(" << n._double << ")";
                break;
        }
        return os;
    }
    
    static bool isSameType(const Number & lhs, const Number & rhs) {
        return lhs.isSameType(rhs);
    }
    
    bool isSameType(const Number & o) const {
        return _type == o._type;
    }
    
    friend Number operator+(const Number & lhs, const Number & rhs) {
        if (!lhs.isSameType(rhs)) {
            throw "Add number must be same type.";
        }
        
        switch (rhs._type) {
            case EMPTY:
                throw "Add number uninitialized.";
            case BOOL:
                throw "Add number type can not be bool.";
            case INT:
                return Number(lhs._int + rhs._int);
            case LONG:
                return Number(lhs._long + rhs._long);
            case FLOAT:
                return Number(lhs._float + rhs._float);
            case DOUBLE:
                return Number(lhs._double + rhs._double);
        }
    }
    
    friend Number operator-(const Number & lhs, const Number & rhs) {
        if (!lhs.isSameType(rhs)) {
            throw "Sub number must be same type.";
        }
        
        switch (rhs._type) {
            case EMPTY:
                throw "Sub number uninitialized.";
            case BOOL:
                throw "Sub number type can not be bool.";
            case INT:
                return Number(lhs._int - rhs._int);
            case LONG:
                return Number(lhs._long - rhs._long);
            case FLOAT:
                return Number(lhs._float - rhs._float);
            case DOUBLE:
                return Number(lhs._double - rhs._double);
        }
    }
    
    friend Number operator*(const Number & lhs, const Number & rhs) {
        if (!lhs.isSameType(rhs)) {
            throw "Mul number must be same type.";
        }
        
        switch (rhs._type) {
            case EMPTY:
                throw "Mul number uninitialized.";
            case BOOL:
                throw "Mul number type can not be bool.";
            case INT:
                return Number(lhs._int * rhs._int);
            case LONG:
                return Number(lhs._long * rhs._long);
            case FLOAT:
                return Number(lhs._float * rhs._float);
            case DOUBLE:
                return Number(lhs._double * rhs._double);
        }
    }
    
    friend Number operator/(const Number & lhs, const Number & rhs) {
        if (!lhs.isSameType(rhs)) {
            throw "Div number must be same type.";
        }
        
        switch (rhs._type) {
            case EMPTY:
                throw "Div number uninitialized.";
            case BOOL:
                throw "Div number type can not be bool.";
            case INT:
                if (rhs._int == 0) throw "Divisor number can not be zero";
                return Number(lhs._int / rhs._int);
            case LONG:
                if (rhs._long == 0) throw "Divisor number can not be zero";
                return Number(lhs._long / rhs._long);
            case FLOAT:
                if (rhs._float == 0) throw "Divisor number can not be zero";
                return Number(lhs._float / rhs._float);
            case DOUBLE:
                if (rhs._double == 0) throw "Divisor number can not be zero";
                return Number(lhs._double / rhs._double);
        }
    }
    
    friend Number operator==(const Number & lhs, const Number & rhs) {
        if (!lhs.isSameType(rhs)) {
            throw "Equal number must be same type.";
        }
        
        switch (rhs._type) {
            case EMPTY:
                throw "Equal number uninitialized.";
            case BOOL:
                throw "Equal number type can not be bool.";
            case INT:
                return Number(lhs._int == rhs._int);
            case LONG:
                return Number(lhs._long == rhs._long);
            case FLOAT:
                return Number(lhs._float == rhs._float);
            case DOUBLE:
                return Number(lhs._double == rhs._double);
        }
    }
    
    friend Number operator<(const Number & lhs, const Number & rhs) {
        if (!lhs.isSameType(rhs)) {
            throw "Less number must be same type.";
        }
        
        switch (rhs._type) {
            case EMPTY:
                throw "Less number uninitialized.";
            case BOOL:
                throw "Less number type can not be bool.";
            case INT:
                return Number(lhs._int < rhs._int);
            case LONG:
                return Number(lhs._long < rhs._long);
            case FLOAT:
                return Number(lhs._float < rhs._float);
            case DOUBLE:
                return Number(lhs._double < rhs._double);
        }
    }
    
    friend Number operator>(const Number & lhs, const Number & rhs) {
        if (!lhs.isSameType(rhs)) {
            throw "Greater number must be same type.";
        }
        
        switch (rhs._type) {
            case EMPTY:
                throw "Greater number uninitialized.";
            case BOOL:
                throw "Greater number type can not be bool.";
            case INT:
                return Number(lhs._int > rhs._int);
            case LONG:
                return Number(lhs._long > rhs._long);
            case FLOAT:
                return Number(lhs._float > rhs._float);
            case DOUBLE:
                return Number(lhs._double > rhs._double);
        }
    }
    
    friend Number operator!(const Number & o) {
        if (o._type != BOOL) {
            throw "Not number must be bool.";
        }
        return Number(!o._bool);
    }
    
    
private:
    
    enum Number_Type {
        EMPTY,
        BOOL,
        INT,
        LONG,
        FLOAT,
        DOUBLE,
    };
    
    Number_Type _type;
    
    union {
        bool _bool;
        int32_t _int;
        int64_t _long;
        float _float;
        double _double;
    };

};



}

#endif /* console_code_hpp */
