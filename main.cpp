#include <iostream>
#include <string>
#include <memory>

class Toy {
private:
	std::string name;
	int count = 0;
public:
	Toy(std::string _name) : name(_name) {
		std::cout << "Constructing class Toy with name \"" << this->name << "\"."<< std::endl;
	}

	Toy() {
		std::cout << "Constructing class Toy by default." << std::endl;
	};

	~Toy() {
		std::cout << "Deleting class Toy \"" << this->name << "\"."<< std::endl;
	}

	std::string get_name() {
		return this->name;
	}

	void set_count(int _count) {
		this->count = _count;
	}

	int use_count() {
		return count;
	}

	void incr_count() {
		this->count++;
	}

	void decr_count() {
		if (this->count > 0)
			this->count--;
	}

	void reset_count() {
		if (this->count > 0)
			this->count = 0;
	}
};

class Shared_ptr_toy {
private:
	Toy* ptr;
public:
	Shared_ptr_toy(Toy* _ptr = nullptr) {
		std::cout << "Constructing shared_ptr with nullptr." << std::endl;
		this->ptr = _ptr;
		this->ptr->set_count(1);
	}

	Shared_ptr_toy(std::string _toy_name) {
		std::cout << "Constructing shared_ptr with nullptr." << std::endl;
		this->ptr = new Toy(std::move(_toy_name));
		this->ptr->incr_count();
	}

	Shared_ptr_toy(const Shared_ptr_toy& other) {
		std::cout << "Making copy of shared_ptr." << std::endl;
		this->ptr = other.ptr;
		this->ptr->incr_count();
	}

	Shared_ptr_toy& operator=(const Shared_ptr_toy& other) {
		if (this == &other)
			return *this;
		std::cout << "Initializing shared_ptr." << std::endl;
		this->ptr = other.ptr;
		this->ptr->incr_count();
		return *this;
	}

	~Shared_ptr_toy() {
		if ((ptr != nullptr) && (this->ptr->use_count() == 1)) {
			std::cout << "Deleting shared_ptr." << std::endl;
			delete this->ptr;
		} else {
			std::cout << "Deleting copy." << std::endl;
			this->ptr->decr_count();
		}
	}

	int use_count() {
		return this->ptr->use_count();
	}
};

Shared_ptr_toy make_shared_toy( std::string _toy_name) {
	Shared_ptr_toy ptr(std::move(_toy_name));
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

void show_count(std::shared_ptr<int>& _ptr) {
	std::cout << "count = " << _ptr.use_count() << std::endl;
	std::cout << "----------------------------" << std::endl;
}

int main() {

	{
		Shared_ptr_toy ptr1("Ball");
		show_count(ptr1);
		Shared_ptr_toy ptr2(ptr1);
		show_count(ptr2);
		Shared_ptr_toy ptr3 = ptr1;
		show_count(ptr3);
		Shared_ptr_toy ptr4 = make_shared_toy(new Toy("Bone"));
		show_count(ptr4);
		Shared_ptr_toy ptr5 = make_shared_toy("Duck");
		show_count(ptr5);
	}
	{
		std::shared_ptr<int> ptr1 = std::make_shared<int>(42);
		show_count(ptr1);
		std::shared_ptr<int> ptr2(ptr1);
		show_count(ptr2);
		std::shared_ptr<int> ptr3(ptr1);
		show_count(ptr3);
	}
}
