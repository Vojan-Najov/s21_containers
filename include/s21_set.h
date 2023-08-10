// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_SET_H
#define INCLUDE_S21_SET_H

#include "s21_avl_tree.h"
#include <memory>
#include <utility>
#include <initializer_list>

namespace s21 {

template <typename Key, typename Compare = s21::Less<Key>,
					typename Allocator = std::allocator<Key>>
class set final {
 private:
	using BinaryTree = AvlTree<Key, Key, s21::Identity<Key>, Compare, Allocator>;

 public:
	using key_type = Key;
	using value_type = Key;
	using key_compare = Compare;
	using value_compare = Compare;
	using allocator_type = Allocator;
	using reference = value_type&;
	using const_reference = const value_type&;
	using iterator = typename BinaryTree::iterator;
	using const_iterator = typename BinaryTree::const_iterator;
	using size_type = size_t;
	using difference_type = typename BinaryTree::difference_type;

 public:
	set(void) : tree_() {}
	set(const std::initializer_list<value_type>& items) : tree_() {
		for (const value_type& item : items) {
			tree_.insert_unique(item);
		}
	}
	set(const set& other) : tree_(other.tree_) {}
	set(set &&other) : tree_(std::move(other.tree_)) {}
	set& operator=(const set& other) {
		tree_ = other.tree_;
		return *this;
	}
	set& operator=(set &&other) noexcept {
		tree_ = std::move(other.tree_);
		return *this;
	}
	~set(void) {}

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
	void erase(iterator position) { tree_.erase(position); }
	void swap(set& other) noexcept { tree_.swap(other.tree_); }
	void merge(set& source) { tree_.merge_unique(source.tree_); }

 public:
	iterator find(const_reference key) { return tree_.find(key); }
	const_iterator find(const_reference key) const { return tree_.find(key); }
	bool contains(const_reference key) const { return tree_.contains(key); }

#ifdef DEBUG
 public:
	int verify(void) const { return tree_.verify(); }
#endif  // DEBUG

 public:
	BinaryTree tree_;
};

}  // namespace s21

#endif  // INCLUDE_S21_SET_H
