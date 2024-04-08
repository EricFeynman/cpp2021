#include <iostream>

// 7.4. RAII idiom.
// resource acquisition is initialization 

// unique_ptr, shared_ptr

// 7.5. Exceptions specification and exception-safety

// basic guarantee
// strong guarantee

struct SmartPtr {
	int* ptr;
	SmartPtr(int* ptr):  ptr(ptr) {}
	~SmartPtr() {
		delete ptr;
	}
};

class MyClass {
	std::string str;
	int* p;
public:
	// function-try block
	MyClass(const std::string& str): str(str), p(new int(5)) {
		if (str.size() == 0) {
			throw std::logic_error("AAA!");
		}
	}
	~MyClass() noexcept(false) {
		if (str.size() == 1 && !std::uncaught_exception()) {
			throw std::logic_error("BBB!");
		}
		delete p;
	}
};

void f(int x) noexcept(noexcept(g())) {
	SmartPtr p = new int(5);
	MyClass a = MyClass("a");

	//if (x == 0) throw std::runtime_error("Oops!");
}

int main() {

	try {

		f(0);
	
	} catch (std::exception& ex) {
		std::cout << ex.what();
	}
}
