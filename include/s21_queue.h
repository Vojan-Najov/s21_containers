// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_QUEUE_H_
#define INCLUDE_S21_QUEUE_H_

#include <cstddef>
#include <initializer_list>
#include <utility>

namespace s21 {

template <typename T>
class queue final {
 public:
  using value_type = T;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;

 public:
  queue(void) : head_(nullptr), tail_(nullptr) {}

  queue(const std::initializer_list<value_type> &items) : queue() {
    for (const_reference item : items) {
      push(item);
    }
  }

  queue(const queue &other) : queue() {
    QueueNode **node_ptr = &head_;
    QueueNode *node_other = other.head_;
    while (node_other != nullptr) {
      QueueNode *tmp = new QueueNode{nullptr, node_other->value};
      *node_ptr = tmp;
      tail_ = tmp;
      node_ptr = &tmp->next;
      node_other = node_other->next;
    }
  }

  queue(queue &&other) : queue() { swap(other); }

  queue &operator=(const queue &other) {
    if (this != &other) {
      queue tmp(other);
      swap(tmp);
    }

    return *this;
  }

  queue &operator=(queue &&other) {
    if (this != &other) {
      swap(other);
    }

    return *this;
  }

  ~queue(void) {
    while (head_ != nullptr) {
      QueueNode *tmp = head_;
      head_ = head_->next;
      delete tmp;
    }
  }

 public:
  bool empty(void) const noexcept { return head_ == nullptr; }

  size_type size(void) const noexcept {
    size_type sz = 0;
    QueueNode *node = head_;
    while (node != nullptr) {
      ++sz;
      node = node->next;
    }

    return sz;
  }

 public:
  const_reference front(void) const { return head_->value; }

  const_reference back(void) const { return tail_->value; }

 public:
  void push(const_reference value) {
    QueueNode *node = new QueueNode{nullptr, value};
    if (tail_ == nullptr) {
      tail_ = node;
      head_ = node;
    } else {
      tail_->next = node;
      tail_ = node;
    }
  }

  void pop(void) {
    QueueNode *tmp = head_;
    head_ = head_->next;
    if (head_ == nullptr) {
      tail_ = nullptr;
    }
    delete tmp;
  }

  void swap(queue &other) noexcept {
    std::swap(head_, other.head_);
    std::swap(tail_, other.tail_);
  }

 private:
  struct QueueNode {
    QueueNode *next;
    value_type value;
  };

 private:
  QueueNode *head_;
  QueueNode *tail_;
};

}  // namespace s21

#endif  // INCLUDE_S21_QUEUE_H_
