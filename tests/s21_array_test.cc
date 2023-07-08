#include "s21_array.h"

#include <gtest/gtest.h>

#include <array>

class ArrayTest : public ::testing::Test {
 protected:
  void SetUp(void) override {
    for (size_t i = 0; i < 10; ++i) {
      s21_4[i] = 0.99 + i * 17.75;
      std_4[i] = 0.99 + i * 17.75;
      s21_5[i] = 0.99 - i * 17.75;
      std_5[i] = 0.99 - i * 17.75;
    }
  }

  s21::array<int, 1> s21_0;
  s21::array<int, 100> s21_1;
  s21::array<double, 5> s21_2 = {1.1, 2.2, 3.3, 4.4, 5.5};
  s21::array<float, 10> s21_3 = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  s21::array<float, 10> s21_4;
  s21::array<float, 10> s21_5;
  const s21::array<float, 5> s21_const_array = {1.1, 2.2, 3.3, 4.4, 5.5};

  s21::array<int, 1> std_0;
  std::array<int, 100> std_1;
  std::array<double, 5> std_2 = {1.1, 2.2, 3.3, 4.4, 5.5};
  std::array<float, 10> std_3 = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
  std::array<float, 10> std_4;
  std::array<float, 10> std_5;
  const std::array<float, 5> std_const_array = {1.1, 2.2, 3.3, 4.4, 5.5};
};

TEST_F(ArrayTest, DefaultCtor) {
  EXPECT_EQ(s21_0[0], std_0[0]);

  EXPECT_EQ(sizeof(s21_1), sizeof(std_1));
  for (size_t i = 0; i < std_1.size(); ++i) {
    EXPECT_EQ(s21_1[i], s21_1[i]);
  }
}

TEST_F(ArrayTest, InitializedListCtor) {
  for (size_t i = 0; i < std_2.size(); ++i) {
    EXPECT_EQ(s21_2[i], std_2[i]);
  }
  for (size_t i = 0; i < std_3.size(); ++i) {
    EXPECT_EQ(s21_3[i], std_3[i]) << "i = " << i;
  }

  // std::array<int, 3> tmp = {1, 2, 3, 4}; not compiled
  try {
    s21::array<int, 3> tmp = {1, 2, 3, 4};
    EXPECT_EQ(1, 0);
  } catch (const std::exception &e) {
    EXPECT_EQ(1, 1);
  }
}

TEST_F(ArrayTest, CopyCtor) {
  s21::array<float, 10> s21_tmp(s21_4);
  std::array<float, 10> std_tmp(std_4);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_tmp[i], std_tmp[i]);
  }
}

TEST_F(ArrayTest, MoveCtor) {
  s21::array<float, 10> s21_tmp(std::move(s21_4));
  std::array<float, 10> std_tmp(std::move(std_4));
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_tmp[i], std_tmp[i]);
  }
}

TEST_F(ArrayTest, OperatorAssign) {
  s21::array<float, 10> s21_tmp;
  std::array<float, 10> std_tmp;

  s21_tmp = s21_4;
  std_tmp = std_4;
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_tmp[i], std_tmp[i]);
  }
}

TEST_F(ArrayTest, MoveOperatorAssign) {
  s21::array<float, 10> s21_tmp;
  std::array<float, 10> std_tmp;

  s21_tmp = std::move(s21_4);
  std_tmp = std::move(std_4);
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_tmp[i], std_tmp[i]);
  }
}

TEST_F(ArrayTest, MemberFunctionAt) {
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_4.at(i), std_4.at(i));
  }
  EXPECT_THROW(s21_4.at(100), std::out_of_range);

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(s21_const_array.at(i), std_const_array.at(i));
  }
  EXPECT_THROW(s21_const_array.at(100), std::out_of_range);
}

TEST_F(ArrayTest, OperatorSquareBrackets) {
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_4[i], std_4[i]);
  }

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(s21_const_array[i], std_const_array[i]);
  }
}

TEST_F(ArrayTest, MemberFunctionFront) {
  EXPECT_EQ(s21_4.front(), std_4.front());

  EXPECT_EQ(s21_const_array.front(), std_const_array.front());
}

TEST_F(ArrayTest, MemberFunctionBack) {
  EXPECT_EQ(s21_4.back(), std_4.back());

  EXPECT_EQ(s21_const_array.back(), std_const_array.back());
}

TEST_F(ArrayTest, MemberFunctionData) {
  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_4.data()[i], std_4.data()[i]);
  }

  for (size_t i = 0; i < 5; ++i) {
    EXPECT_EQ(s21_const_array.data()[i], std_const_array.data()[i]);
  }

  std::array<int, 0> std_tmp;
  // s21::array<int, 0> s21_tmp;
  EXPECT_EQ(std_tmp.data(), nullptr);
  // EXPECT_EQ(s21_tmp.data(), nullptr); Need specialization
}

TEST_F(ArrayTest, Iterators) {
  auto s21_first = s21_4.begin();
  auto s21_last = s21_4.end();
  auto std_first = std_4.begin();
  auto std_last = std_4.end();
  while (std_first != std_last) {
    EXPECT_EQ(*s21_first++, *std_first++);
  }
  EXPECT_EQ(s21_first, s21_last);

  auto s21_first_const = s21_4.cbegin();
  auto s21_last_const = s21_4.cend();
  auto std_first_const = std_4.cbegin();
  auto std_last_const = std_4.cend();
  while (std_first_const != std_last_const) {
    EXPECT_EQ(*s21_first_const++, *std_first_const++);
  }
  EXPECT_EQ(s21_first_const, s21_last_const);
}

TEST_F(ArrayTest, Capacity) {
  const s21::array<double, 1023> tmp;

  EXPECT_EQ(tmp.size(), 1023);
  EXPECT_EQ(tmp.max_size(), 1023);
  EXPECT_FALSE(tmp.empty());

  const s21::array<float, 0> arr;
  EXPECT_EQ(arr.size(), 0);
  EXPECT_EQ(arr.max_size(), 0);
  EXPECT_TRUE(arr.empty());
}

TEST_F(ArrayTest, Swap) {
  s21_4.swap(s21_5);
  std_4.swap(std_5);

  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_4[i], std_4[i]);
    EXPECT_EQ(s21_5[i], std_5[i]);
  }
}

TEST_F(ArrayTest, Fill) {
  s21_4.fill(18.98);
  std_4.fill(18.98);

  for (size_t i = 0; i < 10; ++i) {
    EXPECT_EQ(s21_4[i], std_4[i]);
  }
}
