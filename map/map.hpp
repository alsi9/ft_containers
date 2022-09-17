#include "../RBTree/RBTree.hpp"

#ifndef MAP_HPP
#define MAP_HPP

namespace ft
{
	template <class Key, class T, class Compare>
	struct PairCompare
	{
		bool	operator()(const ft::pair<const Key, T> & first, const ft::pair<const Key, T> & second) const
		{
			return Compare()(first.first, second.first);
		}
	};

	template<class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
		public:
			typedef Key												key_type;
			typedef T 												mapped_type;
			typedef Compare 										key_compare;
			typedef Alloc 											allocator_type;
			typedef typename allocator_type::pointer 				pointer;
			typedef typename allocator_type::const_pointer 			const_pointer;
			typedef ft::pair<const key_type, mapped_type> 			value_type;
			typedef std::size_t 									size_type;
			typedef std::ptrdiff_t 									difference_type;
			typedef PairCompare<Key, T, Compare>					pair_compare;
			typedef value_type &									reference;
			typedef const value_type & 								const_reference;

			typedef RBTreeIterator<ft::pair<const Key, T> >     	iterator;
			typedef RBTreeConstIterator<ft::pair<const Key, T> > 	const_iterator;
			typedef ft::reverse_iterator<iterator> 					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator> 			const_reverse_iterator;


			class value_compare : public std::binary_function<value_type, value_type, bool>
			{
				friend class map<key_type, key_compare, Alloc>;

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
			RBTree<ft::pair<const Key, T>, pair_compare, Alloc> _tree;

		public:
			//constructor
			map() : _tree() {}
			explicit map(const Compare &comp, const Alloc &alloc = Alloc()) : _tree(comp, alloc) {}

			template<class InIt>
			map(InIt first, InIt second, const Compare &comp = Compare(), const Alloc &alloc = Alloc()) : _tree(comp, alloc)
			{
				for (; first != second; ++first)
					_tree.insert(*first);
			}

			map(const map &x) : _tree(x._tree) {}

			map &operator=(const map &x)
			{
				_tree = x._tree;
				return *this;
			}

			~map() {}

			allocator_type get_allocator() const
			{
				return _tree.get_allocator();
			}

			//element access
			mapped_type &at(const Key &key)
			{
				iterator it = find(key);
				if (it == end())
					throw std::out_of_range("vector");
				return (it->second);
			}

			const mapped_type &at(const Key &key) const
			{
				const_iterator it = find(key);
				if (it == end())
					throw std::out_of_range("vector");
				return (it->second);
			}

			mapped_type &operator[](const Key &key)
			{
				ft::pair<iterator, bool> it = insert(ft::make_pair(key, T()));
				return ((it.first)->second);
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
				return (_tree.rend());
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
				return (_tree.erase(ft::make_pair(key, T())));
			}

			void swap(map &x)
			{
				_tree.swap(x._tree);
			}

			//lookup
			size_type count(const key_type &key) const
			{
				return (_tree.find(ft::make_pair(key, T()) == _tree.end() ? 0 : 1));
			}

			iterator find(const key_type &key)
			{
				return (_tree.find(ft::make_pair(key, T())));
			}

			const_iterator find(const key_type &key) const
			{
				return (_tree.find(ft::make_pair(key, T())));
			}

			ft::pair<iterator, iterator> equal_range(const key_type &key)
			{
				return (_tree.equal_range(ft::make_pair(key, T())));
			}

			ft::pair<const_iterator, const_iterator> equal_range(const key_type &key) const
			{
				return (_tree.equal_range(ft::make_pair(key, T())));
			}

			iterator lower_bound(const key_type &key)
			{
				return (_tree.lower_bound(ft::make_pair(key, T())));
			}

			const_iterator lower_bound(const key_type &key) const
			{
				return (_tree.lower_bound(ft::make_pair(key, T())));
			}

			iterator upper_bound(const key_type &key)
			{
				return (_tree.upper_bound(ft::make_pair(key, T())));
			}

			const_iterator upper_bound(const key_type &key) const
			{
				return (_tree.upper_bound(ft::make_pair(key, T())));
			}

			//observers
			key_compare key_comp() const
			{
				return (key_compare());
			}

			value_compare value_comp() const
			{
				return value_compare(key_compare());
			}
	};

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return (x.size() == y.size() && ft::equal(x.begin(), x.end(), y.begin()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return !(x == y);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return (ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return (y < x);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return !(y < x);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		return !(x < y);
	}

	template<class Key, class T, class Compare, class Alloc>
	void swap(const map<Key, T, Compare, Alloc> &x, const map<Key, T, Compare, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif
