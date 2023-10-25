#include <iostream>
#include <string>

class Toy {
private:
	std::string name;
public:
	Toy(std::string _name) : name(_name) {
		std::cout << "Constructing class Toy with name." << std::endl;
	}

	Toy() {
		std::cout << "Constructing class Toy by default." << std::endl;
	};

	~Toy() {
		std::cout << "Deleting class Toy." << std::endl;
	}

	std::string get_name() {
		return this->name;
	}
};

class Shared_ptr_toy {
private:
	Toy* ptr;
	unsigned int count = 0;
public:
	Shared_ptr_toy(Toy* _ptr = nullptr) {
		std::cout << "Constructing shared_ptr." << std::endl;
		count = 0;
		ptr = _ptr;
	}

	Shared_ptr_toy(const Shared_ptr_toy& other) {
		std::cout << "Making copy of shared_ptr." << std::endl;
		ptr = other.ptr;
		count++;
	}

	Shared_ptr_toy& operator=(const Shared_ptr_toy& other) {
		std::cout << "Initializing shared_ptr." << std::endl;
		if (this == &other)
			return *this;
		ptr = other.ptr;
		count++;
		return *this;
	}

	~Shared_ptr_toy() {
		if ((ptr != nullptr) && (count == 0)) {
			std::cout << "Deleting shared_ptr." << std::endl;
			delete ptr;
		} else {
			std::cout << "Deleting copy." << std::endl;
			count--;
		}
	}

	unsigned int use_count() {
		return this->count;
	}

	void reset() {
		if (this->count > 0) this->count = 0;
	}
};

Shared_ptr_toy make_shared_toy(const std::string& _toy_name) {
	Shared_ptr_toy ptr(new Toy(_toy_name));
	return ptr;
}

Shared_ptr_toy make_shared_toy(Toy* _toy) {
	Shared_ptr_toy ptr(_toy);
	return ptr;
}

void show_count(Shared_ptr_toy& _ptr) {
	std::cout << "count = " << _ptr.use_count() << std::endl;
	std::cout << "----------------------------" << std::endl;
}

int main() {
	Shared_ptr_toy ptr1(new Toy("Ball"));
	show_count(ptr1);
	Shared_ptr_toy ptr2(ptr1);
	show_count(ptr2);
	Shared_ptr_toy ptr3 = ptr2;
	show_count(ptr3);
	Shared_ptr_toy ptr4 = make_shared_toy(new Toy("Ball"));
	show_count(ptr4);
	Shared_ptr_toy ptr5 = make_shared_toy("Duck");
	show_count(ptr5);
}
