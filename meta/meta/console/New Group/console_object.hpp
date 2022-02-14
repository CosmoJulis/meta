//
//  console_object.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_object_hpp
#define console_object_hpp

#include <unordered_map>
#include "console_instruction.hpp"

namespace meta::console {

class Object {
public:
    
    int id = -1;
    
    Object(int obj_id) : id(obj_id) { }
    
    
    virtual void set(const std::string & key, const Reg & value) { };
    
    virtual Reg get(const std::string & key) { return Reg(); };
    
    virtual void log() {
        std::cout << "Object\n";
    }
};

class Pool {
public:
    
    static Pool & shared();
    static void clear();
    
    std::unordered_map<int, std::shared_ptr<Object>> obj_id_map;
    std::unordered_map<std::string, std::shared_ptr<Object>> obj_name_map;
    
    Object & find(int id) {
        return *obj_id_map[id];
    }
    
    Object & find(const std::string & name) {
        return *obj_name_map[name];
    }
    
    Object & find(const Reg & r) {
        switch (r.type()) {
            case NUMBER:
                return find(int(r.get_number()));
            case STRING:
                return find(r.get_string());
            default:
                throw "Not support type.";
        }
    }
    
};

}

#endif /* console_object_hpp */
