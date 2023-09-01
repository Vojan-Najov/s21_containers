#ifndef INCLUDE_S21_VECTOR_H_
#define INCLUDE_S21_VECTOR_H_

#include <algorithm>
#include <initializer_list>
#include <limits>
#include <memory>
#include <stdexcept>

namespace s21 {

template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using pointer = T *;
  using const_pointer = const T *;
  using size_type = size_t;

  vector(void);
  vector(size_type len);
  vector(vector const &vect);
  vector(vector<T> &&v);
  vector(std::initializer_list<value_type> const &items);
  ~vector(void);
  vector &operator=(const vector &v);
  vector &operator=(vector &&v) noexcept;

  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos);
  const_reference operator[](size_type pos) const;
  reference front(void);
  const_reference front(void) const;
  reference back(void);
  const_reference back(void) const;
  pointer data(void) noexcept;
  const_pointer data(void) const noexcept;

  iterator begin(void) noexcept;
  const_iterator begin(void) const noexcept;
  iterator end(void) noexcept;
  const_iterator end(void) const noexcept;

  bool empty(void) const noexcept;
  size_type size(void) const noexcept;
  size_type max_size(void) const noexcept;
  void reserve(size_type size);
  size_type capacity(void) const noexcept;
  void shrink_to_fit(void);

  void clear();
  iterator insert(iterator pos, const_reference value);
  void erase(iterator pos);
  void push_back(const_reference value);
  void pop_back();
  void swap(vector &other) noexcept;

  template <typename... Args>
  iterator insert_many(iterator position, Args &&...args);
  template <typename... Args>
  void insert_many_back(Args &&...args);

 private:
  pointer allocate(size_type n);
  void deallocate(pointer ptr);
  void construct(pointer ptr, const_reference value);
  void destroy(pointer ptr);
  void destroy(pointer start, pointer finish);
  pointer uninitialized_fill_n(pointer ptr, size_type n,
                               const value_type &value);
  template <typename InputIterator>
  pointer uninitialized_copy(InputIterator first, InputIterator last,
                             pointer ptr);

 private:
  pointer data_;
  size_type size_;
  size_type capacity_;
};

// Ctors, Dtor, overloaded operator=

template <typename T>
vector<T>::vector(void) : data_(nullptr), size_(0), capacity_(0) {}

template <typename T>
vector<T>::vector(size_type n) : data_(nullptr), size_(n), capacity_(n) {
  data_ = allocate(size_);
  try {
    uninitialized_fill_n(data_, n, value_type());
  } catch (...) {
    deallocate(data_);
    throw;
  }
}

template <typename T>
vector<T>::vector(std::initializer_list<value_type> const &items)
    : data_(nullptr), size_(items.size()), capacity_(items.size()) {
  data_ = allocate(size_);
  try {
    uninitialized_copy(items.begin(), items.end(), data_);
  } catch (...) {
    deallocate(data_);
    throw;
  }
}

template <typename T>
vector<T>::vector(const vector &other)
    : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
  data_ = allocate(capacity_);
  try {
    uninitialized_copy(other.begin(), other.end(), data_);
  } catch (...) {
    deallocate(data_);
    throw;
  }
}

template <typename T>
vector<T>::vector(vector<T> &&other)
    : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
  other.data_ = nullptr;
  other.size_ = 0;
  other.capacity_ = 0;
}

template <typename T>
vector<T>::~vector(void) {
  destroy(data_, data_ + size_);
  deallocate(data_);
}

template <typename T>
vector<T> &vector<T>::operator=(const vector &other) {
  if (this == &other) {
    return *this;
  }

  if (other.size_ > capacity_) {
    pointer new_data = allocate(other.size_);
    try {
      uninitialized_copy(other.begin(), other.end(), new_data);
    } catch (...) {
      deallocate(new_data);
      throw;
    }
    destroy(data_, data_ + size_);
    deallocate(data_);
    data_ = new_data;
    capacity_ = other.size_;
  } else if (other.size_ <= size_) {
    std::copy(other.begin(), other.end(), data_);
    destroy(data_ + other.size_, data_ + size_);
  } else {
    std::copy(other.data_, other.data_ + size_, data_);
    uninitialized_copy(other.data_ + size_, other.data_ + other.size_,
                       data_ + size_);
  }
  size_ = other.size_;

  return *this;
}

