
#ifndef FT_VECTOR
#define FT_VECTOR

#include <iterator>
#include <iostream>
#include <vector>

#include "../utils/iterator_traits.hpp"
#include "../utils/utils.hpp"
#include "../utils/reverse_iterator.hpp"

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector {
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;
		class iterator;
		class const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;


	private:
		T *_arr;
		size_type _size;
		size_type _capacity;
		allocator_type _alloc;

	public:
		vector();
		explicit vector(const Alloc &alloc);
		explicit vector(size_type n, const T &value = T(), const Alloc &alloc = Alloc());

		template<class InputIt>
		vector(InputIt first, InputIt last, const Alloc &alloc = Alloc(),
			   typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = 0);

		vector(const vector<T, Alloc> &x);
		vector &operator=(const vector<T, Alloc> &x);
		~vector();
		allocator_type get_allocator() const;

		//element access
		reference at(size_type n);
		const_reference at(size_type n) const;
		reference operator[](size_type n);
		const_reference operator[](size_type n) const;
		reference front();
		const_reference front() const;
		reference back();
		const_reference back() const;
		pointer data();
		const_pointer data() const;

//		iterators
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		//capacity
		bool empty() const;
		size_type size() const;
		size_type max_size() const;
		void reserve(size_type n);
		size_type capacity() const;

		//modifiers
		void clear();
		iterator insert(iterator it, const T &x);
		void insert(iterator it, size_type n, const T &x);

		template<class InIt>
		void insert(iterator it, InIt first, InIt last,
					typename ft::enable_if<!ft::is_integral<InIt>::value, InIt>::type * = 0);

		iterator erase(iterator it);
		iterator erase(iterator first, iterator last);
		void push_back(const value_type &x);
		void pop_back();
		void resize(size_type n, const_reference value = T());
		void swap(vector<T, Alloc> &x);
		void assign(size_type count, const T &value);

		template<class InputIt>
		void assign(InputIt first, InputIt last,
					typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type * = 0);
	};

		template<class Type, class Allocator>
		bool operator==(const vector<Type, Allocator> &x, const vector<Type, Allocator> &y)
		{
			if (x.size() != y.size())
				return (false);
			return (ft::equal(x.begin(), x.end(), y.begin()));
		}

		template<class Type, class Allocator>
		bool operator!=(const vector<Type, Allocator> &x, const vector<Type, Allocator> &y)
		{
			return !(x == y);
		}

		template<class Type, class Allocator>
		bool operator<(const vector<Type, Allocator> &x, const vector<Type, Allocator> &y)
		{
			return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
		}

		template<class Type, class Allocator>
		bool operator<=(const vector<Type, Allocator> &x, const vector<Type, Allocator> &y)
		{
			return !(x > y);
		}

		template<class Type, class Allocator>
		bool operator>(const vector<Type, Allocator> &x, const vector<Type, Allocator> &y)
		{
			return (y < x);
		}

		template<class Type, class Allocator>
		bool operator>=(const vector<Type, Allocator> &x, const vector<Type, Allocator> &y)
		{
			return !(x < y);
		}
}

#include "vector_constructor.hpp"
#include "vector_element_access.hpp"
#include "vector_capacity.hpp"
#include "vector_iterator.hpp"
#include "vector_modifiers.hpp"
#include "vector_iter_func.hpp"

#endif
