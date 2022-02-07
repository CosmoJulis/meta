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
    PAUSE,
//        play,
//        step,
//        clear,
//        push,
//        pop,
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
    
    Number(const int & n) {
        integer_m = n;
    }
    
    Number(const float & n) {
        float_m = n;
    }
    
    Number(const double & n) {
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



}

#endif /* console_code_hpp */
