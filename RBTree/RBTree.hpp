
#include <iostream>
#include "../utils/utils.hpp"
#include "../utils/iterator_traits.hpp"

#ifndef RBTREE_HPP
#define RBTREE_HPP

namespace ft {
	template<class T>
	class RBTreeIterator;

	template<class T>
	class RBTreeConstIterator;

	template<class T>
	struct Node {
		T value;
		Node *left;
		Node *right;
		Node *parent;
		bool is_red;

		Node(const T &value, Node *left = NULL, Node *right = NULL, Node *parent = NULL, bool is_red = true)
				: value(value), left(left), right(right), parent(parent), is_red(is_red) {}
	};

	template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class RBTree {
	public:
		typedef T value_type;
		typedef Compare comparator_type;
		typedef Alloc allocator_type;
		typedef std::size_t size_type;
		typedef std::ptrdiff_t difference_type;
		typedef Node<T> Node;
		typedef RBTreeIterator<T> iterator;
		typedef RBTreeConstIterator<T> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::template rebind<Node>::other node_allocator_type;

	private:
		Node *_root;
		comparator_type _comp;
		allocator_type _alloc;
		size_type _size;

	public:
		RBTree();
		RBTree(Compare &comp, Alloc &alloc = Alloc());
		RBTree(const RBTree &x);
		RBTree &operator=(const RBTree &x);
		~RBTree();
		allocator_type get_allocator() const;

//			//iterators
		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;

		//capacity
		bool empty() const;
		size_type size() const;
		size_type maxsize() const;

		//modifiers
		void clear();
		ft::pair<iterator, bool> insert(const value_type &x);
		iterator insert(iterator it, const value_type &x);

		template<class InIt>
		void insert(typename enable_if<!is_integral<InIt>::value, InIt>::type first, InIt last);

		void erase(iterator it);
		void erase(iterator first, iterator last);
		size_type erase(const value_type &key);
		void swap(RBTree &x);

		//lookup
		iterator find(const value_type &key);
		const_iterator find(const value_type &key) const;
		ft::pair<iterator, iterator> equal_range(const value_type &key);
		ft::pair<const_iterator, const_iterator> equal_range(const value_type &key) const;
		iterator lower_bound(const value_type &key);
		const_iterator lower_bound(const value_type &key) const;
		iterator upper_bound(const value_type &key);
		const_iterator upper_bound(const value_type &key) const;

	private:
		Node *_get_new_node(const T& value, Node *parent = NULL, Node *left = NULL, Node *right = NULL, bool is_red = true);
		void _remove_node(Node *nod);
		bool _is_red(Node *nod);
		Node *_find_node(const T & key) const;
		ft::pair<Node*, bool> _insert_to_tree(Node **tree, const T & key);
		void _fix_node_after_inserting(Node *nod);
		void _copy_tree(Node *&current, Node *curr_parent, Node *other_node);
		void _clear_tree(Node *current);
		void _rotate_left(Node * nod);
		void _rotate_right(Node * nod);
		void _erase_node(Node *nod);
		void _swap_nodes(Node *nd1, Node *nd2);
		void _fix_node_after_erasing(Node **removed, Node *parent);
	};

	template<class T>
	class RBTreeIterator
	{
	public:
		typedef ft::Node<T> 										Node;
		typedef std::bidirectional_iterator_tag 					iterator_category;
		typedef typename ft::iterator_traits<T*>::value_type 		value_type;
		typedef typename ft::iterator_traits<T*>::reference 		reference;
		typedef typename ft::iterator_traits<T*>::pointer			pointer;
		typedef typename ft::iterator_traits<T*>::difference_type	difference_type;

		Node	*root;
		Node	*node;

		RBTreeIterator() {}
		RBTreeIterator(Node *nod, Node *root) : root(root), node(nod) {};
		RBTreeIterator(const RBTreeIterator &x) : root(x.root), node(x.node) {};

		RBTreeIterator &operator=(const RBTreeIterator &x)
		{
			node = x._node;
			return (*this);
		}

		~RBTreeIterator() {}

		T &operator*()
		{
			return (node->value);
		}

		T *operator->()
		{
			return &(node->value);
		}

		RBTreeIterator &operator++()
		{
			if (node == NULL)
			{
				if (root == NULL)
					return *this;
				node = root;
				while (node->left)
					node = node->left;
				return *this;
			}
			if (node->right)
			{
				node = node->right;
				while (node->left)
					node = node->left;
			}
			else
			{
				while (node->parent and node->parent->right == node)
					node = node->parent;
				node = node->parent;
			}
			return *this;
		}

