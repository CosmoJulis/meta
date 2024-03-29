//
//  arg_position.hpp
//  meta
//
//  Created by Cosmo Julis on 11/11/21.
//

#ifndef arg_position_hpp
#define arg_position_hpp

#include <type_traits>

/*
 * TODO: ignore const
 *       ignore reference
 *       ignore const | reference
 */

namespace meta::arg {


/*
 *  Get first index T at Args...
 *  -1 no exist
 *  获取 T 在 Args... 中的第一个位置
 *  -1 不存在
 */
template <typename T, typename ... Args>
struct index {
    
    template <typename _T, int _index, typename _F, typename ... _Args>
    struct _impl {
        static constexpr int getIndex() {
            if constexpr (std::is_same_v<_T, _F>) {
                return _index + 1;
            } else {
                return _impl<_T, _index + 1, _Args...>::getIndex();
            }
        }
    };

    template <typename _T, int _index, typename _F>
    struct _impl<_T, _index, _F> {
        static constexpr int getIndex() {
            if constexpr (std::is_same_v<_T, _F>) {
                return _index + 1;
            } else {
                return -1;
            }
        }
    };

    template <typename _T, int _idx, typename _F, typename _J>
    struct _impl<_T, _idx, _F, _J> {
        static constexpr int getIndex() {
            if constexpr (std::is_same_v<_T, _F>) {
                return _idx + 1;
            } else {
                return _impl<_T, _idx + 1, _J>::getIndex();
            }
        }
    };
    
    
    struct _placeholder { };
    
    using args_type = std::conditional_t
                            <
                                sizeof...(Args) == 0,
                                _impl<T, -2, _placeholder>,
                                _impl<T, -2, _placeholder, Args...>
                            >;
    
    static inline constexpr int value = args_type::getIndex();
};


/*
 *  Get first index T at Args...
 *  -1 no exist
 *  获取在Args...中index位置的类型
 *  -1 不存在
 */
template <int index, typename ... Args>
struct of {
    
    static_assert(index < sizeof...(Args), "Index out of bounds with args.");
    
    template <int _index, int _idx, typename _T, typename ... _Args>
    struct _impl {
        
        using _type = std::conditional_t<_index == _idx, _T, typename _impl<_index, _idx+1, _Args...>::_type>;
        
        static inline _type && _get_value(_T && t, _Args && ... args) {
            if constexpr (_index == _idx) {
                return std::forward<_T>(t);
            } else {
                return _impl<_index, _idx + 1, _Args...>::_get_value(std::forward<_Args>(args)...);
            }
        }
        
        static inline const _type _get_value(const _T & t, const _Args & ... args) {
            if constexpr (_index == _idx) {
                return t;
            } else {
                return _impl<_index, _idx + 1, _Args...>::_get_value(args...);
            }
        }
        
    };
    
    template <int _index, int _idx, typename _T>
    struct _impl<_index, _idx, _T> {
        
        using _type = _T;
        
        static inline _type && _get_value(_T && t) {
            return std::forward<_T>(t);
        }
        
        static inline const _type _get_value(const _T & t) {
            return t;
        }
    };
        
    using type = typename _impl<index, 0, Args...>::_type;
    
    static inline type && get_value(Args && ... args) {
        return _impl<index, 0, Args...>::_get_value(std::forward<Args>(args)...);
    }
    
    static inline const type get_value(const Args & ... args) {
        return _impl<index, 0, Args...>::_get_value(args...);
    }
};






}

#endif /* arg_position_hpp */
