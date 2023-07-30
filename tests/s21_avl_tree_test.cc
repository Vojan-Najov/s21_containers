#include "s21_avl_tree.h"

#include <memory>

#include <gtest/gtest.h>

class AvlTreeTest : public ::testing::Test {
 public:
	using Node = s21::AvlTreeNode<int>;
	using NodePtr = s21::AvlTreeNode<int>*;
 protected:
	void SetUp(void) override {
		
	}

	NodePtr *head;
};


TEST_F(AvlTreeTest, AvlTreeNode) {
	NodePtr tmp = new Node{0, nullptr, nullptr, nullptr, 0};
	(void) tmp;
}

TEST_F(AvlTreeTest, AvlTreeIteratorBase) {
	NodePtr tmp = new Node{0, nullptr, nullptr, nullptr, 0};
	s21::AvlTreeIteratorBase<int> it(tmp);
	(void) it;
}

TEST_F(AvlTreeTest, AvlTreeIterator) {
	NodePtr tmp = new Node{0, nullptr, nullptr, nullptr, 0};
	s21::AvlTreeIterator<int> it(tmp);
	(void) it;
}

TEST_F(AvlTreeTest, AvlTreeConstIterator) {
	NodePtr tmp = new Node{0, nullptr, nullptr, nullptr, 0};
	s21::AvlTreeConstIterator<int> it(tmp);
	(void) it;
}

TEST_F(AvlTreeTest, AvlTree) {
	s21::AvlTree<int, int, s21::Identity<int>, s21::Less<int>, std::allocator<int>> tree;
}
