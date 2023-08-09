// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef S21_AVL_TREE_H_
#define S21_AVL_TREE_H_

#include "s21_utils.h"

#include <cstddef>
#include <iterator>
#include <utility>

#include <cassert>
#include <iostream>

namespace s21 {

// AVL TREE NODE

template <typename ValueType>
struct AvlTreeNode final {
	int balance_factor;
	AvlTreeNode *parent;
	AvlTreeNode *left;
	AvlTreeNode *right;
	ValueType value;
};


// AVL TREE ITERATOR BASE, AVL TREE ITERATOR, AVL TREE CONST ITERATOR

template <typename ValueType>
class AvlTreeIteratorBase {
 public:
	using NodePtr = AvlTreeNode<ValueType>*;
	using ConstNodePtr = const AvlTreeNode<ValueType>*;

	AvlTreeIteratorBase(void) : node_(nullptr) {}
	explicit AvlTreeIteratorBase(AvlTreeNode<ValueType>* node) : node_(node) {}
	AvlTreeIteratorBase(const AvlTreeIteratorBase& other) : node_(other.node_) {}
	AvlTreeIteratorBase(AvlTreeIteratorBase&& other) : node_(other.node_) {}
	~AvlTreeIteratorBase(void) {}

	void increment(void) {
		if (node_->right != nullptr) {
			node_ = node_->right;
			while (node_->left != nullptr) {
				node_ = node_->left;
			}
		} else {
			NodePtr tmp = node_->parent;
			while (node_ == tmp->right) {
				node_ = tmp;
				tmp = tmp->parent;
			}
			if (node_->right != tmp) {  // when tree consits of a single element
				node_ = tmp;
			}
		}
	}

	void decrement(void) {
		if (node_->parent->parent == node_) {  // when node is the end
			node_ = node_->right;
		} else if (node_->left  != nullptr) {
			NodePtr tmp = node_->left;
			while (tmp->right != nullptr) {
				tmp = tmp->right;
			}
			node_ = tmp;
		} else {
			NodePtr tmp = node_->parent;
			while (node_ == tmp->left) {
				node_ = tmp;
				tmp = tmp->parent;
			}
			node_ = tmp;
		}
	}

 //private:
 public:
	NodePtr node_;
};

template <typename ValueType>
class AvlTreeIterator final : public AvlTreeIteratorBase<ValueType> {
 public:
	using value_type = ValueType;
	using reference = value_type&;
	using pointer = value_type*;
	using difference_type = std::ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;

	using NodePtr = AvlTreeNode<ValueType>*;
	using Base = AvlTreeIteratorBase<ValueType>;
	using Self = AvlTreeIterator<ValueType>;

	explicit AvlTreeIterator(NodePtr node) : Base(node) {}
	AvlTreeIterator(const Self& it) : Base(it.node_) {}

	AvlTreeIterator& operator=(const AvlTreeIterator& other) {
		Base::node_ = other.node_;
		return *this;
	}

	reference operator*(void) const {
		return Base::node_->value;
	}

	pointer operator->(void) const {
		return &Base::node_->value;
	}

	Self& operator++(void) {
		Base::increment();
		return *this;
	}

	Self operator++(int) {
		Self tmp = *this;
		Base::increment();
		return tmp;
	}

	Self& operator--(void) {
		Base::decrement();
		return *this;
	}

	Self operator--(int) {
		Self tmp = *this;
		Base::decrement();
		return tmp;
	}

	template <typename U>
	friend bool operator==(const AvlTreeIterator<U>& lhs,
												 const AvlTreeIterator<U>& rhs);

	// delete it
	NodePtr getNode(void) const { return Base::node_; }
};


template <typename ValueType>
inline bool operator==(const AvlTreeIterator<ValueType>& lhs,
											 const AvlTreeIterator<ValueType>& rhs) {
	return lhs.Base::node_ == rhs.Base::node_;
}

template <typename ValueType>
inline bool operator!=(const AvlTreeIterator<ValueType>& lhs,
											 const AvlTreeIterator<ValueType>& rhs) {
	return !(lhs == rhs);
}

template <typename ValueType>
class AvlTreeConstIterator final : public AvlTreeIteratorBase<ValueType> {
 public:
	using value_type = ValueType;
	using reference = value_type&;
	using const_reference = const value_type&;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using difference_type = ptrdiff_t;
	using iterator_category = std::bidirectional_iterator_tag;

