// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_MAP_H_
#define INCLUDE_S21_MAP_H_

#include <initializer_list>
#include <memory>
#include <stdexcept>
#include <utility>

#include "s21_avl_tree.h"
#include "s21_vector.h"

namespace s21 {

template <typename Key, typename T, typename Compare = s21::Less<Key>,
          typename Allocator = std::allocator<std::pair<const Key, T>>>
class map final {
 private:
  using BinaryTree =
      AvlTree<Key, std::pair<const Key, T>,
              s21::Select1st<std::pair<const Key, T>>, Compare, Allocator>;

 public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<const key_type, mapped_type>;
  using reference = value_type&;
  using const_reference = const value_type&;
  using allocator_type = Allocator;
  using iterator = typename BinaryTree::iterator;
  using const_iterator = typename BinaryTree::const_iterator;
  using size_type = size_t;

 public:
  map(void) : tree_() {}

  map(const std::initializer_list<value_type>& items) : tree_() {
    for (const value_type& item : items) {
      tree_.insert_unique(item);
    }
  }

  map(const map& other) : tree_(other.tree_) {}

  map(map&& other) : tree_(std::move(other.tree_)) {}

  map& operator=(const map& other) {
    tree_ = other.tree_;
    return *this;
  }

  map& operator=(map&& other) noexcept {
    tree_ = std::move(other.tree_);
    return *this;
  }

  ~map(void) {}

 public:
  mapped_type& at(const key_type& key) {
    iterator it = find(key);
    if (it == end()) {
      throw std::out_of_range("Invalid key.");
    }
    return (*it).second;
  }

  const mapped_type& at(const key_type& key) const {
    const_iterator it = find(key);
    if (it == end()) {
      throw std::out_of_range("Invalid key.");
    }
    return (*it).second;
  }

  mapped_type& operator[](const key_type& key) {
    iterator it = find(key);
    if (it == end()) {
      std::pair<iterator, bool> result =
          tree_.insert_unique(std::make_pair(key, mapped_type()));
      it = result.first;
    }
    return (*it).second;
  }

 public:
  iterator begin(void) noexcept { return tree_.begin(); }

  const_iterator begin(void) const noexcept { return tree_.begin(); }

  const_iterator cbegin(void) const noexcept { return tree_.cbegin(); }

  iterator end(void) noexcept { return tree_.end(); }

  const_iterator end(void) const noexcept { return tree_.end(); }

  const_iterator cend(void) const noexcept { return tree_.cend(); }

 public:
  bool empty(void) const noexcept { return tree_.empty(); }

  size_type size(void) const noexcept { return tree_.size(); }

  size_type max_size(void) const noexcept { return tree_.max_size(); }

 public:
  void clear(void) { tree_.clear(); }

  std::pair<iterator, bool> insert(const_reference value) {
    return tree_.insert_unique(value);
  }

  std::pair<iterator, bool> insert(const key_type& key,
                                   const mapped_type& value) {
    return tree_.insert_unique(std::make_pair(key, value));
  }

  std::pair<iterator, bool> insert_or_assign(const key_type& key,
                                             mapped_type&& value) {
    iterator it = find(key);
    if (it != end()) {
      (*it).second = std::forward<mapped_type>(value);
      return std::make_pair(it, false);
    } else {
      return insert(key, value);
    }
  }

  void erase(iterator position) { tree_.erase(position); }

  void swap(map& other) noexcept { tree_.swap(other.tree_); }

  void merge(map& source) { tree_.merge_unique(source.tree_); }

 public:
  iterator find(const key_type& key) { return tree_.find(key); }

  const_iterator find(const key_type& key) const { return tree_.find(key); }

  bool contains(const Key& key) const { return tree_.contains(key); }

 public:
  vector<std::pair<iterator, bool>> insert_many(void) {
    return vector<std::pair<iterator, bool>>();
  }

  template <typename... Args>
  vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    vector<std::pair<iterator, bool>> vec;
    vec.reserve(sizeof...(args));

    for (auto&& arg : {args...}) {
      vec.push_back(tree_.insert_unique(arg));
    }

    return vec;
  }

#ifdef DEBUG

 public:
  int verify(void) const { return tree_.verify(); }

#endif  // DEBUG

 private:
  BinaryTree tree_;
};

}  // namespace s21

#endif  // INCLUDE_S21_MAP_H_
