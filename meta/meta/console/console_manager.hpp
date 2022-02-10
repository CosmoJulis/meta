//
//  console_manager.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_manager_hpp
#define console_manager_hpp

#include <map>
#include <stack>
#include <queue>
#include "arg.hpp"
#include "console_instruction.hpp"

namespace meta::console {


class Stack {
public:
    
    size_t size() const {
        return _stack.size();
    }
    
    void push(const int & id) {
        _stack.push(id);
    }
    
    void pop() {
        _stack.pop();
    }
    
    Instruction & top_inst();
    
    int top() const {
        return _stack.top();
    }
    
private:
    
    std::stack<int> _stack;
};


class Map {
public:
    
    int add(const Code & c) {
        int r = _icount;
        Instruction inst = Instruction(c);
        inst.setID(r);
        _map[_icount] = inst;
        _icount++;
        return r;
    }
    
    bool remove(const InstID & id) {
        if (_map.contains(id)) {
            auto & inst = _map[id];
            inst.pop();
            _map.erase(id);
            return true;
        }
        return false;
    }
    
    size_t size() const {
        return _map.size();
    }
    
    bool contains(const InstID & id) const {
        return _map.contains(id);
    }
    
    Instruction & get(InstID id) {
        if (_map.contains(id)) {
            return _map[id];
        } else {
            std::string msg = "Missing instruction id: " + std::to_string(id);
            throw msg;
        }
    }
    
private:
    
    int _icount = 0;
    std::map<int, Instruction> _map;
};

class Queue {
public:
    
    void push(const int & id) {
        _queue.push(id);
    }
    
    const int & front() const {
        return _queue.front();
    }
    
    size_t size() const {
        return _queue.size();
    }
    
    void pop();
    
private:
    
    std::queue<int> _queue;
};

class Manager {
public:
    
    static Manager & shared();
    static void clear();
    
    template <typename T>
    void push(const T t) {
        if constexpr (std::is_same_v<T, Code>) {
            InstID id = _map.add(t);
            if (_stack.size() > 0) {
                _stack.top_inst().push(id);
            } else {
                _queue.push(id);
            }
            _stack.push(id);
        }
        else if constexpr (NumberSupportType<T>) {
            _stack.top_inst().push(Number(t));
        }
        else if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char *>) {
            _stack.top_inst().push(std::string(t));
        }
        else {
            std::cout << meta::arg::list_log<T> << std::endl;
            throw "Type not match.";
        }
        popFullInstruction();
    }
    
    void popFullInstruction() {
        while (_stack.size() > 0) {
            if (_map.contains(_stack.top())) {
                auto & inst = _map.get(_stack.top());
                if (inst.isFullBranch()) {
                    _stack.pop();
                    continue;
                }
            }
            break;
        }
    }
    
    void execute() {
        while (_queue.size() > 0) {
            auto & inst = _map.get(_queue.front());
            inst.execute();
            _queue.pop();
        }
    }
    
    void debug_log() {
        std::cout << "queue size: " << _queue.size() << std::endl;
        std::cout << "stack size: " << _stack.size() << std::endl;
        std::cout << "map size: " << _map.size() << std::endl;
    }

private:
    
    Map _map;
    
    Stack _stack;

    Queue _queue;
    
    friend class Map;
    friend class Stack;
    friend class Queue;

    friend class Instruction;

//    void perform(Statement & s);
    
};

}

#endif /* console_manager_hpp */
