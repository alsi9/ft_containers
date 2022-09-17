
#ifndef FT_STACK
#define FT_STACK

#include <iostream>
#include "../vector/vector.hpp"

namespace ft
{
	template<class T, class Container = ft::vector<T> >
	class stack
	{
		public:
			typedef Container container_type;
			typedef typename container_type::value_type value_type;
			typedef typename container_type::reference reference;
			typedef typename container_type::const_reference const_reference;
			typedef typename container_type::size_type size_type;

		protected:
			container_type _c;

		public:
			explicit stack(const container_type &cont = container_type()) : _c(cont) {};

			stack(const stack<T, Container> &other) : _c(other._c) {};

			stack &operator=(const stack<T, Container> &other)
			{
				if (this != &other)
					_c = other._c;
				return (*this);
			}

			~stack() {}

			void push(const value_type &value)
			{
				return (_c.push_back(value));
			}

			void pop()
			{
				return (_c.pop_back());
			}

			size_type size() const
			{
				return (_c.size());
			}

			reference top()
			{
				return (_c.back());
			}

			const_reference top() const
			{
				return (_c.back());
			}

			bool empty() const
			{
				return (_c.empty());
			}

			template<class Type, class Cont>
			friend bool operator!=(const stack<Type, Cont> &x, const stack<Type, Cont> &y)
			{
				return (x._c != y._c);
			}

			template<class Type, class Cont>
			friend bool operator<(const stack<Type, Cont> &x, const stack<Type, Cont> &y)
			{
				return (x._c < y._c);
			}

			template<class Type, class Cont>
			friend bool operator<=(const stack<Type, Cont> &x, const stack<Type, Cont> &y)
			{
				return (x._c <= y._c);
			}

			template<class Type, class Cont>
			friend bool operator==(const stack<Type, Cont> &x, const stack<Type, Cont> &y)
			{
				return (x._c == y._c);
			}

			template<class Type, class Cont>
			friend bool operator>(const stack<Type, Cont> &x, const stack<Type, Cont> &y)
			{
				return (x._c > y._c);
			}

			template<class Type, class Cont>
			friend bool operator>=(const stack<Type, Cont> &x, const stack<Type, Cont> &y)
			{
				return (x._c >= y._c);
			}
	};
}

#endif