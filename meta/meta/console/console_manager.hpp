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
    
    int add(const Instruction & inst) {
        int r = _icount;
        _map[_icount] = inst;
        _icount++;
        return r;
    }
    
    bool remove(const int & id) {
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
    
    bool contains(const int & id) const {
        return _map.contains(id);
    }
    
    Instruction & get(int id) {
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
            int inst_id = _map.add(Instruction(t));
            if (_stack.size() > 0) {
                _stack.top_inst().push(inst_id);
            } else {
                _queue.push(inst_id);
            }
            _stack.push(inst_id);
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
                auto & i = _map.get(_stack.top());
                if (i.isFullBranch()) {
                    _stack.pop();
                    continue;
                }
            }
            break;
        }
    }
    
    void execute() {
        std::cout << "queue size: " << _queue.size() << std::endl;
        std::cout << "stack size: " << _stack.size() << std::endl;
        while (_queue.size() > 0) {
            std::cout << "queue pop\n";
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
