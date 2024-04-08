#include <iostream>

// V. Templates.

// 5.1. General idea, basic examples.

// Template instantiation.

template <typename T>
void swap(T& x, T& y) {
	T tmp = x;
	x = y;
	y = tmp;
}

template <typename T>
class vector {
private: 
	T* arr;
	int sz;
	int cap;
public:
  	
	template <typename U>
	void push_back(const U& x);
};

template <typename T>
template <typename U>
void vector<T>::push_back(const U& x);

// since c++11
using vi = vector<int>;

template <typename T>
using mymap = map<T, T>;

//since c++14

template <typename T>
int value = MyClass<T>::value;

int main() {
	int x = 5;
	int y = 6;
	
	swap(x, y);

	double a = 2.0;
	double b = 3.0;

	swap(a, b);

}
