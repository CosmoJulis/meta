//
//  arg_is.hpp
//  meta
//
//  Created by Cosmo Julis on 11/13/21.
//

#ifndef arg_is_hpp
#define arg_is_hpp


#include <vector>


namespace meta {

namespace arg {

namespace is {

template<typename T, typename Allocator>
struct _vector {
    static constexpr bool value = false;
};

template<typename T, typename Allocator>
struct _vector<std::vector<T>, Allocator> {
    static constexpr bool value = true;
};

template<typename T, typename Allocator = std::allocator<T>>
static constexpr bool vector = _vector<T, Allocator>::value;





}

}

}

#endif /* arg_is_hpp */
