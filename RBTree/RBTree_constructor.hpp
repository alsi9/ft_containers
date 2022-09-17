
#include "RBTree.hpp"

#ifndef RBTREE_CONSTRUCTOR_HPP
#define RBTREE_CONSTRUCTOR_HPP

namespace ft
{
	template<class T, class Compare, class Alloc>
	RBTree<T, Compare, Alloc>::RBTree() : _root(NULL), _alloc(), _size(0) {}

	template<class T, class Compare, class Alloc>
	RBTree<T, Compare, Alloc>::RBTree(Compare &comp, Alloc &alloc) : _root(NULL), _alloc(alloc), _comp(comp), _size(0) {}

	template<class T, class Compare, class Alloc>
	RBTree<T, Compare, Alloc>::RBTree(const RBTree &x) :_alloc(x._alloc), _comp(x._comp), _root(NULL)
	{
		_copy_tree(_root, NULL, x._root);
		_size = x._size;
	}

	template<class T, class Compare, class Alloc>
	RBTree<T, Compare, Alloc> &RBTree<T, Compare, Alloc>::operator=(const RBTree &x)
	{
		Node	*tmp = NULL;
		_copy_tree(tmp, NULL, x._root);
		_clear_tree(_root);
		_root = tmp;
		_size = x._size;
		return *this;
	}

	template<class T, class Compare, class Alloc>
	RBTree<T, Compare, Alloc>::~RBTree()
	{
		_clear_tree(_root);
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::allocator_type RBTree<T, Compare, Alloc>::get_allocator() const
	{
		return _alloc;
	}
}


#endif
