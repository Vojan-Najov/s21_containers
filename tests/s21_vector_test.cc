#include "s21_vector.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class VectorTest : public ::testing::Test {
 public:
  void SetUp(void) override { ErrorClass::count = 0; }

  template <typename T>
  bool VectorEqual(const s21::vector<T> &lhs, const s21::vector<T> &rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           lhs.capacity() == rhs.capacity() &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }

  template <typename T>
  bool VectorEqual(const std::vector<T> &lhs, const s21::vector<T> &rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           lhs.capacity() == rhs.capacity() &&
           std::distance(lhs.begin(), lhs.end()) ==
               std::distance(rhs.begin(), rhs.end()) &&
           std::equal(lhs.begin(), lhs.end(), rhs.begin());
  }
  template <typename T>
  bool VectorEqual(const s21::vector<T> &lhs, const std::vector<T> &rhs) {
    return VectorEqual(rhs, lhs);
  }
  template <typename T>
  void VectorEqual2(const s21::vector<T> &lhs, const std::vector<T> &rhs) {
    EXPECT_TRUE(lhs.empty() == rhs.empty());
    EXPECT_TRUE(lhs.size() == rhs.size());
    EXPECT_TRUE(lhs.capacity() == rhs.capacity());
    EXPECT_EQ(std::distance(lhs.begin(), lhs.end()),
              std::distance(rhs.begin(), rhs.end()));
    EXPECT_TRUE(std::equal(lhs.begin(), lhs.end(), rhs.begin()));
  }

  class ErrorClass {
   public:
    static int count;
    ErrorClass(int num = 0) {
      if (count == 100) {
        throw 1;
      }
      num_ = new int(num);
      ++count;
    }
    ErrorClass(const ErrorClass &other) {
      if (count == 100) {
        throw 1;
      }
      num_ = new int(*other.num_);
      ++count;
    }
    ErrorClass &operator=(const ErrorClass &other) {
      if (count == 100) {
        throw 1;
      }
      if (this != &other) {
        *num_ = *other.num_;
        ++count;
      }
      return *this;
    }
    ~ErrorClass(void) { delete num_; }

   private:
    int *num_;
  };
};

int VectorTest::ErrorClass::count = 0;

TEST_F(VectorTest, DefaultCtor) {
  {
    s21::vector<double> s21_vec;
    std::vector<double> std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
}

TEST_F(VectorTest, ParameterizedCtor) {
  {
    size_t n = 0;
    s21::vector<std::string> s21_vec(n);
    std::vector<std::string> std_vec(n);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    size_t n = 1;
    s21::vector<std::string> s21_vec(n);
    std::vector<std::string> std_vec(n);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    size_t n = 2;
    s21::vector<std::string> s21_vec(n);
    std::vector<std::string> std_vec(n);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    size_t n = 10;
    s21::vector<std::string> s21_vec(n);
    std::vector<std::string> std_vec(n);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    size_t n = 100;
    s21::vector<std::string> s21_vec(n);
    std::vector<std::string> std_vec(n);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    size_t n = 100000;
    s21::vector<std::string> s21_vec(n);
    std::vector<std::string> std_vec(n);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
}

TEST_F(VectorTest, InitializerCtor) {
  {
    s21::vector<int> s21_vec = std::initializer_list<int>{};
    std::vector<int> std_vec = std::initializer_list<int>{};

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789"};
    std::vector<std::string> std_vec = {"123", "456", "789"};

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};
    std::vector<std::string> std_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
}

TEST_F(VectorTest, CopyCtor) {
  {
    s21::vector<int> s21_vec = std::initializer_list<int>{};
    std::vector<int> std_vec = std::initializer_list<int>{};

    s21::vector<int> s21_copy = s21_vec;
    std::vector<int> std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789"};
    std::vector<std::string> std_vec = {"123", "456", "789"};

    s21::vector<std::string> s21_copy = s21_vec;
    std::vector<std::string> std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};
    std::vector<std::string> std_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};

    s21::vector<std::string> s21_copy = s21_vec;
    std::vector<std::string> std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
}

TEST_F(VectorTest, MoveCtor) {
  {
    s21::vector<int> s21_vec = std::initializer_list<int>{};
    std::vector<int> std_vec = std::initializer_list<int>{};

    s21::vector<int> s21_copy = std::move(s21_vec);
    std::vector<int> std_copy = std::move(std_vec);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789"};
    std::vector<std::string> std_vec = {"123", "456", "789"};

    s21::vector<std::string> s21_copy = std::move(s21_vec);
    std::vector<std::string> std_copy = std::move(std_vec);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};
    std::vector<std::string> std_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};

    s21::vector<std::string> s21_copy = std::move(s21_vec);
    std::vector<std::string> std_copy = std::move(std_vec);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
}