template <typename T>
vector<T> &vector<T>::operator=(vector &&other) noexcept {
  swap(other);
  return *this;
}

// Element access

template <typename T>
inline typename vector<T>::reference vector<T>::at(size_type pos) {
  if (pos >= size_) {
    throw std::out_of_range("vector: at out of range");
  }
  return data_[pos];
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::at(size_type pos) const {
  if (pos >= size_) {
    throw std::out_of_range("vector: at out of range");
  }
  return data_[pos];
}

template <typename T>
inline typename vector<T>::reference vector<T>::operator[](size_type pos) {
  return data_[pos];
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::operator[](
    size_type pos) const {
  return data_[pos];
}

template <typename T>
inline typename vector<T>::reference vector<T>::front(void) {
  return data_[0];
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::front(void) const {
  return data_[0];
}

template <typename T>
inline typename vector<T>::reference vector<T>::back(void) {
  return data_[size_ - 1];
}

template <typename T>
inline typename vector<T>::const_reference vector<T>::back(void) const {
  return data_[size_ - 1];
}

template <typename T>
inline typename vector<T>::pointer vector<T>::data(void) noexcept {
  return data_;
}

template <typename T>
inline typename vector<T>::const_pointer vector<T>::data(void) const noexcept {
  return data_;
}

// ITERATORS

template <typename T>
inline typename vector<T>::iterator vector<T>::begin(void) noexcept {
  return data_;
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::begin(
    void) const noexcept {
  return data_;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::end(void) noexcept {
  return data_ + size_;
}

template <typename T>
inline typename vector<T>::const_iterator vector<T>::end(void) const noexcept {
  return data_ + size_;
}

// CAPACITY

template <typename T>
inline bool vector<T>::empty(void) const noexcept {
  return size_ == 0;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::size(void) const noexcept {
  return size_;
}

template <typename T>
inline typename vector<T>::size_type vector<T>::max_size(void) const noexcept {
  /*
   * return std::numeric_limits<size_type>::max() / 2 / sizeof(T);
   */

  return std::allocator<T>().max_size();
}

template <typename T>
inline void vector<T>::reserve(size_type new_cap) {
  if (new_cap > capacity_) {
    pointer new_data = allocate(new_cap);
    try {
      uninitialized_copy(data_, data_ + size_, new_data);
    } catch (...) {
      deallocate(new_data);
      throw;
    }
    destroy(data_, data_ + size_);
    deallocate(data_);
    data_ = new_data;
    capacity_ = new_cap;
  }
}

template <typename T>
inline typename vector<T>::size_type vector<T>::capacity(void) const noexcept {
  return capacity_;
}

template <typename T>
inline void vector<T>::shrink_to_fit(void) {
  if (capacity_ > size_) {
    pointer new_data = allocate(size_);
    try {
      uninitialized_copy(data_, data_ + size_, new_data);
    } catch (...) {
      deallocate(new_data);
      throw;
    }
    destroy(data_, data_ + size_);
    deallocate(data_);
    data_ = new_data;
    capacity_ = size_;
  }
}

// MODIFIERS

template <typename T>
inline void vector<T>::clear() {
  destroy(data_, data_ + size_);
  size_ = 0;
}

template <typename T>
inline typename vector<T>::iterator vector<T>::insert(iterator position,
                                                      const_reference value) {
  size_type diff = position - data_;
  if (size_ != capacity_ && position == end()) {
    construct(data_ + size_, value);
    ++size_;
  } else if (size_ < capacity_) {
    construct(data_ + size_, data_[size_ - 1]);
    ++size_;
    std::copy_backward(position, data_ + size_ - 2, data_ + size_ - 1);
    *position = value;
  } else {
    size_type new_capacity = size_ == 0 ? 1 : 2 * size_;
    pointer new_data = allocate(new_capacity);
    pointer last = new_data;
    pointer except_ptr = new_data;
    try {
      last = uninitialized_copy(data_, position, new_data);
      except_ptr = last;
      construct(last, value);
      ++last;
      ++except_ptr;
      last = uninitialized_copy(position, data_ + size_, last);
    } catch (...) {
      destroy(new_data, except_ptr);
      deallocate(new_data);
      throw;
    }
    destroy(data_, data_ + size_);
    deallocate(data_);
    data_ = new_data;
    ++size_;
    capacity_ = new_capacity;
  }

  return data_ + diff;
}

template <typename T>
inline void vector<T>::erase(iterator pos) {
  if (pos != end()) {
    std::copy(pos + 1, data_ + size_, pos);
  }
  --size_;
  destroy(data_ + size_);
}

template <typename T>
inline void vector<T>::push_back(const_reference value) {
  if (size_ != capacity_) {
    construct(data_ + size_, value);
    ++size_;
  } else {
    size_type new_capacity = size_ == 0 ? 1 : 2 * size_;
    pointer new_data = allocate(new_capacity);
    try {
      uninitialized_copy(data_, data_ + size_, new_data);
    } catch (...) {
      deallocate(new_data);
      throw;
    }
    try {
      construct(new_data + size_, value);
    } catch (...) {
      destroy(new_data, new_data + size_);
      deallocate(new_data);
      throw;
    }
    destroy(data_, data_ + size_);
    deallocate(data_);
    data_ = new_data;
    ++size_;
    capacity_ = new_capacity;
  }
}

template <typename T>
void vector<T>::pop_back() {
  --size_;
  destroy(data_ + size_);
}

template <typename T>
void vector<T>::swap(vector<T> &other) noexcept {
  std::swap(data_, other.data_);
  std::swap(size_, other.size_);
  std::swap(capacity_, other.capacity_);
}

// INSERT MANY

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::insert_many(iterator pos,
                                                    Args &&...args) {
  vector<value_type> temp{args...};
  iterator insert_pos = begin() + (pos - begin());
  for (size_t i = 0; i < temp.size(); i++, insert_pos++) {
    insert_pos = insert(insert_pos, temp[i]);
  }

  return insert_pos;
}

template <typename T>
template <typename... Args>
void vector<T>::insert_many_back(Args &&...args) {
  insert_many(end(), args...);
}

// Auxiliary private methods

/*
 *  Allocate uninitialized memory for n cells.
 */
template <typename T>
inline typename vector<T>::pointer vector<T>::allocate(size_type n) {
  if (n > max_size()) {
    throw std::length_error("cannot create vector larger then max_size()");
  }
  return static_cast<pointer>(operator new(sizeof(value_type) * n));
}

/*
 *  Deallocate array.
 */
template <typename T>
inline void vector<T>::deallocate(pointer ptr) {
  operator delete(static_cast<void *>(ptr));
}

/*
 *  Construct value.
 */
template <typename T>
inline void vector<T>::construct(pointer ptr, const_reference value) {
  new (ptr) value_type(value);
}

/*
 *  Destroy objects in the range.
 */
template <typename T>
inline void vector<T>::destroy(pointer start, pointer finish) {
  while (start != finish) {
    start->~value_type();
    ++start;
  }
}

/*
 *  Destroy the only single object.
 */
template <typename T>
inline void vector<T>::destroy(pointer ptr) {
  ptr->~value_type();
}

/*
 *  Initialize n array cells with the value passed as an argument.
 *  Returns the address behind the last initialized cell.
 */
template <typename T>
inline typename vector<T>::pointer vector<T>::uninitialized_fill_n(
    pointer ptr, size_type n, const value_type &value) {
  pointer tmp = ptr;
  while (n > 0) {
    try {
      new (ptr) value_type(value);
      ++ptr;
      --n;
    } catch (...) {
      destroy(tmp, ptr);
      throw;
    }
  }
  return ptr;
}

/*
 *  Copy values from the range [first, last)  and initialize cells with these
 * values. Returns the address behind the last initialized cell.
 */
template <typename T>
template <typename InputIterator>
inline typename vector<T>::pointer vector<T>::uninitialized_copy(
    InputIterator first, InputIterator last, pointer ptr) {
  pointer tmp = ptr;
  while (first != last) {
    try {
      new (ptr) value_type(*first);
      ++ptr;
      ++first;
    } catch (...) {
      destroy(tmp, ptr);
      throw;
    }
  }
  return ptr;
}

}  // namespace s21

#endif  // INCLUDE_S21_VECTOR_H_
