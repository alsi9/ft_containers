#include "vector.hpp"

#ifndef VECTOR_ELEMENT_ACCESS_HPP
#define VECTOR_ELEMENT_ACCESS_HPP

namespace ft
{
	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::at(size_type n)
	{
		if (n >= _size)
			throw std::out_of_range("vector");
		return (_arr[n]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::at(size_type n) const
	{
		if (n >= _size)
			throw std::out_of_range("vector");
		return (_arr[n]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::operator[](size_type n)
	{
		return (_arr[n]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::operator[](size_type n) const
	{
		return (_arr[n]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::front()
	{
		return (_arr[0]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::front() const
	{
		return (_arr[0]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::reference vector<T, Alloc>::back()
	{
		return (_arr[_size - 1]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::const_reference vector<T, Alloc>::back() const
	{
		return (_arr[_size - 1]);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::pointer vector<T, Alloc>::data()
	{
		return (_arr);
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::const_pointer vector<T, Alloc>::data() const
	{
		return (_arr);
	}
}

#endif
