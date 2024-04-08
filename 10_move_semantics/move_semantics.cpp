#include <iostream>
#include <vector>

// X. Move semantics and rvalue references (since C++11).

// 10.1. Motivation of move-semantics. Magic function std::move.

// 10.3. std::move implementation.

template <typename T> 
std::remove_reference_t<T>&& move(T&& x) {
	return static_cast<std::remove_reference_t<T>&&>(x);
}	

template <typename T>
void swap(T& x, T& y) {
	T t = std::move(x); // std::string
	// now x is a correct empty string
	x = std::move(y);
	y = std::move(t);
}

/*BigInteger operator+(BigInteger a, const BigInteger& b) {
	a += b;
	return std::move(a);
}*/

struct S {
	void f() & {
		std::cout << 1;
	}

	void f() && {
		std::cout << 2;
	}
	
	void f() const && {
		std::cout << 3;
	}
};

int main() {

	S s;
	s.f();

	std::move(s).f();

	/*string s = "abcde";

	throw s;

	std::vector<std::string> v;

	//v.push_back("abc");

	v.emplace_back();
	
	std::vector<std::vector<int>> vv;

	v.push_back(std::vector<int>(5, 10))'

	v.emplace_back(5, 10);*/

}