TEST_F(VectorTest, CopyOperatorAssign1) {
  {
    s21::vector<int> s21_vec = std::initializer_list<int>{};
    std::vector<int> std_vec = std::initializer_list<int>{};

    s21::vector<int> s21_copy;
    std::vector<int> std_copy;

    s21_copy = s21_vec;
    std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789"};
    std::vector<std::string> std_vec = {"123", "456", "789"};

    s21::vector<std::string> s21_copy = {"1", "2", "3", "4"};
    std::vector<std::string> std_copy = {"1", "2", "3", "4"};

    s21_copy = s21_vec;
    std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};
    std::vector<std::string> std_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};

    s21::vector<std::string> s21_copy = {"1", "2", "3", "4"};
    std::vector<std::string> std_copy = {"1", "2", "3", "4"};

    s21_copy = s21_vec;
    std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
}

TEST_F(VectorTest, CopyOperatorAssign2) {
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;
    s21::vector<std::string> s21_copy;
    std::vector<std::string> std_copy;

    s21_copy.reserve(60);
    std_copy.reserve(60);

    for (int i = 0; i < 100; ++i) {
      int value = rand();
      s21_vec.push_back(std::to_string(value));
      std_vec.push_back(std::to_string(value));
      if (i % 2) {
        s21_copy.push_back(std::to_string(value));
        std_copy.push_back(std::to_string(value));
      }
    }

    EXPECT_TRUE(s21_vec.size() > s21_copy.capacity());

    s21_copy = s21_vec;
    std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;
    s21::vector<std::string> s21_copy;
    std::vector<std::string> std_copy;

    s21_vec.reserve(60);
    std_vec.reserve(60);
    s21_copy.reserve(110);
    std_copy.reserve(110);

    for (int i = 0; i < 100; ++i) {
      int value = rand();
      s21_copy.push_back(std::to_string(value));
      std_copy.push_back(std::to_string(value));
      if (i % 2) {
        s21_vec.push_back(std::to_string(value));
        std_vec.push_back(std::to_string(value));
      }
    }

    EXPECT_TRUE(s21_vec.size() <= s21_copy.capacity());
    EXPECT_TRUE(s21_vec.size() <= s21_copy.size());

    s21_copy = s21_vec;
    std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;
    s21::vector<std::string> s21_copy;
    std::vector<std::string> std_copy;

    s21_vec.reserve(60);
    std_vec.reserve(60);
    s21_copy.reserve(110);
    std_copy.reserve(110);

    for (int i = 0; i < 50; ++i) {
      int value = rand();
      s21_vec.push_back(std::to_string(value));
      std_vec.push_back(std::to_string(value));
      if (i % 2) {
        s21_copy.push_back(std::to_string(value));
        std_copy.push_back(std::to_string(value));
      }
    }

    EXPECT_TRUE(s21_vec.size() <= s21_copy.capacity());
    EXPECT_TRUE(s21_vec.size() > s21_copy.size());

    s21_copy = s21_vec;
    std_copy = std_vec;

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
}

