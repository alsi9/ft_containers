#include "RBTree.hpp"

#ifndef RBTREE_CAPACITY_HPP
#define RBTREE_CAPACITY_HPP

namespace ft
{
	template<class T, class Compare, class Alloc>
	bool RBTree<T, Compare, Alloc>::empty() const
	{
		return (_size == 0);
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::size_type RBTree<T, Compare, Alloc>::size() const
	{
		return (_size);
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::size_type RBTree<T, Compare, Alloc>::maxsize() const
	{
		return (node_allocator_type().max_size());
	}
}

#endif
