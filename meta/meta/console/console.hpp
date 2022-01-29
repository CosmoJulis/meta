//
//  console.hpp
//  meta
//
//  Created by Cosmo Julis on 1/25/22.
//

#ifndef console_hpp
#define console_hpp

#include <iostream>
#include <stack>
#include <queue>

namespace meta::console {

class Object {
    
};

enum Code {
    NOP,
    SET,
    GET,
    SHOW,
    REPEAT,
//        pause,
//        play,
//        step,
//        clear,
//        push,
//        pop,
};

std::ostream & operator<<(std::ostream & os, const Code & c) {
    switch (c) {
        case NOP:
            os << "nop";
            break;
        case SET:
            os << "set";
            break;
        case GET:
            os << "get";
            break;
        case SHOW:
            os << "show";
            break;
        case REPEAT:
            os << "repeat";
            break;
        default:
            os << "unknown";
            break;
    }
    return os;
}



struct Reg;
struct Inst {
    
    Code code;
    
    Inst() { }
    Inst(std::stack<Reg> & sr);
    
    virtual void execute() { }
};



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
    NUMBER,
    STRING,
};

struct Reg {
    
    Type type;
    
    union {
        Code code;
        Number number;
    };
    
    std::string string;    // property or value
    
    Reg(const Code & c) : type(INSTRUCTION), code(c) { }
    
    Reg(const Number & n) : type(NUMBER), number(n) { }
    Reg(const int & i) : Reg(Number(i)) { }
    Reg(const float & f) : Reg(Number(f)) { }
    
    Reg(const char * s) : type(STRING), string(s) { }
    Reg(const std::string & str) : type(STRING), string(str) { }
    
    Reg() : type(NONE) { }
    
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
    
    
};

Inst::Inst(std::stack<Reg> & sr) { }

class Stack {
public:
    
    void push(const Reg & reg) {
        if (reg.type == INSTRUCTION && reg.code == REPEAT) {
            
        }
        _reg_stack.push(reg);
    }
    
    Reg & pop() {
        Reg & r = _reg_stack.top();
        _reg_stack.pop();
        return r;
    }
    
    size_t size() const {
        return _reg_stack.size();
    }
    
private:
    
    Stack _repeat;
    std::stack<Reg> _reg_stack;
};


class Queue {
public:
    
    void push(const Stack & s) {
        _stack_queue.push(s);
    }
    
    Stack & front() {
        return _stack_queue.front();
    }
    
    void pop() {
        _stack_queue.pop();
    }

    size_t size() const {
        return _stack_queue.size();
    }
    
private:
    std::queue<Stack> _stack_queue;
};
















class Manager {
public:
    
    static Manager & shared() {
        static Manager * pm = new Manager();
        return *pm;
    }
    
    void push(const Stack & stack) {
        _queue.push(stack);
    }
    
    void pop() {
        _queue.pop();
    }
    
    Stack & currentStack() {
        return _queue.front();
    }
    
    size_t size() const {
        return _queue.size();
    }
    
    void execute() {
        while (size() > 0) {
            run(currentStack());
            pop();
        }
    }
    


private:
    
    Queue _queue;
    
    void run(Stack & s);
    
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

void Manager::run(Stack & s) {
    while (s.size() > 0) {
        std::stack<Reg> inst_stack;
        
        Reg r;
        do {
            r = s.pop();
            inst_stack.push(r);
        } while (r.type != INSTRUCTION);
        
        r = inst_stack.top();
        inst_stack.pop();
        switch (r.code) {
            case NOP:
                break;
            case SET:
                Set(inst_stack).execute();
                break;
            case GET:
                Get(inst_stack).execute();
                break;
            case SHOW:
                Show(inst_stack).execute();
                break;
            case REPEAT:
                break;
            default:
                break;
        }
        
    }
}


}


#endif /* console_hpp */
