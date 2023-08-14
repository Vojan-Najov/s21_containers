// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_LIST_H_
#define INCLUDE_S21_LIST_H_

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iterator>

namespace s21 {

template <typename T>
struct ListNode;

template <typename T>
class ListIteratorBase;

template <typename T>
class ListIterator;

template <typename T>
class ListConstIterator;

template <typename T>
class list;


// LIST NODE

template <typename T>
struct ListNode final {
  ListNode *prev;
  ListNode *next;
  T value;
};


// LIST_ITERATOR_BASE, LIST_ITERATOR, LIST_CONST_ITERATOR

template <typename T>
class ListIteratorBase {
 public:
  explicit ListIteratorBase(ListNode<T> *node) : node_(node) {}

  void increment(void) { node_ = node_->next; }

  void decrement(void) { node_ = node_->prev; }

  template <typename U>
  friend bool operator==(const ListIteratorBase<U> &lhs,
                         const ListIteratorBase<U> &rhs);

 protected:
  ~ListIteratorBase(void) {}

 protected:
  ListNode<T> *node_;
};

template <typename T>
inline bool operator==(const ListIteratorBase<T> &lhs,
                       const ListIteratorBase<T> &rhs) {
  return lhs.node_ == rhs.node_;
}

template <typename T>
inline bool operator!=(const ListIteratorBase<T> &lhs,
                       const ListIteratorBase<T> &rhs) {
  return !(lhs == rhs);
}


template <typename T>
class ListIterator final : public ListIteratorBase<T> {
 public:
  friend list<T>;
	friend ListConstIterator<T>;

  using difference_type = std::ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using pointer = T *;
  using reference = T &;

  explicit ListIterator(ListNode<T> *node) : ListIteratorBase<T>(node) {}

  ListIterator &operator++(void) {
    ListIteratorBase<T>::increment();
    return *this;
  }

  ListIterator operator++(int) {
    ListIterator tmp{*this};
    ListIteratorBase<T>::increment();
    return tmp;
  }

  ListIterator &operator--(void) {
    ListIteratorBase<T>::decrement();
    return *this;
  }

  ListIterator operator--(int) {
    ListIterator tmp{*this};
    ListIteratorBase<T>::decrement();
    return tmp;
  }

  T &operator*(void) { return ListIteratorBase<T>::node_->value; }

  T *operator->(void) { return &ListIteratorBase<T>::node_->value; }
};


template <typename T>
class ListConstIterator final : public ListIteratorBase<T> {
 public:
  friend list<T>;

  using difference_type = ptrdiff_t;
  using iterator_category = std::bidirectional_iterator_tag;
  using value_type = T;
  using pointer = T *;
  using reference = T &;

  explicit ListConstIterator(ListNode<T> *node) : ListIteratorBase<T>(node) {}

	ListConstIterator(const ListIterator<T> &other)
		: ListIteratorBase<T>(other.node_) {}

  ListConstIterator &operator++(void) {
    ListIteratorBase<T>::increment();
    return *this;
  }

  ListConstIterator operator++(int) {
    ListIterator tmp{*this};
    ListIteratorBase<T>::increment();
    return tmp;
  }

  ListConstIterator &operator--(void) {
    ListIteratorBase<T>::decrement();
    return *this;
  }

  ListConstIterator operator--(int) {
    ListConstIterator tmp{*this};
    ListIteratorBase<T>::decrement();
    return tmp;
  }

  const T &operator*(void) { return ListIteratorBase<T>::node_->value; }

  const T *operator->(void) { return &ListIteratorBase<T>::node_->value; }
};


// LIST

template <typename T>
class list final {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = ListIterator<T>;
  using const_iterator = ListConstIterator<T>;
  using size_type = size_t;

 public:
  list(void);
  explicit list(size_type n);
  list(const std::initializer_list<value_type> &items);
  list(const list &other);
  list(list &&other);
  ~list(void);
  list &operator=(const list &other);
  list &operator=(list &&other);

 public:
  reference front(void);
  reference back(void);
  const_reference front(void) const;
  const_reference back(void) const;

 public:
  iterator begin(void) noexcept;
  const_iterator begin(void) const noexcept;
  iterator end(void) noexcept;
  const_iterator end(void) const noexcept;
  const_iterator cbegin(void) const noexcept;
  const_iterator cend(void) const noexcept;

