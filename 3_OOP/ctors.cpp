#include <cstring>
#include <iostream>

// 3.3 Constructors and destructors

// 3.4 The Rule of Three

class Complex {
private:
	double re = 0.0;
	double im = 0.0;
public:
	Complex() {
		std::cout << "OAOAOA!!!\n";
	}
	Complex(const Complex&) = default;
	Complex(double re, double im): re(re), im(im) {}
	Complex(double re): re(re) {}
};

class String {
private: 
	char* str = nullptr;
	size_t sz = 0;
public:
	String() = delete;
	String(size_t n, char c): str(new char[n]), sz(n) {
		std::cout << "String " << sz << '\n';
		memset(str, c, n);
	}

	String(const String& s): String(s.sz, '\0') {
		memcpy(str, s.str, sz);
	}


	void swap(String& s) {
		std::swap(str, s.str);
		std::swap(sz, s.sz);
	}

	// Copy-and-swap idiom.
	String& operator=(const String& s) {
		String copy = s;
		swap(copy);
		return *this;
		/*delete[] str;
		str = new char[s.sz];
		sz = s.sz;
		memcpy(str, s.s tr, sz);
		return *this;*/
	}

	~String() {
		std::cout << "~String " << sz << '\n';
		delete[] str;
	}
};

int main() {
	Complex c; //(1.0, 2.0);
	{
		String s(10, 'a');
		String ss(20, 'b');
		
		s = ss;
	}
	std::cout << "AAAA";
		   
}
