#include "s21_multiset.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdlib>
#include <set>
#include <string>

class MultisetTest : public ::testing::Test {
 public:
  void SetUp(void) override {
    srand(42);

    int multiset_size = 100000;
    for (int i = 0; i < multiset_size; ++i) {
      int key = rand() % 100000;
      mss21.insert(std::to_string(key));
      msstd.insert(std::to_string(key));
    }
  }

  template <typename Key>
  bool MultisetEqual(const s21::multiset<Key>& lhs,
                     const s21::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           lhs.verify() == 0 && rhs.verify() == 0 &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool MultisetEqual(const s21::multiset<Key>& lhs,
                     const std::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           lhs.verify() == 0 &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key>
  bool MultisetEqual(const std::multiset<Key>& lhs,
                     const s21::multiset<Key>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           rhs.verify() == 0 &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }

  s21::multiset<std::string> mss21;
  std::multiset<std::string> msstd;
};

TEST_F(MultisetTest, DefaultCtor) {
  {
    s21::multiset<int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
  }
  {
    const s21::multiset<int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
  }
  {
    s21::multiset<std::string> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
  }
  const s21::multiset<std::string> m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST_F(MultisetTest, InitializerCtor) {
  {
    s21::multiset<std::string> ms21 = {"123", "abc", "Abc"};
    std::multiset<std::string> mstd = {"123", "abc", "Abc"};

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
  }
  {
    s21::multiset<std::string> ms21 = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    std::multiset<std::string> mstd = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
  }
}

TEST_F(MultisetTest, CopyCtor) {
  {
    s21::multiset<std::string> ms21;
    s21::multiset<std::string> ms21_copy = ms21;
    std::multiset<std::string> mstd;
    std::multiset<std::string> mstd_copy = mstd;

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    const s21::multiset<std::string> ms21;
    const s21::multiset<std::string> ms21_copy = ms21;
    const std::multiset<std::string> mstd;
    const std::multiset<std::string> mstd_copy = mstd;

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    s21::multiset<std::string> ms21 = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    s21::multiset<std::string> ms21_copy = ms21;
    std::multiset<std::string> mstd = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    std::multiset<std::string> mstd_copy = mstd;

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    const s21::multiset<std::string> ms21 = {"123", "abc", "Abc", "123",
                                             "q",   "432", "abc", "abc"};
    const s21::multiset<std::string> ms21_copy = ms21;
    const std::multiset<std::string> mstd = {"123", "abc", "Abc", "123",
                                             "q",   "432", "abc", "abc"};
    const std::multiset<std::string> mstd_copy = mstd;

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    const s21::multiset<std::string> ms21_copy = mss21;
    const std::multiset<std::string> mstd_copy = msstd;

    EXPECT_TRUE(MultisetEqual(mss21, msstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
}

TEST_F(MultisetTest, MoveCtor) {
  {
    s21::multiset<std::string> ms21;
    s21::multiset<std::string> ms21_copy = std::move(ms21);
    std::multiset<std::string> mstd;
    std::multiset<std::string> mstd_copy = std::move(mstd);

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    const s21::multiset<std::string> ms21;
    const s21::multiset<std::string> ms21_copy = std::move(ms21);
    const std::multiset<std::string> mstd;
    const std::multiset<std::string> mstd_copy = std::move(mstd);

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    s21::multiset<std::string> ms21 = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    s21::multiset<std::string> ms21_copy = std::move(ms21);
    std::multiset<std::string> mstd = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    std::multiset<std::string> mstd_copy = std::move(mstd);

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    const s21::multiset<std::string> ms21 = {"123", "abc", "Abc", "123",
                                             "q",   "432", "abc", "abc"};
    const s21::multiset<std::string> ms21_copy = std::move(ms21);
    const std::multiset<std::string> mstd = {"123", "abc", "Abc", "123",
                                             "q",   "432", "abc", "abc"};
    const std::multiset<std::string> mstd_copy = std::move(mstd);

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    const s21::multiset<std::string> ms21_copy = std::move(mss21);
    const std::multiset<std::string> mstd_copy = std::move(msstd);

    EXPECT_TRUE(MultisetEqual(mss21, msstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
}

TEST_F(MultisetTest, CopyOperatorAssign) {
  {
    s21::multiset<std::string> ms21;
    s21::multiset<std::string> ms21_copy;
    std::multiset<std::string> mstd;
    std::multiset<std::string> mstd_copy;

    ms21_copy = ms21;
    mstd_copy = mstd;

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    s21::multiset<std::string> ms21 = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    s21::multiset<std::string> ms21_copy = {"rt"};
    std::multiset<std::string> mstd = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    std::multiset<std::string> mstd_copy = {"rt"};

    ms21_copy = ms21;
    mstd_copy = mstd;

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    s21::multiset<std::string> ms21_copy = {"123", "456"};
    std::multiset<std::string> mstd_copy = {"123", "456"};

    ms21_copy = mss21;
    mstd_copy = msstd;

    EXPECT_TRUE(MultisetEqual(mss21, msstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
}

TEST_F(MultisetTest, MoveOperatorAssign) {
  {
    s21::multiset<std::string> ms21;
    s21::multiset<std::string> ms21_copy;
    std::multiset<std::string> mstd;
    std::multiset<std::string> mstd_copy;

    ms21_copy = std::move(ms21);
    mstd_copy = std::move(mstd);

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    s21::multiset<std::string> ms21 = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    s21::multiset<std::string> ms21_copy = {"rt"};
    std::multiset<std::string> mstd = {"123", "abc", "Abc", "123",
                                       "q",   "432", "abc", "abc"};
    std::multiset<std::string> mstd_copy = {"rt"};

    ms21_copy = std::move(ms21);
    // mstd_copy = std::move(mstd);
    mstd_copy.swap(mstd);

    EXPECT_TRUE(MultisetEqual(ms21, mstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
  {
    s21::multiset<std::string> ms21_copy = {"123", "456"};
    std::multiset<std::string> mstd_copy = {"123", "456"};

    ms21_copy = std::move(mss21);
    // mstd_copy = std::move(msstd);
    mstd_copy.swap(msstd);

    EXPECT_TRUE(MultisetEqual(mss21, msstd));
    EXPECT_TRUE(MultisetEqual(ms21_copy, mstd_copy));
  }
}

TEST_F(MultisetTest, Iterator) {
  {
    s21::multiset<std::string>::iterator s21_it = mss21.begin();
    std::multiset<std::string>::iterator std_it = msstd.begin();

    ++s21_it;
    ++s21_it;
    ++std_it;
    ++std_it;
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it, *std_it);
    --s21_it;
    --std_it;
    EXPECT_EQ(s21_it++->size(), std_it++->size());

    auto s21_tmp = s21_it++;
    auto std_tmp = std_it++;
    EXPECT_FALSE(s21_tmp == s21_it);
    EXPECT_FALSE(std_tmp == std_it);
    EXPECT_TRUE(s21_tmp != s21_it);
    EXPECT_TRUE(std_tmp != std_it);
    ++s21_tmp;
    ++std_tmp;
    EXPECT_TRUE(s21_tmp == s21_it);
    EXPECT_TRUE(std_tmp == std_it);
    EXPECT_FALSE(s21_tmp != s21_it);
    EXPECT_FALSE(std_tmp != std_it);
  }
  {
    s21::multiset<std::string>::iterator s21_it = mss21.end();
    std::multiset<std::string>::iterator std_it = msstd.end();
    --s21_it;
    --s21_it;
    --std_it;
    --std_it;
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it, *std_it);
    --s21_it;
    --std_it;
    EXPECT_EQ(s21_it--->size(), std_it--->size());
  }
}

TEST_F(MultisetTest, ConstIterator) {
  {
    s21::multiset<std::string>::const_iterator s21_it = mss21.cbegin();
    std::multiset<std::string>::const_iterator std_it = msstd.cbegin();

    ++s21_it;
    ++s21_it;
    ++std_it;
    ++std_it;
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it, *std_it);
    --s21_it;
    --std_it;
    EXPECT_EQ(s21_it++->size(), std_it++->size());

    auto s21_tmp = s21_it++;
    auto std_tmp = std_it++;
    EXPECT_FALSE(s21_tmp == s21_it);
    EXPECT_FALSE(std_tmp == std_it);
    EXPECT_TRUE(s21_tmp != s21_it);
    EXPECT_TRUE(std_tmp != std_it);
    ++s21_tmp;
    ++std_tmp;
    EXPECT_TRUE(s21_tmp == s21_it);
    EXPECT_TRUE(std_tmp == std_it);
    EXPECT_FALSE(s21_tmp != s21_it);
    EXPECT_FALSE(std_tmp != std_it);
  }
  {
    s21::multiset<std::string>::const_iterator s21_it = mss21.cend();
    std::multiset<std::string>::const_iterator std_it = msstd.cend();
    --s21_it;
    --s21_it;
    --std_it;
    --std_it;
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*--s21_it, *--std_it);
    EXPECT_EQ(*s21_it--, *std_it--);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*s21_it++, *std_it++);
    EXPECT_EQ(*s21_it, *std_it);
    EXPECT_EQ(*++s21_it, *++std_it);
    EXPECT_EQ(*s21_it, *std_it);
    --s21_it;
    --std_it;
    EXPECT_EQ(s21_it--->size(), std_it--->size());
  }
}

TEST_F(MultisetTest, Capacity) {
  {
    s21::multiset<std::vector<double>> s21_s;
    std::multiset<std::vector<double>> std_s;

    EXPECT_EQ(s21_s.empty(), std_s.empty());
    EXPECT_EQ(s21_s.size(), std_s.size());
    EXPECT_EQ(s21_s.max_size(), std_s.max_size());
  }
  {
    s21::multiset<std::vector<double>> s21_s{std::vector<double>{1.0, 2.0}};
    std::multiset<std::vector<double>> std_s{std::vector<double>{1.0, 2.0}};

    EXPECT_EQ(s21_s.empty(), std_s.empty());
    EXPECT_EQ(s21_s.size(), std_s.size());
    EXPECT_EQ(s21_s.max_size(), std_s.max_size());
  }
  {
    s21::multiset<std::vector<double>> s21_s{std::vector<double>{1.0, 2.0},
                                             std::vector<double>{10.0, 20.0},
                                             std::vector<double>{100.0, 200.0}};
    std::multiset<std::vector<double>> std_s{std::vector<double>{1.0, 2.0},
                                             std::vector<double>{10.0, 20.0},
                                             std::vector<double>{100.0, 200.0}};

    EXPECT_EQ(s21_s.empty(), std_s.empty());
    EXPECT_EQ(s21_s.size(), std_s.size());
    EXPECT_EQ(s21_s.max_size(), std_s.max_size());
  }
  {
    EXPECT_EQ(mss21.empty(), msstd.empty());
    EXPECT_EQ(mss21.size(), msstd.size());
    EXPECT_EQ(mss21.max_size(), msstd.max_size());
  }
  {
    const s21::multiset<std::string> cmss21 = mss21;
    const std::multiset<std::string> cmsstd = msstd;

    EXPECT_EQ(cmss21.empty(), cmsstd.empty());
    EXPECT_EQ(cmss21.size(), cmsstd.size());
    EXPECT_EQ(cmss21.max_size(), cmsstd.max_size());
  }
}

TEST_F(MultisetTest, Clear) {
  {
    s21::multiset<std::string> s_s21;
    std::multiset<std::string> s_std;

    s_s21.clear();
    s_std.clear();

    EXPECT_TRUE(MultisetEqual(s_s21, s_std));
  }
  {
    s21::multiset<std::string> s_s21 = mss21;
    std::multiset<std::string> s_std = msstd;

    s_s21.clear();
    s_std.clear();

    EXPECT_TRUE(MultisetEqual(s_s21, s_std));
  }
  {
    s21::multiset<std::string> s_s21;
    std::multiset<std::string> s_std;

    for (int i = 0; i < 10000; ++i) {
      s_s21.insert(std::to_string(i));
      s_std.insert(std::to_string(i));
    }

    s_s21.clear();
    s_std.clear();

    EXPECT_TRUE(MultisetEqual(s_s21, s_std));
  }
}

TEST_F(MultisetTest, Insert1) {
  s21::multiset<std::string> ms21;
  std::multiset<std::string> mstd;

  for (int i = 0; i < 1000; ++i) {
    auto it_s21 = ms21.insert("123");
    auto it_std = mstd.insert("123");
    EXPECT_EQ(*it_s21, *it_std);
  }

  EXPECT_TRUE(MultisetEqual(mstd, ms21));
}

TEST_F(MultisetTest, Insert2) {
  s21::multiset<std::string> ms21;
  std::multiset<std::string> mstd;

  for (int i = 0; i < 1000; ++i) {
    auto it_s21 = ms21.insert(std::to_string(i % 2));
    auto it_std = mstd.insert(std::to_string(i % 2));
    EXPECT_EQ(*it_s21, *it_std);
  }

  EXPECT_TRUE(MultisetEqual(mstd, ms21));
}

TEST_F(MultisetTest, Insert3) {
  s21::multiset<std::string> ms21;
  std::multiset<std::string> mstd;

  for (int i = 0; i < 1000; ++i) {
    auto it_s21 = ms21.insert(std::to_string(i % 2));
    auto it_std = mstd.insert(std::to_string(i % 2));
    EXPECT_EQ(*it_s21, *it_std);
  }
  for (int i = 0; i < 1000; ++i) {
    auto it_s21 = ms21.insert(std::to_string(i % 3));
    auto it_std = mstd.insert(std::to_string(i % 3));
    EXPECT_EQ(*it_s21, *it_std);
  }

  EXPECT_TRUE(MultisetEqual(mstd, ms21));
}

TEST_F(MultisetTest, Insert4) {
  s21::multiset<std::string> ms21;
  std::multiset<std::string> mstd;

  for (int i = 0; i < 10000; ++i) {
    auto it_s21 = ms21.insert(std::to_string(i % 100));
    auto it_std = mstd.insert(std::to_string(i % 100));
    EXPECT_EQ(*it_s21, *it_std);
  }

  EXPECT_TRUE(MultisetEqual(mstd, ms21));
}

TEST_F(MultisetTest, Erase) {
  s21::multiset<std::string> ms21;
  std::multiset<std::string> mstd;

  for (int i = 0; i < 10000; ++i) {
    auto it_s21 = ms21.insert(std::to_string(i % 100));
    auto it_std = mstd.insert(std::to_string(i % 100));
    EXPECT_EQ(*it_s21, *it_std);
  }

  EXPECT_TRUE(MultisetEqual(mstd, ms21));

  for (int i = 0; i < 5000; ++i) {
    auto it_s21 = ms21.find(std::to_string(i % 150));
    auto it_std = mstd.find(std::to_string(i % 150));

    if (it_std != mstd.end()) {
      EXPECT_NE(it_s21, ms21.end());
      ms21.erase(it_s21);
      mstd.erase(it_std);
    } else {
      EXPECT_EQ(it_s21, ms21.end());
    }
  }

  EXPECT_TRUE(MultisetEqual(mstd, ms21));

  for (int i = 0; i < 10000; ++i) {
    auto it_s21 = ms21.insert(std::to_string(i % 200));
    auto it_std = mstd.insert(std::to_string(i % 200));
    EXPECT_EQ(*it_s21, *it_std);
  }

  EXPECT_TRUE(MultisetEqual(mstd, ms21));

  for (int i = 0; i < 5000; ++i) {
    auto it_s21 = ms21.find(std::to_string(i % 150));
    auto it_std = mstd.find(std::to_string(i % 150));

    if (it_std != mstd.end()) {
      EXPECT_NE(it_s21, ms21.end());
      ms21.erase(it_s21);
      mstd.erase(it_std);
    } else {
      EXPECT_EQ(it_s21, ms21.end());
    }
  }

  EXPECT_TRUE(MultisetEqual(mstd, ms21));
}

TEST_F(MultisetTest, Swap) {
  s21::multiset<std::string> ms21;
  std::multiset<std::string> mstd;

  for (int i = 0; i < 10000; ++i) {
    ms21.insert(std::to_string(i % 100));
    mstd.insert(std::to_string(i % 100));
  }

  ms21.swap(mss21);
  mstd.swap(msstd);

  EXPECT_TRUE(MultisetEqual(mstd, ms21));
  EXPECT_TRUE(MultisetEqual(msstd, mss21));
}

TEST_F(MultisetTest, Merge) {
  s21::multiset<std::string> ms21;
  std::multiset<std::string> mstd;

  for (int i = 0; i < 10000; ++i) {
    ms21.insert(std::to_string(i % 100));
    mstd.insert(std::to_string(i % 100));
  }

  s21::multiset<std::string> source_s21;
  std::multiset<std::string> source_std;

  for (int i = 0; i < 10000; ++i) {
    source_s21.insert(std::to_string(i % 200));
    source_std.insert(std::to_string(i % 200));
  }

  ms21.merge(source_s21);
  mstd.merge(source_std);

  EXPECT_TRUE(MultisetEqual(mstd, ms21));
  EXPECT_TRUE(MultisetEqual(source_std, source_s21));
}

TEST_F(MultisetTest, Find) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 100000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 50000;
    auto it1 = ms_s21.find(key);
    auto it2 = ms_std.find(key);
    if (it2 != ms_std.end()) {
      EXPECT_EQ(*it1, *it2);
    } else {
      EXPECT_EQ(it1, ms_s21.end());
    }
  }
}

TEST_F(MultisetTest, ConstFind) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 10000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  const s21::multiset<int> cms_s21 = std::move(ms_s21);
  const std::multiset<int> cms_std = std::move(ms_std);

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 50000;
    auto it1 = cms_s21.find(key);
    auto it2 = cms_std.find(key);
    if (it2 != cms_std.end()) {
      EXPECT_EQ(*it1, *it2);
    } else {
      EXPECT_EQ(it1, cms_s21.end());
    }
  }
}

TEST_F(MultisetTest, Contains) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 100000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  const s21::multiset<int> cms_s21 = std::move(ms_s21);
  const std::multiset<int> cms_std = std::move(ms_std);

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 500000;
    bool res_s21 = cms_s21.contains(key);
    auto it = cms_std.find(key);
    bool res_std = (it != cms_std.end());
    EXPECT_EQ(res_s21, res_std);
  }
}

TEST_F(MultisetTest, LowerBound) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 100000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  for (int i = 0; i < 10000; ++i) {
    int key = rand() % 500000;
    auto it1 = ms_s21.lower_bound(key);
    auto it2 = ms_std.lower_bound(key);
    if (it2 != ms_std.end()) {
      EXPECT_EQ(*it1, *it2);
    } else {
      EXPECT_EQ(it1, ms_s21.end());
    }
  }

  EXPECT_EQ(ms_s21.lower_bound(9999999), ms_s21.end());
  EXPECT_EQ(ms_std.lower_bound(9999999), ms_std.end());
}

TEST_F(MultisetTest, ConstLowerBound) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 10000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  const s21::multiset<int> cms_s21 = std::move(ms_s21);
  const std::multiset<int> cms_std = std::move(ms_std);

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 500000;
    auto it1 = cms_s21.lower_bound(key);
    auto it2 = cms_std.lower_bound(key);
    if (it2 != cms_std.end()) {
      EXPECT_EQ(*it1, *it2);
    } else {
      EXPECT_EQ(it1, cms_s21.end());
    }
  }

  EXPECT_EQ(cms_s21.lower_bound(9999999), cms_s21.end());
  EXPECT_EQ(cms_std.lower_bound(9999999), cms_std.end());
}

TEST_F(MultisetTest, UpperBound) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 100000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  for (int i = 0; i < 10000; ++i) {
    int key = rand() % 500000;
    auto it1 = ms_s21.upper_bound(key);
    auto it2 = ms_std.upper_bound(key);
    if (it2 != ms_std.end()) {
      EXPECT_EQ(*it1, *it2);
    } else {
      EXPECT_EQ(it1, ms_s21.end());
    }
  }

