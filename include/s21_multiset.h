// Copyright 2023 <Carmine Cartman, Vojan Najov>

#ifndef INCLUDE_S21_MULTISET_H
#define INCLUDE_S21_MULTISET_H

#include "s21_avl_tree.h"
#include <memory>
#include <utility>
#include <initializer_list>

namespace s21 {

template <typename Key, typename Compare = s21::Less<Key>,
					typename Allocator = std::allocator<Key>>
class multiset final {
 private:
	using BinaryTree = AvlTree<Key, Key, s21::Identity<Key>, Compare, Allocator>;

 public:
	using key_type = Key;
	using value_type = Key;
	using reference = value_type&;
	using const_reference = const value_type&;
	using iterator = typename BinaryTree::iterator;
	using const_iterator = typename BinaryTree::const_iterator;
	using size_type = size_t;
	using difference_type = typename BinaryTree::difference_type;
	using allocator_type = Allocator;
	using key_compare = Compare;
	using value_compare = Compare;

 public:
	multiset(void) : tree_() {}
	multiset(const std::initializer_list<value_type>& items) : tree_() {
		for (const value_type& item : items) {
			tree_.insert_equal(item);
		}
	}
	multiset(const multiset& other) : tree_(other.tree_) {}
	multiset(multiset &&other) : tree_(std::move(other.tree_)) {}
	multiset& operator=(const multiset& other) {
		tree_ = other.tree_;
		return *this;
	}
	multiset& operator=(multiset&& other) {
		tree_ = std::move(other.tree_);
		return *this;
	}
	~multiset(void) {}

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
	iterator insert(const_reference& value) { return tree_.insert_equal(value); }
	void erase(iterator position) { tree_.erase(position); }
	void swap(multiset& other) { tree_.swap(other.tree_); }
	void merge(multiset& source) { tree_.merge_equal(source.tree_); }

 public:
	size_type count(const key_type& key) const noexcept { return tree_.count(key); }
	iterator find(const key_type& key) noexcept { return tree_.find(key); }
	const_iterator find(const key_type& key) const noexcept { return tree_.find(key); }
	bool contains(const key_type& key) const noexcept { return tree_.contains(key); }
	iterator lower_bound(const key_type& key) noexcept
	{ return tree_.lower_bound(key); }
	const_iterator lower_bound(const key_type& key) const noexcept
	{ return tree_.lower_bound(key); }
	iterator upper_bound(const key_type& key) noexcept
	{ return tree_.upper_bound(key); }
	const_iterator upper_bound(const key_type& key) const noexcept
	{ return tree_.upper_bound(key); }
	std::pair<iterator, iterator> equal_range(const key_type &key) noexcept
	{ return tree_.equal_range(key); }
	std::pair<const_iterator, const_iterator>
	equal_range(const key_type &key) const noexcept
	{ return tree_.equal_range(key); }

#ifdef DEBUG
 public:
	int verify(void) const { return tree_.verify(); }
#endif  // DEBUG

 private:
	BinaryTree tree_;
};

}  // namespace s21

#endif  // INCLUDE_S21_MULTISET_H