TEST_F(VectorTest, MoveOperatorAssign) {
  {
    s21::vector<int> s21_vec = std::initializer_list<int>{};
    std::vector<int> std_vec = std::initializer_list<int>{};

    s21::vector<int> s21_copy;
    std::vector<int> std_copy;

    s21_copy = std::move(s21_vec);
    std_copy = std::move(std_vec);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789"};
    std::vector<std::string> std_vec = {"123", "456", "789"};

    s21::vector<std::string> s21_copy = {"1", "2", "3", "4"};
    std::vector<std::string> std_copy = {"1", "2", "3", "4"};

    s21_copy = std::move(s21_vec);
    // std_copy = std::move(std_vec);
    std_copy.swap(std_vec);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
  {
    s21::vector<std::string> s21_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};
    std::vector<std::string> std_vec = {"123", "456", "789", "1",
                                        "2",   "3",   "4",   "5"};

    s21::vector<std::string> s21_copy = {"1", "2", "3", "4"};
    std::vector<std::string> std_copy = {"1", "2", "3", "4"};

    s21_copy = std::move(s21_vec);
    // std_copy = std::move(std_vec);
    std_copy.swap(std_vec);

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
    EXPECT_TRUE(VectorEqual(s21_copy, std_copy));
  }
}

TEST_F(VectorTest, At) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
  }

  for (size_t i = 0; i < 10010; ++i) {
    try {
      auto val1 = std_vec.at(i);
      auto val2 = s21_vec.at(i);
      EXPECT_EQ(val1, val2);
    } catch (std::out_of_range &e1) {
      try {
        s21_vec.at(i);
        EXPECT_TRUE(false);
      } catch (std::out_of_range &e2) {
        EXPECT_TRUE(true);
      }
    }
  }
}

TEST_F(VectorTest, ConstAt) {
  s21::vector<std::string> s21_tmp;
  std::vector<std::string> std_tmp;

  for (int i = 0; i < 10000; ++i) {
    int value = rand();
    s21_tmp.push_back(std::to_string(value));
    std_tmp.push_back(std::to_string(value));
  }

  const s21::vector<std::string> s21_vec = s21_tmp;
  const std::vector<std::string> std_vec = std_tmp;

  for (size_t i = 0; i < 10010; ++i) {
    try {
      auto val1 = std_vec.at(i);
      auto val2 = s21_vec.at(i);
      EXPECT_EQ(val1, val2);
    } catch (std::out_of_range &e1) {
      try {
        s21_vec.at(i);
        EXPECT_TRUE(false);
      } catch (std::out_of_range &e2) {
        EXPECT_TRUE(true);
      }
    }
  }
}

TEST_F(VectorTest, OperatorSquareBraces) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
  }

  for (size_t i = 0; i < 10000; ++i) {
    auto val1 = std_vec[i];
    auto val2 = s21_vec[i];
    EXPECT_EQ(val1, val2);
  }
}

TEST_F(VectorTest, ConstOperatorSquareBraces) {
  s21::vector<std::string> s21_tmp;
  std::vector<std::string> std_tmp;

  for (int i = 0; i < 10000; ++i) {
    int value = rand();
    s21_tmp.push_back(std::to_string(value));
    std_tmp.push_back(std::to_string(value));
  }

  const s21::vector<std::string> s21_vec = s21_tmp;
  const std::vector<std::string> std_vec = std_tmp;

  for (size_t i = 0; i < 10000; ++i) {
    auto val1 = std_vec[i];
    auto val2 = s21_vec[i];
    EXPECT_EQ(val1, val2);
  }
}

TEST_F(VectorTest, Front) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
  }

  EXPECT_EQ(s21_vec.front(), std_vec.front());
}

TEST_F(VectorTest, ConstFront) {
  s21::vector<std::string> s21_tmp;
  std::vector<std::string> std_tmp;

  for (int i = 0; i < 10; ++i) {
    int value = rand();
    s21_tmp.push_back(std::to_string(value));
    std_tmp.push_back(std::to_string(value));
  }

  const s21::vector<std::string> s21_vec = s21_tmp;
  const std::vector<std::string> std_vec = std_tmp;

  EXPECT_EQ(s21_vec.front(), std_vec.front());
}

TEST_F(VectorTest, Back) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
  }

  EXPECT_EQ(s21_vec.back(), std_vec.back());
}