  EXPECT_EQ(ms_s21.upper_bound(9999999), ms_s21.end());
  EXPECT_EQ(ms_std.upper_bound(9999999), ms_std.end());
}

TEST_F(MultisetTest, ConstUpperBound) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 10000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  const s21::multiset<int> cms_s21 = std::move(ms_s21);
  const std::multiset<int> cms_std = std::move(ms_std);

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 500000;
    auto it1 = cms_s21.upper_bound(key);
    auto it2 = cms_std.upper_bound(key);
    if (it2 != cms_std.end()) {
      EXPECT_EQ(*it1, *it2);
    } else {
      EXPECT_EQ(it1, cms_s21.end());
    }
  }

  EXPECT_EQ(cms_s21.upper_bound(9999999), cms_s21.end());
  EXPECT_EQ(cms_std.upper_bound(9999999), cms_std.end());
}

TEST_F(MultisetTest, EqualRange) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 100000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  for (int i = 0; i < 100; ++i) {
    int key = rand() % 5000;
    auto ps21 = ms_s21.equal_range(key);
    auto pstd = ms_std.equal_range(key);
    EXPECT_TRUE(equal(pstd.first, pstd.second, ps21.first));
    EXPECT_TRUE(equal(ps21.first, ps21.second, pstd.first));
  }
}

