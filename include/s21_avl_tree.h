#ifndef S21_AVL_TREE_H_
#define S21_AVL_TREE_H_

#include <cstddef>
#include <iterator>
#include <utility>

namespace s21 {

// Auxiliary structs

template <typename Arg, typename Result>
struct UnaryFunction {
	using argument_type = Arg;
	using result_type = Result;
};

template <typename T>
struct Identity : public UnaryFunction<T, T> {
	T& operator()(T& x) const { return x; }
	const T& operator()(const T& x) const { return x; }
};

template <typename Pair>
struct Select1st : public UnaryFunction<Pair, typename Pair::first_type> {
	typename Pair::first_type& operator()(Pair& x) const { return x.first; }
	const typename Pair::first_type& operator()(const Pair& x) const { return x.first; }
};

template <typename Pair>
struct Select2nd : public UnaryFunction<Pair, typename Pair::second_type> {
	typename Pair::second_type& operator()(Pair& x) const { return x.second; }
	const typename Pair::second_type& operator()(const Pair& x) const { return x.second; }
};

template <typename Arg1, typename Arg2, typename Result>
struct BinaryFunction {
	using first_argument_type = Arg1;
	using second_argument_type = Arg2;
	using result_type = Result;
};

template <typename T>
struct Less: public BinaryFunction<T, T, bool> {
	bool operator()(const T& lhs, const T& rhs) const { return lhs < rhs; }
};

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
			if (node_->right != tmp) { // whent tree consits of a single element
				node_ = tmp;
			}
		}
	}

	void decrement(void) {
		if (node_->parent->parent == node_) { // when node is the end
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

	reference operator*(void) const {
		return Base::node_->value;
	}

	pointer operator->(void) const {
		return &Base::node->value;
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
		return &Base::node->value;
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


// AVL TREE ROTATE LEFT

template <typename ValueType>
inline void avlTreeRotateLeft(AvlTreeNode<ValueType> *x,
															AvlTreeNode<ValueType>*& root) {
	AvlTreeNode<ValueType> *z = x->right;
	x->right = z->left;
	if (z->left != nullptr) {
		z->left->parent = x;
	}
	z->parent = x->parent;
	if (x == root) {
		root = z;
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
}

// AVL TREE ROTATE RIGHT

template <typename ValueType>
inline void avlTreeRotateRight(AvlTreeNode<ValueType>* x,
															 AvlTreeNode<ValueType>*& root) {
	AvlTreeNode<ValueType> *z = x->left;
	x->left = z->right;
	if (z->right != nullptr) {
		z->right->parent = x;
	}
	z->parent = x->parent;
	if (x == root) {
		root = z;
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
}

// AVL TREE ROTATE RIGHT-LEFT

template <typename ValueType>
void avlTreeRotateLeftRight(AvlTreeNode<ValueType> *x,
														AvlTreeNode<ValueType>*& root) {
	AvlTreeNode<ValueType> *z = x->right;
	AvlTreeNode<ValueType> *y = z->left;

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
	if (x == root) {
		root = y;
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
		z->balance_Factor = 0;
	} else {
		x->balance_factor = 0;
		z->balance_factor = 1;
	}
	y->balance_factor = 0;
}

// AVL TREE ROTATE LEFT-RIGHT

template <typename ValueType>
void avlTreeRotateRightLeft(AvlTreeNode<ValueType> *x,
														AvlTreeNode<ValueType>*& root) {
	AvlTreeNode<ValueType> *z = x->left;
	AvlTreeNode<ValueType> *y = z->right;

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
	if (x == root) {
		root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->right = x;
	parent(x) = y;

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
	AvlTree &operator=(AvlTree&& other);
	~AvlTree(void);

 public:
	bool empty(void) const;
	size_type size(void) const;
	size_type max_size(void) const;

 public:
	iterator begin(void) { return iterator(leftmost()); }
	const_iterator cbegin(void) const { return const_iterator(leftmost()); }
	iterator end(void) { return iterator(head_); }
	const_iterator cend(void) const { return const_iterator(head_); }

 public:
	std::pair<iterator, bool> insert_unique(reference value);
	iterator insert_unique(iterator position, reference value);
	const_iterator insert_unique(const_iterator position, reference value);
	template <typename InputIterator>
		void insert_unique(InputIterator first, InputIterator last);

 public:
	void erase(iterator position);
	void erase(const_iterator position);
	size_type erase(const key_type &key);
	void erase(const_iterator first, const_iterator last);
	void erase(const key_type* first, const key_type* last);
	void Clear(void);

 public:
	iterator find(const key_type& key);
	const_iterator find(const key_type& x) const;
	size_type count(const key_type& key) const;
	iterator lower_bound(const key_type& x);
	const_iterator lower_bound(const key_type& x) const;
	iterator upper_bound(const key_type& x) const;
	std::pair<iterator, iterator> equal_range(const key_type& key);
	std::pair<const_iterator, const_iterator> equl_range(const key_type& key) const;
	
 //private:
 public:
	link_type& root(void) const { return head_->parent; }
	link_type& leftmost(void) const { return head_->left; }
	link_type& rightmost(void) const { return head_->right; }
	link_type& left(link_type node) { return node->left; }
	link_type& right(link_type node) { return node->right; }
	link_type& parent(link_type node) { return node->parent; }
	reference value(link_type node) { return node->value; }
	const key_type& key(link_type node) { return KeyOfValue()(node->value); }
	int& balanceFactor(link_type node) { return node->balance_factor; }
	link_type minimum(link_type node) const;
	link_type maximum(link_type node) const;

 //private:
 public:
	link_type GetNode(void);
	void PutNode(link_type ptr);
	void ConstructValue(pointer ptr, const_reference value);
	void DestroyValue(pointer ptr);
	link_type CreateNode(const value_type& val);
	link_type CloneNode(link_type node);
	void DestroyNode(link_type node);
	void EmptyInitialize(void);
	link_type Copy(link_type node, link_type node_parent);
	void EraseSubTree(link_type node);

 //private:
 public:
	node_allocator_type node_allocator_;
	value_allocator_type value_allocator_;
	comparator_type key_compare_;
	size_type node_count_;
	link_type head_;

 public:
	void TestTree(void);
};

/*
*  Default constructor.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>::AvlTree(void)
		: node_allocator_(AvlTree<K, V, KoV, C, A>::node_allocator_type()),
			value_allocator_(AvlTree<K, V, KoV, C, A>::value_allocator_type()),
			key_compare_(AvlTree<K, V, KoV, C, A>::comparator_type()),
			node_count_(0),
			head_(nullptr) {
		EmptyInitialize();
}

/*
*  Copy constructor.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>::AvlTree(const AvlTree& copy)
		: node_allocator_(AvlTree::node_allocator_type()),
			value_allocator_(AvlTree::value_allocator_type()),
			key_compare_(AvlTree::comparator_type()),
			node_count_(copy.node_count_),
			head_(nullptr)
{
	if (copy.node_count_ == 0) {
		EmptyInitialize();
	} else {
		root() = Copy(copy.root(), head_);
		leftmost() = minimum(root());
		rightmost() = maximum(root());
	}
}

/*
*  Move constructor.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>::AvlTree(AvlTree&& other)
		: node_allocator_(AvlTree::node_allocator_type()),
			value_allocator_(AvlTree::value_allocator_type()),
			key_compare_(AvlTree::comparator_type()),
			node_count_(other.node_count_),
			head_(other.head_)
{
	other.EmptyInitialize(); 
}

/*
*  Destroy.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
AvlTree<K, V, KoV, C, A>::~AvlTree(void) {
	Clear();
	PutNode(head_);
}


// Modifiers

/*
*  Erases all nodes from the tree.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
void AvlTree<K, V, KoV, C, A>::Clear(void) {
	if (node_count_) {
		EraseSubTree(root());
		root() = nullptr;
		leftmost() = head_;
		rightmost() = head_;
		node_count_ = 0;
	}
}

/*
*  Allocate memory for a node.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::GetNode(void) {
	return node_allocator_.allocate(1);
}

/*
*  Deallocate node memory.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void
AvlTree<K, V, KoV, C, A>::PutNode(AvlTreeNode<V>* ptr) {
	node_allocator_.deallocate(ptr, 1);
}

/*
*  Construt a value of node in uninitialized memory.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void
AvlTree<K, V, KoV, C, A>::ConstructValue(pointer ptr, const_reference value) {
	value_allocator_.construct(ptr, value);
}

/*
*  Destruct a value of node.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void
AvlTree<K, V, KoV, C, A>::DestroyValue(V* ptr) {
	value_allocator_.destroy(ptr);
}

/*
*  Create a node and initialize the passed value.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::CreateNode(const value_type& value)
{
	link_type node = GetNode();

	try {
		ConstructValue(&node->value, value);
	} catch (...) {
		PutNode(node);
		throw;
	}

	return node;
}

/*
*  Clone the node. Utility for creating a copy of a tree
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::CloneNode(const link_type node)
{
	link_type clone = CreateNode(value(node));

	BalanceFactor(clone) = BalanceFactor(node);
	Left(clone) = nullptr;
	Right(clone) = nullptr;
	Parent(clone) = nullptr;

	return clone;
}

/*
*  Destroy the value and deallocate the node.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::DestroyNode(
		const typename AvlTree<K, V, KoV, C, A>::link_type node) {
	DestroyValue(&value(node));
	PutNode(node);
}

/*
*  Find the leftmost node in the subtree
*  with the root passed as an argument "node".  
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::minimum(link_type node) const {
	while (left(node) != nullptr) {
		node = node->left;
	}
	return node;
}

/*
*  Find the rightmost node in the subtree
*  with the root passed as an argument "node".  
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::maximum(link_type node) const {
	while (right(node) != nullptr) {
		node = node->right;
	}
	return node;
}

/*
* Initialize the header of an empty tree. 
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::EmptyInitialize(void) {
	head_ = GetNode();
	balanceFactor(head_) = 0;
	root() = nullptr;
	leftmost() = head_;
	rightmost() = head_;
}

/*
*  Copy the subtree with the root passed as an argument "node".
*  Attach a copy to the parent passed as an argument "node".
*  Return copy.
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline typename AvlTree<K, V, KoV, C, A>::link_type
AvlTree<K, V, KoV, C, A>::Copy(link_type node, link_type parent)
{
	link_type top = CloneNode(node);
	parent(top) = parent;

	try {
		if (right(node) != nullptr) {
			right(top) = Copy(right(node), top);
		}
		parent = top;
		node = left(node);
		while (node != nullptr) {
			link_type tmp = CloneNode(node);
			left(parent) = tmp;
			parent(tmp) = parent;
			if (right(node) != nullptr) {
				right(tmp) = Copy(right(node), tmp);
			}
			parent = tmp;
			node = left(node);
		}
	} catch (...) {
		EraseSubTree(top);
		throw;
	}

	return top;
}

/*
*  Clear the subtree with the root passed as an argument "node".
*/
template <typename K, typename V, typename KoV, typename C, typename A>
inline void AvlTree<K, V, KoV, C, A>::EraseSubTree(link_type node) {
	while (node != nullptr) {
		EraseSubTree(right(node));
		link_type tmp = left(node);
		DestroyNode(node);
		node = tmp;
	}
}

} // namespace s21

#endif // S21_AVL_TREE_H_
