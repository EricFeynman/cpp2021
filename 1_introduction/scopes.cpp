#include <iostream>

// scope
char y = 'c';

// declaration != definition
// Any definition is declaration

// One Definition Rule
int f(int x);

namespace N {

int f(int x);

}


// qualified-id
int N::f(int x) {
	return x+1;
} 

namespace N {

	int x = 3;
}

using vi = std::vector<int>;

int main() {
	using namespace N;
	vi v = {1, 2, 3, 4, 5};

	int vi;

	using std::count;
	int x = 5;
	
	{
		int x = 10;
		cout << N::x <<'\n';
	}
	cout << x << '\n'; 
	f(x);
}
