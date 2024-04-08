#include <iostream>
#include <vector>
#include <type_traits>

// XV. Template metaprogramming, SFINAE and concepts.

// 15.1. Basic primitives for template metaprogramming.

template <typename T, T x>
struct integral_constant {
	static const T value = x;
};

template <bool B>
using bool_constant = integral_constant<bool, B>;

using true_type = bool_constant<true>;

using false_type = bool_constant<false>;

template <typename T, typename U>
struct is_same: false_type {};

template <typename T>
struct is_same<T, T>: true_type {};

/*
template <typename T1, typename T2, typename... Ts>
struct conjuction: conjuction<conjuction<T1, T2>, conjuction<Ts...>> {};

template <typename T, typename U>
struct conjuction<T, U>: bool_constant<T::value && U::value> {};

template <typename T>
struct conjuction<T>: bool_constant<T::value> {};
*/

template <typename T>
struct type_identity {
	using type = T;
};

template <typename T>
struct remove_reference: type_identity<T> {};

template <typename T>
struct remove_reference<T&>: type_identity<T> {};

template <typename T>
struct remove_reference<T&&>: type_identity<T> {};

// 15.2. SFINAE idiom, enable_if.
// Substitution Failure Is Not An Error!

template <typename T, typename U = T::value_type>
void f(T x) {
	std::cout << 1;
}

void f(...) {
	std::cout << 2;
}

template <bool B, typename T>
struct enable_if {};

template <typename T>
struct enable_if<true, T>: type_identity<T> {};

template <bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;

template <typename T, enable_if_t<std::is_class_v<T>, bool> = true>
void g(T x) {
	std::cout << 1;
}

template <typename T, enable_if_t<!std::is_class_v<T>, bool> = false>
void g(T x) {
	std::cout << 2;
}

// 15.3. Check of method presence in a class.

template <typename T>
T&& declval();

template <typename T, typename... Args>
auto hmc_helper(int) -> integral_constant<
			decltype(declval<T>().construct(declval<Args>()...) bool()), // comma-trick
			true
		>;

template <typename T, typename ...Args>
auto hmc_helper(...) -> false_type;

template <typename T, typename... Args>
struct has_method_construct: decltype(hmc_helper<T, Args...>(0)) {};

template <typename T, typename... Args>
const bool has_method_construct_v = has_method_construct<T, Args...>::value;

// 15.4. is_nothrow_move_constructible, move_if_noexcept.

template <typename T, typename... Args>
auto inthmc_helper(int, enable_if_t<noexcept(T(declval<T>())), bool> = true ) 
	-> true_type;
	//-> integral_constant<
	//		decltype(declval<T>().construct(declval<Args>()...) bool()), // comma-trick
	//		true
	//	>;

template <typename T, typename... Args>
auto intmc_helper(...) -> false_type;

template <typename T>
auto move_if_noexcept(T& x) 
	-> std::conditional_t<
		std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>, 
		T&&, 
		const T&
	>
{
	return std::move(x);
}

// 15.5 is_base_of.

template <typename B, typename D>
auto is_base_of_helper(B*) -> true_type;

template <typename B, typename D>
auto is_base_of_helper(...) -> false_type;

template <typename B, typename D>
auto test_is_base_of(int) -> decltype(is_base_of_helper<B, D>(declval<D*>()));

template <typename B, typename D>
auto test_is_base_of(...) -> true_type;

template <typename B, typename D>
struct is_base_of: 
	std::conjunction<
		std::is_class<B> && 
		std::is_class<D> &&
		decltype(test_is_base_of<B, D>(0))
	>
{};

// 15.6. common_type

template <typename T1, typename T2, typename... Types>
struct common_type: common_type<T1, T2>, Types...> {};

template <typename T1, typename T2>
struct common_type<T1, T2>
	: type_identity<decltype(true ? declval<T1>() : declval<T2>())> {};

template <typename T>
struct common_type<T>: type_identity<T> {};

template <typename T>
using common_type_t = typename common_type<T>::type;

struct S {
	S() = delete;
	~S() = delete;
	void construct(int);
	void construct(int, int);
};

int main() {

	std::cout << has_method_construct_v<S, int>;
	std::cout << has_method_construct_v<S, int, int>;
	std::cout << has_method_construct_v<S, int, int, int>;

}
