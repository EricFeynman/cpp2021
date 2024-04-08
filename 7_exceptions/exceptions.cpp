#include <iostream>
#include <vector>

// VII. Exceptions.

// 7.1. Basic idea and usage examples.

// 7.2. Difference between exceptions and runtime errors.  

// main -> f1 -> f2 -> ... -> f5 -> ...  -> f9 -> f10
//			      catch               throw

// 7.3. Deep diving into throwing and catching mechanism.

void f(int a) {
	std::string abc = "aaaaaa";

	//...

	throw abc;
}

int f(int a, int b) {
	int* p = new int; // std::bad_alloc
	// std::bad_cast
	//if (b == 0) throw 1; // very bad, throwing int is stupid
	return a / b;
}

int main() {
	
	int x = 2;
	int y = 0;

	//std::cin >> x >> y;
	
	try { 
		//int z = f(x, y);

		//std::cout << z << '\n';

		//std::vector<int> v(10);
		// v.at(100'000) = 1; // std::out_of_range

		throw std::runtime_error("AAA!");
		// std::runtime_error

	} catch (const std::exception s) {
		std::cout << "Oops! " << '\n';
		throw;
	} catch (std::runtime_error& d) {
		std::cout << "AAA!" << '\n';
	}

	//int error_code = f(&x, y, z);

}
