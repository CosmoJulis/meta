//
//  console_object.hpp
//  meta
//
//  Created by Cosmo Julis on 1/27/22.
//

#ifndef console_object_hpp
#define console_object_hpp

namespace meta::console {

class object {
public:
    virtual void execute(const std::string & property) = 0;
};

}

#endif /* console_object_hpp */
