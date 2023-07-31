#include "s21_avl_tree.h"

#include <memory>
#include <iostream>

#include <gtest/gtest.h>

class AvlTreeTest : public ::testing::Test {
 public:
	using Node = s21::AvlTreeNode<int>;
	using NodePtr = s21::AvlTreeNode<int>*;
 protected:
	void SetUp(void) override {
		s21::AvlTreeNode<int> *a[13];
		for (int i = 0; i < 13; ++i) {
			a[i] = test_tree.CreateNode(100 * i + 100);
		}
		a[0]->left = nullptr; 	a[0]->right = nullptr; 	a[0]->parent = a[1];
		a[1]->left = a[0]; 			a[1]->right = nullptr; 	a[1]->parent = a[2];
		a[2]->left = a[1]; 			a[2]->right = a[3]; 		a[2]->parent = a[4];
		a[3]->left = nullptr; 	a[3]->right = nullptr; 	a[3]->parent = a[2];
		a[4]->left = a[2]; 			a[4]->right = a[7]; 		a[4]->parent = test_tree.head_;
		a[5]->left = nullptr; 	a[5]->right = a[6]; 		a[5]->parent =a[7] ;
		a[6]->left = nullptr; 	a[6]->right = nullptr; 	a[6]->parent = a[5];
		a[7]->left = a[5]; 			a[7]->right = a[11]; 		a[7]->parent = a[4];
		a[8]->left = nullptr;	 	a[8]->right = nullptr;	a[8]->parent = a[9];
		a[9]->left = a[8]; 			a[9]->right = a[10]; 		a[9]->parent = a[11];
		a[10]->left = nullptr;	a[10]->right = nullptr; a[10]->parent = a[9];
		a[11]->left = a[9]; 		a[11]->right = a[12];		a[11]->parent = a[7];
		a[12]->left = nullptr;	a[12]->right = nullptr;	a[12]->parent = a[11];

		test_tree.head_->parent = a[4];
		test_tree.head_->left = a[0];
		test_tree.head_->right = a[12];
		test_tree.node_count_ = 13;
	}

	s21::AvlTree<int, int, s21::Identity<int>, s21::Less<int>, std::allocator<int>> test_tree;
};


TEST_F(AvlTreeTest, AvlTreeNode) {
	NodePtr tmp = new Node{0, nullptr, nullptr, nullptr, 0};
	delete tmp;
	(void) tmp;
}

TEST_F(AvlTreeTest, AvlTreeIteratorBase) {
	NodePtr tmp = new Node{0, nullptr, nullptr, nullptr, 0};
	s21::AvlTreeIteratorBase<int> it(tmp);
	delete tmp;
	(void) it;
}

TEST_F(AvlTreeTest, AvlTreeIterator) {
	NodePtr tmp = new Node{0, nullptr, nullptr, nullptr, 0};
	s21::AvlTreeIterator<int> it(tmp);
	delete tmp;
	(void) it;
}

TEST_F(AvlTreeTest, AvlTreeConstIterator) {
	NodePtr tmp = new Node{0, nullptr, nullptr, nullptr, 0};
	s21::AvlTreeConstIterator<int> it(tmp);
	delete tmp;
	(void) it;
}

TEST_F(AvlTreeTest, AvlTree) {
	s21::AvlTree<int, int, s21::Identity<int>, s21::Less<int>, std::allocator<int>> tree;
}

TEST_F(AvlTreeTest, AvlTree2) {
	auto it = test_tree.begin();
	while (it != test_tree.end()) {
		std::cout << it.getNode()->value << '\n';
		++it;
	}
}