TEST_F(VectorTest, ConstBack) {
  s21::vector<std::string> s21_tmp;
  std::vector<std::string> std_tmp;

  for (int i = 0; i < 10; ++i) {
    int value = rand();
    s21_tmp.push_back(std::to_string(value));
    std_tmp.push_back(std::to_string(value));
  }

  const s21::vector<std::string> s21_vec = s21_tmp;
  const std::vector<std::string> std_vec = std_tmp;

  EXPECT_EQ(s21_vec.back(), std_vec.back());
}

TEST_F(VectorTest, Data) {
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    EXPECT_EQ(s21_vec.data(), std_vec.data());
  }
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    for (int i = 0; i < 10000; ++i) {
      int value = rand();
      s21_vec.push_back(std::to_string(value));
      std_vec.push_back(std::to_string(value));
    }

    EXPECT_EQ(*s21_vec.data(), *std_vec.data());
  }
}

TEST_F(VectorTest, ConstData) {
  {
    const s21::vector<std::string> s21_vec;
    const std::vector<std::string> std_vec;

    EXPECT_EQ(s21_vec.data(), std_vec.data());
  }
  {
    s21::vector<std::string> s21_tmp;
    std::vector<std::string> std_tmp;

    for (int i = 0; i < 10; ++i) {
      int value = rand();
      s21_tmp.push_back(std::to_string(value));
      std_tmp.push_back(std::to_string(value));
    }

    const s21::vector<std::string> s21_vec = s21_tmp;
    const std::vector<std::string> std_vec = std_tmp;

    EXPECT_EQ(*s21_vec.data(), *std_vec.data());
  }
}

TEST_F(VectorTest, Iterator) {
  s21::vector<std::string> s21_tmp;
  std::vector<std::string> std_tmp;

  for (int i = 0; i < 100; ++i) {
    int value = rand();
    s21_tmp.push_back(std::to_string(value));
    std_tmp.push_back(std::to_string(value));
  }

  auto s21_it = s21_tmp.begin();
  auto std_it = std_tmp.begin();

  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(*s21_it++, *std_it++);
  EXPECT_EQ(*++s21_it, *++std_it);
  EXPECT_EQ(*++s21_it, *++std_it);
  EXPECT_EQ(*s21_it--, *std_it--);
  EXPECT_EQ(*--s21_it, *--std_it);
  s21_it += 2;
  std_it += 2;
  EXPECT_EQ(*s21_it, *std_it);
  s21_it -= 3;
  std_it -= 3;
  EXPECT_EQ(*s21_it, *std_it);
  *s21_it = 19;
  *std_it = 19;
  EXPECT_EQ(*s21_it, *std_it);

  s21_it = s21_tmp.end();
  std_it = std_tmp.end();

  EXPECT_EQ(*--s21_it, *--std_it);
  EXPECT_EQ(*s21_it--, *std_it--);
  EXPECT_EQ(*s21_it, *std_it);
  s21_it -= 3;
  std_it -= 3;
  EXPECT_EQ(*s21_it, *std_it);
  s21_it += 2;
  std_it += 2;
  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(*--s21_it, *--std_it);
  EXPECT_EQ(*++s21_it, *++std_it);
  EXPECT_EQ(*s21_it++, *std_it++);
}

TEST_F(VectorTest, ConstIterator) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 100; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
  }

  const s21::vector<std::string> s21_tmp = s21_vec;
  const std::vector<std::string> std_tmp = std_vec;

  auto s21_it = s21_tmp.begin();
  auto std_it = std_tmp.begin();

  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(*s21_it++, *std_it++);
  EXPECT_EQ(*++s21_it, *++std_it);
  EXPECT_EQ(*++s21_it, *++std_it);
  EXPECT_EQ(*s21_it--, *std_it--);
  EXPECT_EQ(*--s21_it, *--std_it);
  s21_it += 2;
  std_it += 2;
  EXPECT_EQ(*s21_it, *std_it);
  s21_it -= 3;
  std_it -= 3;
  EXPECT_EQ(*s21_it, *std_it);

  s21_it = s21_tmp.end();
  std_it = std_tmp.end();

  EXPECT_EQ(*--s21_it, *--std_it);
  EXPECT_EQ(*s21_it--, *std_it--);
  EXPECT_EQ(*s21_it, *std_it);
  s21_it -= 3;
  std_it -= 3;
  EXPECT_EQ(*s21_it, *std_it);
  s21_it += 2;
  std_it += 2;
  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(*--s21_it, *--std_it);
  EXPECT_EQ(*++s21_it, *++std_it);
  EXPECT_EQ(*s21_it++, *std_it++);
}