 public:
  bool empty(void) const noexcept;
  size_type size(void) const noexcept;
  size_type max_size(void) const noexcept;

 public:
  void clear(void);
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back(void);
  void push_front(const_reference value);
  void pop_front(void);
  void swap(list &other);
  void merge(list &other);
  void splice(const_iterator pos, list &other);
  void reverse(void);
  void unique(void);
  void sort(void);

 public:
	template <typename... Args>
	iterator insert_many(const_iterator pos, Args&&... args);
	template <typename... Args>
	void insert_many_back(Args&&... args);
	template <typename... Args>
	void insert_many_front(Args&&... args);

 private:
  ListNode<T> *CreateNode(ListNode<T> *prev, ListNode<T> *next,
                          const value_type &value);
  void DestroyNode(ListNode<T> *node);
  void Transfer(iterator position, iterator first, iterator last);

 private:
  ListNode<T> *head_;
};


// list: auxiliary private member functions.

template <typename T>
ListNode<T> *list<T>::CreateNode(ListNode<T> *prev,
																 ListNode<T> *next,
                                 const T &value) {
  ListNode<T> *node =
      static_cast<ListNode<T> *>(operator new(sizeof(ListNode<T>)));
  node->prev = prev;
  node->next = next;
  try {
    new (&node->value) T(value);
  } catch (std::exception &e) {
    operator delete(node);
    throw e;
  }

  return node;
}

template <typename T>
void list<T>::DestroyNode(ListNode<T> *node) {
  node->value.~T();
  operator delete(static_cast<void *>(node));
}

template <typename T>
void list<T>::Transfer(iterator position, iterator first, iterator last) {
  if (position != first && position != last) {
    ListNode<T> *tmp = position.node_->prev;
    last.node_->prev->next = position.node_;
    first.node_->prev->next = last.node_;
    position.node_->prev->next = first.node_;
    position.node_->prev = last.node_->prev;
    last.node_->prev = first.node_->prev;
    first.node_->prev = tmp;
  }
}


// list: ctors, dtor, overloading operator=.

template <typename T>
list<T>::list(void) : head_(nullptr) {
  head_ = static_cast<ListNode<T> *>(operator new(sizeof(ListNode<T>)));
  head_->prev = head_;
  head_->next = head_;
}

template <typename T>
list<T>::list(typename list<T>::size_type n) : list() {
  for (size_t i = 0; i < n; ++i) {
    push_back(value_type());
  }
}

template <typename T>
list<T>::list(const std::initializer_list<T> &items) : list() {
  for (const T &item : items) {
    push_back(item);
  }
}

template <typename T>
list<T>::list(const list<T> &other) : list() {
  const_iterator it = other.cbegin();
  const_iterator last = other.cend();
  while (it != last) {
    push_back(*it);
    ++it;
  }
}

template <typename T>
list<T>::list(list<T> &&other) : list() {
  swap(other);
}

template <typename T>
inline list<T> &list<T>::operator=(const list<T> &other) {
  if (this != &other) {
    list<T> tmp(other);
    swap(tmp);
  }
  return *this;
}

template <typename T>
inline list<T> &list<T>::operator=(list<T> &&other) {
  if (this != &other) {
    swap(other);
  }
  return *this;
}

template <typename T>
list<T>::~list(void) {
  clear();
  operator delete(head_);
}


// list: element access

template <typename T>
inline T &list<T>::front(void) {
  return head_->next->value;
}

template <typename T>
inline const T &list<T>::front(void) const {
  return head_->next->value;
}

template <typename T>
inline T &list<T>::back(void) {
  return head_->prev->value;
}

template <typename T>
inline const T &list<T>::back(void) const {
  return head_->prev->value;
}


// list: iterators

template <typename T>
inline ListIterator<T> list<T>::begin(void) noexcept {
  return iterator(head_->next);
}

template <typename T>
inline ListConstIterator<T> list<T>::begin(void) const noexcept {
  return const_iterator(head_->next);
}

template <typename T>
inline ListIterator<T> list<T>::end(void) noexcept {
  return iterator(head_);
}

template <typename T>
inline ListConstIterator<T> list<T>::end(void) const noexcept {
  return const_iterator(head_);
}

template <typename T>
inline ListConstIterator<T> list<T>::cbegin(void) const noexcept {
  return const_iterator{head_->next};
}

template <typename T>
inline ListConstIterator<T> list<T>::cend(void) const noexcept {
  return const_iterator{head_};
}


// list: capacity

template <typename T>
inline bool list<T>::empty(void) const noexcept {
  return head_ == head_->next;
}

template <typename T>
inline size_t list<T>::size(void) const noexcept {
  size_t n = 0;
  for (const_iterator it = cbegin(), last = cend(); it != last; ++it) {
    ++n;
  }
  return n;
}

template <typename T>
inline size_t list<T>::max_size(void) const noexcept {
  return size_t(-1) / 2 / sizeof(ListNode<T>);
}


// list: modifiers

template <typename T>
inline void list<T>::clear(void) {
  ListNode<T> *node = head_->next;
  while (node != head_) {
    ListNode<T> *tmp = node;
    node = node->next;
    DestroyNode(tmp);
  }
  head_->next = head_;
  head_->prev = head_;
}

template <typename T>
inline typename list<T>::iterator list<T>::insert(
    typename list<T>::iterator pos, typename list<T>::const_reference value) {
  ListNode<T> *node = CreateNode(pos.node_->prev, pos.node_, value);
  pos.node_->prev->next = node;
  pos.node_->prev = node;

  return iterator(node);
}

template <typename T>
inline void list<T>::erase(typename list<T>::iterator pos) {
  ListNode<T> *node = pos.node_;
  node->prev->next = node->next;
  node->next->prev = node->prev;
  DestroyNode(node);
}

template <typename T>
inline void list<T>::push_back(const T &value) {
  insert(end(), value);
}

template <typename T>
inline void list<T>::pop_back(void) {
  erase(--end());
}

template <typename T>
inline void list<T>::push_front(const T &value) {
  insert(begin(), value);
}

template <typename T>
inline void list<T>::pop_front(void) {
  erase(begin());
}

template <typename T>
inline void list<T>::swap(list<T> &other) {
  std::swap(head_, other.head_);
}

template <typename T>
inline void list<T>::merge(list<T> &other) {
  iterator it = begin();
  iterator last = end();
  iterator it_other = other.begin();
  iterator last_other = other.end();

  while (it != last && it_other != last_other) {
    if (*it_other < *it) {
      iterator cur = it_other++;
      Transfer(it, cur, it_other);
    } else {
      ++it;
    }
  }
  if (it_other != last_other) {
    Transfer(last, it_other, last_other);
  }
}

template <typename T>
inline void list<T>::splice(const_iterator pos, list &other) {
  Transfer(iterator{pos.node_}, other.begin(), other.end());
}

template <typename T>
inline void list<T>::reverse(void) {
  ListNode<T> *node = head_;
  do {
    std::swap(node->prev, node->next);
    node = node->prev;
  } while (node != head_);
}

template <typename T>
inline void list<T>::unique(void) {
  iterator it = begin();
  iterator last = end();
  iterator next = it;
  while (++next != last) {
    if (*it == *next) {
      erase(next);
    } else {
      it = next;
    }
    next = it;
  }
}

template <typename T>
inline void list<T>::sort(void) {
  if (head_ == head_->next || head_->next->next == head_) {
    return;
  }

  list hooks[64];
  list carry;
  int fill_hooks = 0;
  while (!empty()) {
    carry.Transfer(carry.begin(), begin(), ++begin());
    int i = 0;
    while (i < fill_hooks && !hooks[i].empty()) {
      hooks[i].merge(carry);
      carry.swap(hooks[i]);
      ++i;
    }
    carry.swap(hooks[i]);
    if (i == fill_hooks) {
      ++fill_hooks;
    }
  }
  for (int i = 1; i < fill_hooks; ++i) {
    hooks[i].merge(hooks[i - 1]);
  }
  swap(hooks[fill_hooks - 1]);
}

template <typename T>
template <typename... Args>
inline typename list<T>::iterator
list<T>::insert_many(const_iterator pos, Args&&... args) {
	list tmp{args...};
	if (!tmp.empty()) {
		Transfer(iterator(pos.node_), tmp.begin(), tmp.end());
	}
	return iterator(pos.node_);
}

template <typename T>
template <typename... Args>
inline void list<T>::insert_many_back(Args&&... args) {
	insert_many(cend(), args...);
}

template <typename T>
template <typename... Args>
inline void list<T>::insert_many_front(Args&&... args) {
	insert_many(cbegin(), args...);
}

}  // namespace s21

#endif  // INCLUDE_S21_LIST_H_
