#include <iostream>

// 8.7. Internals of std::map

template <typename First, typename Second>
struct pair {
	First first;
	Second second;
};

template <typename T>
struct less {
bool operator()(const T& x, const T& y) const {
		return abc(x - 5) < abc(y - 5);
	}
};

template <typename  Key, typename Value, 
	 typename Compare = std::less<Key>>
class map { 
	using value_type = pair<const Key, Value>;
private:
	BaseNode* leftmost;
	BaseNode* root;
	Compare comp;
	
	//	fakeroot <- end
	//    /
	//  tree

	struct BaseNode {
		Node* left;
		Node* right;
		Node* parent;
		bool red;
	};

	struct Node: BaseNode {
		value_type kv;
	};
	
public:

	struct iterator {
		BaseNode* node;
		
		value_type& operator*() const {
			return (static_cast<Node*>(node))->kv;
		}
	};

	Value& operator[](const Key& key);
	Value& at(const Key& key);
	const Value& at(const Key& key) const;

	iterator find(const Key& key); 

	size_t count(const Key& key) const;
};

int main() {

	std::map<int, std::string> m;
	m[0] = "abc"; // less effective
	m.insert({0, "abc"});

	std::map<int, std::string>::iterator it = m.find(0);	
	if (it != m.end()) {
		it->second = "abc";
	}

	//...

	for (std::map<std::string, int>::iterator it = m.begin(); it != m.end(); ++it) {
		it->second = 1; // OK!
		it->first = "abc"; // Not OK, CE!
	}

	for (auto el: m) {
		m.erase(el);
	}
}
