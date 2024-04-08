#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <set>

// XIII. Lambda functions and elements of functional programming.

// 13.1. Idea and basic usage of lambda functions (since c++11)

// 13.2. Capture lists.

struct Compare {
	bool operator()(int x, int y) const {
		return x > y;
	}
};

struct S {

	auto get_function() {
		auto f = [a = a](int x) {
			return x + a;
		};
		return f;
	}

	int a = 5;

};

int main() {

	S x{5};
	auto f = x.get_function();

	std::cout << f(10);


	return 0;
	
	/*std::vector<int> v = {3, 6, 5, 2, 8, 6, 9};

	int mid = 5;
	int count = 0;

	std::string s = "abcde";

	auto f = [count, mid = std::cref(mid)](int x, int y) mutable -> bool {
		++count;
		std::cout << count << '\n';
		return std::abs(x - mid) < std::abs(y - mid);
	};

	std::sort(v.begin(), v.end(), f);
		
	//std::set<int, decltype(f)> s(f);


	for (auto x: v) {
		s.insert(x);
	}

	for (auto x: v) {
		std::cout << x << ' ';
	}

	std::cout << '\n';
	std::cout << count << '\n';*/
}
