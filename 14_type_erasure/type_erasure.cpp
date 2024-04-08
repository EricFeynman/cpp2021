#include <iostream>
#include <any>
#include <vector>

// XIV. Type erasure and unions.

// 14.1. Basic idea, std::any (since c++17).

class any {

	struct Base {
		virtual Base* clone() = 0;
		virtual ~Base() = default;
	};

	template <typename T>
	struct Derived: public Base {
		T object;
		Base* clone() override {
			return new Derived<T>(object);
		}
		Derived(const T& object): object(object) {}
	};

	Base* ptr = nullptr;
 
public:

	template <typename U>
	any(const U& object): ptr(new Derived<U>(object)) {}

	any(const any& other): ptr(ptr->clone()) {}

	// TODO: copy-assignment operator for any?
	template <typename U>
	auto& operator=(const U& object) {
		delete ptr;
		ptr = new Derived<U>(object);
	}

	~any() {
		delete ptr;
	}
};	

int main() {

	std::any a = 5;

	std::vector<int> v = {1, 2, 3, 4, 5};

	auto& x = std::any_cast<int&>(a);
	x = 6;

	std::cout << std::any_cast<int>(a);

	a = std::move(v);

	//std::cout << std::any_cast<int>(a);

	a = 'a';

}
