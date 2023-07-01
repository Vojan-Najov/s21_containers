// Copyright 2023 <Carmine Carman, Vojan Najov>

#ifndef INCLUDE_S21_LIST_H_
#define INCLUDE_S21_LIST_H_

#include <cstddef>
#include <new>

namespace s21 {

template<typename T>
struct ListNode {
	ListNode *prev;
	ListNode *next;
	T value;
};

template <typename T>
class list;

template<typename T>
class ListIterator {
 public:
  ListIterator(ListNode<T> *node) : node_(node) {}
  ListIterator(const ListIterator &other) : node_(other.node_) {}
  ListIterator(ListIterator &&other) : node_(other.node_) {}
  ListIterator &operator=(const ListIterator &other) {
    node_ = other.node_;
    return *this;
  }
  ListIterator &operator=(ListIterator &other) {
    node_ = other.node_;
    return *this;
  }
  ListIterator& operator++(void) {
    node_ = node_->next;
    return *this;
  }
  ListIterator& operator++(int) {
    ListIterator tmp(*this);
    node_ = node_->next;
    return tmp;
  }
  ListIterator& operator--(void) {
    node_ = node_->prev;
    return *this;
  }
  ListIterator& operator--(int) {
    ListIterator tmp(*this);
    node_ = node_->prev;
    return tmp;
  }
  T &operator*(void) { return node_->value; }
  const T &operator*(void) const { return node_->value; }
  T *operator->(void) { return &node_->value; }
  const T *operator->(void) const { return &node_->value; }

  template <typename U>
  friend bool operator==(const ListIterator<U> &lhs, const ListIterator<U> &rhs);

  friend list<T>;

 private:
  ListNode<T> *node_;
};

template <typename T>
bool operator==(const ListIterator<T> &lhs, const ListIterator<T> &rhs) {
	return lhs.node_ == rhs.node_;
}

template <typename T>
bool operator!=(const ListIterator<T> &lhs, const ListIterator<T> &rhs) {
	return !(lhs == rhs);
}

template<typename T>
class list {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef ListIterator<value_type> iterator;
  typedef const ListIterator<value_type> const_iterator;
  typedef size_t size_type;

  list(void);
  list(size_type n);
  list(const std::initializer_list<value_type>& items);
  list(const list& other);
  list(list&& other);
  list& operator=(const list& other);
  list& operator=(list&& other);
  ~list(void);

  reference front(void);
  const_reference front(void) const;
  reference back(void);
  const_reference back(void) const;

  iterator begin(void);
  const_iterator begin(void) const;
  iterator end(void);
  const_iterator end(void) const;

  bool empty(void) const noexcept;
  size_type size(void) const noexcept;
  //size_type max_size(void) const;

  void clear(void);
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back(void);
  void push_front(const_reference value);
  void pop_front(void);
  void swap(list& other);
  void merge(list& other);
  void splice(const_iterator pos, list&  other);
  void reverse(void);
  void unique(void);
  //void sort(void);

 private:
  ListNode<T> *head_;

