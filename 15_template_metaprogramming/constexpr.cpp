#include <iostream>
#include <array>

// 15.8. constexpr-functions (since c++11) and compile-time computations.

constexpr int fact(int n) {
	return n > 1 ? n * fact(n-1) : 1;
}

int main() {
	//std::array<int, fact(5)> a;
	int x;
	std::cin >> x;
	const int y = fact(x);

	//constexpr int x = fact(10);
}
