#include "../vector/vector.hpp"

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
	template<class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type make_distance(InputIt first, InputIt last, std::random_access_iterator_tag)
	{
		return (last - first);
	}

	template<class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type make_distance(InputIt first, InputIt last, std::input_iterator_tag)
	{
		typename ft::iterator_traits<InputIt>::difference_type num = 0;
		while (first != last)
		{
			++first;
			++num;
		}
		return (num);
	}

	template<class InputIt>
	typename ft::iterator_traits<InputIt>::difference_type distance(InputIt first, InputIt last)
	{
		return (ft::make_distance(first, last, typename ft::iterator_traits<InputIt>::iterator_category()));
	}


	template<bool B, typename T = void>
	struct enable_if {};

	template<typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};


	template<bool B, class T>
	struct is_integral_res
	{
		static const bool value = B;
		operator T() const {return value;}
	};

	template<typename T> struct is_integral 				: public is_integral_res<false, T> {};

	template<> struct is_integral<bool> 					: public is_integral_res<true, bool> {};
	template<> struct is_integral<char> 					: public is_integral_res<true, char> {};
	template<> struct is_integral<signed char> 				: public is_integral_res<true, signed char> {};
	template<> struct is_integral<unsigned char> 			: public is_integral_res<true, unsigned char> {};
	template<> struct is_integral<wchar_t> 					: public is_integral_res<true, wchar_t> {};

	template<> struct is_integral<char16_t> 				: public is_integral_res<true, char16_t> {};
	template<> struct is_integral<char32_t> 				: public is_integral_res<true, char32_t> {};

	template<> struct is_integral<short> 					: public is_integral_res<true, short> {};
	template<> struct is_integral<unsigned short> 			: public is_integral_res<true, unsigned short> {};
	template<> struct is_integral<int> 						: public is_integral_res<true, int> {};
	template<> struct is_integral<unsigned int> 			: public is_integral_res<true, unsigned int> {};
	template<> struct is_integral<long int> 				: public is_integral_res<true, long int> {};
	template<> struct is_integral<unsigned long int> 		: public is_integral_res<true, unsigned long int> {};
	template<> struct is_integral<long long int> 			: public is_integral_res<true, long long int> {};
	template<> struct is_integral<unsigned long long int> 	: public is_integral_res<true, unsigned long long int> {};



	template<class InIt1, class InIt2>
	bool lexicographical_compare(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first1 > *first2)
				return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	template<class InIt1, class InIt2, class Compare>
	bool lexicographical_compare(InIt1 first1, InIt1 last1, InIt2 first2, InIt2 last2, Compare comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
			{
				if (comp(*first1, *first2))
					return true;
				if (comp(*first2, *first1))
					return false;
			}
			return (first1 == last1) && (first2 != last2);
	}


	template<class InIt1, class InIt2>
	bool equal(InIt1 first1, InIt1 last1, InIt2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
				return false;
		}
		return true;
	}

	template<class InIt1, class InIt2, class BinaryPredicate>
	bool equal(InIt1 first1, InIt1 last1, InIt2 first2, BinaryPredicate p)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
				return false;
		}
		return true;
	}


	template<class T1, class T2>
	struct pair
	{
		T1 first;
		T2 second;

		pair() : first(), second() {};
		pair(const T1 &x, const T2 &y) : first(x), second(y) {};

		template<class U1, class U2>
		pair(const pair<U1, U2> &x) : first(x.first), second(x.second) {};

		template<class V1, class V2>
		pair<V1, V2> &operator=(const pair<V1, V2> &x)
		{
			if (this == &x)
				return (*this);
			first = x.first;
			second = x.second;
			return (*this);
		}
	};

	template<class T1, class T2>
	bool operator==(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return (x.first == y.first && x.second == y.second);
	}

	template<class T1, class T2>
	bool operator!=(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return !(x == y);
	}

	template<class T1, class T2>
	bool operator<(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return (x.first < y.first || (!(x.first < y.first) && x.second < y.second));
	}

	template<class T1, class T2>
	bool operator>(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return (y < x);
	}

	template<class T1, class T2>
	bool operator<=(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return !(y < x);
	}

	template<class T1, class T2>
	bool operator>=(const pair<T1, T2> &x, const pair<T1, T2> &y)
	{
		return !(x < y);
	}

	template< class T1, class T2 >
	pair<T1,T2> make_pair(T1 x, T2 y)
	{
		return (pair<T1, T2>(x, y));
	}

	template<class T>
	void	swap(T & a, T & b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}
}

#endif
