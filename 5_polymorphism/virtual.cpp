#include <iostream>

// 6.2.  Some more complex exaxples.

// 6.3. Abstract classes and pure virtual functions.

// 6.4. Virtual destructor problem.

struct Mother {
	virtual void f() = 0;
	virtual ~Mother() = 0;
};

Mother::~Mother() {}

void Mother::f() {

}

/*struct Father {
	virtual void f() {
		std::cout << 2 << '\n';
	}
};*/

struct Son: Mother {
	int *p;
	Son(): p(new int(2)) {}
	void f() override {
		Mother::f();
		std::cout << 3 << '\n';
	}

	~Son() {
		std::cout << "~Son" << '\n';
		delete p;
	}
};

int main() {
	Mother* m = new Son();
	m->f();
	delete m;
}
