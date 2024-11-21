#include <algorithm>
#include <print>

//Rule of Six
/*
Default constructor,
Copy Constructor,
Move Constructor,
Copy Assignment,
Move Assignment,
Destructor

also a Swap pattern (six and a half?)
*/

class Vec {
public:
	Vec() //default constructor
	{
		ptr_ = nullptr;
		size_ = 0;
		std::println("default constructor called");
	};

	Vec(const Vec& that) //copy constructor
	{
		ptr_ = new int[that.size_];
		size_ = that.size_;
		std::copy(that.ptr_, that.ptr_ + size_, ptr_);
		std::println("copy constructor called");
	}

	Vec(Vec&& that) noexcept //move constructor
	{
		ptr_ = that.ptr_;
		size_ = that.size_;
		that.ptr_ = nullptr;
		that.size_ = 0;
		std::println("move constructor called");
	}

	Vec& operator=(Vec that) //copy assignment operator
	{
		swap(*this, that); //swap function
		return *this;
	}
	
	~Vec() //destructor
	{
		delete[] ptr_;
		std::println("desctuctor called");
	};

	friend void swap(Vec& lhs, Vec& rhs) noexcept //copy assign?
	{
		using std::swap;
		swap(lhs.ptr_, rhs.ptr_);
		std::println("copy assign called - more of a swap, actually");
	}

private:
	int* ptr_ = nullptr;
	size_t size_ = 0;
};

int main()
{
	Vec aVec; //declare an empty container
	Vec bVec = aVec; //copy constructor called
	
	bVec = aVec; //copy assignment

	std::print("test");
	return 0;
}