 private:
  ListNode<T> *CreateNode(ListNode<T> *prev, ListNode<T> *next, const T& value);
  void DestroyNode(ListNode<T> *node);
  void TransferNode(ListNode<T> *pos, ListNode<T> *node);
};

// Auxiliary private member function for work with nodes.

template<typename T>
ListNode<T> *list<T>::CreateNode(ListNode<T> *prev, ListNode<T> *next,
                                 const T& value) {
  ListNode<T> *nptr = static_cast<ListNode<T> *>(operator new (sizeof(ListNode<T>)));
  nptr->prev = prev;
  nptr->next = next;
  try {
    new (&nptr->value) T(value);
  } catch (std::exception &e) {
    operator delete(nptr);
    throw e;
  }

  return nptr;
}

template<typename T>
void list<T>::DestroyNode(ListNode<T> *node) {
  node->value.~T();
  operator delete (static_cast<void *>(node));
}

/*
template<typename T>
void list<T>::TransferNode(ListNode<T> *pos, ListNode<T> *node) {
  
}
*/

// Ctors, Dtor, overloading operator=

template <typename T>
list<T>::list(void) {
	head_ = static_cast<ListNode<T> *>(operator new (sizeof(ListNode<T>)));
	head_->next = head_;
	head_->prev = head_;
}

template <typename T>
list<T>::list(size_t n) : list() {
  if (n == 0) {
    return;
  }
  for (size_t i = 0; i < n; ++i) {
    push_back(T());
  }
}

template <typename T>
list<T>::list(const std::initializer_list<T>& items) : list() {
  for (const T &item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list<T> &other) : list() {
  ListNode<T> *nptr = other.head_->next;
  while (nptr != other.head_) {
    push_back(nptr->value);
	nptr = nptr->next;
  }
}

template <typename T>
list<T>::list(list<T> &&other) : list() {
  std::swap(head_, other.head_);
}

template <typename T>
list<T> &list<T>::operator=(const list<T> &other) {
  if (this != &other) {
    list tmp(other);
    std::swap(tmp.head_, head_);
  }

  return *this;
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&other) {
  if (this != &other) {
    std::swap(other.head_, head_);
  }

  return *this;
}

template <typename T>
list<T>::~list(void) {
	clear();
	operator delete (head_);
}

// List element access

template <typename T>
T& list<T>::front(void) {
  return head_->next->value;
}

template <typename T>
const T& list<T>::front(void) const {
  return head_->next->value;
}

template <typename T>
T& list<T>::back(void) {
  return head_->prev->value;
}

template <typename T>
const T& list<T>::back(void) const {
  return head_->prev->value;
}

// List iterators

template <typename T>
ListIterator<T> list<T>::begin(void) {
  return ListIterator(head_->next);
}

template <typename T>
const ListIterator<T> list<T>::begin(void) const {
  return ListIterator(head_->next);
}

template <typename T>
ListIterator<T> list<T>::end(void) {
  return ListIterator(head_);
}

template <typename T>
const ListIterator<T> list<T>::end(void) const {
  return ListIterator(head_);
}


// List capacity

template<typename T>
inline bool list<T>::empty(void) const noexcept {
	return head_->next == head_;
}

template<typename T>
inline size_t list<T>::size(void) const noexcept {
	size_t n = 0;
	ListNode<T> *tmp = head_->next;
	while (tmp != head_) {
		++n;
		tmp = tmp->next;
	}
	return n;
}

// List modifiers

template <typename T>
void list<T>::clear(void) {
  ListNode<T> *node = head_->next;
  while (node != head_) {
    ListNode<T> *tmp = node;
    node = node->next;
    DestroyNode(tmp);
  }
}

template <typename T>
ListIterator<T> list<T>::insert(ListIterator<T> pos, const T &value) {
  ListNode<T> * node = CreateNode(pos.node_, pos.node_->next, value);
  pos.node_->next->prev = node;
  pos.node_->next = node;
  return pos;
}

template <typename T>
void list<T>::erase(ListIterator<T> pos) {
  ListNode<T> *node = pos.node_;
  node->prev->next = node->next;
  node->next->prev = node->prev;
  DestroyNode(node);
}

template <typename T>
void list<T>::push_back(list<T>::const_reference value) {
  ListNode<T> *nptr = CreateNode(head_->prev, head_, value);
  if (empty()) {
    head_->next = nptr;
  } else {
    head_->prev->next = nptr;
  }
  head_->prev = nptr;
}

template<typename T>
void list<T>::pop_back(void) {
  if (empty()) {
    return;
  }

  ListNode<T> *tmp = head_->prev;
  tmp->prev->next = head_;
  head_->prev = tmp->prev;
  DestroyNode(tmp);
}

template<typename T>
void list<T>::push_front(list<T>::const_reference value) {
  ListNode<T> *nptr = CreateNode(head_, head_->next, value);
  if (empty()) {
    head_->prev = nptr;
  } else {
    head_->next->prev = nptr;
  }
    head_->next = nptr;
}

template <typename T>
void list<T>::pop_front(void) {
  if (empty()) {
    return;
  }

  ListNode<T> *tmp = head_->next;
  head_->next = tmp->next;
  tmp->next->prev = head_;
  DestroyNode(tmp);
}

template <typename T>
void list<T>::swap(list& other) {
  std::swap(head_, other.head_);
}

template <typename T>
void list<T>::merge(list& other) {
  if (this == &other) {
    return ;
  }

  iterator first1 = begin();
  iterator last1 = end();
  iterator first2 = other.begin();
  iterator last2 = other.end();
  while (first1 != last1 && first2 != last2) {
   if (*first2 < *first1) {
     iterator next = first2;
     ++next;
     {
        ListNode<T> *tmp = first2.node_;
        tmp->prev->next = tmp->next;
        tmp->next->prev = tmp->prev;
        ListNode<T> *node = first1.node_;
        tmp->next = node;
        tmp->prev = node->prev;
        node->prev->next = tmp;
        node->prev = tmp;
     }
     first2 = next;
   } else {
     ++first1;
   }
  }
  while (first2 != last2) {
    iterator next = first2;
    ++next;
    ListNode<T> *tmp = first2.node_;
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    tmp->next = head_;
    tmp->prev = head_->prev;
    head_->prev->next = tmp;
    head_->prev = tmp;
    first2 = next;
  }
}

template <typename T>
void list<T>::splice(const ListIterator<T> pos, list<T>& other) {
  iterator first = other.begin();
  iterator last = other.end();
  while (first != last) {
    iterator next = first;
    ++next;
    ListNode<T> *tmp = first.node_;
    tmp->prev->next = tmp->next;
    tmp->next->prev = tmp->prev;
    tmp->next = pos.node_;
    tmp->prev = pos.node_->prev;
    pos.node_->prev->next = tmp;
    pos.node_->prev = tmp;
    first = next;
  }
}

template <typename T>
void list<T>::reverse(void) {
  ListNode<T> *node = head_;
  do {
    std::swap(node->prev, node->next);
    node = node->prev;
  } while (node != head_);
}

template <typename T>
void list<T>::unique(void) {
  ListNode<T> *node = head_->next;
  while (node != head_) {
    while (node->value == node->next->value) {
      erase(node->next);
    }
    node = node->next;
  }
}

} // namespace s21

#endif  // INCLUDE_S21_LIST_H_
