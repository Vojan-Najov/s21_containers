#include "s21_stack.h"

#include <gtest/gtest.h>

#include <cstdlib>
#include <exception>
#include <stack>
#include <vector>

class StackTest : public ::testing::Test {
 protected:
  void SetUp(void) override { srand(1); }

  template <typename T>
  void StacksEqual(s21::stack<T> &s, std::stack<T> &ss) {
    EXPECT_EQ(s.empty(), ss.empty());
    EXPECT_EQ(s.size(), ss.size());
    while (!ss.empty()) {
      EXPECT_EQ(s.top(), ss.top());
      s.pop();
      ss.pop();
    }
  }

  std::vector<double> v1 = {1.1, 1.2, 1.3, 1.4};
  std::vector<double> v2 = {2.1, 2.2, 2.3};
  std::vector<double> v3 = {3.1, 3.2, 3.3};

 public:
  class Tmp {
   public:
    Tmp() {}
    Tmp(const Tmp &other) {
      (void)other;
      ++count;
      if (count == 3) {
        throw std::bad_alloc();
      }
    }
    ~Tmp() {}

   public:
    static int count;
  };
};

int StackTest::Tmp::count = 0;

TEST_F(StackTest, DefaultCtor) {
  s21::stack<std::vector<int>> st;
  EXPECT_TRUE(st.empty());
  EXPECT_EQ(st.size(), 0);

  const s21::stack<std::vector<int>> cst;
  EXPECT_TRUE(cst.empty());
  EXPECT_EQ(cst.size(), 0);
}

TEST_F(StackTest, InitializerCtor) {
  s21::stack<int> st = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_FALSE(st.empty());
  EXPECT_EQ(st.size(), 10);

  // compile test with -std=c++23
  // int arr[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  // std::stack<int> stdst(&arr[0], arr + 10);
  // StacksEqual(st, stdst);

  const s21::stack<int> cst = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_FALSE(cst.empty());
  EXPECT_EQ(cst.size(), 10);

  try {
    s21::stack<Tmp> tmpst = {Tmp(), Tmp(), Tmp(), Tmp()};
    EXPECT_TRUE(false);
  } catch (std::exception &e) {
    EXPECT_TRUE(true);
    (void)e;
  }
}

TEST_F(StackTest, CopyCtor) {
  {
    const s21::stack<int> copy;
    s21::stack<int> st(copy);
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0);
  }
  {
    s21::stack<int> copy = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::stack<int> st(copy);
    EXPECT_FALSE(st.empty());
    EXPECT_EQ(st.size(), 10);
    for (int i = 0; i < 10; ++i) {
      EXPECT_EQ(st.top(), copy.top());
      st.pop();
      copy.pop();
    }
  }
}

TEST_F(StackTest, MoveCtor) {
  {
    s21::stack<int> copy;
    s21::stack<int> st(std::move(copy));
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0);
  }
  {
    s21::stack<int> copy = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::stack<int> st(std::move(copy));
    EXPECT_FALSE(st.empty());
    EXPECT_EQ(st.size(), 10);
    EXPECT_TRUE(copy.empty());
    EXPECT_EQ(copy.size(), 0);
  }
}

TEST_F(StackTest, CopyOperatorAssign) {
  {
    s21::stack<int> st;
    s21::stack<int> s = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    st = s;
    EXPECT_EQ(st.empty(), s.empty());
    EXPECT_EQ(st.size(), s.size());
    while (!st.empty()) {
      EXPECT_EQ(st.top(), s.top());
      st.pop();
      s.pop();
    }
  }
  {
    s21::stack<int> st = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::stack<int> s;
    st = s;
    EXPECT_EQ(st.empty(), s.empty());
    EXPECT_EQ(st.size(), s.size());
    while (!st.empty()) {
      EXPECT_EQ(st.top(), s.top());
      st.pop();
      s.pop();
    }
  }
}

TEST_F(StackTest, MoveOperatorAssign) {
  {
    s21::stack<int> st;
    s21::stack<int> s = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::stack<int> copy(s);
    st = std::move(s);
    EXPECT_EQ(st.empty(), copy.empty());
    EXPECT_EQ(st.size(), copy.size());
    while (!st.empty()) {
      EXPECT_EQ(st.top(), copy.top());
      st.pop();
      copy.pop();
    }
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0);
  }
  {
    s21::stack<int> st = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    s21::stack<int> s;
    st = std::move(s);
    EXPECT_TRUE(st.empty());
    EXPECT_EQ(st.size(), 0);
  }
}

TEST_F(StackTest, TopPopPush) {
  s21::stack<int> st;
  std::stack<int> std_st;

  for (int i = 0; i < 10000; ++i) {
    int value = rand();
    st.push(value);
    std_st.push(value);
  }
  // top() and pop() are called in StacksEqual()
  StacksEqual(st, std_st);
}

TEST_F(StackTest, ConstTop) {
  const s21::stack<int> st = {11, 12, 14};

  EXPECT_EQ(st.top(), 14);
}

TEST_F(StackTest, Swap) {
  s21::stack<int> st1;
  std::stack<int> std_st1;
  s21::stack<int> st2;
  std::stack<int> std_st2;

  for (int i = 0; i < 10000; ++i) {
    int value = rand();
    st1.push(value);
    std_st1.push(value);
  }
  for (int i = 0; i < 2000; ++i) {
    int value = rand();
    st2.push(value);
    std_st2.push(value);
  }

  st1.swap(st2);
  std_st1.swap(std_st2);

  // top() and pop() are called in StacksEqual()
  StacksEqual(st1, std_st1);
  StacksEqual(st2, std_st2);
}

TEST_F(StackTest, TopPopPushVector) {
  s21::stack<std::vector<double>> st;
  std::stack<std::vector<double>> std_st;

  st.push(v1);
  st.push(v2);
  st.push(v3);
  std_st.push(v1);
  std_st.push(v2);
  std_st.push(v3);

  // top() and pop() are called in StacksEqual()
  StacksEqual(st, std_st);
}
