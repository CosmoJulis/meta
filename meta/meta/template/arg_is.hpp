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

#pragma mark - is vector
template <typename T, typename Allocator>
struct _vector {
    static inline constexpr bool value = false;
};

template <typename T, typename Allocator>
struct _vector<std::vector<T>, Allocator> {
    static inline constexpr bool value = true;
};

template <typename T, typename Allocator = std::allocator<T>>
static inline constexpr bool vector_v = _vector<T, Allocator>::value;



#pragma mark - variadic template is

#pragma mark - Logic
struct And { };
struct Or { };


#pragma mark - is base of
template <typename L, typename Base, typename T, typename ... Args>
struct _base_of {
    static inline constexpr bool value =
        std::is_same_v<L, And> ?
            _base_of<L, Base, T>::value && _base_of<L, Base, Args...>::value
            :
            _base_of<L, Base, T>::value || _base_of<L, Base, Args...>::value;
};

template <typename L, typename Base, typename T>
struct _base_of<L, Base, T> {
    static inline constexpr bool value = std::is_base_of_v<Base, T>;
};

template <typename Base, typename ... Args>
static inline constexpr bool all_base_of_v = _base_of<And, Base, Args...>::value;

template <typename Base, typename ... Args>
static inline constexpr bool any_base_of_v = _base_of<Or, Base, Args...>::value;


#pragma mark - is const
template <typename L, typename T, typename ... Args>
struct _const {
    static inline constexpr bool value =
        std::is_same_v<L, And> ?
            _const<L, T>::value && _const<L, Args...>::value
            :
            _const<L, T>::value || _const<L, Args...>::value;
};

template <typename L, typename T>
struct _const<L, T> {
    static inline constexpr bool value = std::is_const_v<T>;
};

template <typename ... Args>
static inline constexpr bool all_const_v = _const<And, Args...>::value;

template <typename ... Args>
static inline constexpr bool any_const_v = _const<Or, Args...>::value;


#pragma mark - is reference
template <typename L, typename T, typename ... Args>
struct _reference {
    static inline constexpr bool value =
        std::is_same_v<L, And> ?
            _reference<L, T>::value && _reference<L, Args...>::value
            :
            _reference<L, T>::value || _reference<L, Args...>::value;
};

template <typename L, typename T>
struct _reference<L, T> {
    static inline constexpr bool value = std::is_reference_v<T>;
};

template <typename ... Args>
static inline constexpr bool all_reference_v = _reference<And, Args...>::value;

template <typename ... Args>
static inline constexpr bool any_reference_v = _reference<Or, Args...>::value;


#pragma mark - is pointer
template <typename L, typename T, typename ... Args>
struct _pointer {
    static inline constexpr bool value =
        std::is_same_v<L, And> ?
            _pointer<L, T>::value && _pointer<L, Args...>::value
            :
            _pointer<L, T>::value || _pointer<L, Args...>::value;
};

template <typename L, typename T>
struct _pointer<L, T> {
    static inline constexpr bool value = std::is_pointer_v<T>;
};

template <typename ... Args>
static inline constexpr bool all_pointer_v = _pointer<And, Args...>::value;

template <typename ... Args>
static inline constexpr bool any_pointer_v = _pointer<Or, Args...>::value;


}

}

}

#endif /* arg_is_hpp */
