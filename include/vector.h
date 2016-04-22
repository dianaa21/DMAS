#ifndef ARRAY_ARRAY_H
#define ARRAY_ARRAY_H

#include <cstddef>
#include <iostream>
#include <stdexcept>

template<class T>
class Vector 
{
public:
	using value_type = T;
	using size_type = std::size_t;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;

	Vector()//
	{
		data_ = new value_type[1];
		data_[0] = 0;
		capacity_ = 1;
		size_ = 0;
	}

	explicit Vector(size_type count) 
	{
		data_ = new value_type[count];
		capacity_ = count;
		size_ = count;
	}

	Vector(size_type count, const value_type& value) 
	{
		data_ = new value_type[count];
		capacity_ = count;
		size_ = count;
		for (size_type i = 0; i < count; i++) 
		{
			*(data_ + i) = value;
		}
	}

	Vector(const Vector &other) 
	{
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = new value_type[capacity_];
		for (size_type i = 0; i < size_; i++) 
		{
			*(data_ + i) = *(other.data_ + i);
		}
	}

	Vector(Vector&& other) noexcept 
	{
		size_ = other.size_;
		other.size_ = 0;
		capacity_ = other.capacity_;
		other.capacity_ = 0;
		data_ = other.data_;
		other.data_ = nullptr;
	}

	~Vector()
	{
			delete[] data_;
	}

	Vector<T> &operator=(const Vector& other) 
	{
		if (capacity_ >= other.size_) 
		{
			for (size_type i = 0; i < other.size_; i++)
			{
				*(data_ + i) = *(other.data_ + i);
			}
		}
		else 
		{
			delete[] data_;
			data_ = new value_type[other.size_];
			capacity_ = other.size_;
			for (size_type i = 0; i < other.size_; ++i) 
			{
				*(data_ + i) = *(other.data_ + i);
			}
		}
		size_ = other.size_;
	}

	Vector<T> & operator=(Vector&& other) noexcept
	{
		delete[] data_;
		size_ = other.size_;
		capacity_ = other.capacity_;
		data_ = other.data_;
		other.size_ = 0;
		other.capacity_ = 0;
		other.data_ = nullptr;
		return *this;
	}

	T& operator[](size_type pos) noexcept 
	{ 
		return *(data_ + pos);
	}

	const T& operator[](size_type pos) const noexcept 
	{ 
		return *(data_ + pos);
	}
	
	T& at(size_type pos) 
	{
		if (pos >= size_) 
		{
			throw std::out_of_range("positon >= size of vector");
		}
		value_type *pt = data_ + pos;
		return *(pt);
	}

	const T& at(size_type pos) const 
	{
		if (pos >= size_) 
		{
			throw std::out_of_range("positon >= size of vector");
		}
		char *temp = data_ + pos;//
		return *(temp);
	}

	T& front() noexcept 
	{
		return *data_;
	}

	const T& front() const noexcept 
	{
		return *data_;
	}

	T& back() noexcept 
	{
		return *(data_ + size_ - 1);
	}

	const T& back() const noexcept 
	{
		return *(data_ + size_ - 1);
	}

	T* data() noexcept 
	{
		return data_;
	}

	const T* data() const noexcept 
	{
		return data_;
	}

	bool empty() const noexcept 
	{
		if (size_ == 0)
		{
			return true;
		}
		return false;
	}

	std::size_t size() const noexcept 
	{
		return size_;
	}

	std::size_t capacity() const noexcept 
	{
		return capacity_;
	}

	void clear() 
	{
		size_ = 0;
	}

	void push_back(const value_type& value)
	{
		if ((size_ + 1) <= capacity_)
		{
			*(data_ + size_) = value;
			size_++;
		}
		else
		{
			size_++;
			capacity_ = 2 * size_;
			value_type *temp = new value_type[capacity_];
			for (size_type i = 0; i < size_ - 1; i++)
			{
				*(temp + i) = *(data_ + i);
			}
			*(temp + size_ - 1) = value;
			data_ = temp;
		}
	}

private:
	value_type *data_;
	size_type size_;
	size_type capacity_;

};
#endif //ARRAY_ARRAY_H