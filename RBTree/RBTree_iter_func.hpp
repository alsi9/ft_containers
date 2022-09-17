#include "RBTree.hpp"

#ifndef RBTREE_ITER_FUNC_HPP
#define RBTREE_ITER_FUNC_HPP

namespace ft
{
	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::iterator RBTree<T, Compare, Alloc>::begin()
	{
		Node *min = _root;
		if (min)
		{
			while (min->left)
				min = min->left;
		}
		return (iterator(min, _root));
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::const_iterator RBTree<T, Compare, Alloc>::begin() const
	{
		Node *min = _root;
		if (min)
		{
			while (min->left)
				min = min->left;
		}
		return (const_iterator(min, _root));
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::iterator RBTree<T, Compare, Alloc>::end()
	{
		return (iterator(NULL, _root));
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::const_iterator RBTree<T, Compare, Alloc>::end() const
	{
		return (const_iterator(NULL, _root));
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::reverse_iterator RBTree<T, Compare, Alloc>::rbegin()
	{
		return (reverse_iterator(end()));
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::const_reverse_iterator RBTree<T, Compare, Alloc>::rbegin() const
	{
		return (const_reverse_iterator(end()));
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::reverse_iterator RBTree<T, Compare, Alloc>::rend()
	{
		return (reverse_iterator(begin()));
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::const_reverse_iterator RBTree<T, Compare, Alloc>::rend() const
	{
		return (const_reverse_iterator(begin()));
	}
}

#endif