	using NodePtr = AvlTreeNode<ValueType>*;
	using Base = AvlTreeIteratorBase<ValueType>;
	using Self = AvlTreeConstIterator<ValueType>;

	explicit AvlTreeConstIterator(NodePtr node) : Base(node) {}
	AvlTreeConstIterator(const Self& it) : Base(it.node_) {}

	const_reference operator*(void) const {
		return Base::node_->value;
	}

	const_pointer operator->(void) const {
		return &Base::node_->value;
	}

	Self& operator++(void) {
		Base::increment();
		return *this;
	}

	Self operator++(int) {
		Self tmp = *this;
		Base::increment();
		return tmp;
	}

	Self& operator--(void) {
		Base::decrement();
		return *this;
	}

	Self operator--(int) {
		Self tmp = *this;
		Base::decrement();
		return tmp;
	}

	template <typename U>
	friend bool operator==(const AvlTreeConstIterator<U>& lhs,
												 const AvlTreeConstIterator<U>& rhs);
};


template <typename ValueType>
inline bool operator==(const AvlTreeConstIterator<ValueType>& lhs,
											 const AvlTreeConstIterator<ValueType>& rhs) {
	return lhs.Base::node_ == rhs.Base::node_;
}

template <typename ValueType>
inline bool operator!=(const AvlTreeConstIterator<ValueType>& lhs,
											 const AvlTreeConstIterator<ValueType>& rhs) {
	return !(lhs == rhs);
}


// AVL TREE

template <typename Key, typename Value, typename KeyOfValue,
					typename Compare, typename Allocator>
class AvlTree final {
 public:
	using value_allocator_type = Allocator;
	using node_allocator_type =
			typename Allocator::template rebind<AvlTreeNode<Value>>::other;
	using comparator_type = Compare;
	using key_type = Key;
	using value_type = Value;
	using key_of_value = KeyOfValue;
	using pointer = value_type*;
	using const_pointer = const value_type*;
	using reference = value_type&;
	using const_reference = const value_type&;
	using size_type = typename node_allocator_type::size_type;
	using difference_type = ptrdiff_t;
	using link_type = AvlTreeNode<value_type>*;
	using iterator = AvlTreeIterator<value_type>;
	using const_iterator = AvlTreeConstIterator<value_type>;

 public:
	AvlTree(void);
	AvlTree(const AvlTree& other);
	AvlTree(AvlTree&& other);
	AvlTree &operator=(const AvlTree& other);
	AvlTree &operator=(AvlTree&& other) noexcept;
	~AvlTree(void);

 public:
	bool empty(void) const noexcept { return node_count_ == 0; }
	size_type size(void) const noexcept{ return node_count_; }
	size_type max_size(void) const noexcept { return node_allocator_.max_size(); }

 public:
	iterator begin(void) noexcept { return iterator(leftmost()); }
	const_iterator begin(void) const noexcept { return const_iterator(leftmost()); }
	const_iterator cbegin(void) const noexcept { return const_iterator(leftmost()); }
	iterator end(void) noexcept{ return iterator(head_); }
	const_iterator end(void) const noexcept { return const_iterator(head_); }
	const_iterator cend(void) const noexcept { return const_iterator(head_); }

 public:
	void swap(AvlTree& other) noexcept;
	void clear(void);
	std::pair<iterator, bool> insert_unique(const_reference value);
	iterator insert_equal(const_reference value);
	void erase(iterator position);
	void erase(const_iterator position);
	void merge(AvlTree &sourse);

 public:
	iterator find(const key_type& key);
	const_iterator find(const key_type& x) const;
	bool contains(const key_type& key) const;

 public:
	size_t height(link_type x) const;
	int verify(void) const;
	
 private:
	link_type& root(void) const { return head_->parent; }
	link_type& leftmost(void) const { return head_->left; }
	link_type& rightmost(void) const { return head_->right; }

 public:
	static link_type& left(link_type node) { return node->left; }
	static link_type& right(link_type node) { return node->right; }
	static link_type& parent(link_type node) { return node->parent; }
	static reference value(link_type node) { return node->value; }
	static const key_type& key(link_type node) { return KeyOfValue()(node->value); }
	static int& balance_factor(link_type node) { return node->balance_factor; }
	static link_type minimum(link_type node);
	static link_type maximum(link_type node);

