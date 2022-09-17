#include "../vector/vector.hpp"
#include "iterator_traits.hpp"

#ifndef REVERSE_ITERATOR_HPP
#define REVERSE_ITERATOR_HPP

namespace ft
{
	template<class Iter>
	class reverse_iterator
	{
	public:
		typedef Iter 															iterator_type;
		typedef typename ft::iterator_traits<iterator_type>::value_type			value_type;
		typedef typename ft::iterator_traits<iterator_type>::pointer			pointer;
		typedef typename ft::iterator_traits<iterator_type>::reference			reference;
		typedef typename ft::iterator_traits<iterator_type>::difference_type	difference_type;
		typedef typename ft::iterator_traits<iterator_type>::iterator_category	iterator_category;

	private:
		iterator_type it;

	public:
		reverse_iterator() : it() {}
		explicit reverse_iterator(iterator_type ptr) : it(ptr) {}
		reverse_iterator(const reverse_iterator &other) : it(other.it) {}

		reverse_iterator &operator=(const reverse_iterator &other)
		{
			if (this != &other)
				it = other.it;
			return (*this);
		}

		~reverse_iterator() {}

		pointer base()
		{
			return (it);
		}

		reference operator*() const
		{
			iterator_type tmp = it;
			return (*(--tmp));
		}

		pointer operator->() const
		{
			return (&(operator*()));
		}

		reverse_iterator &operator++()
		{
			it--;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator tmp = *this;
			++(*this);
			return (tmp);
		}

		reverse_iterator &operator--()
		{
			it++;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator tmp = *this;
			--(*this);
			return(tmp);
		}

		reverse_iterator &operator+=(difference_type n)
		{
			it -= n;
			return (*this);
		}

		reverse_iterator &operator-=(difference_type n)
		{
			it += n;
			return (*this);
		}

		reverse_iterator operator+(difference_type n) const
		{
			reverse_iterator tmp = *this;
			return (static_cast<reverse_iterator>(tmp - n));
		}

		reverse_iterator operator-(difference_type n) const
		{
			reverse_iterator tmp = *this;
			return (static_cast<reverse_iterator>(tmp + n));
		}

		reference operator[](difference_type i)
		{
			return (*(*this + i));
		}

		friend bool operator==(const reverse_iterator &left, const reverse_iterator &right)
		{
			return (left.base() == right.base());
		}

		friend bool operator!=(const reverse_iterator &left, const reverse_iterator &right)
		{
			return (left.base() != right.base());
		}

		friend bool operator>(const reverse_iterator &left, const reverse_iterator &right)
		{
			return (left.base() > right.base());
		}

		friend bool operator>=(const reverse_iterator &left, const reverse_iterator &right)
		{
			return (left.base() >= right.base());
		}

		friend bool operator<(const reverse_iterator &left, const reverse_iterator &right)
		{
			return (left.base() < right.base());
		}

		friend bool operator<=(const reverse_iterator &left, const reverse_iterator &right)
		{
			return (left.base() <= right.base());
		}

		template<class T, class Alloc>
		friend difference_type operator-(const reverse_iterator &left, const reverse_iterator &right)
		{
			return (left.base() - right.base());
		}

		template<class T, class Alloc>
		friend difference_type operator+(const reverse_iterator &left, const reverse_iterator &right)
		{
			return (left.base() + right.base());
		}

		template<class Itr>
		operator typename ft::reverse_iterator<Itr>()
		{
			return (ft::reverse_iterator<Itr>(it));
		}
	};
}

#endif
