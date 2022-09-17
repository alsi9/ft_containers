#include "RBTree.hpp"

#ifndef RBTREE_LOOKUP_HPP
#define RBTREE_LOOKUP_HPP

namespace ft
{
	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::iterator RBTree<T, Compare, Alloc>::find(const value_type &key)
	{
		return iterator(_find_node(key), _root);
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::const_iterator RBTree<T, Compare, Alloc>::find(const value_type &key) const
	{
		return const_iterator(_find_node(key), _root);
	}

	template<class T, class Compare, class Alloc>
	ft::pair<typename RBTree<T, Compare, Alloc>::iterator, typename RBTree<T, Compare, Alloc>::iterator> RBTree<T, Compare, Alloc>::equal_range(const value_type &key)
	{
		return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
	}

	template<class T, class Compare, class Alloc>
	ft::pair<typename RBTree<T, Compare, Alloc>::const_iterator, typename RBTree<T, Compare, Alloc>::const_iterator> RBTree<T, Compare, Alloc>::equal_range(const value_type &key) const
	{
		return (ft::make_pair(this->lower_bound(key), this->upper_bound(key)));
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::iterator RBTree<T, Compare, Alloc>::lower_bound(const value_type &key)
	{
		Node *curr = _root;
		Node *res = NULL;
		while (curr)
		{
			if (_comp(key, curr->value))
			{
				res = curr;
				curr = curr->left;
			}
			else if (not _comp(curr->value, key))
			{
				res = curr;
				curr = curr->left;
			}
			else
				curr = curr->right;
		}
		return iterator(res, _root);
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::const_iterator RBTree<T, Compare, Alloc>::lower_bound(const value_type &key) const
	{
		Node *curr = _root;
		Node *res = NULL;
		while (curr)
		{
			if (_comp(key, curr->value))
			{
				res = curr;
				curr = curr->left;
			}
			else if (not _comp(curr->value, key))
			{
				res = curr;
				curr = curr->left;
			}
			else
				curr = curr->right;
		}
		return const_iterator(res, _root);
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::iterator RBTree<T, Compare, Alloc>::upper_bound(const value_type &key)
	{
		Node *curr = _root;
		Node *res = NULL;
		while (curr)
		{
			if (_comp(key, curr->value))
			{
				res = curr;
				curr = curr->left;
			}
			else
				curr = curr->right;
		}
		return iterator(res, _root);
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::const_iterator RBTree<T, Compare, Alloc>::upper_bound(const value_type &key) const
	{
		Node *curr = _root;
		Node *res = NULL;
		while (curr)
		{
			if (_comp(key, curr->value))
			{
				res = curr;
				curr = curr->left;
			}
			else
				curr = curr->right;
		}
		return const_iterator(res, _root);
	}
}

#endif
