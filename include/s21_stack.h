// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_STACK_H_
#define INCLUDE_S21_STACK_H_

#include <cstddef>
#include <exception>
#include <initializer_list>
#include <utility>

namespace s21 {

template <typename T>
class stack final {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 public:
  stack(void) : head_(nullptr) {}

  stack(std::initializer_list<value_type> const &items) : stack() {
    for (const value_type &item : items) {
      push(item);
    }
  }

  stack(const stack &other) : stack() {
    StackNode **node_ptr = &head_;
    StackNode *node_other = other.head_;
    while (node_other != nullptr) {
      StackNode *tmp = new StackNode{nullptr, node_other->value};
      *node_ptr = tmp;
      node_ptr = &tmp->next;
      node_other = node_other->next;
    }
  }

  stack(stack &&other) : stack() { swap(other); }

  stack &operator=(const stack &other) {
    if (this != &other) {
      stack tmp(other);
      tmp.swap(*this);
    }
    return *this;
  }

  stack &operator=(stack &&other) {
    if (this != &other) {
      swap(other);
    }

    return *this;
  }

  ~stack(void) {
    while (head_ != nullptr) {
      StackNode *tmp = head_;
      head_ = head_->next;
      delete tmp;
    }
  }

 public:
  reference top(void) { return head_->value; }
  const_reference top(void) const { return head_->value; }

 public:
  bool empty(void) const noexcept { return head_ == nullptr; }
  size_type size(void) const noexcept {
    size_type sz = 0;
    StackNode *tmp = head_;
    while (tmp != nullptr) {
      ++sz;
      tmp = tmp->next;
    }
    return sz;
  }

 public:
  void push(const_reference value) {
    StackNode *node = new StackNode{head_, value};
    head_ = node;
  }
  void pop(void) {
    StackNode *node = head_;
    head_ = head_->next;
    delete node;
  }
  void swap(stack &other) noexcept { std::swap(head_, other.head_); }

 private:
  struct StackNode final {
    StackNode *next;
    T value;
  };

 private:
  StackNode *head_;
};

}  // namespace s21

#endif  // INCLUDE_S21_STACK_H_
