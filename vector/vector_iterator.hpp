#include "vector.hpp"
#include "../utils/iterator_traits.hpp"

#ifndef VECTOR_ITERATOR_HPP
#define VECTOR_ITERATOR_HPP


namespace ft
{
	template<class T, class Alloc>
	class ft::vector<T, Alloc>::iterator
	{
		private:
			T *arr;

		public:
			typedef typename ft::iterator_traits<T *>::value_type			value_type;
			typedef typename ft::iterator_traits<T *>::pointer				pointer;
			typedef typename ft::iterator_traits<T *>::reference			reference;
			typedef typename ft::iterator_traits<T *>::difference_type		difference_type;
			typedef typename ft::iterator_traits<T *>::iterator_category	iterator_category;

			iterator() {}
			explicit iterator(T *ptr) : arr(ptr) {}
			iterator(const iterator &other) : arr(other.base()) {}

			iterator &operator=(const iterator &other)
			{
				arr = other.arr;
				return (*this);
			}

			~iterator() {}

			pointer base() const
			{
				return (arr);
			}

			reference operator*() const
			{
				return (*arr);
			}

			pointer operator->() const
			{
				return (arr);
			}

			iterator &operator++()
			{
				arr++;
				return (*this);
			}

			iterator operator++(int)
			{
				iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			iterator &operator--()
			{
				arr--;
				return (*this);
			}

			iterator operator--(int)
			{
				iterator tmp(*this);
				--(*this);
				return(tmp);
			}

			iterator &operator+=(difference_type n)
			{
				arr += n;
				return (*this);
			}

			iterator &operator-=(difference_type n)
			{
				arr -= n;
				return (*this);
			}

			iterator operator+(difference_type n) const
			{
				iterator tmp(*this);
				tmp += n;
				return (tmp);
			}

			iterator operator-(difference_type n) const
			{
				iterator tmp(*this);
				tmp -= n;
				return (tmp);
			}

			reference operator[](difference_type i)
			{
				return (*(arr + i));
			}

			operator vector<T, Alloc>::const_iterator() const
			{
				return (vector<T, Alloc>::const_iterator(arr));
			}

			friend bool operator==(const vector<T, Alloc>::iterator &left, const vector<T, Alloc>::iterator &right)
			{
				return (left.base() == right.base());
			}

			friend bool operator!=(const vector<T, Alloc>::iterator &left, const vector<T, Alloc>::iterator &right)
			{
				return (left.base() != right.base());
			}

			friend bool operator>(const vector<T, Alloc>::iterator &left, const vector<T, Alloc>::iterator &right)
			{
				return (left.base() > right.base());
			}

			friend bool operator>=(const vector<T, Alloc>::iterator &left, const vector<T, Alloc>::iterator &right)
			{
				return (left.base() >= right.base());
			}

			friend bool operator<(const vector<T, Alloc>::iterator &left, const vector<T, Alloc>::iterator &right)
			{
				return (left.base() < right.base());
			}

			friend bool operator<=(const vector<T, Alloc>::iterator &left, const vector<T, Alloc>::iterator &right)
			{
				return (left.base() <= right.base());
			}

			friend vector<T, Alloc>::difference_type operator-(const vector<T, Alloc>::iterator &left, const vector<T, Alloc>::iterator &right)
			{
				return (left.base() - right.base());
			}

			friend vector<T, Alloc>::difference_type operator+(const vector<T, Alloc>::iterator &left, const vector<T, Alloc>::iterator &right)
			{
				return (left.base() + right.base());
			}
	};

	template<class T, class Alloc>
	class ft::vector<T, Alloc>::const_iterator
	{
		private:
			const T *arr;

		public:
			typedef typename ft::iterator_traits<const T *>::value_type			value_type;
			typedef typename ft::iterator_traits<const T *>::pointer			pointer;
			typedef typename ft::iterator_traits<const T *>::reference			reference;
			typedef typename ft::iterator_traits<const T *>::difference_type	difference_type;
			typedef typename ft::iterator_traits<const T *>::iterator_category	iterator_category;

			const_iterator() {}
			explicit const_iterator(const T *ptr) : arr(ptr) {}
			const_iterator(const const_iterator &other) : arr(other.base()) {}

			const_iterator &operator=(const const_iterator &other)
			{
				arr = other.arr;
				return (*this);
			}

			~const_iterator() {}

			const pointer base() const
			{
				return (arr);
			}

			const reference operator*() const
			{
				return (*arr);
			}

			const pointer operator->() const
			{
				return (arr);
			}

			const_iterator &operator++()
			{
				arr++;
				return (*this);
			}

			const_iterator operator++(int)
			{
				const_iterator tmp(*this);
				++(*this);
				return (tmp);
			}

			const_iterator &operator--()
			{
				arr--;
				return (*this);
			}

			const_iterator operator--(int)
			{
				const_iterator tmp(*this);
				--(*this);
				return(tmp);
			}

			const_iterator &operator+=(difference_type n)
			{
				arr += n;
				return (*this);
			}

			const_iterator &operator-=(difference_type n)
			{
				arr -= n;
				return (*this);
			}

			const_iterator operator+(difference_type n) const
			{
				const_iterator tmp(*this);
				tmp += n;
				return (tmp);
			}

			const_iterator operator-(difference_type n) const
			{
				const_iterator tmp(*this);
				tmp -= n;
				return (tmp);
			}

			const reference operator[](difference_type i)
			{
				return (*(arr + i));
			}

			friend bool operator==(const vector<T, Alloc>::const_iterator &left, const vector<T, Alloc>::const_iterator &right)
			{
				return (left.base() == right.base());
			}

			friend bool operator!=(const vector<T, Alloc>::const_iterator &left, const vector<T, Alloc>::const_iterator &right)
			{
				return (left.base() != right.base());
			}

			friend bool operator>(const vector<T, Alloc>::const_iterator &left, const vector<T, Alloc>::const_iterator &right)
			{
				return (left.base() > right.base());
			}

			friend bool operator>=(const vector<T, Alloc>::const_iterator &left, const vector<T, Alloc>::const_iterator &right)
			{
				return (left.base() >= right.base());
			}

			friend bool operator<(const vector<T, Alloc>::const_iterator &left, const vector<T, Alloc>::const_iterator &right)
			{
				return (left.base() < right.base());
			}

			friend bool operator<=(const vector<T, Alloc>::const_iterator &left, const vector<T, Alloc>::const_iterator &right)
			{
				return (left.base() <= right.base());
			}

			friend vector<T, Alloc>::difference_type operator-(const vector<T, Alloc>::const_iterator &left, const vector<T, Alloc>::const_iterator &right)
			{
				return (left.base() - right.base());
			}

			friend vector<T, Alloc>::difference_type operator+(const vector<T, Alloc>::const_iterator &left, const vector<T, Alloc>::const_iterator &right)
			{
				return (left.base() + right.base());
			}
	};
}

#endif
