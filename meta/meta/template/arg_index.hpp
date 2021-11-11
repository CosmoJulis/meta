//
//  arg_index.hpp
//  meta
//
//  Created by Cosmo Julis on 11/11/21.
//

#ifndef arg_index_hpp
#define arg_index_hpp

#include <stdio.h>

namespace meta {

class arg_index_impl_placeholder {
private:
    arg_index_impl_placeholder() { }
};

template<typename T, int index, typename F, typename ... Args>
struct arg_index_impl {
    static constexpr int getIndex() {
        if constexpr (std::is_same_v<T, F>) {
            return index + 1;
        } else {
            return arg_index_impl<T, index + 1, Args...>::getIndex();
        }
    }
};


template<typename T, int index, typename F>
struct arg_index_impl<T, index, F> {
    static constexpr int getIndex() {
        if constexpr (std::is_same_v<T, F>) {
            return index + 1;
        } else {
            return -1;
        }
    }
};

template<typename T, int idx, typename F, typename J>
struct arg_index_impl<T, idx, F, J> {
    static constexpr int getIndex() {
        if constexpr (std::is_same_v<T, F>) {
            return idx + 1;
        } else {
            return arg_index_impl<T, idx + 1, J>::getIndex();
        }
    }
};

/*
 *  return T of Args... first index
 *  -1 no exist
 *  获取 T 在 Args... 中的第一个位置
 *  -1 不存在
 */
template<typename T, typename... Args>
struct arg_index {
    using IndexArgsType = std::conditional_t
                            <
                                sizeof...(Args) == 0,
                                arg_index_impl<T, -2, arg_index_impl_placeholder>,
                                arg_index_impl<T, -2, arg_index_impl_placeholder, Args...>
                            >;
    static constexpr int index = IndexArgsType::getIndex();
};


}

#endif /* arg_index_hpp */
