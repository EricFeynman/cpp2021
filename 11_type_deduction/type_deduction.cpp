#include <iostream>
#include <map>
#include <vector>

// XI. Type deduction.
// 11.1. auto keyword (since c++11)

// 11.2. decltype keyword (since c++11)

// 11.3. Class Template Argument Deduction (CTAD) (since c++17)

// 11.4. structured bindings (since c++17)

// since c++20
auto& f(auto& x, auto y) {
	return x += y;
}

template <typename T, typename U>
auto& f(T& x, U y) {
	return x += y;
}

template <typename Container>
auto getByIndex(Container& container, size_t index) 
	-> decltype(container[index]) {
	std::cout << "get By Index called\n";
	return container[index];
}

int main() {

	std::map<int, std::string> m;
	m[1] = "abc";
	m[3] = "bbbbb";

	for (auto& [key, value]: m) {
		value = "aaa";	
	}

	int a = 5;

	std::vector v(5, 10);

	std::vector vv{v.begin(), v.end()};
	std::cout << vv.size();

	//std::vector v = {1, 2, 3};
	//getByIndex(v, 1) = 0;
}
