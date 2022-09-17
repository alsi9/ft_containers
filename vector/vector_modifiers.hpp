#include "vector.hpp"

#ifndef VECTOR_MODIFIERS_HPP
#define VECTOR_MODIFIERS_HPP

namespace ft
{
	template<class T, class Alloc>
	void vector<T, Alloc>::clear()
	{
		size_type i;
		for (i = 0; i < _size; i++)
			_alloc.destroy(_arr + i);
		_size = 0;
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::insert(iterator it, const T &x)
	{
		if (it < begin() || it > end())
			throw std::length_error("vector");
		size_type dist = it - begin();
		size_type i;
		if (_size == _capacity)
		{
			T *new_arr = _alloc.allocate(_capacity * 2);
			try
			{
				for (i = 0; i < dist; i++)
					_alloc.construct(new_arr + i, _arr[i]);
				_alloc.construct(new_arr + i, x);
			}
			catch (...)
			{
				for (; i > 0; i--)
					_alloc.destroy(new_arr + i - 1);
				_alloc.deallocate(new_arr, _capacity * 2);
				throw ;
			}
			try
			{
				for (i = dist; i < _size; i++)
					_alloc.allocate(new_arr + i + 1, _arr[i]);
			}
			catch (...)
			{
				for (; i > 0; i--)
					_alloc.destroy(new_arr + i - 1);
				_alloc.deallocate(new_arr, _capacity * 2);
				throw ;
			}
			_size += 1;
			_capacity *= 2;
			_arr = new_arr;
			return (vector<T, Alloc>::iterator(_arr + dist));
		}
		else
		{
			if (_size != 0)
			{
				for (i = _size; i > dist; i--)
				{
					try
					{
						_alloc.construct(_arr + i, *(_arr + i - 1));
					}
					catch (...)
					{
						for (size_type j = 0; j < i; j++)
							_alloc.destroy(_arr + j);
						for (size_type j = i + 1; j < _size + 1; j++)
							_alloc.destroy(_arr + j);
						_size = 0;
						throw ;
					}
					_alloc.destroy(_arr + i - 1);
				}
			}
			try
			{
				_alloc.construct(_arr + dist, x);
			}
			catch (...)
			{
				for (i = 0; i < dist; i++)
					_alloc.destroy(_arr + i);
				for (i = dist + 1; i < _size + 1; i++)
					_alloc.destroy(_arr + i);
				_size = 0;
				throw ;
			}
			_size += 1;
			return (vector<T, Alloc>::iterator(_arr + dist));
		}
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::insert(iterator it, size_type n, const T &x)
	{
		if (n == 0)
			return ;
		if (_alloc.max_size() - _size < n)
			throw std::length_error("vector");
		if (it < begin() || it > end())
			throw std::length_error("vector");
		size_type dist = it - begin();
		size_type i;
		if (_size + n > _capacity)
		{
			size_type new_capacity = _capacity * 2 > _size + n ? _capacity * 2 : _size + n;
			T *new_arr = _alloc.allocate(new_capacity);
			try
			{
				for (i = 0; i < dist; i++)
					_alloc.construct(new_arr + i, _arr[i]);
			}
			catch (...)
			{
				for (; i > 0; i--)
					_alloc.destroy(new_arr + i - 1);
				_alloc.deallocate(new_arr, new_capacity);
				throw ;
			}
			try
			{
				for (i = dist; i < dist + n; i++)
					_alloc.construct(new_arr + i, x);
			}
			catch (...)
			{
				for (; i > 0; i--)
					_alloc.destroy(new_arr + i - 1);
				_alloc.deallocate(new_arr, new_capacity);
				throw ;
			}
			try
			{
				for (i = n + dist; i < _size + n; i++)
					_alloc.construct(new_arr + i, _arr[i - n]);
			}
			catch (...)
			{
				for (; i > 0; i--)
					_alloc.destroy(new_arr + i - 1);
				_alloc.deallocate(new_arr, new_capacity);
				throw ;
			}
			for (size_type j = 0; j < _size; j++)
				_alloc.destroy(_arr + j);
			_alloc.deallocate(_arr, _capacity);
			_arr = new_arr;
			_capacity = new_capacity;
			_size += n;
		}
		else
		{
			if (_size != 0)
			{
				for (i = _size + n - 1; i >= dist + n; i--)
				{
					try
					{
						_alloc.construct(_arr + i, _arr[i - n]);
					}
					catch (...)
					{
						for (size_type j = 0; j <= i - n; i++)
							_alloc.destroy(_arr + j);
						for (size_type j = i + 1; j < _size + n; j++)
							_alloc.destroy(_arr + j);
						_size = 0;
						throw ;
					}
					_alloc.destroy(_arr + i - n);
				}
				for (i = 0; i < n; i++)
				{
					try
					{
						_alloc.construct(_arr + i + dist, x);
					}
					catch (...)
					{
						for (size_type j = 0; j < i + dist; j++)
							_alloc.destroy(_arr + j);
						for (size_type j = n + dist; j > _size + n; j++)
							_alloc.destroy(_arr + j);
						_size = 0;
						throw ;
					}
				}
				_size += n;
			}
		}
	}

	template<class T, class Alloc>
	template <class InIt>
	void vector<T, Alloc>::insert(iterator it, InIt first, InIt last, typename ft::enable_if<!ft::is_integral<InIt>::value, InIt>::type*)
	{
		if (it < begin() || it > end())
			throw std::length_error("vector");
		size_type dist = it - begin();
		size_type size_it = last - first;
		if (_alloc.max_size() - _size < size_it)
			throw std::length_error("vector");
		if (size_it == 0)
			return;
		size_type i = 0;
		if (size_it + _size > _capacity)
		{
			size_type new_capacity = _capacity * 2 > size_it + _size ? _capacity * 2 : size_it + _size;
			T *new_arr = _alloc.allocate(new_capacity);
			try
			{
				for (; i < dist; i++)
					_alloc.construct(new_arr + i, _arr[i]);
			}
			catch (...)
			{
				for (; i > 0; i--)
					_alloc.destroy(new_arr + i - 1);
				_alloc.deallocate(new_arr, new_capacity);
				throw ;
			}
			try
			{
				for (i = dist; i < size_it + dist; i++)
				{
					_alloc.construct(new_arr + i, (*first));
					first++;
				}
			}
			catch (...)
			{
				for (; i > 0; i--)
					_alloc.destroy(new_arr + i - 1);
				_alloc.deallocate(new_arr, new_capacity);
				throw ;
			}
			try
			{
				for (i = dist + size_it; i < _size + size_it; i++)
					_alloc.construct(new_arr + i, _arr[i - size_it]);
			}
			catch (...)
			{
				for (; i > 0; i--)
					_alloc.destroy(new_arr + i - 1);
				_alloc.deallocate(new_arr, new_capacity);
				throw ;
			}
			for (size_type j = 0; j < _size; j++)
				_alloc.destroy(_arr + i);
			_alloc.deallocate(_arr, _capacity);
			_arr = new_arr;
			_capacity = new_capacity;
		}
		else
		{
			if (_size != 0)
			{
				for (i = _size + size_it - 1; i >= dist + size_it; i--)
				{
					try
					{
						_alloc.construct(_arr + i, _arr[i - size_it]);
					}
					catch (...)
					{
						for (size_type j = 0; j <= i - size_it; i++)
							_alloc.destroy(_arr + j);
						for (size_type j = i + 1; j < _size + size_it; j++)
							_alloc.destroy(_arr + j);
						_size = 0;
						throw ;
					}
					_alloc.destroy(_arr + i - size_it);
				}
				for (i = 0; i < size_it; i++)
				{
					try
					{
						_alloc.construct(_arr + i + dist, *first);
						first++;
					}
					catch (...)
					{
						for (size_type j = 0; j < i + dist; j++)
							_alloc.destroy(_arr + j);
						for (size_type j = size_it + dist; j > _size + size_it; j++)
							_alloc.destroy(_arr + j);
						_size = 0;
						throw ;
					}
				}
			}
		}
		_size += size_it;
	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator it)
	{
		size_type dist = it - begin();

		for (size_type i = dist; i < _size - 1; i++)
		{
			_alloc.destroy(_arr + i);
			try
			{
				_alloc.construct(_arr + i, _arr[i + 1]);
			}
			catch (...)
			{
				for (size_type j = 0; j < i; j++)
					_alloc.destroy(_arr + j);
				for (size_type j = i + 1; j < _size; j++)
					_alloc.destroy(_arr + j);
				_size = 0;
				throw ;
			}
		}
		_alloc.destroy(_arr + _size - 1);
		_size--;
		if (dist == _size)
			dist--;
		return iterator(_arr + dist);

	}

	template<class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last)
	{
		size_type size_it = last - first;
		size_type dist = first - begin();
		if (size_it == 0)
			return (last);
		for (size_type i = 0; i < size_it; i++)
			_alloc.destroy(_arr + i + dist);
		for (size_type i = dist + size_it; i < _size; i++)
		{
			try
			{
				_alloc.construct(_arr + i - size_it, _arr[i]);
			}
			catch (...)
			{
				for (size_type j = 0; j < i - size_it; j++)
					_alloc.destroy(_arr + j);
				for (size_type j = i; j < _size; j++)
					_alloc.destroy(_arr + j);
				_size = 0;
				throw ;
			}
			_alloc.destroy(_arr + i);
		}
		_size -= size_it;
		if (last == end())
			dist -= size_it;
		return iterator(_arr + dist);
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type &x)
	{
		if (_size == _capacity)
			reserve(_capacity == 0 ? 1 : _capacity * 2);
		_alloc.construct(_arr + _size, x);
		_size++;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::pop_back()
	{
		_alloc.destroy(_arr + _size - 1);
		_size--;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::resize(size_type n, const_reference value)
	{
		if (n < _size)
		{
			for (size_type i = n; i < _size; i++)
				_alloc.destroy(_arr + i);
		}
		else
		{
			if (n > _capacity)
				reserve(_capacity * 2 >= n ? _capacity * 2 : n);
			for (size_type i = _size; i < n; i++)
			{
				try
				{
					_alloc.construct(_arr + i, value);
				}
				catch (...)
				{
					for (size_type j = _size; j < i; j++)
						_alloc.destroy(_arr + j);
					throw ;
				}
			}
		}
		_size = n;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::swap(vector<T, Alloc> &x)
	{
		std::swap(_arr, x._arr);
		std::swap(_size, x._size);
		std::swap(_capacity, x._capacity);
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::assign(size_type count, const T& value)
	{
		clear();
		if (count > _capacity)
		{
			T *new_arr = _alloc.allocate(count);
			_alloc.deallocate(_arr, _capacity);
			_arr = new_arr;
			_capacity = count;
		}
		for (size_type i = 0; i < count; i++)
		{
			try
			{
				_alloc.construct(_arr + i, value);
			}
			catch (...)
			{
				for (size_type j = 0; j < i; j++)
					_alloc.destroy(_arr + j);
				_alloc.deallocate(_arr, _capacity);
				_size = 0;
				throw ;
			}
			_size++;
		}
	}

	template<class T, class Alloc>
	template<class InputIt>
	void vector<T, Alloc>::assign(InputIt first, InputIt last, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type*)
	{
		clear();
		size_type dist = last - first;
		if (dist > _capacity)
		{
			T *new_arr = _alloc.allocate(dist);
			_alloc.deallocate(_arr, _capacity);
			_arr = new_arr;
			_capacity = dist;
		}
		for (size_type i = 0; i < dist; i++)
		{
			try
			{
				_alloc.construct(_arr + i, *first);
				first++;
			}
			catch (...)
			{
				for (size_type j = 0; j < i; j++)
					_alloc.destroy(_arr + j);
				_alloc.deallocate(_arr, _capacity);
				_size = 0;
				throw ;
			}
			_size++;
		}
	}
}

#endif
