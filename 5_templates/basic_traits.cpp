#include <iostream>

// 5.7. Basic type traits.

template <typename T, typename U>
struct is_same {
	static const bool value = false;
};

template <typename T>
struct is_same<T, T> {
	static const bool value = true;
};

template <typename T, typename U>
const bool is_same_v = is_same<T, U>::value;

template <typename T>
struct remove_const {
	using type = T;
};

template <typename T>
struct remove_const<const T> {
	using type = T;
};

template <typename T>
using remove_const_t = typename remove_const<T>::type;

template <typename T>
struct remove_reference {
	using type = T;
};

template <typename T>
struct remove_reference<T&> {
	using type = T;
};

template <typename T>
using remove_reference_t = typename remove_reference<T>::type;

template <typename T> 
void g() {
	remove_const_t<T> x;
}

template <typename T, typename U>
void f() {
	//..

	if (is_same_v<T, U>) {
	
	}
}