 private:
	link_type get_node(void);
	void put_node(link_type ptr);
	void construct_value(pointer ptr, const_reference value);
	void destroy_value(pointer ptr);
	link_type create_node(const value_type& val);
	link_type clone_node(link_type node);
	void destroy_node(link_type node);
	link_type copy(link_type node, link_type node_parent);
	void erase_subtree(link_type node);
	link_type find_node(const key_type& key) const;
	iterator insert_aux(link_type x, link_type z);
	link_type erase_aux(link_type z);

 private:
	link_type rotate_left(link_type x);
	link_type rotate_right(link_type x);
	link_type rotate_left_right(link_type x);
	link_type rotate_right_left(link_type x);
	void insert_rebalance(link_type z);
	void erase_rebalance(link_type n, int left_side);

 private:
	node_allocator_type node_allocator_;
	value_allocator_type value_allocator_;
	comparator_type key_compare_;
	key_of_value key_select_;
	size_type node_count_;
	link_type head_;
};


// Ctors, Dtor, overloading assign operator.

/*
*  Default constructor.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>::AvlTree(void)
		: node_allocator_(AvlTree<K, V, KoV, C, A>::node_allocator_type()),
			value_allocator_(AvlTree<K, V, KoV, C, A>::value_allocator_type()),
			key_compare_(AvlTree<K, V, KoV, C, A>::comparator_type()),
			key_select_(AvlTree<K, V, KoV, C, A>::key_of_value()),
			node_count_(0),
			head_(nullptr) {
	head_ = get_node();
	balance_factor(head_) = 0;
	root() = nullptr;
	leftmost() = head_;
	rightmost() = head_;
}

/*
*  Copy constructor.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>::AvlTree(const AvlTree& other)
		: AvlTree()
{
	if (other.node_count_) {
		root() = copy(other.root(), head_);
		node_count_ = other.node_count_;
		leftmost() = minimum(root());
		rightmost() = maximum(root());
	}
}

/*
*  Move constructor.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>::AvlTree(AvlTree&& other)
		: AvlTree()
{
	swap(other);
}

/*
*  Overloading copy operator=.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>& AvlTree<K, V, KoV, C, A>::operator=(const AvlTree& other) {
	if (this != &other) {
		AvlTree tmp(other);
		swap(tmp);
	}
	return *this;
}

/*
*  Overloading move operator=.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>&
AvlTree<K, V, KoV, C, A>::operator=(AvlTree&& other) noexcept {
	if (this != &other) {
		swap(other);
	}
	return *this;
}

/*
*  Destructor
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>::~AvlTree(void) {
	clear();
	put_node(head_);
}


// Modifiers

/*
*  Swap the contents of the trees.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::swap(AvlTree& other) noexcept {
	std::swap(head_, other.head_);
	std::swap(node_count_, other.node_count_);
	std::swap(key_compare_, other.key_compare_);
}

/*
*  Erases all nodes from the tree.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
void AvlTree<K, V, KoV, C, A>::clear(void) {
	if (node_count_) {
		erase_subtree(root());
		root() = nullptr;
		leftmost() = head_;
		rightmost() = head_;
		node_count_ = 0;
	}
}

/*
*  Inserts element into the container,
*  if the container doesn't already contain an element with an equivalent key. 
*/
template <typename K, typename V, typename KoV, typename C, typename A>
std::pair<typename AvlTree<K, V, KoV, C, A>::iterator, bool>
AvlTree<K, V, KoV, C, A>::insert_unique(const_reference value) {
	link_type y = head_;
	link_type x = root();
	bool comp = true;
	key_type new_key = key_select_(value);

	while (x != nullptr) {
		y = x;
		comp = key_compare_(new_key, key(x));
		x = comp ? left(x) : right(x);
	}

	iterator j = iterator(y);
	if (comp) {
		if (j == begin()) {
			link_type z = create_node(value);
			return std::make_pair(insert_aux(y, z), true);
		} else {
			--j;
		}
	}
	if (key_compare_(key(j.node_), new_key)) {
		link_type z = create_node(value);
		return std::make_pair(insert_aux(y, z), true);
	}
	return std::pair<iterator, bool>(j, false);
}

template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::iterator
AvlTree<K, V, KoV, C, A>::insert_equal(const_reference value) {
	link_type y = head_;
	link_type x = root();
	key_type new_key = key_select_(value);

	while (x != nullptr) {
		y = x;
		x = key_compare_(new_key, key(x)) ? left(x) : right(x);
	}

	link_type z = create_node(value);
	return insert_aux(y, z);
}

template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::erase(iterator position) {
	link_type z = erase_aux(position.node_);
	destroy_node(z);
}

template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::erase(const_iterator position) {
	link_type z = erase_aux(position.node_);
	destroy_node(z);
}

template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::merge(AvlTree &source) {
	iterator it = source.begin();
	iterator last = source.end();

	while (it != last) {
		link_type z = it.node_;
		++it;
		if (find_node(key(z)) == head_) {
			link_type y = head_;
			link_type x = root();
			while (x != nullptr) {
				y = x;
				x = key_compare_(key(z), key(x)) ? left(x) : right(x);	
			}
			z = source.erase_aux(z);
			auto t = source.begin();
			right(z) = nullptr;
			left(z) = nullptr;
			balance_factor(z) = 0;
			insert_aux(y, z);
		}
	}
}


// Search for extreme nodes.

/*
*  find the leftmost node in the subtree
*  with the root passed as an argument "node".  
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::minimum(link_type node) {
	while (left(node) != nullptr) {
		node = node->left;
	}
	return node;
}

/*
*  find the rightmost node in the subtree
*  with the root passed as an argument "node".  
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::maximum(link_type node) {
	while (right(node) != nullptr) {
		node = node->right;
	}
	return node;
}


// Lookup

/*
*  find an element with key equivalent to key.  
*  Iterator to an element with key equivalent to key.
*  If no such element is found, past-the-end ( end() ) iterator is returned. 
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::iterator
AvlTree<K, V, KoV, C, A>::find(const key_type& key) {
	return iterator(find_node(key));
}

template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::const_iterator
AvlTree<K, V, KoV, C, A>::find(const key_type& key) const {
	return const_iterator(find_node(key));
}

/*
*  Check if there is an element with key equivalent to key in the container.
*/

template <typename K, typename V, typename KoV, typename C, typename A>
inline bool
AvlTree<K, V, KoV, C, A>::contains(const key_type& key) const {
	return find_node(key) != head_;
}



// Auxiliary methods for allocating and clearing memory
// and constructing and destructing node values.

/*
*  Allocate memory for a node.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::get_node(void) {
	return node_allocator_.allocate(1);
}

/*
*  Deallocate node memory.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void
AvlTree<K, V, KoV, C, A>::put_node(AvlTreeNode<V>* ptr) {
	node_allocator_.deallocate(ptr, 1);
}

/*
*  Construt a value of node in uninitialized memory.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void
AvlTree<K, V, KoV, C, A>::construct_value(pointer ptr, const_reference value) {
	value_allocator_.construct(ptr, value);
}

/*
*  Destruct a value of node.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void
AvlTree<K, V, KoV, C, A>::destroy_value(V* ptr) {
	value_allocator_.destroy(ptr);
}

/*
*  Create a node and initialize the passed value.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::create_node(const value_type& value)
{
	link_type node = get_node();

	try {
		construct_value(&node->value, value);
	} catch (...) {
		put_node(node);
		throw;
	}

	parent(node) = nullptr;
	left(node) = nullptr;
	right(node) = nullptr;
	balance_factor(node) = 0;

	return node;
}

/*
*  Clone the node. Utility for creating a copy of a tree
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::clone_node(const link_type node)
{
	link_type clone = create_node(value(node));

	balance_factor(clone) = balance_factor(node);

	return clone;
}

/*
*  Destroy the value and deallocate the node.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::destroy_node(
		const typename AvlTree<K, V, KoV, C, A>::link_type node) {
	destroy_value(&value(node));
	put_node(node);
}

/*
*  Copy the subtree with the root passed as an argument "node".
*  Attach a copy to the parent passed as an argument "parent_for_copy".
*  Return copy.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::copy(link_type node, link_type parent_for_copy)
{
	
	link_type top = clone_node(node);
	parent(top) = parent_for_copy;

	try {
		if (right(node) != nullptr) {
			right(top) = copy(right(node), top);
		}
		parent_for_copy = top;
		node = left(node);
		while (node != nullptr) {
			link_type tmp = clone_node(node);
			left(parent_for_copy) = tmp;
			parent(tmp) = parent_for_copy;
			if (right(node) != nullptr) {
				right(tmp) = copy(right(node), tmp);
			}
			parent_for_copy = tmp;
			node = left(node);
		}
	} catch (...) {
		erase_subtree(top);
		throw;
	}

	return top;
}

/*
*  Clear the subtree with the root passed as an argument "node".
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::erase_subtree(link_type node) {
	while (node != nullptr) {
		erase_subtree(right(node));
		link_type tmp = left(node);
		destroy_node(node);
		node = tmp;
	}
}


// Auxiliary methods to search, insert and delete nodes

/*
*  Search for a node with the required key.
*  If the node is not found, a pointer to the header is returned.
*/ 
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::find_node(const key_type& looking_key) const {
	link_type result = head_;
	link_type node = root();

	while (node != nullptr) {
		if (!key_compare_(key(node), looking_key)) {  // key(node) >= looking_key
			result = node;
			node = left(node);
		} else {
			node = right(node);
		}
	}

	if (result != head_ && key_compare_(looking_key, key(result))) {
		result = head_;
	}

	return result;
}

/*
*  Inserts a new node as a child for node y. 
*/
template <typename K, typename V, typename KoV, typename C, typename A>
typename AvlTree<K, V, KoV, C, A>::iterator
AvlTree<K, V, KoV, C, A>::insert_aux(link_type x, link_type z) {
	key_type new_key = key(z);

	if (x == head_ || key_compare_(new_key, key(x))) {
		left(x) = z;
		if (x == head_) {
			root() = z;
			rightmost() = z;
		} else if (x == leftmost()) {
			leftmost() = z;
		}
	} else {
		right(x) = z;
		if (x == rightmost()) {
			rightmost() = z;
		}
	}
	parent(z) = x;
	insert_rebalance(z);
	++node_count_;

	return iterator(z);
}

/*
*  Deleting a node "z" with subsequent rebalancing.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::erase_aux(link_type z) {
	link_type y = nullptr;
	link_type x = nullptr;
	link_type node_for_balance = nullptr;
	enum {none_side = -1, right_side = 0, left_side = 1} side = none_side;

	if (right(z) == nullptr || left(z) == nullptr) {
		node_for_balance = z->parent;
		if (right(z) == nullptr) {
			x = left(z);
		} else {
			x = right(z);
		}
		if (x != nullptr) {
			parent(x) = parent(z);
		}
		if (z == root()) {
			root() = x;
		} else if (z == left(parent(z))) {
			side = left_side;
			left(parent(z)) = x;
		} else {  // z == right(parent(z));
			side = right_side;
			right(parent(z)) = x;
		}
	} else {
		y = right(z);
		while (left(y) != nullptr) {
			y = left(y);
		}
		x = right(y);
		if (left(z) != nullptr) {
			parent(left(z)) = y;
		}
		left(y) = left(z);
		if (y == right(z)) {
			node_for_balance = y;
			side = right_side;
		} else {
			node_for_balance = parent(y);
			side = left_side;
			if (x != nullptr) {
				parent(x) = parent(y);
			}
			left(parent(y)) = x;
			right(y) = right(z);
			parent(right(z)) = y;
		}
		if (z == root()) {
			root() = y;
		} else if (z == left(parent(z))) {
			left(parent(z)) = y;
		} else {
			right(parent(z)) = y;
		}
		parent(y) = parent(z);
		balance_factor(y) = balance_factor(z);
	}

	if (node_for_balance != head_)
		erase_rebalance(node_for_balance, side);

	if (root() != nullptr) {
		leftmost() = minimum(root());
		rightmost() = maximum(root());
	} else {
		leftmost() = head_;
		rightmost() = head_;
	}

	--node_count_;

	return z;
}


// Operations on the binary search tree.

/*
* AVL TREE ROTATE LEFT
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::rotate_left(link_type x) {
	assert(x != nullptr);
	assert(x->right != nullptr);
	link_type z = x->right;

	x->right = z->left;
	if (z->left != nullptr) {
		z->left->parent = x;
	}
	z->parent = x->parent;
	if (x == root()) {
		root() = z;
	} else if (x == x->parent->left) {
		x->parent->left = z;
	} else {
		x->parent->right = z;
	}
	z->left = x;
	x->parent = z;

	if (z->balance_factor == 0) {
		x->balance_factor = 1;
		z->balance_factor = -1;
	} else {
		x->balance_factor = 0;
		z->balance_factor = 0;
	}

	return z;
}

/*
* AVL TREE ROTATE RIGHT
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::rotate_right(link_type x) {
	assert(x != nullptr);
	assert(x->left != nullptr);
	link_type z = x->left;

	x->left = z->right;
	if (z->right != nullptr) {
		z->right->parent = x;
	}
	z->parent = x->parent;
	if (x == root()) {
		root() = z;
	} else if (x->parent->left == x) {
		x->parent->left = z;
	} else {
		x->parent->right = z;
	}
	z->right = x;
	x->parent = z;

	if (z->balance_factor == 0) {
		x->balance_factor = -1;
		z->balance_factor = 1;
	} else {
		x->balance_factor = 0;
		z->balance_factor = 0;
	}

	return z;
}

/*
*  AVL TREE ROTATE RIGHT-LEFT
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::rotate_right_left(link_type x) {
	assert(x != nullptr);
	assert(x->right != nullptr);
	assert(x->right->left != nullptr);
	link_type z = x->right;
	link_type y = z->left;

	z->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = z;
	}
	y->right = z;
	z->parent = y;

	x->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x == root()) {
		root() = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;

	if (y->balance_factor == 0) {
		x->balance_factor = 0;
		z->balance_factor = 0;
	} else if (y->balance_factor > 0) {
		x->balance_factor = -1;
		z->balance_factor = 0;
	} else {
		x->balance_factor = 0;
		z->balance_factor = 1;
	}
	y->balance_factor = 0;

	return y;
}

/*
*   AVL TREE ROTATE LEFT-RIGHT
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::rotate_left_right(link_type x) {
	assert(x != nullptr);
	assert(x->left != nullptr);
	assert(x->left->right != nullptr);
	link_type z = x->left;
	link_type y = z->right;

	z->right = y->left;
	if (y->left != nullptr) {
		y->left->parent = z;
	}
	y->left = z;
	z->parent = y;

	x->left = y->right;
	if (y->right != nullptr) {
		y->right->parent = x;
	}
	y->parent = x->parent;
	if (x == root()) {
		root() = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->right = x;
	x->parent = y;

	if (y->balance_factor == 0) {
		x->balance_factor = 0;
		z->balance_factor = 0;
	} else if (y->balance_factor > 0) {
		x->balance_factor = 0;
		z->balance_factor = -1;
	} else {
		x->balance_factor = 1;
		z->balance_factor = 0;
	}
	y->balance_factor = 0;

	return y;
}

/*
*  Rebalancing after insertion.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
void AvlTree<K, V, KoV, C, A>::insert_rebalance(link_type z) {
	for (link_type x = parent(z); x != head_; x = parent(z)) {
		if (z == right(x)) {
			if (balance_factor(x) > 0) {
				if (balance_factor(z) < 0) {
					rotate_right_left(x);
				} else {
					rotate_left(x);
				}
			} else {
				if (balance_factor(x) < 0) {
					balance_factor(x) = 0;
					break;
				} else {
					balance_factor(x) = 1;
					z = x;
					continue;
				}
			}
		} else {
			if (balance_factor(x) < 0) {
				if (balance_factor(z) > 0) {
					rotate_left_right(x);
				} else {
					rotate_right(x);
				}
			} else {
				if (balance_factor(x) > 0) {
					balance_factor(x) = 0;
					break;
				} else {
					balance_factor(x) = -1;
					z = x;
					continue;
				}
			}
		}
		break;
	}
}

/*
*  Rebalancing after erasing.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
void AvlTree<K, V, KoV, C, A>::erase_rebalance(link_type x, int left_side) {
	while (x != head_) {
		if (left_side) {
			if (balance_factor(x) < 0) {
				balance_factor(x) = 0;
			} else if (balance_factor(x) == 0) {
				balance_factor(x) = 1;
				break;
			} else {
				link_type z = right(x);
				int bf = balance_factor(z);
				if (bf < 0) {
					x = rotate_right_left(x);
				} else {
					x = rotate_left(x);
					if (bf == 0) {
						break;
					}
				}
			}
		} else {
			if (balance_factor(x) > 0) {
				balance_factor(x) = 0;
			} else if (balance_factor(x) == 0) {
				balance_factor(x) = -1;
				break;
			} else {
				link_type z = left(x);
				int bf = balance_factor(z);
				if (bf > 0 ) {
					x = rotate_left_right(x);
				} else {
					x = rotate_right(x);
					if (bf == 0) {
						break;
					}
				}
			}
		}

		link_type g = parent(x);
		if (x == left(g)) {
			left_side = 1;
		} else {
			left_side = 0;
		}
		x = g;
	}
}


// verify method for debug

template <typename K, typename V, typename KoV, typename C, typename A>
size_t AvlTree<K, V, KoV, C, A>::height(link_type x) const {
	size_t h = 0;
	if (x == nullptr)
		return 0;
	size_t h_r = height(x->right);
	size_t h_l = height(x->left);
	if (h_r > h_l) {
		h = h_r + 1;
	} else {
		h = h_l + 1;
	}
	return h;
}

template <typename K, typename V, typename KoV, typename C, typename A>
int AvlTree<K, V, KoV, C, A>::verify(void) const {
	if (node_count_ == 0 || begin() == end()) {
		if (node_count_ != 0)
			return 1;
		if (begin() != end()) 
			return 2;
		if (head_->left != head_)
			return 3;
		if (head_->right != head_)
			return 4;
		if (head_->parent != nullptr)
			return 5;
	}

	for (const_iterator it = begin(); it != end(); ++it) {
		if (it.node_->left) {
			if (key_compare_(key(it.node_), key(it.node_->left)))
				return 6;
		}
		if (it.node_->right) {
			if (key_compare_(key(it.node_->right), key(it.node_)))
				return 7;
		}
		size_t h_l = height(it.node_->left);
		size_t h_r = height(it.node_->right);
		int bf = h_r - h_l;
		if (bf > 1) return 8;
	 	if (bf < -1) return 9;
		if (bf != balance_factor(it.node_)) {
			return 10;
		}
	}

	if (root() != nullptr) {
		if (leftmost() != minimum(root())) return 11;
		if (rightmost() != maximum(root())) return 12;
	}

	return 0;
}



/*
template <typename K, typename V, typename KoV, typename C, typename A>
void AvlTree<K, V, KoV, C, A>::erase_rebalance(link_type n, int left_side) {
	link_type x = nullptr;
	link_type z = nullptr;
	link_type g = nullptr;
	int bf = 0;

	//std::cout << "start prebalance\n";
	//std::cout << "start prebalance key = " << key(n) << '\n';
	//std::cout << "start prebalance bf = " << balance_factor(n) << '\n';
	//std::cout << "start side = " << (left_side ? "left\n" : "right\n");
	if (left_side) {
		if (balance_factor(n) < 0) {
			balance_factor(n) = 0;
		} else if (balance_factor(n) == 0) {
			balance_factor(n) = +1;
			return;
		} else {
			link_type z = right(n);              // Sibling of N (higher by 2);
			assert(z != nullptr);
			int bf = balance_factor(z);
			if (bf < 0) {                        // Right-Left case;
				n = rotate_right_left(n);
			} else {                             // Right-Right case;
				n = rotate_left(n);
			}
			if (bf == 0) return;
		}
	} else {
		if (balance_factor(n) > 0) {
			balance_factor(n) = 0;
		} else if (balance_factor(n) == 0) {
			balance_factor(n) = -1;
			return;
		} else {
			link_type z = left(n);                         // sibling of n (higher by 2);
			assert(z != nullptr);
			bf = balance_factor(z);
			if (bf > 0) {                        // Left-Right case;
				n = rotate_left_right(n);
			} else {                             // Left-Left case;
				n = rotate_right(n);
			}
			if (bf == 0) return;
		}
	}
	//std::cout << "end prebalance\n";

	//std::cout << "start balance key = " << key(n) << '\n';
	//std::cout << "start balance bf = " << balance_factor(n) << '\n';
	for (x = parent(n); x != head_; x = g) {
		g = parent(x);                           // Save parent of x around rotations
		if (n == left(x)) {                      // the left subtree decreases;
			//std::cout << "left_case start\n";
			assert(x != nullptr);
			assert(n != nullptr);
			if (balance_factor(x) > 0) {					 // x is right-heavy;
			                                       // The temorary bf of x == +2;
                                             // rebalancing is required;
				link_type z = right(x);              // Sibling of N (higher by 2);
				assert(z != nullptr);
				int bf = balance_factor(z);
				if (bf < 0) {                        // Right-Left case;
					n = rotate_right_left(x);
				} else {                             // Right-Right case;
					n = rotate_left(x);
				}
				if (bf == 0) break;
				//std::cout << "left_case end\n";
			} else if (balance_factor(x) == 0) {   // n's height decrease is absorbed at x;
					balance_factor(x) = 1;
					// std::cout << "left_case end\n";
					break;
			} else {                               // balance_factor(x) < 0;
				n = x;
				balance_factor(n) = 0;               // Height of n decreases by 1;
				//std::cout << "left_case end\n";
				continue;
			}
		} else {                                 // the right subtree decreases;
			//std::cout << "right_case start\n";
			assert(x != nullptr);
			assert(n != nullptr);
			if (balance_factor(x) < 0) {           // x is left-heavy;
                                             // the temporary bf of x == -2;
																						 // rebalancing is required;
				z = left(x);                         // sibling of n (higher by 2);
				assert(z != nullptr);
				bf = balance_factor(z);
				if (bf > 0) {                        // Left-Right case;
					n = rotate_left_right(x);
				} else {                             // Left-Left case;
					n = rotate_right(x);
				}
				if (bf == 0) break;
				//std::cout << "right_case end\n";
			} else if (balance_factor(x) == 0) {   // n's height decrease by 1;
					balance_factor(x) = -1;
					//std::cout << "right_case end\n";
					break;
			} else {                               // balance_factor(x) > 0;
				n = x;
				balance_factor(n) = 0;               // height of n decreases by 1;
				//std::cout << "right_case end\n";
				continue;
			}
		}

		//if (bf == 0) {                           // height does not changed
		//	break;
		//}
	}
}

template <typename K, typename V, typename KoV, typename C, typename A>
void AvlTree<K, V, KoV, C, A>::erase_aux(link_type z) {
	link_type y = z;
	link_type x = nullptr;
	link_type rotated_node = nullptr;

	//enum {left, right} side;

	if (y->right == nullptr) {
			rotated_node = y->parent;
			x = y->left;
			if (x != nullptr) {
				x->parent = y->parent;
			}
			if (root() == z) {
				root() = x;
			} else if (z == z->parent->left) {
				z->parent->left = x;
				if (balance_factor(rotated_node) < 0) {
					balance_factor(rotated_node) = 0;
				} else if (balance_factor(rotated_node) == 0) {
					balance_factor(rotated_node) = +1;
				} else {
					//std::cout << "abort1\n";
					//abort();
					link_type tmp = rotated_node->right;
					assert(rotated_node->right != nullptr);
					if (balance_factor(tmp) < 0) {
						rotated_node = rotate_right_left(rotated_node);
					} else if (balance_factor(tmp) > 0) {
						rotated_node = rotate_left(rotated_node);
					} else {
						rotated_node = rotate_left(rotated_node)
					}
				}
			} else {
				z->parent->right = x;
				if (balance_factor(rotated_node) > 0) {
					balance_factor(rotated_node) = 0;
				} else if (balance_factor(rotated_node) == 0) {
					balance_factor(rotated_node) = -1;
				} else {
					//std::cout << "abort2\n";
					//abort();
					link_type tmp = rotated_node->left;
					assert(rotated_node->left != nullptr);
					if (balance_factor(tmp) > 0) {
						rotated_node = rotate_left_right(rotated_node);
					} else if (balance_factor(tmp) < 0) {
						rotated_node = rotate_right(rotated_node);
					} else {
						rotated_node = rotate_right(rotated_node);
					}
				}
		}
	} else {
		y = y->right;
		while (y->left != nullptr) {
			y = y->left;
		}
		x = y->right;
		
		if (z->left != nullptr) {
			z->left->parent = y;             // z has two non-null child
		}
		y->left = z->left;			   			 // we link z's left child to y's left child
		if (y == z->right) {
			rotated_node = y;
		} else {                         // y is not z's right child
			rotated_node = y->parent;
			if (x != nullptr) {
				x->parent = y->parent;
			}
			y->parent->left = x;           // there y must be a left child
			y->right = z->right;
			z->right->parent = y;
		}
		if (root() == z) {
			root() = y;
		} else if (z->parent->left == z) {
			z->parent->left = y;
		} else {
			z->parent->right = y;
		}
		y->parent = z->parent;
		y->balance_factor = z->balance_factor;
	}

	if (rotated_node != head_)
		erase_rebalance(rotated_node);

	if (root() != nullptr) {
		leftmost() = minimum(root());
		rightmost() = maximum(root());
	} else {
		leftmost() = head_;
		rightmost() = head_;
	}

	destroy_node(z);
}
	
*/




} // namespace s21

#endif // S21_AVL_TREE_H_
