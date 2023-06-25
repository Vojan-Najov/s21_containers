// Copyright 2023 <Carmine Carman, Vojan Najov>

#ifndef INCLUDE_S21_LIST_H_
#define INCLUDE_S21_LIST_H_

#include <cstddef>
#include <new>

namespace s21 {

template<typename T>
class list {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  // typedef ListIterator<value_type> iterator;
  // typedef ListConstIterator<value_type> iterator;
  typedef size_t size_type;

  list(void);
  //list(size_type n);
  //list(const std::initialized_list<value_type>& items);
  //list(const list& other);
  //list(list&& other);
  //list& operator=(const list& other);
  //list& operator=(list&& other);
  ~list(void);

  //reference front(void);
  //const_reference front(void) const;
  //reference back(void);
  //const_reference back(void) const;

  //iterator begin(void);
  //const_iterator begin(void) const;
  //iterator end(void);
  //const_iterator end(void) const;

  bool empty(void) const noexcept;
  size_type size(void) const noexcept;
  //size_type max_size(void) const;

  //void clear(void);
  //iterator insert(iterator pos, const_reference value);
  //void erase(iterator pos);
  void push_back(const_reference value);
  //void pop_back(void);
  void push_front(const_reference value);
  //void pop_front(void);
  //void swap(list& other);
  //void merge(list& other);
  //void splice(const_iterartor pos, list&  other);
  //void reverse(void);
  //void unique(void);
  //void sort(void);

 private:
  struct Node;
  Node *head_;
};

template<typename T>
struct list<T>::Node {
  Node *prev;
  Node *next;
  T value;
};

/*
template<typename T>
Node<T> *create_node(Node<T> *next, Node<T> *prev, const T& value) {
  Node<T> *nptr = static_cast<Node<T> *>(operator new (sizeof(Node<T>)));
  nptr->next = next;
  nptr->prev = prev;
  new (nptr) T(value);

  return nptr;
}

template<typename T>
destroy_node(Node<T> *node) {
  node.T.~Node();
  operator delete (static_cast<void *>(node));
}
*/


template <typename T>
list<T>::list(void) {
	head_ = static_cast<list::Node *>(operator new (sizeof(list::Node)));
	head_->next = head_;
	head_->prev = head_;
}

/*
template <typename T>
list<T>::list(size_t n) : node_(nullptr) {
	if (n == 0) {
		return;
	}

	Node *nodes = new Node[n];
	node_ = nodes;
	for (size_t i = 1; i < n; ++i) {
		node_->next = nodes + i;
		node_->next->prev = node_;
		node_ = node_->next;
	}
	node_ = nodes;
	if (n > 1) {
		node_->prev = nodes + (n - 1);
		// node_->prev->next = node_;
	}
}
*/

template <typename T>
list<T>::~list(void) {
	operator delete (head_);

//	if (node_ != nullptr) {
//		Node *nptr = node_->next;
//		while (nptr != node_) {
//			Node *tmp = nptr;
//			nptr = nptr->next;
//			delete tmp;
//		}
//		delete node_;
//	}
}

template <typename T>
void list<T>::push_back(list<T>::const_reference value) {
	Node *nptr = new Node{head_->prev, head_, value};
	if (empty()) {
		head_->next = nptr;
	} else {
		head_->prev->next = nptr;
	}
	head_->prev = nptr;
}

template<typename T>
inline bool list<T>::empty(void) const noexcept {
	return head_->next == head_;
}

template<typename T>
inline size_t list<T>::size(void) const noexcept {
	size_t n = 0;
	Node *tmp = head_->next;
	while (tmp != head_) {
		++n;
		tmp = tmp->next;
	}
	return n;
}

template<typename T>
void list<T>::push_front(list<T>::const_reference value) {
	Node *nptr = new Node{head_, head_->next, value};
	if (empty()) {
		head_->prev = nptr;
	} else {
		head_->next->prev = nptr;
	}
	head_->next = nptr;
}

} // namespace s21

#endif  // INCLUDE_S21_LIST_H_
