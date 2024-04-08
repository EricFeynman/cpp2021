#include <iostream>

// 14.4. unions.

union U {
	int x;
	double d = 1.0;
	std::string s;
	
	U(double d): d(d) {}
	U(const char* s): s(s) {}
	~U() {}
};

int main() {
	U u = 3.14;
	
	std::cout << u.d << '\n';
	
	//u.s.~basic_string();
	//u.s = "abc";
	new(&u.s) std::string("abc"); 
	std::cout << u.s << '\n';

	u.s.~basic_string();	
}