TEST_F(VectorTest, Capacity) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  EXPECT_EQ(s21_vec.max_size(), std_vec.max_size());

  EXPECT_EQ(s21_vec.empty(), std_vec.empty());
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  for (int i = 0; i < 100; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
    EXPECT_EQ(s21_vec.empty(), std_vec.empty());
    EXPECT_EQ(s21_vec.size(), std_vec.size());
    EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
  }

  const s21::vector<std::string> s21_tmp = s21_vec;
  const std::vector<std::string> std_tmp = std_vec;

  EXPECT_EQ(s21_vec.empty(), std_vec.empty());
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST_F(VectorTest, ReserveAndShrinkToFit) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 1000; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
  }

  s21_vec.reserve(1024);
  std_vec.reserve(1024);

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  s21_vec.reserve(500);
  std_vec.reserve(500);

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  s21_vec.reserve(20000);
  std_vec.reserve(20000);

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  for (size_t i = std_vec.size(); i < 20000; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
  }

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  s21_vec.reserve(30000);
  std_vec.reserve(30000);

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());

  s21_vec.shrink_to_fit();
  std_vec.shrink_to_fit();

  for (size_t i = std_vec.size(); i < 20500; ++i) {
    int value = rand();
    s21_vec.push_back(std::to_string(value));
    std_vec.push_back(std::to_string(value));
  }

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  EXPECT_EQ(s21_vec.size(), std_vec.size());
  EXPECT_EQ(s21_vec.capacity(), std_vec.capacity());
}

TEST_F(VectorTest, Clear) {
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    s21_vec.clear();
    std_vec.clear();

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    for (int i = 0; i < 20000; ++i) {
      s21_vec.push_back(std::to_string(i));
      std_vec.push_back(std::to_string(i));
    }

    s21_vec.clear();
    std_vec.clear();

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
}

TEST_F(VectorTest, InsertToBegin) {
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    s21_vec.reserve(100);
    std_vec.reserve(100);

    for (int i = 0; i < 110; ++i) {
      auto s21_it = s21_vec.insert(s21_vec.begin(), std::to_string(i));
      auto std_it = std_vec.insert(std_vec.begin(), std::to_string(i));

      EXPECT_EQ(*s21_it, *std_it);
    }
    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    for (int i = 0; i < 10000; ++i) {
      auto s21_it = s21_vec.insert(s21_vec.begin(), std::to_string(i));
      auto std_it = std_vec.insert(std_vec.begin(), std::to_string(i));

      EXPECT_EQ(*s21_it, *std_it);
    }

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
}

TEST_F(VectorTest, InsertToEnd) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    auto s21_it = s21_vec.insert(s21_vec.end(), std::to_string(i));
    auto std_it = std_vec.insert(std_vec.end(), std::to_string(i));

    EXPECT_EQ(*s21_it, *std_it);
  }

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
}

TEST_F(VectorTest, InsertToMidle) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    auto s21_mid = s21_vec.begin() + (s21_vec.size() / 2);
    auto std_mid = std_vec.begin() + (std_vec.size() / 2);
    auto s21_it = s21_vec.insert(s21_mid, std::to_string(i));
    auto std_it = std_vec.insert(std_mid, std::to_string(i));

    EXPECT_EQ(*s21_it, *std_it);
  }

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
}

TEST_F(VectorTest, EraseFromBegin) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    s21_vec.insert(s21_vec.begin(), std::to_string(i));
    std_vec.insert(std_vec.begin(), std::to_string(i));
  }

  for (int i = 0; i < 5000; ++i) {
    s21_vec.erase(s21_vec.begin());
    std_vec.erase(std_vec.begin());
  }

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
}

TEST_F(VectorTest, EraseFromEnd) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    s21_vec.insert(s21_vec.end(), std::to_string(i));
    std_vec.insert(std_vec.end(), std::to_string(i));
  }

  for (int i = 0; i < 5000; ++i) {
    s21_vec.erase(s21_vec.end() - 1);
    std_vec.erase(std_vec.end() - 1);
  }

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
}

