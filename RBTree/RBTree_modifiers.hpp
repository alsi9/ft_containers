#include "RBTree.hpp"

#ifndef RBTREE_MODIFIERS_HPP
#define RBTREE_MODIFIERS_HPP

namespace ft
{
	template<class T, class Compare, class Alloc>
	void RBTree<T, Compare, Alloc>::clear()
	{
		_clear_tree(_root);
		_root = NULL;
	}

	template<class T, class Compare, class Alloc>
	ft::pair<typename RBTree<T, Compare, Alloc>::iterator, bool> RBTree<T, Compare, Alloc>::insert(const value_type &x)
	{
		ft::pair<Node *, bool>	tmp = _insert_to_tree(&_root, x);
		return ft::make_pair(iterator(tmp.first, _root), tmp.second);

	}

	template<class T, class Compare, class Alloc>
	typename ft::RBTree<T, Compare, Alloc>::iterator ft::RBTree<T, Compare, Alloc>::insert(iterator it, const value_type &x)
	{
		ft::pair<Node *, bool>	tmp = _insert_to_tree(&_root, x);
		return iterator(tmp.first, _root);
	}

	template<class T, class Compare, class Alloc>
	template<class InIt>
	void RBTree<T, Compare, Alloc>::insert(typename enable_if<!is_integral<InIt>::value, InIt>::type first, InIt last)
	{
		for (InIt it = first; it != last; ++it)
		insert(*it);
	}

	template<class T, class Compare, class Alloc>
	void RBTree<T, Compare, Alloc>::erase(typename RBTree<T, Compare, Alloc>::iterator it)
	{
		_erase_node(it.node);
	}

	template<class T, class Compare, class Alloc>
	void RBTree<T, Compare, Alloc>::erase(iterator first, iterator last)
	{
		for (; first != last; )
		_erase_node((first++).node);
	}

	template<class T, class Compare, class Alloc>
	typename RBTree<T, Compare, Alloc>::size_type RBTree<T, Compare, Alloc>::erase(const value_type &key)
	{
		Node *node = _find_node(key);
		if (node)
		{
			_erase_node(node);
			return (1);
		}
		return (0);
	}

	template<class T, class Compare, class Alloc>
	void RBTree<T, Compare, Alloc>::swap(RBTree &x)
	{
		ft::swap(x._root, _root);
		ft::swap(x._size, _size);
	}
}

#endif