		RBTreeIterator operator++(int)
		{
			RBTreeIterator tmp(*this);
			++(*this);
			return (tmp);
		}

		RBTreeIterator &operator--()
		{
			if (node == NULL)
			{
				if (root == NULL)
					return *this;
				node = root;
				while (node->right)
					node = node->right;
				return *this;
			}
			if (node->left)
			{
				node = node->left;
				while (node->right)
					node = node->right;
			}
			else
			{
				while (node->parent and node->parent->left == node)
					node = node->parent;
				node = node->parent;
			}
			return *this;
		}

		RBTreeIterator operator--(int)
		{
			RBTreeIterator tmp(*this);
			--(*this);
			return (tmp);
		}

		friend bool operator==(const RBTreeIterator &x, const RBTreeIterator &y)
		{
			return (x.node == y.node);
		}

		friend bool operator!=(const RBTreeIterator &x, const RBTreeIterator &y)
		{
			return (x.node != y.node);
		}
	};

	template<class T>
	class RBTreeConstIterator
	{
	public:
		typedef ft::Node<T> 											Node;
		typedef std::bidirectional_iterator_tag 						iterator_category;
		typedef typename ft::iterator_traits<const T*>::value_type 		value_type;
		typedef typename ft::iterator_traits<const T*>::reference 		reference;
		typedef typename ft::iterator_traits<const T*>::pointer			pointer;
		typedef typename ft::iterator_traits<const T*>::difference_type	difference_type;

		Node	*root;
		Node	*node;

		RBTreeConstIterator() {}
		RBTreeConstIterator(Node *nod, Node *root) : node(nod), root(root) {};
		RBTreeConstIterator(const RBTreeConstIterator &x) : root(x.root), node(x.node) {};

		RBTreeConstIterator &operator=(const RBTreeConstIterator &x)
		{
			node = x._node;
			return (*this);
		}

		~RBTreeConstIterator() {}

		T &operator*()
		{
			return (node->value);
		}

		T *operator->()
		{
			return &(node->value);
		}

		RBTreeConstIterator &operator++()
		{
			if (node == NULL)
			{
				if (root == NULL)
					return *this;
				node = root;
				while (node->left)
					node = node->left;
				return *this;
			}
			if (node->right)
			{
				node = node->right;
				while (node->left)
					node = node->left;
			}
			else
			{
				while (node->parent and node->parent->right == node)
					node = node->parent;
				node = node->parent;
			}
			return *this;
		}

		RBTreeConstIterator operator++(int)
		{
			RBTreeConstIterator tmp(*this);
			++(*this);
			return (tmp);
		}

		RBTreeConstIterator &operator--()
		{
			if (node == NULL)
			{
				if (root == NULL)
					return *this;
				node = root;
				while (node->right)
					node = node->right;
				return *this;
			}
			if (node->left)
			{
				node = node->left;
				while (node->right)
					node = node->right;
			}
			else
			{
				while (node->parent and node->parent->left == node)
					node = node->parent;
				node = node->parent;
			}
			return *this;
		}

		RBTreeConstIterator operator--(int)
		{
			RBTreeConstIterator tmp(*this);
			--(*this);
			return (tmp);
		}

		friend bool operator==(const RBTreeConstIterator &x, const RBTreeConstIterator &y)
		{
			return (x.node == y.node);
		}

		friend bool operator!=(const RBTreeConstIterator &x, const RBTreeConstIterator &y)
		{
			return (x.node != y.node);
		}
	};

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::Node *RBTree<T, Compare, Allocator>::_get_new_node(const T& value, Node *parent, Node *left, Node *right, bool is_red)
	{
		Node *tmp = node_allocator_type().allocate(1);
		node_allocator_type().construct(tmp, Node(value, left, right, parent, is_red));
		_size++;
		return tmp;
	}

	template <class T, class Compare, class Allocator>
	void RBTree<T, Compare, Allocator>::_remove_node(Node *nod)
	{
		node_allocator_type().destroy(nod);
		node_allocator_type().deallocate(nod, 1);
		_size--;
	}

	template <class T, class Compare, class Allocator>
	bool RBTree<T, Compare, Allocator>::_is_red(Node *nod)
	{
		return nod == NULL ? false : nod->is_red;
	}

	template <class T, class Compare, class Allocator>
	typename RBTree<T, Compare, Allocator>::Node *	RBTree<T, Compare, Allocator>::_find_node(const T & key) const
	{
		Node *tmp = _root;
		while (tmp != NULL)
		{
			if (_comp(key, tmp->value))
				tmp = tmp->left;
			else if (_comp(tmp->value, key))
				tmp = tmp->right;
			else
				return tmp;
		}
		return NULL;
	}

