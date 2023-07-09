// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_ARRAY_H_
#define INCLUDE_S21_ARRAY_H_

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T, size_t N>
class array final {
 public:
  typedef T value_type;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef size_t size_type;

 public:
  array(void);
  array(const std::initializer_list<value_type>& items);
  array(const array& other);
  array(array&& other);
  array& operator=(const array& a);
  array& operator=(array&& other);
  ~array(void);

 public:
  reference at(size_type pos);
  const_reference at(size_type pos) const;
  reference operator[](size_type pos) noexcept;
  const_reference operator[](size_type pos) const noexcept;
  reference front(void) noexcept;
  const_reference front(void) const noexcept;
  reference back(void) noexcept;
  const_reference back(void) const noexcept;
  iterator data(void) noexcept;
  const_iterator data(void) const noexcept;

 public:
  iterator begin(void) noexcept;
  iterator end(void) noexcept;
  const_iterator cbegin(void) const noexcept;
  const_iterator cend(void) const noexcept;

 public:
  bool empty(void) const noexcept;
  size_type size(void) const noexcept;
  size_type max_size(void) const noexcept;

 public:
  void swap(array& other) noexcept;
  void fill(const_reference value);

 private:
  value_type elements_[N];
};

// Constructors, destructor and overloading operator=.

template <typename T, size_t N>
array<T, N>::array(void) : elements_() {}

template <typename T, size_t N>
array<T, N>::array(std::initializer_list<T> const& items) : elements_() {
  if (items.size() > N) {
    throw std::out_of_range("array::initilized_constructor out of range");
  }

  iterator it = begin();
  for (value_type item : items) {
    *it++ = item;
  }
}

template <typename T, size_t N>
array<T, N>::array(const array<T, N>& other) {
  std::copy_n(other.elements_, N, elements_);
}

template <typename T, size_t N>
array<T, N>::array(array<T, N>&& other) : elements_() {
  std::swap(elements_, other.elements_);
}

template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(const array<T, N>& other) {
  std::copy_n(other.elements_, N, elements_);
  return *this;
}

template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(array<T, N>&& other) {
  std::swap(elements_, other.elements_);
  return *this;
}

template <typename T, size_t N>
array<T, N>::~array(void) {}

// Array element's access.

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::at(
    typename array<T, N>::size_type n) {
  if (n >= N) {
    throw std::out_of_range("array::at out of range");
  }

  return elements_[n];
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::at(
    typename array<T, N>::size_type n) const {
  if (n >= N) {
    throw std::out_of_range("array::at out of range");
  }

  return elements_[n];
}

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::operator[](
    typename array<T, N>::size_type n) noexcept {
  return elements_[n];
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::operator[](
    typename array<T, N>::size_type n) const noexcept {
  return elements_[n];
}

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::front(void) noexcept {
  return elements_[0];
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::front(
    void) const noexcept {
  return elements_[0];
}

template <typename T, size_t N>
inline typename array<T, N>::reference array<T, N>::back(void) noexcept {
  return elements_[N - 1];
}

template <typename T, size_t N>
inline typename array<T, N>::const_reference array<T, N>::back(
    void) const noexcept {
  return elements_[N - 1];
}

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::data(void) noexcept {
  return iterator(elements_);
}

template <typename T, size_t N>
inline typename array<T, N>::const_iterator array<T, N>::data(
    void) const noexcept {
  return const_iterator(elements_);
}

// Array iterators.

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::begin(void) noexcept {
  return iterator(elements_);
}

template <typename T, size_t N>
inline typename array<T, N>::const_iterator array<T, N>::cbegin(
    void) const noexcept {
  return const_iterator(elements_);
}

template <typename T, size_t N>
inline typename array<T, N>::iterator array<T, N>::end(void) noexcept {
  return iterator(elements_ + N);
}

template <typename T, size_t N>
inline typename array<T, N>::const_iterator array<T, N>::cend(
    void) const noexcept {
  return const_iterator(elements_ + N);
}

// Array capacity

template <typename T, size_t N>
inline typename array<T, N>::size_type array<T, N>::size(void) const noexcept {
  return N;
}

template <typename T, size_t N>
inline typename array<T, N>::size_type array<T, N>::max_size(
    void) const noexcept {
  return N;
}

template <typename T, size_t N>
inline bool array<T, N>::empty(void) const noexcept {
  return N == 0;
}

// Array modifiers

template <typename T, size_t N>
void array<T, N>::swap(array<T, N>& other) noexcept {
  std::swap_ranges(other.elements_, other.elements_ + N, elements_);
}

template <typename T, size_t N>
void array<T, N>::fill(array<T, N>::const_reference value) {
  std::fill_n(elements_, N, value);
}

}  // namespace s21

#endif  // INCLUDE_S21_ARRAY_H_
