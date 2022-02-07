//
//  console_object.hpp
//  meta
//
//  Created by Cosmo Julis on 1/30/22.
//

#ifndef console_object_hpp
#define console_object_hpp

namespace meta::console {

class Object {
public:
    
    static Object & find(int id) {
        static Object * po = new Object(id);
        return *po;
    }
    
    static Object & find(const std::string & name) {
        static Object * po = new Object(0);
        return *po;
    }
    
    static Object & find(const Reg & r) {
        switch (r.type()) {
            case NUMBER:
                return find(int(r.get_number()));
            case STRING:
                return find(r.get_string());
            default:
                throw "Not support type.";
        }
    }
    
    int id;
    
    Object(int obj_id = -1) : id(obj_id) { }
    
    
    virtual void set(const std::string & key, const Reg & value) {
        
    }
    
    virtual Reg get(const std::string & key) {
        Reg r;
        return r;
    }
    
};

}

#endif /* console_object_hpp */