	template <class T, class Compare, class Allocator>
	ft::pair<typename RBTree<T, Compare, Allocator>::Node *, bool>	RBTree<T, Compare, Allocator>::_insert_to_tree(Node **tree, const T & key)
	{
		Node *parent = *tree == NULL ? NULL : (*tree)->parent;
		while (*tree != NULL)
		{
			if (_comp(key, (*tree)->value))
			{
				parent = *tree;
				tree = &((*tree)->left);
			}
			else if (_comp((*tree)->value, key))
			{
				parent = *tree;
				tree = &((*tree)->right);
			}
			else
				return ft::make_pair(*tree, false);
		}
		*tree = _get_new_node(key, parent);
		_fix_node_after_inserting(*tree);
		return ft::make_pair(*tree, true);
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::_fix_node_after_inserting(Node *nod)
	{
		while (_is_red(nod->parent))
		{
			if (nod == nod->parent->left)
			{
				if (_is_red(nod->parent->parent->right))
				{
					nod->parent->is_red = false;
					nod->parent->parent->right->is_red = false;
					nod->parent->parent->is_red = true;
					nod = nod->parent->parent;
					continue;
				}
				else
				{
					nod->parent->is_red = false;
					nod->parent->parent->is_red = true;
					_rotate_right(nod->parent->parent);
					break ;
				}
			}
			else
			{
				if (_is_red(nod->parent->parent->left))
				{
					nod->parent->is_red = false;
					nod->parent->parent->left->is_red = false;
					nod->parent->parent->is_red = true;
					nod = nod->parent->parent;
					continue;
				}
				else
				{
					nod->parent->is_red = false;
					nod->parent->parent->is_red = true;
					_rotate_left(nod->parent->parent);
					break ;
				}
			}
		}
		_root->is_red = false;
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::_copy_tree(Node *&current, Node *curr_parent, Node *other_node)
	{
		if (other_node == NULL)
			return ;
		current = _get_new_node(other_node->value, curr_parent);
		_copy_tree(current->left, current, other_node->left);
		_copy_tree(current->right, current, other_node->right);
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::_clear_tree(Node *current)
	{
		if (current == NULL)
			return ;
		_clear_tree(current->left);
		_clear_tree(current->right);
		_remove_node(current);
	}


	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::_rotate_left(Node *nod)
	{
		Node *tmp = nod->right;
		nod->right = tmp->left;
		if (tmp->left)
			tmp->left->parent = nod;
		tmp->left = nod;
		tmp->parent = nod->parent;
		nod->parent = tmp;
		if (tmp->parent)
		{
			if (tmp->parent->right == tmp->left)
				tmp->parent->right = tmp;
			else
				tmp->parent->left = tmp;
		}
		else
			_root = tmp;
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::_rotate_right(Node *nod)
	{
		Node *tmp = nod->left;
		nod->left = tmp->right;
		if (tmp->right)
			tmp->right->parent = nod;
		tmp->right = nod;
		tmp->parent = nod->parent;
		nod->parent = tmp;
		if (tmp->parent)
		{
			if (tmp->parent->left == tmp->right)
				tmp->parent->left = tmp;
			else
				tmp->parent->right = tmp;
		}
		else
			_root = tmp;
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::_erase_node(Node *nod)
	{
		Node *to_del = nod;
		if (nod->left and nod->right)
		{
			to_del = nod->right;
			while (to_del->left)
				to_del = to_del->left;
			_swap_nodes(nod, to_del);
			_erase_node(nod);
		}
		else if (nod->left)
		{
			nod->left->is_red = false;
			nod->left->parent = nod->parent;
			if (nod->parent)
			{
				if (nod->parent->left == nod)
					nod->parent->left = nod->left;
				else
					nod->parent->right = nod->left;
			}
			else
				_root = nod->left;
			_remove_node(to_del);
			return ;
		}
		else if (nod->right)
		{
			nod->right->is_red = false;
			nod->right->parent = nod->parent;
			if (nod->parent)
			{
				if (nod->parent->right == nod)
					nod->parent->right = nod->right;
				else
					nod->parent->left = nod->right;
			}
			else
				_root = nod->right;
			_remove_node(to_del);
			return ;
		}
		else
		{
			if (nod->is_red)
			{
				Node **tmp;
				if (nod->parent->right == nod)
					tmp = &nod->parent->right;
				else
					tmp = &nod->parent->left;
				_remove_node(*tmp);
				*tmp = NULL;
			}
			else
			{
				Node **tmp;
				Node *parent = nod->parent;
				if (nod->parent)
				{
					if (nod->parent->right == nod)
						tmp = &nod->parent->right;
					else
						tmp = &nod->parent->left;
				}
				else
					tmp = &_root;
				_remove_node(*tmp);
				*tmp = NULL;
				_fix_node_after_erasing(tmp, parent);
			}
		}
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::_swap_nodes(Node *nd1, Node *nd2)
	{
		ft::swap(nd1->is_red, nd2->is_red);
		if (nd1->left)
			nd1->left->parent = nd2;
		if (nd2->left)
			nd2->left->parent = nd1;
		ft::swap(nd1->left, nd2->left);
		if (nd1->right)
			nd1->right->parent = nd2;
		if (nd2->right)
			nd2->right->parent = nd1;
		ft::swap(nd1->right, nd2->right);
		if (nd1->parent)
		{
			if (nd1->parent->left == nd1)
				nd1->parent->left = nd2;
			else
				nd1->parent->right = nd2;
		}
		else
			_root = nd2;
		if (nd2->parent)
		{
			if (nd2->parent->left == nd2)
				nd2->parent->left = nd1;
			else
				nd2->parent->right = nd1;
		}
		else
			_root = nd1;
		ft::swap(nd1->parent, nd2->parent);
	}

	template <class T, class Compare, class Allocator>
	void	RBTree<T, Compare, Allocator>::_fix_node_after_erasing(Node **removed, Node *parent)
	{
		while (parent != NULL)
		{
			if (&parent->right == removed)
			{
				if (_is_red(parent))
				{
					if (_is_red(parent->left->right))
					{
						parent->is_red = false;
						_rotate_left(parent->left);
					}
					_rotate_right(parent);
					return ;
				}
				else
				{
					if (_is_red(parent->left))
					{
						if (_is_red(parent->left->right->left))
						{
							parent->left->right->left->is_red = false;
							_rotate_left(parent->left);
							_rotate_right(parent);
						}
						else if (_is_red(parent->left->right->right))
						{
							ft::swap(parent->left->right->is_red,
									 parent->left->right->right->is_red);
							_rotate_left(parent->left->right);
							parent->left->right->left->is_red = false;
							_rotate_left(parent->left);
							_rotate_right(parent);
						}
						else
						{
							parent->left->is_red = false;
							parent->left->right->is_red = true;
							_rotate_right(parent);
						}
						return;
					}
					else
					{
						if (_is_red(parent->left->right))
						{
							parent->left->right->is_red = false;
							_rotate_left(parent->left);
							_rotate_right(parent);
							return ;
						}
						else if (_is_red(parent->left->left))
						{
							parent->left->left->is_red = false;
							_rotate_right(parent);
							return ;
						}
						parent->left->is_red = true;
						if (parent->parent)
						{
							if (parent->parent->left == parent)
								removed = &parent->parent->left;
							else
								removed = &parent->parent->right;
						}
						parent = parent->parent;
					}
				}
			}
			else
			{
				if (_is_red(parent))
				{
					if (_is_red(parent->right->left))
					{
						parent->is_red = false;
						_rotate_right(parent->right);
					}
					_rotate_left(parent);
					return ;
				}
				else
				{
					if (_is_red(parent->right))
					{
						if (_is_red(parent->right->left->right))
						{
							parent->right->left->right->is_red = false;
							_rotate_right(parent->right);
							_rotate_left(parent);
						}
						else if (_is_red(parent->right->left->left))
						{
							ft::swap(parent->right->left->is_red,
									 parent->right->left->left->is_red);
							_rotate_right(parent->right->left);
							parent->right->left->right->is_red = false;
							_rotate_right(parent->right);
							_rotate_left(parent);
						}
						else
						{
							parent->right->is_red = false;
							parent->right->left->is_red = true;
							_rotate_left(parent);
						}
						return;
					}
					else
					{
						if (_is_red(parent->right->left))
						{
							parent->right->left->is_red = false;
							_rotate_right(parent->right);
							_rotate_left(parent);
							return ;
						}
						else if (_is_red(parent->right->right))
						{
							parent->right->right->is_red = false;
							_rotate_left(parent);
							return ;
						}
						parent->right->is_red = true;
						if (parent->parent)
						{
							if (parent->parent->right == parent)
								removed = &parent->parent->right;
							else
								removed = &parent->parent->left;
						}
						parent = parent->parent;
					}
				}
			}
		}
	}
}

#include "RBTree_constructor.hpp"
#include "RBTree_capacity.hpp"
#include "RBTree_iter_func.hpp"
#include "RBTree_lookup.hpp"
#include "RBTree_modifiers.hpp"

#endif
