#include "vector.hpp"

#ifndef VECTOR_CAPACITY_HPP
#define VECTOR_CAPACITY_HPP

namespace ft
{
	template<class T, class Alloc>
	bool vector<T, Alloc>::empty() const
	{
		return (_size == 0);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::size() const
	{
		return (_size);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::max_size() const
	{
		return (_alloc.max_size());
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::reserve(size_type n)
	{
		if (n <= _capacity)
			return ;
		if (n > _alloc.max_size())
			throw std::length_error("vector");
		T *new_arr = _alloc.allocate(n);
		size_type i;
		try
		{
			for (i = 0; i < _size; i++)
				_alloc.construct(new_arr + i, _arr[i]);
		}
		catch (...)
		{
			for (; i > 0; i--)
				_alloc.destroy(new_arr + i - 1);
			_alloc.deallocate(new_arr, n);
			throw ;
		}
		for (size_type j = 0; j < _size; j++)
			_alloc.destroy(_arr + j);
		_alloc.deallocate(_arr, _capacity);
		_capacity = n;
		_arr = new_arr;
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::capacity() const
	{
		return (_capacity);
	}
}

#endif