TEST_F(VectorTest, EraseFromMidle) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 10000; ++i) {
    auto s21_mid = s21_vec.begin() + (s21_vec.size() / 2);
    auto std_mid = std_vec.begin() + (std_vec.size() / 2);
    s21_vec.insert(s21_mid, std::to_string(i));
    std_vec.insert(std_mid, std::to_string(i));
  }

  for (int i = 0; i < 5000; ++i) {
    auto s21_mid = s21_vec.begin() + (s21_vec.size() / 2);
    auto std_mid = std_vec.begin() + (std_vec.size() / 2);
    s21_vec.erase(s21_mid);
    std_vec.erase(std_mid);
  }

  EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
}

TEST_F(VectorTest, PushBack) {
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    s21_vec.push_back("1");
    std_vec.push_back("1");

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));

    s21_vec.push_back("2");
    s21_vec.push_back("3");
    std_vec.push_back("2");
    std_vec.push_back("3");

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));

    for (int i = 0; i < 100000; ++i) {
      int value = rand();
      s21_vec.push_back(std::to_string(value));
      std_vec.push_back(std::to_string(value));
    }

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
  {
    s21::vector<std::string> s21_vec;
    std::vector<std::string> std_vec;

    s21_vec.reserve(100);
    std_vec.reserve(100);

    for (int i = 0; i < 200; ++i) {
      int value = rand();
      s21_vec.push_back(std::to_string(value));
      std_vec.push_back(std::to_string(value));
    }

    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
}

TEST_F(VectorTest, PopBack) {
  s21::vector<std::string> s21_vec;
  std::vector<std::string> std_vec;

  for (int i = 0; i < 1000; ++i) {
    s21_vec.push_back(std::to_string(i));
    std_vec.push_back(std::to_string(i));
  }

  for (int i = 0; i < 1000; ++i) {
    s21_vec.pop_back();
    std_vec.pop_back();
    EXPECT_TRUE(VectorEqual(s21_vec, std_vec));
  }
}

TEST_F(VectorTest, Swap) {
  {
    s21::vector<std::string> s21_vec1;
    std::vector<std::string> std_vec1;
    s21::vector<std::string> s21_vec2;
    std::vector<std::string> std_vec2;

    s21_vec1.swap(s21_vec2);
    std_vec1.swap(std_vec2);

    EXPECT_TRUE(VectorEqual(s21_vec1, std_vec1));
    EXPECT_TRUE(VectorEqual(s21_vec2, std_vec2));
  }
  {
    s21::vector<std::string> s21_vec1;
    std::vector<std::string> std_vec1;
    s21::vector<std::string> s21_vec2;
    std::vector<std::string> std_vec2;

    for (int i = 0; i < 1000; ++i) {
      s21_vec1.push_back(std::to_string(i));
      std_vec1.push_back(std::to_string(i));
    }

    s21_vec1.swap(s21_vec2);
    std_vec1.swap(std_vec2);

    EXPECT_TRUE(VectorEqual(s21_vec1, std_vec1));
    EXPECT_TRUE(VectorEqual(s21_vec2, std_vec2));
  }
  {
    s21::vector<std::string> s21_vec1;
    std::vector<std::string> std_vec1;
    s21::vector<std::string> s21_vec2;
    std::vector<std::string> std_vec2;

    for (int i = 0; i < 1000; ++i) {
      s21_vec2.push_back(std::to_string(i));
      std_vec2.push_back(std::to_string(i));
    }

    s21_vec1.swap(s21_vec2);
    std_vec1.swap(std_vec2);

    EXPECT_TRUE(VectorEqual(s21_vec1, std_vec1));
    EXPECT_TRUE(VectorEqual(s21_vec2, std_vec2));
  }
  {
    s21::vector<std::string> s21_vec1;
    std::vector<std::string> std_vec1;
    s21::vector<std::string> s21_vec2;
    std::vector<std::string> std_vec2;

    for (int i = 0; i < 1000; ++i) {
      s21_vec2.push_back(std::to_string(i));
      std_vec2.push_back(std::to_string(i));
    }
    for (int i = 0; i < 200; ++i) {
      s21_vec2.push_back(std::to_string(i));
      std_vec2.push_back(std::to_string(i));
    }

    s21_vec1.swap(s21_vec2);
    std_vec1.swap(std_vec2);

    EXPECT_TRUE(VectorEqual(s21_vec1, std_vec1));
    EXPECT_TRUE(VectorEqual(s21_vec2, std_vec2));
  }
}

