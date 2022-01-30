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
    int id;
    
    Object(int obj_id = -1) : id(obj_id) { }
};

}

#endif /* console_object_hpp */
