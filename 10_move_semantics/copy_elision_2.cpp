#include <iostream>
#include <vector>

// 10.8. copy elision.

struct S {
	int x;
	S(int x): x(x) {
		std::cout << x << '\n';
	}
	S(const S&) {
		std::cout << "copy";
	}
	S(S&&) {
		std::cout << "move";
	}

	S& operator+=(const S& a) {
		x += a.x;
		return *this;
	}
};

S f(int n) {
	return S(n);
}

// NRVO
S operator+(const S& a, const S& b) {
	S copy = a;
	copy += b;
	return copy;
}

/*BigInteger operator+(const BigInteger& a, const BigInteger& b) {
	BigInteger copy = a;
	copy += b;
	return copy;
}*/

int main() {

	S s(5);
	S s2(6);

	S s3 = s + s2;

	//S s = S(S(S(S(S(5)))));

	//S v = f(10);
	
	// temporary materialization
	//int x = f(10).x; // <- xvalue

}