TEST_F(VectorTest, InsertMany) {
  s21::vector<int> v = {1, 2, 3, 7, 8, 5, 6, 2, 4, 5, 6, 7, 8, 9, 1, 6, 7};
  std::vector<int> cv = {4, 5, 6, 8, 8, 8, 3, 4, 5, 6, 7, 8, 9, 2, 6, 1,
                         2, 3, 7, 8, 5, 6, 2, 4, 5, 6, 7, 8, 9, 1, 6, 7};
  auto pos_s21 = v.begin();
  v.insert_many(pos_s21, 4, 5, 6, 8, 8, 8, 3, 4, 5, 6, 7, 8, 9, 2, 6);
  EXPECT_TRUE(std::equal(v.begin(), v.end(), cv.begin()));
}

TEST_F(VectorTest, InsertManyBack) {
  s21::vector<int> v = {1, 2, 3};
  std::vector<int> cv = {1, 2, 3, 4, 5, 6, 7, 8, 9, 4, 5, 6,
                         8, 8, 8, 3, 4, 5, 6, 7, 8, 9, 2, 6};
  v.insert_many_back(4, 5, 6, 7, 8, 9, 4, 5, 6, 8, 8, 8, 3, 4, 5, 6, 7, 8, 9, 2,
                     6);
  EXPECT_TRUE(std::equal(v.begin(), v.end(), cv.begin()));
}

TEST_F(VectorTest, ErrorTest01) {
  try {
    s21::vector<ErrorClass> v(110);
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest02) {
  try {
    s21::vector<ErrorClass> v = {1, 2, 3, 4, 5,  6, 7, 8, 9, 10, 1, 2, 3, 4, 5,
                                 6, 7, 8, 9, 10, 1, 2, 3, 4, 5,  6, 7, 8, 9, 10,
                                 1, 2, 3, 4, 5,  6, 7, 8, 9, 10, 1, 2, 3, 4, 5,
                                 6, 7, 8, 9, 10, 1, 2, 3, 4, 5,  6, 7, 8, 9, 10,
                                 1, 2, 3, 4, 5,  6, 7, 8, 9, 10};
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest03) {
  s21::vector<ErrorClass> v1(60);
  try {
    s21::vector<ErrorClass> v2 = v1;
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest04) {
  s21::vector<ErrorClass> v1(60);
  s21::vector<ErrorClass> v2(10);
  try {
    v2 = v1;
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest05) {
  s21::vector<ErrorClass> v1(40);
  s21::vector<ErrorClass> v2(50);
  try {
    v2 = v1;
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest06) {
  s21::vector<ErrorClass> v1(50);
  s21::vector<ErrorClass> v2(20);
  v2.reserve(100);
  try {
    v2 = v1;
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest07) {
  s21::vector<ErrorClass> v1(60);
  try {
    v1.reserve(100);
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest08) {
  s21::vector<ErrorClass> v1(40);
  v1.reserve(100);
  try {
    v1.shrink_to_fit();
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest09) {
  s21::vector<ErrorClass> v1(40);
  try {
    for (int i = 0; i < 100; ++i) {
      v1.push_back(i);
    }
  } catch (...) {
    EXPECT_TRUE(true);
  }
}

TEST_F(VectorTest, ErrorTest10) {
  s21::vector<ErrorClass> v1(40);
  try {
    for (int i = 0; i < 100; ++i) {
      auto it = v1.begin() + std::distance(v1.begin(), v1.end()) / 2;
      v1.insert(it, i);
    }
  } catch (...) {
    EXPECT_TRUE(true);
  }
}