TEST_F(MultisetTest, ConstEqualRange) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 10000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  const s21::multiset<int> cms_s21 = std::move(ms_s21);
  const std::multiset<int> cms_std = std::move(ms_std);

  for (int i = 0; i < 100; ++i) {
    int key = rand() % 5000;
    auto ps21 = cms_s21.equal_range(key);
    auto pstd = cms_std.equal_range(key);
    EXPECT_TRUE(equal(pstd.first, pstd.second, ps21.first));
    EXPECT_TRUE(equal(ps21.first, ps21.second, pstd.first));
  }
}

TEST_F(MultisetTest, Count) {
  s21::multiset<int> ms_s21;
  std::multiset<int> ms_std;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 10000;
    ms_s21.insert(key);
    ms_std.insert(key);
  }

  const s21::multiset<int> cms_s21 = std::move(ms_s21);
  const std::multiset<int> cms_std = std::move(ms_std);

  for (int i = 0; i < 10000; ++i) {
    int key = rand() % 5000;
    EXPECT_EQ(cms_s21.count(key), cms_std.count(key));
  }

  EXPECT_EQ(cms_s21.count(-100), cms_std.count(-100));
  EXPECT_EQ(cms_s21.count(9999999), cms_std.count(9999999));
}

TEST_F(MultisetTest, InsertMany) {
  {
    s21::multiset<std::string> s = {"1", "2"};

    s.insert_many(std::string("5"), std::string("3"), std::string("3"),
                  std::string("4"));

    std::multiset<std::string> std_s = {"1", "2", "3", "3", "4", "5"};

    EXPECT_TRUE(MultisetEqual(s, std_s));
  }
  {
    s21::multiset<std::string> s = {"1", "2"};

    s.insert_many(std::string("5"));

    std::multiset<std::string> std_s = {"1", "2", "5"};

    EXPECT_TRUE(MultisetEqual(s, std_s));
  }
  {
    s21::multiset<std::string> s = {"1", "2"};

    s.insert_many();

    std::multiset<std::string> std_s = {"1", "2"};

    EXPECT_TRUE(MultisetEqual(s, std_s));
  }
}
