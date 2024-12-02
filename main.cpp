#include <algorithm>
#include <numeric>
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
private:
	size_t size_ = 0;
public:
	int* data_ = nullptr;

	Vec() noexcept { std::println("default constructor called."); } //default constructor

	explicit Vec(size_t count) noexcept //override constructor
	{
		data_ = new int[count];
		size_ = count;
		std::iota(data_, data_ + size_, 0);
		std::println("Override constructor called.");
	};

	Vec(const Vec& that) : //copy constructor
		size_(that.size_), 
		data_(new int[size_]) // <-- if new int[size_] isn't called, the vec is put in the wrong address causing issues with delete[]
	{
		std::copy(begin(), end(), data_);
	}

	Vec(Vec&& that) noexcept : //move constructor
		data_(that.data_) 
	{
		that.data_ = nullptr;
	}

	Vec& operator=(const Vec& other) //copy assignment
	{
		if (&other != this)
		{
			Vec copy(other);
			std::swap(data_, copy.data_);
		}
		return *this;
	}

	Vec& operator=(Vec&& other) //move assignment
	{
		if (&other != this)
		{
			std::swap(data_, other.data_);
			std::swap(size_, other.size_);
		}
		std::println("move assign called");
		return *this;
	}
	
	int* begin() const noexcept //retrieve ptr of first position
	{
		return data_;
	}

	int* end() const noexcept //retrieve ptr of last position
	{
		return data_ + size_;
	}

	~Vec() noexcept //destructor
	{
		delete[] data_;
	};

};

int main()
{
	auto aVec = Vec(3); //calls default constructor
	auto bVec = Vec(7); //calls default constructor
	aVec = bVec; //calls copy assignment which calls copy constructor

	aVec = std::move(bVec); //calls move assignment
	Vec c{ std::move(aVec) }; //calls move constructor
	if (aVec.data_ == nullptr)
	{
		std::println("data has been deleted!");
	}
	return 0;
}