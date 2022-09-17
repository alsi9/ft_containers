#include "../RBTree/RBTree.hpp"

#ifndef SET_HPP
#define SET_HPP

namespace ft
{
	template<class Key, class Compare = std::less<Key>, class Alloc = std::allocator<Key> >
	class set
	{
		public:
			typedef Key								key_type;
			typedef Key								value_type;
			typedef std::size_t						size_type;
			typedef std::ptrdiff_t 					difference_type;
			typedef Compare							key_compare;
			typedef Alloc							allocator_type;
			typedef value_type&						reference;
			typedef const value_type&				const_reference;
			typedef typename Alloc::pointer			pointer;
			typedef typename Alloc::const_pointer	const_pointer;

			typedef typename ft::RBTree<Key, Compare, Alloc>::iterator					iterator;
			typedef typename ft::RBTree<Key, Compare, Alloc>::const_iterator			const_iterator;
			typedef	typename ft::RBTree<Key, Compare, Alloc>::reverse_iterator			reverse_iterator;
			typedef	typename ft::RBTree<Key, Compare, Alloc>::const_reverse_iterator	const_reverse_iterator;

			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class set<key_type, key_compare, Alloc>;

				protected:
				Compare comp;

				public:
				value_compare() : comp(Compare()) {}
				value_compare(Compare c) : comp(c()) {}

				bool operator()(const value_type &x, const value_type &y) const {
					return (comp(x.first, y.first));
				}
			};

	private:
		ft::RBTree<Key, Compare, Alloc> _tree;
	public:
		//constructor
		set() : _tree() {}

		explicit set(const Compare& comp, const Alloc& alloc = Alloc()) : _tree(comp, alloc) {}

		template<class InIt>
		set(InIt first, InIt last, const Compare& comp = Compare(), const Alloc& alloc = Alloc()) : _tree(comp, alloc)
		{
			for (; first != last; ++first)
				_tree.insert(*first);
		}

		set(const set &x) : _tree(x._tree) {}

		set &operator=(const set &x)
		{
			_tree = x._tree;
			return (*this);
		}

		~set() {}

		allocator_type get_allocator() const
		{
			return (_tree.get_allocator());
		}

		//iterators
		iterator begin()
		{
			return (_tree.begin());
		}

		const_iterator begin() const
		{
			return (_tree.begin());
		}

		iterator end()
		{
			return (_tree.end());
		}

		const_iterator end() const
		{
			return (_tree.end());
		}

		reverse_iterator rbegin()
		{
			return (_tree.rbegin());
		}

		const_reverse_iterator rbegin() const
		{
			return (_tree.rbegin());
		}

		reverse_iterator rend()
		{
			return (_tree.rend());
		}

		const_reverse_iterator rend() const
		{
			return (_tree.rend());
		}

		//capacity
		bool empty() const
		{
			return (_tree.end());
		}

		size_type size() const
		{
			return (_tree.size());
		}

		size_type maxsize() const
		{
			return (_tree.maxsize());
		}

		//modifiers
		void clear()
		{
			_tree.clear();
		}

		ft::pair<iterator, bool> insert(const value_type &x)
		{
			return (_tree.insert(x));
		}

		iterator insert(iterator it, const value_type &x)
		{
			return (_tree.insert(it, x));
		}

		template<class InIt>
		void insert(typename enable_if<!is_integral<InIt>::value, InIt>::type first, InIt last)
		{
			_tree.insert(first, last);
		}

		void erase(iterator it)
		{
			return (_tree.erase(it));
		}

		void erase(iterator first, iterator last)
		{
			return (_tree.erase(first, last));
		}

		size_type erase(const key_type &key)
		{
			return (_tree.erase(ft::make_pair(key, Key())));
		}

		void swap(set &x)
		{
			_tree.swap(x._tree);
		}

		//lookup
		size_type count(const key_type &key) const
		{
			return (_tree.find(key) == _tree.end() ? 0 : 1);
		}

		iterator find(const key_type &key)
		{
			return (_tree.find(key));
		}

		const_iterator find(const key_type &key) const
		{
			return (_tree.find(key));
		}

		ft::pair<iterator, iterator> equal_range(const key_type &key)
		{
			return (_tree.equal_range(key));
		}

		ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const
		{
			return (_tree.equal_range(key));
		}

		iterator lower_bound(const key_type &key)
		{
			return (_tree.lower_bound(key));
		}

		const_iterator lower_bound(const key_type &key) const
		{
			return (_tree.lower_bound(key));
		}

		iterator upper_bound(const key_type &key)
		{
			return (_tree.upper_bound(key));
		}

		const_iterator upper_bound(const key_type &key) const
		{
			return (_tree.upper_bound(key));
		}

		//observers
		key_compare key_comp() const
		{
			return (key_compare());
		}
		value_compare value_comp() const
		{
			return (value_compare(key_compare()));
		}
	};

	template<class Key, class Compare, class Alloc>
	bool operator==(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
	{
		return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
	}

	template<class Key, class Compare, class Alloc>
	bool operator!=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
	{
		return !(x == y);
	}

	template<class Key, class Compare, class Alloc>
	bool operator<(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template<class Key, class Compare, class Alloc>
	bool operator>(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
	{
		return (y < x);
	}

	template<class Key, class Compare, class Alloc>
	bool operator<=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
	{
		return !(y < x);
	}

	template<class Key, class Compare, class Alloc>
	bool operator>=(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
	{
		return !(x < y);
	}

	template<class Key, class Compare, class Alloc>
	void swap(const set<Key, Compare, Alloc> &x, const set<Key, Compare, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif
