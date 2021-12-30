//
//  arg_is.hpp
//  meta
//
//  Created by Cosmo Julis on 11/13/21.
//

#ifndef arg_is_hpp
#define arg_is_hpp


#include <vector>


/*
 *  || && ?: is not meta operator
 *  fix
 */

namespace meta::arg::is {

#pragma mark - is template
/*
 *  not work for
 *      template <int c> { } not type template class
 *      neither
 *      template <typename T, int c> { } mix template class
 */
template <typename T>
struct template_class {
    template <typename _T>
    struct _impl : std::false_type { };
    
    template <template <typename ...> typename C, typename ... Args>
    struct _impl<C<Args...>> : std::true_type { };
    
    static inline constexpr bool value = _impl<T>::value;
};


#pragma mark - is class template
template <template<typename...> typename C, typename T, typename ... Args>
struct class_template {
    template <typename _T, typename ... _Args>
    struct _impl : std::false_type { };
    
    template <typename _T, typename ... _Args>
    struct _impl<C<_T, _Args...>> : std::true_type { };
    
    static inline constexpr bool value = _impl<T, Args...>::value;
};

#pragma mark - is vector
template <typename T>
static inline constexpr bool vector_v = class_template<std::vector, T>::value;






#pragma mark - variadic template is

#pragma mark - Logic
struct And { };
struct Or { };


#pragma mark - is base of

template <typename L, typename Base, typename ... Args>
struct base_of {
    
    template <typename _L, typename _Base, typename _T, typename ... _Args>
    struct _impl {
        static inline constexpr bool value = [](){
            if constexpr (std::is_same_v<_L, And>) {
                return _impl<_L, _Base, _T>::value && _impl<_L, _Base, _Args...>::value;
            } else {
                return _impl<_L, _Base, _T>::value || _impl<_L, _Base, _Args...>::value;
            }
        }();
    };

    template <typename _L, typename _Base, typename _T>
    struct _impl<_L, _Base, _T> {
        static inline constexpr bool value = std::is_base_of_v<_Base, _T>;
    };
    
    static inline constexpr bool value = [](){
        if constexpr (sizeof...(Args) > 1) {
            return _impl<L, Base, Args...>::value;
        } else {
            return true;
        }
    }();
};

template <typename Base, typename ... Args>
static inline constexpr bool all_base_of_v = base_of<And, Base, Args...>::value;

template <typename Base, typename ... Args>
static inline constexpr bool any_base_of_v = base_of<Or, Base, Args...>::value;



#pragma mark - is same

template <typename L, typename ... Args>
struct same {

    template <typename _L, typename _Same, typename _T, typename ... _Args>
    struct _impl {
        static inline constexpr bool value = [](){
            if constexpr (std::is_same_v<_L, And>) {
                return _impl<_L, _Same, _T>::value && _impl<_L, _Same, _Args...>::value;
            } else {
                return _impl<_L, _Same, _T>::value || _impl<_L, _Same, _Args...>::value;
            }
        }();
    };

    template <typename _L, typename _Same, typename _T>
    struct _impl<_L, _Same, _T> {
        static inline constexpr bool value = std::is_same_v<_Same, _T>;
    };
    
    static inline constexpr bool value = [](){
        if constexpr (sizeof...(Args) > 1) {
            return _impl<L, Args...>::value;
        } else {
            return true;
        }
    }();
};

template <typename ... Args>
static inline constexpr bool all_same_v = same<And, Args...>::value;

template <typename ... Args>
static inline constexpr bool any_same_v = same<Or, Args...>::value;




#pragma mark - is const
template <typename L, typename ... Args>
struct const_ {
    template <typename _L, typename _T, typename ... _Args>
    struct _impl {
        static inline constexpr bool value = [](){
            if constexpr (std::is_same_v<_L, And>) {
                return _impl<_L, _T>::value && _impl<_L, _Args...>::value;
            } else {
                return _impl<_L, _T>::value || _impl<_L, _Args...>::value;
            }
        }();
    };

    template <typename _L, typename _T>
    struct _impl<_L, _T> {
        static inline constexpr bool value = std::is_const_v<_T>;
    };
    
    static inline constexpr bool value = _impl<L, Args...>::value;
};


template <typename ... Args>
static inline constexpr bool all_const_v = const_<And, Args...>::value;

template <typename ... Args>
static inline constexpr bool any_const_v = const_<Or, Args...>::value;



#pragma mark - is reference
template <typename L, typename ... Args>
struct reference {
    template <typename _L, typename _T, typename ... _Args>
    struct _impl {
        static inline constexpr bool value = [](){
            if constexpr (std::is_same_v<_L, And>) {
                return _impl<_L, _T>::value && _impl<_L, _Args...>::value;
            } else {
                return _impl<_L, _T>::value || _impl<_L, _Args...>::value;
            }
        }();
    };

    template <typename _L, typename _T>
    struct _impl<_L, _T> {
        static inline constexpr bool value = std::is_reference_v<_T>;
    };
    
    static inline constexpr bool value = _impl<L, Args...>::value;
};

template <typename ... Args>
static inline constexpr bool all_reference_v = reference<And, Args...>::value;

template <typename ... Args>
static inline constexpr bool any_reference_v = reference<Or, Args...>::value;




#pragma mark - is pointer
template <typename L, typename ... Args>
struct pointer {
    template <typename _L, typename _T, typename ... _Args>
    struct _impl {
        static inline constexpr bool value = [](){
            if constexpr (std::is_same_v<_L, And>) {
                return _impl<_L, _T>::value && _impl<_L, _Args...>::value;
            } else {
                return _impl<_L, _T>::value || _impl<_L, _Args...>::value;
            }
        }();
    };

    template <typename _L, typename _T>
    struct _impl<_L, _T> {
        static inline constexpr bool value = std::is_pointer_v<_T>;
    };
    
    static inline constexpr bool value = _impl<L, Args...>::value;
};


template <typename ... Args>
static inline constexpr bool all_pointer_v = pointer<And, Args...>::value;

template <typename ... Args>
static inline constexpr bool any_pointer_v = pointer<Or, Args...>::value;


}

#endif /* arg_is_hpp */
