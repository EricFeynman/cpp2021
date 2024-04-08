#include <iostream>
#include <vector>
#include <cstdlib>

// 9.4. new/delete overloading.

void* operator new(size_t n) {
	std::cout << "Allocating " << n << " bytes\n";
	void* ptr = std::malloc(n);
	if (!ptr) {
		throw std::bad_alloc();
	}
	return ptr;
}

void operator delete(void* ptr) {
	std::cout << "Deallocating\n";
	std::free(ptr);
}

void* operator new(size_t n, const std::nothrow_t&) {
	std::cout << "Allocating " << n << " bytes non-throwing\n";
	void* ptr = std::malloc(n);
	return ptr;
}

/*void* operator new(size_t n, void* ptr) noexcept {
	std::cout << "Placement new " << n << " bytes\n";
	void* ptr = std::malloc(n);
	return ptr;
}*/

struct S {
	void* operator new(size_t n) {
		std::cout << "Allocating " << n << " bytes for S\n";
		void* ptr = std::malloc(n);
		if (!ptr) {
			throw std::bad_alloc();
		}
		return ptr;
	}

	void operator delete(void* ptr) {
		std::cout << "Deallocating S\n";
		std::free(ptr);
	}
};

int main() {

	S* p = new S();
	delete p;

	ptr->~T();
	::operator delete(ptr);

	std::vector<S> v(5);

	for (int i = 6; i < 100; ++i) {
		v.push_back(S());
	}
}
