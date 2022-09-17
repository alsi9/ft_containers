#include "vector.hpp"

#ifndef VECTOR_CONSTRUCTOR_HPP
#define VECTOR_CONSTRUCTOR_HPP

namespace ft
{
	template<class T, class Alloc>
	vector<T, Alloc>::vector() : _size(0), _capacity(0), _alloc()
	{
		_arr = _alloc.allocate(0);
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(const Alloc &alloc) : _size(0), _capacity(0), _alloc(alloc)
	{
		_arr = _alloc.allocate(0);
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(size_type n, const T& value, const Alloc& alloc) : _size(n), _capacity(n), _alloc(alloc)
	{
		_arr = _alloc.allocate(_capacity);
		size_type i;
		try
		{
			for (i = 0; i < n; i++)
				_alloc.construct(_arr + i, value);
		}
		catch (...)
		{
			for (; i > 0; --i)
				_alloc.destroy(_arr + i - 1);
			_alloc.deallocate(_arr, _capacity);
			throw ;
		}
	}

	template<class T, class Alloc>
	template< class InputIt >
	vector<T, Alloc>::vector(InputIt first, InputIt last, const Alloc& alloc, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*) : _size(0), _capacity(0), _alloc(alloc)
	{
		difference_type dist = ft::distance(first, last);
		size_type i;
		_arr = _alloc.allocate(dist);
		try
		{
			for (i = 0; first != last; i++, first++)
				_alloc.construct(_arr + i, *first);
		}
		catch (...)
		{
			for (; i > 0; i--)
				_alloc.destroy(_arr + i - 1);
			_alloc.deallocate(_arr, dist);
			throw ;
		}
		_size = dist;
		_capacity = dist;
	}

	template<class T, class Alloc>
	vector<T, Alloc>::vector(const vector<T, Alloc> &x) : _size(x._size), _capacity(x._capacity), _alloc(x.get_allocator())
	{
		_arr = _alloc.allocate(x._capacity);
		size_type i;
		try
		{
			for (i = 0; i < x._capacity; i++)
				_alloc.construct(_arr + i, x._arr[i]);
		}
		catch (...)
		{
			for (; i > 0; i--)
				_alloc.destroy(_arr + i - 1);
			_alloc.deallocate(_arr, _capacity);
			throw ;
		}
	}

	template<class T, class Alloc>
	vector<T, Alloc> &vector<T, Alloc>::operator=(const vector<T, Alloc> &x)
	{
		if (this == &x)
			return (*this);
		T *tmp;
		tmp = _alloc.allocate(x._capacity);
		size_type i;
		try
		{
			for (i = 0; i < x.size; i++)
				_alloc.construct(_arr + i, x._arr[i]);
		}
		catch (...)
		{
			for (; i > 0; i--)
				_alloc.destroy(_arr + i - 1);
			_alloc.deallocate(_arr, x._capacity);
			throw ;
		}
		for (size_type j = 0; j < _capacity; j++)
			_alloc.destroy(_arr + j - 1);
		_alloc.deallocate(_arr, _capacity);
		_arr = NULL;
		_size = x.size();
		_capacity = x.capacity();
		_arr = tmp;
	}

	template<class T, class Alloc>
	vector<T, Alloc>::~vector()
	{
		size_type i;
		for (i = 0; i > _size; i++)
			_alloc.destroy(_arr + i - 1);
		_alloc.deallocate(_arr, _capacity);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::allocator_type vector<T, Alloc>::get_allocator() const
	{
		return (_alloc);
	}
}

#endif
