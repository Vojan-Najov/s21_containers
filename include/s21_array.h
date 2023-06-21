// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_ARRAY_H_
#define INCLUDE_S21_ARRAY_H_

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace s21 {

template <typename T, std::size_t N>
class array {
 public:
  typedef T value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef value_type* iterator;
  typedef const value_type* const_iterator;
  typedef std::size_t size_type;

  array(void);
  // array(std::initializer_list<value_type> const &items);
  array(const array& other);
  array(array&& other);
  array& operator=(const array& a);
  array& operator=(array&& other);
  ~array(void);

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

  iterator begin(void) noexcept;
  const_iterator begin(void) const noexcept;
  iterator end(void) noexcept;
  const_iterator end(void) const noexcept;

  bool empty(void) const noexcept;
  size_type size(void) const noexcept;
  size_type max_size(void) const noexcept;

  void swap(array& other);
  void fill(const_reference value);

 private:
  value_type elements_[N];
};

template <typename T, std::size_t N>
array<T, N>::array(void) {}

template <typename T, std::size_t N>
array<T, N>::array(const array<T, N>& other) {
  // std::copy_n(elelements_, N, other.elements_);
  for (size_t i = 0; i < N; ++i) {
    elements_[i] = other.elements_[i];
  }
}

template <typename T, std::size_t N>
array<T, N>::array(array<T, N>&& other) {
  // std::swap_ranges(elements_, elements_ + N, other.elements_);
  // std::swap(elemets_, other.elements_);
  for (size_t i = 0; i < N; ++i) {
    std::swap(elements_, other.elements_);
  }
}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(const array<T, N>& other) {
  // std::copy_n(elelements_, N, other.elements_);
  for (size_t i = 0; i < N; ++i) {
    elements_ = other.elements_;
  }
}

template <typename T, std::size_t N>
array<T, N>& array<T, N>::operator=(array<T, N>&& other) {
  // std::swap_ranges(elements_, elements_ + N, other.elements_);
  // std::swap(elemets_, other.elements_);
  for (size_t i = 0; i < N; ++i) {
    std::swap(elements_, other.elements_);
  }
}

template <typename T, std::size_t N>
array<T, N>::~array(void) {}

template <typename T, std::size_t N>
void array<T, N>::fill(array<T, N>::const_reference value) {
  // std::fill_n(elements_, n, value);
  for (size_t i = 0; i < N; ++i) {
    elements_[i] = value;
  }
}

template <typename T, std::size_t N>
void array<T, N>::swap(array<T, N>& other) {
  // std::swap_ranges(elements_, elements_ + N, other.elements_);
  for (size_t i = 0; i < N; ++i) {
    std::swap(elements_, other.elements_);
  }
}

template <typename T, std::size_t N>
inline typename array<T, N>::iterator array<T, N>::begin(void) noexcept {
  return iterator(elements_);
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_iterator array<T, N>::begin(
    void) const noexcept {
  return const_iterator(elements_);
}

template <typename T, std::size_t N>
inline typename array<T, N>::iterator array<T, N>::end(void) noexcept {
  return iterator(elements_ + N);
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_iterator array<T, N>::end(
    void) const noexcept {
  return const_iterator(elements_ + N);
}

template <typename T, std::size_t N>
inline typename array<T, N>::size_type array<T, N>::size(void) const noexcept {
  return N;
}

template <typename T, std::size_t N>
inline typename array<T, N>::size_type array<T, N>::max_size(
    void) const noexcept {
  return N;
}

template <typename T, std::size_t N>
inline bool array<T, N>::empty(void) const noexcept {
  return N == 0;
}

template <typename T, std::size_t N>
inline typename array<T, N>::reference array<T, N>::at(
    typename array<T, N>::size_type n) {
  if (n >= N) {
    throw std::out_of_range("array::at out of range");
  }

  return elements_[n];
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_reference array<T, N>::at(
    typename array<T, N>::size_type n) const {
  if (n >= N) {
    throw std::out_of_range("array::at out of range");
  }

  return elements_[n];
}

template <typename T, std::size_t N>
inline typename array<T, N>::reference array<T, N>::operator[](
    typename array<T, N>::size_type n) noexcept {
  return elements_[n];
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_reference array<T, N>::operator[](
    typename array<T, N>::size_type n) const noexcept {
  return elements_[n];
}

template <typename T, std::size_t N>
inline typename array<T, N>::reference array<T, N>::front(void) noexcept {
  return elements_[0];
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_reference array<T, N>::front(
    void) const noexcept {
  return elements_[0];
}

template <typename T, std::size_t N>
inline typename array<T, N>::reference array<T, N>::back(void) noexcept {
  return elements_[N - 1];
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_reference array<T, N>::back(
    void) const noexcept {
  return elements_[N - 1];
}

template <typename T, std::size_t N>
inline typename array<T, N>::iterator array<T, N>::data(void) noexcept {
  return iterator(elements_);
}

template <typename T, std::size_t N>
inline typename array<T, N>::const_iterator array<T, N>::data(
    void) const noexcept {
  return const_iterator(elements_);
}
}  // namespace s21

#endif  // INCLUDE_S21_ARRAY_H_
