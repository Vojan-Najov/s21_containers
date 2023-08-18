#include "s21_queue.h"

#include <gtest/gtest.h>

#include <cstdlib>
#include <queue>
#include <vector>

class QueueTest : public ::testing::Test {
 protected:
  void SetUp(void) override { std::srand(1); }

  template <typename T>
  void QueuesEqual(s21::queue<T> s, std::queue<T> ss) {
    EXPECT_EQ(s.empty(), ss.empty());
    EXPECT_EQ(s.size(), ss.size());
    while (!ss.empty()) {
      EXPECT_EQ(s.front(), ss.front());
      EXPECT_EQ(s.back(), ss.back());
      s.pop();
      ss.pop();
    }
  }

  template <typename T>
  void QueuesEqual(s21::queue<T> s, s21::queue<T> ss) {
    EXPECT_EQ(s.empty(), ss.empty());
    EXPECT_EQ(s.size(), ss.size());
    while (!ss.empty()) {
      EXPECT_EQ(s.front(), ss.front());
      EXPECT_EQ(s.back(), ss.back());
      s.pop();
      ss.pop();
    }
  }

  std::vector<double> v1 = {1.1, 1.2, 1.3, 1.4, 1.5};
  std::vector<double> v2 = {2.1, 2.2, 2.3, 2.4};
  std::vector<double> v3 = {3.1, 3.2, 3.3};
};

TEST_F(QueueTest, DeafultCtor) {
  s21::queue<std::vector<int>> q;
  EXPECT_TRUE(q.empty());
  EXPECT_EQ(q.size(), 0);

  const s21::queue<std::vector<int>> cq;
  EXPECT_TRUE(cq.empty());
  EXPECT_EQ(cq.size(), 0);
}

TEST_F(QueueTest, InitializerCtor) {
  s21::queue<int> q = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 10);
  EXPECT_EQ(q.front(), 0);
  EXPECT_EQ(q.back(), 9);

  int value = 0;
  while (!q.empty()) {
    EXPECT_EQ(q.front(), value);
    ++value;
    q.pop();
  }
}

TEST_F(QueueTest, CopyCtor) {
  s21::queue<int> copy = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::queue<int> q(copy);

  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 10);
  EXPECT_EQ(q.front(), 0);
  EXPECT_EQ(q.back(), 9);

  QueuesEqual(q, copy);
}

TEST_F(QueueTest, MoveCtor) {
  s21::queue<int> copy = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::queue<int> q(std::move(copy));

  EXPECT_TRUE(copy.empty());
  EXPECT_EQ(copy.size(), 0);

  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 10);
  EXPECT_EQ(q.front(), 0);
  EXPECT_EQ(q.back(), 9);

  int value = 0;
  while (!q.empty()) {
    EXPECT_EQ(q.front(), value);
    ++value;
    q.pop();
  }
}

TEST_F(QueueTest, CopyOperatorAssign) {
  s21::queue<int> copy = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::queue<int> q = {1, 2, 3};

  q = copy;

  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 10);
  EXPECT_EQ(q.front(), 0);
  EXPECT_EQ(q.back(), 9);

  QueuesEqual(q, copy);
}

TEST_F(QueueTest, MoveOperatorAssign) {
  s21::queue<int> copy = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::queue<int> q = {1, 2, 3};

  q = std::move(copy);

  EXPECT_FALSE(copy.empty());
  EXPECT_EQ(copy.size(), 3);

  EXPECT_FALSE(q.empty());
  EXPECT_EQ(q.size(), 10);
  EXPECT_EQ(q.front(), 0);
  EXPECT_EQ(q.back(), 9);

  int value = 0;
  while (!q.empty()) {
    EXPECT_EQ(q.front(), value);
    ++value;
    q.pop();
  }
}

TEST_F(QueueTest, Capacity) {
  const s21::queue<double> q1;
  const s21::queue<double> q2 = {1, 2, 3, 4, 5};
  s21::queue<double> q3;
  s21::queue<double> q4;

  EXPECT_TRUE(q1.empty());
  EXPECT_FALSE(q2.empty());
  EXPECT_TRUE(q3.empty());
  EXPECT_EQ(q1.size(), 0);
  EXPECT_EQ(q2.size(), 5);
  EXPECT_EQ(q3.size(), 0);

  for (int i = 0; i < 100000; ++i) {
    q4.push(std::rand());
  }

  EXPECT_FALSE(q4.empty());
  EXPECT_EQ(q4.size(), 100000);
}

TEST_F(QueueTest, PushPopFrontBack) {
  s21::queue<int> q;
  std::queue<int> qq;

  for (int i = 0; i < 100000; ++i) {
    int value = std::rand();
    q.push(value);
    qq.push(value);
  }

  // Pop, Front and Back are called in QueuesEqual
  QueuesEqual(q, qq);

  q.front() = 19;
  q.back() = -19;
  qq.front() = 19;
  qq.back() = -19;

  QueuesEqual(q, qq);
}

TEST_F(QueueTest, PushPopFrontBackVector) {
  s21::queue<std::vector<double>> q;
  std::queue<std::vector<double>> qq;

  q.push(v1);
  q.push(v2);
  q.push(v3);
  qq.push(v1);
  qq.push(v2);
  qq.push(v3);

  // Pop, Front and Back are called in QueuesEqual
  QueuesEqual(q, qq);
}

TEST_F(QueueTest, Swap) {
  s21::queue<std::vector<double>> q1;
  s21::queue<std::vector<double>> q2;
  std::queue<std::vector<double>> qq1;
  std::queue<std::vector<double>> qq2;

  q1.push(v1);
  q1.push(v2);
  q1.push(v3);
  q2.push(v3);
  q2.push(v1);
  qq1.push(v1);
  qq1.push(v2);
  qq1.push(v3);
  qq2.push(v3);
  qq2.push(v1);

  q1.swap(q2);
  qq1.swap(qq2);

  // Pop, Front and Back are called in QueuesEqual
  QueuesEqual(q1, qq1);
  QueuesEqual(q2, qq2);
}

TEST_F(QueueTest, InsertManyBack) {
  {
    s21::queue<double> q = {1.0, 2.0};
    q.insert_many_back(3, 4.4, 5.0f, 6L);

    std::queue<double> std_q;
    std_q.push(1.0);
    std_q.push(2.0);
    std_q.push(3.0);
    std_q.push(4.4);
    std_q.push(5.0);
    std_q.push(6.0);

    QueuesEqual(q, std_q);
  }
  {
    s21::queue<double> q = {1.0, 2.0};
    q.insert_many_back(3, 4.4);

    std::queue<double> std_q;
    std_q.push(1.0);
    std_q.push(2.0);
    std_q.push(3.0);
    std_q.push(4.4);

    QueuesEqual(q, std_q);
  }
  {
    s21::queue<double> q = {1.0, 2.0};
    q.insert_many_back(3);

    std::queue<double> std_q;
    std_q.push(1.0);
    std_q.push(2.0);
    std_q.push(3.0);

    QueuesEqual(q, std_q);
  }
  {
    s21::queue<double> q = {1.0, 2.0};
    q.insert_many_back();

    std::queue<double> std_q;
    std_q.push(1.0);
    std_q.push(2.0);

    QueuesEqual(q, std_q);
  }
}
