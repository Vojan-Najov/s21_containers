// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_MAP_H
#define INCLUDE_S21_MAP_H

#include "s21_avl_tree.h"
#include <memory>
#include <utility>
#include <initializer_list>

namespace s21 {

template <typename Key, typename T, typename Compare = s21::Less<Key>,
					typename Allocator = std::allocator<std::pair<const Key, T>>>
class map final {
 private:
	using BinaryTree = AvlTree<Key, std::pair<const Key, T>,
														 s21::Select1st<std::pair<const Key, T>>,
														 Compare, Allocator>;
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
			tree_.InsertUnique(item);
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
	void clear(void) { tree_.Clear(); }
	std::pair<iterator, bool> insert(const_reference value) {
		return tree_.InsertUnique(value);
	}

 public:
	bool contains(const Key& key) const;

 private:
	BinaryTree tree_;
};

} // namespace s21

#endif  // INCLUDE_S21_MAP_H
