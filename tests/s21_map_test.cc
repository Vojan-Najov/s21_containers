#include "s21_map.h"

#include <gtest/gtest.h>

#include <algorithm>
#include <cstdlib>
#include <map>
#include <string>

class MapTest : public ::testing::Test {
 public:
  void SetUp(void) override {
    std::srand(42);

    int map_size = 1000;
    for (int i = 0; i < map_size; ++i) {
      int key = rand();
      std::string value = std::to_string(key + i);
      ms21.insert(std::make_pair(key, value));
      mstd.insert(std::make_pair(key, value));
    }

    mms21.insert(std::make_pair(500, std::to_string(500)));
    mmstd.insert(std::make_pair(500, std::to_string(500)));
    mms21.insert(std::make_pair(300, std::to_string(300)));
    mmstd.insert(std::make_pair(300, std::to_string(300)));
    mms21.insert(std::make_pair(800, std::to_string(800)));
    mmstd.insert(std::make_pair(800, std::to_string(800)));
    mms21.insert(std::make_pair(200, std::to_string(200)));
    mmstd.insert(std::make_pair(200, std::to_string(200)));
    mms21.insert(std::make_pair(400, std::to_string(400)));
    mmstd.insert(std::make_pair(400, std::to_string(400)));
    mms21.insert(std::make_pair(600, std::to_string(600)));
    mmstd.insert(std::make_pair(600, std::to_string(600)));
    mms21.insert(std::make_pair(1200, std::to_string(1200)));
    mmstd.insert(std::make_pair(1200, std::to_string(1200)));
    mms21.insert(std::make_pair(100, std::to_string(100)));
    mmstd.insert(std::make_pair(100, std::to_string(100)));
    mms21.insert(std::make_pair(700, std::to_string(700)));
    mmstd.insert(std::make_pair(700, std::to_string(700)));
    mms21.insert(std::make_pair(1000, std::to_string(1000)));
    mmstd.insert(std::make_pair(1000, std::to_string(1000)));
    mms21.insert(std::make_pair(1300, std::to_string(1300)));
    mmstd.insert(std::make_pair(1300, std::to_string(1300)));
    mms21.insert(std::make_pair(900, std::to_string(900)));
    mmstd.insert(std::make_pair(900, std::to_string(900)));
    mms21.insert(std::make_pair(1100, std::to_string(1100)));
    mmstd.insert(std::make_pair(1100, std::to_string(1100)));
  }

  template <typename Key, typename Value>
  bool MapEqual(const s21::map<Key, Value>& lhs,
                const s21::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           lhs.verify() == 0 && rhs.verify() == 0 &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key, typename Value>
  bool MapEqual(const s21::map<Key, Value>& lhs,
                const std::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           lhs.verify() == 0 &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }
  template <typename Key, typename Value>
  bool MapEqual(const std::map<Key, Value>& lhs,
                const s21::map<Key, Value>& rhs) {
    return lhs.empty() == rhs.empty() && lhs.size() == rhs.size() &&
           rhs.verify() == 0 &&
           std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
  }

  s21::map<int, std::string> ms21;
  std::map<int, std::string> mstd;

  s21::map<int, std::string> mms21;
  std::map<int, std::string> mmstd;
};

TEST_F(MapTest, VerifyTest) {
  {
    s21::map<int, int> m;
    ASSERT_EQ(m.verify(), 0);
  }
  {
    s21::map<int, int> m = {{1, 1}};
    ASSERT_EQ(m.verify(), 0);
  }
  {
    s21::map<int, int> m = {{1, 1}, {2, 1}};
    ASSERT_EQ(m.verify(), 0);
  }
  {
    s21::map<int, std::string> m;
    std::map<int, std::string> s;

    for (int i = 0; i < 1000000; ++i) {
      int key = rand() / 100000;
      m.insert(std::make_pair(key, std::to_string(key)));
      s.insert(std::make_pair(key, std::to_string(key)));
    }
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }
}

TEST_F(MapTest, DefaultCtor) {
  {
    s21::map<int, int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
  }
  {
    const s21::map<int, int> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
  }
  {
    s21::map<std::string, std::vector<int>> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
  }
  {
    const s21::map<std::string, std::vector<int>> m;
    EXPECT_TRUE(m.empty());
    EXPECT_EQ(m.size(), 0);
  }
}

TEST_F(MapTest, InitializeCtor) {
  s21::map<int, double> s21_map = {
      std::make_pair(15, 78.1),      std::make_pair(-100, 0.1),
      std::make_pair(158, 278.1),    std::make_pair(254, 30.1),
      std::make_pair(1158, 178.1),   std::make_pair(1254, 40.1),
      std::make_pair(-1158, -178.1), std::make_pair(-1254, -40.1),
      std::make_pair(1, -9178.1),    std::make_pair(0, -40.1),
      std::make_pair(158, 21.3),     std::make_pair(254, 31.1)};
  std::map<int, double> std_map = {
      std::make_pair(15, 78.1),      std::make_pair(-100, 0.1),
      std::make_pair(158, 278.1),    std::make_pair(254, 30.1),
      std::make_pair(1158, 178.1),   std::make_pair(1254, 40.1),
      std::make_pair(-1158, -178.1), std::make_pair(-1254, -40.1),
      std::make_pair(1, -9178.1),    std::make_pair(0, -40.1),
      std::make_pair(158, 21.3),     std::make_pair(254, 31.1)};

  EXPECT_TRUE(MapEqual(s21_map, std_map));

  const s21::map<int, double> s21_cmap = {
      std::make_pair(15, 78.1),
      std::make_pair(-100, 0.1),
      std::make_pair(158, 278.1),
      std::make_pair(254, 30.1),
  };
  const std::map<int, double> std_cmap = {
      std::make_pair(15, 78.1),
      std::make_pair(-100, 0.1),
      std::make_pair(158, 278.1),
      std::make_pair(254, 30.1),
  };

  EXPECT_TRUE(MapEqual(s21_cmap, std_cmap));
}

TEST_F(MapTest, CopyCtor) {
  {
    s21::map<int, std::string> s21_empty_map;
    std::map<int, std::string> std_empty_map;
    s21::map<int, std::string> s21_map(s21_empty_map);
    std::map<int, std::string> std_map(std_empty_map);

    EXPECT_TRUE(MapEqual(s21_empty_map, std_empty_map));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    const s21::map<int, std::string> s21_const_empty_map;
    const std::map<int, std::string> std_const_empty_map;
    const s21::map<int, std::string> s21_map(s21_const_empty_map);
    const std::map<int, std::string> std_map(std_const_empty_map);

    EXPECT_TRUE(MapEqual(s21_const_empty_map, std_const_empty_map));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, int> s21_tmp = {std::make_pair(10, 1)};
    std::map<int, int> std_tmp = {std::make_pair(10, 1)};
    s21::map<int, int> s21_map(s21_tmp);
    std::map<int, int> std_map(std_tmp);

    EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, int> s21_tmp = {std::make_pair(10, 1), std::make_pair(5, 3),
                                  std::make_pair(15, 5)};
    std::map<int, int> std_tmp = {std::make_pair(10, 1), std::make_pair(5, 3),
                                  std::make_pair(15, 5)};
    s21::map<int, int> s21_map(s21_tmp);
    std::map<int, int> std_map(std_tmp);

    EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, std::string> s21_map(ms21);
    std::map<int, std::string> std_map(mstd);

    EXPECT_TRUE(MapEqual(ms21, mstd));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    const s21::map<int, std::string> s21_map(ms21);
    const std::map<int, std::string> std_map(mstd);

    EXPECT_TRUE(MapEqual(ms21, mstd));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
}

TEST_F(MapTest, MoveCtor) {
  {
    s21::map<int, std::string> s21_empty_map;
    std::map<int, std::string> std_empty_map;
    s21::map<int, std::string> s21_map(std::move(s21_empty_map));
    std::map<int, std::string> std_map(std::move(std_empty_map));

    EXPECT_TRUE(MapEqual(s21_empty_map, std_empty_map));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    const s21::map<int, std::string> s21_const_empty_map;
    const std::map<int, std::string> std_const_empty_map;
    const s21::map<int, std::string> s21_map(std::move(s21_const_empty_map));
    const std::map<int, std::string> std_map(std::move(std_const_empty_map));

    EXPECT_TRUE(MapEqual(s21_const_empty_map, std_const_empty_map));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, int> s21_tmp = {std::make_pair(10, 1)};
    std::map<int, int> std_tmp = {std::make_pair(10, 1)};
    s21::map<int, int> s21_map(std::move(s21_tmp));
    std::map<int, int> std_map(std::move(std_tmp));

    EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, int> s21_tmp = {std::make_pair(10, 1), std::make_pair(5, 3),
                                  std::make_pair(15, 5)};
    std::map<int, int> std_tmp = {std::make_pair(10, 1), std::make_pair(5, 3),
                                  std::make_pair(15, 5)};
    s21::map<int, int> s21_map(std::move(s21_tmp));
    std::map<int, int> std_map(std::move(std_tmp));

    EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, std::string> s21_map(std::move(ms21));
    std::map<int, std::string> std_map(std::move(mstd));

    EXPECT_TRUE(MapEqual(ms21, mstd));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    const s21::map<int, std::string> s21_map(std::move(ms21));
    const std::map<int, std::string> std_map(std::move(mstd));

    EXPECT_TRUE(MapEqual(ms21, mstd));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
}

TEST_F(MapTest, CopyOpearotAssign) {
  {
    s21::map<int, std::string> s21_empty_map;
    std::map<int, std::string> std_empty_map;
    s21::map<int, std::string> s21_map;
    std::map<int, std::string> std_map;

    s21_map = s21_empty_map;
    std_map = std_empty_map;

    EXPECT_TRUE(MapEqual(s21_empty_map, std_empty_map));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, int> s21_tmp = {std::make_pair(10, 1)};
    std::map<int, int> std_tmp = {std::make_pair(10, 1)};
    s21::map<int, int> s21_map;
    std::map<int, int> std_map;

    s21_map = s21_tmp;
    std_map = std_tmp;

    EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, int> s21_tmp = {std::make_pair(10, 1), std::make_pair(5, 3),
                                  std::make_pair(15, 5)};
    std::map<int, int> std_tmp = {std::make_pair(10, 1), std::make_pair(5, 3),
                                  std::make_pair(15, 5)};
    s21::map<int, int> s21_map = {std::make_pair(10, 1)};
    std::map<int, int> std_map = {std::make_pair(10, 1)};

    s21_map = s21_tmp;
    std_map = std_tmp;

    EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, std::string> s21_map = {
        std::make_pair(10, std::to_string(1))};
    std::map<int, std::string> std_map = {
        std::make_pair(10, std::to_string(1))};

    s21_map = ms21;
    std_map = mstd;

    EXPECT_TRUE(MapEqual(ms21, mstd));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
}

TEST_F(MapTest, MoveOpearotAssign) {
  {
    s21::map<int, std::string> s21_empty_map;
    std::map<int, std::string> std_empty_map;
    s21::map<int, std::string> s21_map;
    std::map<int, std::string> std_map;

    s21_map = std::move(s21_empty_map);
    std_map = std::move(std_empty_map);

    EXPECT_TRUE(MapEqual(s21_empty_map, std_empty_map));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, int> s21_tmp = {std::make_pair(10, 1)};
    std::map<int, int> std_tmp = {std::make_pair(10, 1)};
    s21::map<int, int> s21_map(s21_tmp);
    std::map<int, int> std_map(std_tmp);

    s21_map = std::move(s21_tmp);
    // std_map = std::move(std_tmp);
    std_map.swap(std_tmp);

    EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, int> s21_tmp = {std::make_pair(10, 1), std::make_pair(5, 3),
                                  std::make_pair(15, 5)};
    std::map<int, int> std_tmp = {std::make_pair(10, 1), std::make_pair(5, 3),
                                  std::make_pair(15, 5)};
    s21::map<int, int> s21_map = {std::make_pair(10, 1)};
    std::map<int, int> std_map = {std::make_pair(10, 1)};

    s21_map = std::move(s21_tmp);
    // std_map = std::move(std_tmp);
    std_map.swap(std_tmp);

    EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
  {
    s21::map<int, std::string> s21_map = {
        std::make_pair(10, std::to_string(1))};
    std::map<int, std::string> std_map = {
        std::make_pair(10, std::to_string(1))};

    s21_map = std::move(ms21);
    // std_map = std::move(mstd);
    std_map.swap(mstd);

    EXPECT_TRUE(MapEqual(ms21, mstd));
    EXPECT_TRUE(MapEqual(s21_map, std_map));
  }
}

TEST_F(MapTest, ConstAt) {
  const s21::map<int, std::string> cms21 = mms21;
  const std::map<int, std::string> cmstd = mmstd;

  for (int i = 0; i < 1500; i += 10) {
    try {
      std::string val_s21 = cms21.at(i);
      std::string val_std = cmstd.at(i);
      EXPECT_EQ(val_s21, val_std);
    } catch (std::out_of_range& e_s21) {
      try {
        std::string val_std = cmstd.at(i);
        EXPECT_TRUE(false);
      } catch (std::out_of_range& e_std) {
        EXPECT_TRUE(true);
      }
    }
  }
  EXPECT_TRUE(MapEqual(cms21, cmstd));
}

TEST_F(MapTest, At) {
  for (int i = 0; i < 1500; i += 10) {
    try {
      std::string val_s21 = mms21.at(i);
      std::string val_std = mmstd.at(i);
      EXPECT_EQ(val_s21, val_std);
      val_s21 = "ABCDEF";
      val_std = "ABCDEF";
      val_s21 = mms21.at(i);
      val_std = mmstd.at(i);
      EXPECT_EQ(val_s21, val_std);
    } catch (std::out_of_range& e_s21) {
      try {
        std::string val_std = mmstd.at(i);
        EXPECT_EQ(21, 42);
      } catch (std::out_of_range& e_std) {
        EXPECT_EQ(42, 42);
      }
    }
  }
  EXPECT_TRUE(MapEqual(mms21, mmstd));
}

TEST_F(MapTest, OperatorSquareBrackets) {
  for (int i = 0; i < 1500; i += 10) {
    std::string val_s21 = mms21[i];
    std::string val_std = mmstd[i];
    EXPECT_EQ(val_s21, val_std);
    val_s21 = "ABCDEF";
    val_std = "ABCDEF";
    val_s21 = mms21[i];
    val_std = mmstd[i];
  }
  EXPECT_TRUE(MapEqual(mms21, mmstd));
}

TEST_F(MapTest, Iterator) {
  {
    s21::map<int, std::string>::iterator s21_it = ms21.begin();
    std::map<int, std::string>::iterator std_it = mstd.begin();

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
    EXPECT_EQ(s21_it->second, std_it->second);
    EXPECT_EQ(s21_it++->first, std_it++->first);

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
    s21::map<int, std::string>::iterator s21_it = ms21.end();
    std::map<int, std::string>::iterator std_it = mstd.end();
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
    EXPECT_EQ(s21_it->second, std_it->second);
    EXPECT_EQ(s21_it--->first, std_it--->first);
  }
}

TEST_F(MapTest, ConstIterator) {
  const s21::map<int, std::string> cms21 = ms21;
  const std::map<int, std::string> cmstd = mstd;
  {
    s21::map<int, std::string>::const_iterator s21_it = cms21.begin();
    std::map<int, std::string>::const_iterator std_it = cmstd.begin();

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
    EXPECT_EQ(s21_it->second, std_it->second);
    EXPECT_EQ(s21_it++->first, std_it++->first);

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
    s21::map<int, std::string>::const_iterator s21_it = cms21.end();
    std::map<int, std::string>::const_iterator std_it = cmstd.end();
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
    EXPECT_EQ(s21_it->second, std_it->second);
    EXPECT_EQ(s21_it--->first, std_it--->first);
  }
}

TEST_F(MapTest, Capacity) {
  {
    s21::map<int, std::vector<double>> s21_m;
    std::map<int, std::vector<double>> std_m;

    EXPECT_EQ(s21_m.empty(), std_m.empty());
    EXPECT_EQ(s21_m.size(), std_m.size());
    EXPECT_EQ(s21_m.max_size(), std_m.max_size());
  }
  {
    s21::map<int, std::vector<double>> s21_m{
        std::make_pair(10, std::vector<double>{1.0, 2.0})};
    std::map<int, std::vector<double>> std_m{
        std::make_pair(10, std::vector<double>{1.0, 2.0})};

    EXPECT_EQ(s21_m.empty(), std_m.empty());
    EXPECT_EQ(s21_m.size(), std_m.size());
    EXPECT_EQ(s21_m.max_size(), std_m.max_size());
  }
  {
    s21::map<int, std::vector<double>> s21_m{
        std::make_pair(10, std::vector<double>{1.0, 2.0}),
        std::make_pair(19, std::vector<double>{10.0, 20.0}),
        std::make_pair(-19, std::vector<double>{100.0, 200.0})};
    std::map<int, std::vector<double>> std_m{
        std::make_pair(10, std::vector<double>{1.0, 2.0}),
        std::make_pair(19, std::vector<double>{10.0, 20.0}),
        std::make_pair(-19, std::vector<double>{100.0, 200.0})};

    EXPECT_EQ(s21_m.empty(), std_m.empty());
    EXPECT_EQ(s21_m.size(), std_m.size());
    EXPECT_EQ(s21_m.max_size(), std_m.max_size());
  }
  {
    EXPECT_EQ(ms21.empty(), mstd.empty());
    EXPECT_EQ(ms21.size(), mstd.size());
    EXPECT_EQ(ms21.max_size(), mstd.max_size());
  }
  {
    const s21::map<int, std::string> cms21 = ms21;
    const std::map<int, std::string> cmstd = mstd;

    EXPECT_EQ(cms21.empty(), cmstd.empty());
    EXPECT_EQ(cms21.size(), cmstd.size());
    EXPECT_EQ(cms21.max_size(), cmstd.max_size());
  }
}

TEST_F(MapTest, Clear) {
  s21::map<int, std::string> m = ms21;
  std::map<int, std::string> s = mstd;

  m.clear();
  s.clear();

  EXPECT_EQ(m.empty(), s.empty());
  EXPECT_TRUE(MapEqual(m, s));
}

TEST_F(MapTest, Insert1) {
  s21::map<int, std::string> m;
  std::map<int, std::string> s;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() % 1000000;
    auto ps21 = m.insert(std::make_pair(key, std::to_string(key)));
    auto pstd = s.insert(std::make_pair(key, std::to_string(key)));
    EXPECT_EQ(*ps21.first, *pstd.first);
    EXPECT_EQ(ps21.second, pstd.second);
  }
  EXPECT_TRUE(MapEqual(m, s));
}

TEST_F(MapTest, Insert2) {
  s21::map<int, std::string> m;
  std::map<int, std::string> s;

  for (int i = 0; i < 10000; ++i) {
    int key = rand() / 10000;
    auto ps21 = m.insert(key, std::to_string(key));
    auto pstd = s.insert(std::make_pair(key, std::to_string(key)));
    EXPECT_EQ(*ps21.first, *pstd.first);
    EXPECT_EQ(ps21.second, pstd.second);
  }
  EXPECT_TRUE(MapEqual(m, s));
}

TEST_F(MapTest, InsertOrAssign) {
  s21::map<int, std::string> m;
  std::map<int, std::string> s;

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 1000;
    auto ps21 = m.insert_or_assign(key, std::to_string(key + i));
    auto pstd = s.insert_or_assign(key, std::to_string(key + i));
    EXPECT_EQ(*ps21.first, *pstd.first);
    EXPECT_EQ(ps21.second, pstd.second);
  }
  EXPECT_TRUE(MapEqual(m, s));
}

TEST_F(MapTest, Erase1) {
  s21::map<int, std::string> m = ms21;
  std::map<int, std::string> s = mstd;

  auto mit = m.begin();
  m.erase(mit);
  auto sit = s.begin();
  s.erase(sit);
  EXPECT_TRUE(MapEqual(m, s));

  mit = --m.end();
  m.erase(mit);
  sit = --s.end();
  s.erase(sit);
  EXPECT_TRUE(MapEqual(m, s));

  mit = m.end();
  sit = s.end();
  for (int i = 0; i < 100; ++i) {
    --mit;
    --sit;
  }
  m.erase(mit);
  s.erase(sit);
  EXPECT_TRUE(MapEqual(m, s));

  mit = m.begin();
  sit = s.begin();
  for (int i = 0; i < 100; ++i) {
    ++mit;
    ++sit;
  }
  m.erase(mit);
  s.erase(sit);
  EXPECT_TRUE(MapEqual(m, s));
}

TEST_F(MapTest, Erase2) {
  s21::map<int, std::string> m;
  std::map<int, std::string> s;

  m.insert(std::make_pair(10, "10"));
  s.insert(std::make_pair(10, "10"));

  m.erase(m.begin());
  s.erase(s.begin());
  EXPECT_TRUE(MapEqual(m, s));
}

TEST_F(MapTest, Erase3) {
  s21::map<int, std::string> mm;
  std::map<int, std::string> ss;

  mm.insert(std::make_pair(10, "10"));
  mm.insert(std::make_pair(8, "8"));
  mm.insert(std::make_pair(11, "11"));

  ss.insert(std::make_pair(10, "10"));
  ss.insert(std::make_pair(8, "8"));
  ss.insert(std::make_pair(11, "11"));

  {
    s21::map<int, std::string> m = mm;
    std::map<int, std::string> s = ss;

    m.erase(m.begin());
    s.erase(s.begin());
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mm;
    std::map<int, std::string> s = ss;

    m.erase(++m.begin());
    s.erase(++s.begin());
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mm;
    std::map<int, std::string> s = ss;

    m.erase(--m.end());
    s.erase(--s.end());
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mm;
    std::map<int, std::string> s = ss;

    m.erase(--m.end());
    s.erase(--s.end());
    m.erase(++m.begin());
    s.erase(++s.begin());
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mm;
    std::map<int, std::string> s = ss;

    m.erase(--m.end());
    s.erase(--s.end());
    m.erase(++m.begin());
    s.erase(++s.begin());
    m.erase(m.begin());
    s.erase(s.begin());
    EXPECT_TRUE(MapEqual(m, s));
  }
}

TEST_F(MapTest, Erase4) {
  {
    s21::map<int, std::string> m = mms21;
    std::map<int, std::string> s = mmstd;

    auto mit = m.find(600);
    auto sit = s.find(600);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mms21;
    std::map<int, std::string> s = mmstd;

    auto mit = m.find(200);
    auto sit = s.find(200);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mms21;
    std::map<int, std::string> s = mmstd;

    m.insert(std::make_pair(350, "a"));
    s.insert(std::make_pair(350, "a"));

    auto mit = m.find(300);
    auto sit = s.find(300);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mms21;
    std::map<int, std::string> s = mmstd;

    m.insert(std::make_pair(450, "a"));
    s.insert(std::make_pair(450, "a"));
    m.insert(std::make_pair(430, "b"));
    s.insert(std::make_pair(430, "b"));
    m.insert(std::make_pair(460, "c"));
    s.insert(std::make_pair(460, "c"));

    auto mit = m.find(300);
    auto sit = s.find(300);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }

  {
    s21::map<int, std::string> m = mms21;
    std::map<int, std::string> s = mmstd;

    auto mit = m.find(800);
    auto sit = s.find(800);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mms21;
    std::map<int, std::string> s = mmstd;

    auto mit = m.find(500);
    auto sit = s.find(500);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mms21;
    std::map<int, std::string> s = mmstd;

    auto mit = m.find(900);
    auto sit = s.find(900);
    m.erase(mit);
    s.erase(sit);
    EXPECT_TRUE(MapEqual(m, s));

    mit = m.find(800);
    sit = s.find(800);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }
  {
    s21::map<int, std::string> m = mms21;
    std::map<int, std::string> s = mmstd;

    auto mit = m.find(900);
    auto sit = s.find(900);
    m.erase(mit);
    s.erase(sit);
    EXPECT_TRUE(MapEqual(m, s));

    mit = m.find(800);
    sit = s.find(800);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));

    mit = m.find(300);
    sit = s.find(300);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));

    mit = m.find(1000);
    sit = s.find(1000);
    m.erase(mit);
    s.erase(sit);
    ASSERT_EQ(m.verify(), 0);
    EXPECT_TRUE(MapEqual(m, s));
  }
}

TEST_F(MapTest, Erase5) {
  s21::map<int, std::string> m;
  std::map<int, std::string> s;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() / 100000;
    m.insert(std::make_pair(key, std::to_string(key)));
    s.insert(std::make_pair(key, std::to_string(key)));
  }
  EXPECT_TRUE(MapEqual(m, s));

  for (int i = 0; i < 10000; ++i) {
    int key = rand() / 100000;
    auto it1 = m.find(key);
    auto it2 = s.find(key);
    if (it2 != s.end()) {
      EXPECT_EQ(*it1, *it2);
    }
  }

  for (int i = 0; i < 100000; ++i) {
    int key = rand() / 100000;
    auto it1 = m.find(key);
    auto it2 = s.find(key);
    if (it2 != s.end()) {
      m.erase(it1);
      s.erase(it2);
    }
  }
  ASSERT_EQ(m.verify(), 0);
  EXPECT_TRUE(MapEqual(m, s));
}

TEST_F(MapTest, Swap) {
  s21::map<int, std::string> m = {{1, "1"}};
  std::map<int, std::string> s = {{1, "1"}};

  m.swap(ms21);
  s.swap(mstd);

  EXPECT_TRUE(MapEqual(m, s));
  EXPECT_TRUE(MapEqual(ms21, mstd));
}

TEST_F(MapTest, Merge1) {
  {
    s21::map<int, std::string> m_s21;
    s21::map<int, std::string> source_s21;
    std::map<int, std::string> m_std;
    std::map<int, std::string> source_std;

    m_s21.merge(source_s21);
    m_std.merge(source_std);

    EXPECT_TRUE(MapEqual(m_s21, m_std));
    EXPECT_TRUE(MapEqual(source_s21, source_std));
  }
  {
    s21::map<int, std::string> m_s21 = {{1, "1"}};
    s21::map<int, std::string> source_s21;
    std::map<int, std::string> m_std = {{1, "1"}};
    std::map<int, std::string> source_std;

    m_s21.merge(source_s21);
    m_std.merge(source_std);

    EXPECT_TRUE(MapEqual(m_s21, m_std));
    EXPECT_TRUE(MapEqual(source_s21, source_std));
  }
  {
    s21::map<int, std::string> m_s21;
    s21::map<int, std::string> source_s21 = {{1, "1"}};
    std::map<int, std::string> m_std;
    std::map<int, std::string> source_std = {{1, "1"}};

    m_s21.merge(source_s21);
    m_std.merge(source_std);

    EXPECT_TRUE(MapEqual(m_s21, m_std));
    EXPECT_TRUE(MapEqual(source_s21, source_std));
  }
  {
    s21::map<int, std::string> m_s21 = {{2, "2"}};
    s21::map<int, std::string> source_s21 = {{1, "1"}};
    std::map<int, std::string> m_std = {{2, "2"}};
    std::map<int, std::string> source_std = {{1, "1"}};

    m_s21.merge(source_s21);
    m_std.merge(source_std);

    EXPECT_TRUE(MapEqual(m_s21, m_std));
    EXPECT_TRUE(MapEqual(source_s21, source_std));
  }
  {
    s21::map<int, std::string> m_s21 = {{1, "1"}, {2, "2"}};
    s21::map<int, std::string> source_s21 = {{1, "1"}};
    std::map<int, std::string> m_std = {{1, "1"}, {2, "2"}};
    std::map<int, std::string> source_std = {{1, "1"}};

    m_s21.merge(source_s21);
    m_std.merge(source_std);

    EXPECT_TRUE(MapEqual(m_s21, m_std));
    EXPECT_TRUE(MapEqual(source_s21, source_std));
  }
  {
    s21::map<int, std::string> m_s21 = {{1, "1"}, {2, "2"}};
    s21::map<int, std::string> source_s21 = {{1, "1"}, {3, "3"}};
    std::map<int, std::string> m_std = {{1, "1"}, {2, "2"}};
    std::map<int, std::string> source_std = {{1, "1"}, {3, "3"}};

    m_s21.merge(source_s21);
    m_std.merge(source_std);

    EXPECT_TRUE(MapEqual(m_s21, m_std));
    EXPECT_TRUE(MapEqual(source_s21, source_std));
  }
  {
    s21::map<int, std::string> m_s21 = {
        {1, "1"}, {2, "2"}, {0, "0"}, {-1, "-1"}, {2, "2"}};
    s21::map<int, std::string> source_s21 = {
        {1, "1"}, {3, "3"}, {2, "2"}, {4, "4"}, {5, "5"}};
    std::map<int, std::string> m_std = {
        {1, "1"}, {2, "2"}, {0, "0"}, {-1, "-1"}, {2, "2"}};
    std::map<int, std::string> source_std = {
        {1, "1"}, {3, "3"}, {2, "2"}, {4, "4"}, {5, "5"}};

    m_s21.merge(source_s21);
    m_std.merge(source_std);

    EXPECT_TRUE(MapEqual(m_s21, m_std));
    EXPECT_TRUE(MapEqual(source_s21, source_std));
  }
}

TEST_F(MapTest, Merge2) {
  s21::map<int, std::string> m_s21;
  s21::map<int, std::string> source_s21;
  std::map<int, std::string> m_std;
  std::map<int, std::string> source_std;

  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 1000000;
    m_s21.insert(std::make_pair(key, std::to_string(key)));
    m_std.insert(std::make_pair(key, std::to_string(key)));
  }
  for (int i = 0; i < 100000; ++i) {
    int key = rand() % 100000;
    source_s21.insert(std::make_pair(key, std::to_string(key + i)));
    source_std.insert(std::make_pair(key, std::to_string(key + i)));
  }

  EXPECT_FALSE(MapEqual(m_s21, source_s21));

  m_s21.merge(source_s21);
  m_std.merge(source_std);

  EXPECT_TRUE(MapEqual(m_s21, m_std));
  EXPECT_TRUE(MapEqual(source_s21, source_std));
}

TEST_F(MapTest, Find) {
  s21::map<int, std::string> m;
  std::map<int, std::string> s;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() / 100000;
    m.insert(std::make_pair(key, std::to_string(key)));
    s.insert(std::make_pair(key, std::to_string(key)));
  }
  EXPECT_TRUE(MapEqual(m, s));

  for (int i = 0; i < 10000; ++i) {
    int key = rand() / 100000;
    auto it1 = m.find(key);
    auto it2 = s.find(key);
    if (it2 != s.end()) {
      EXPECT_EQ(*it1, *it2);
    } else {
      EXPECT_EQ(it1, m.end());
    }
  }
}

TEST_F(MapTest, ConstFind) {
  s21::map<int, std::string> m;
  std::map<int, std::string> s;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() / 100000;
    m.insert(std::make_pair(key, std::to_string(key)));
    s.insert(std::make_pair(key, std::to_string(key)));
  }
  EXPECT_TRUE(MapEqual(m, s));

  const s21::map<int, std::string> cm = m;
  const std::map<int, std::string> cs = s;

  for (int i = 0; i < 10000; ++i) {
    int key = rand() / 100000;
    auto it1 = cm.find(key);
    auto it2 = cs.find(key);
    if (it2 != s.cend()) {
      EXPECT_EQ(*it1, *it2);
    } else {
      EXPECT_EQ(it1, m.cend());
    }
  }
}

TEST_F(MapTest, Contains) {
  s21::map<int, std::string> m;
  std::map<int, std::string> s;

  for (int i = 0; i < 1000000; ++i) {
    int key = rand() / 100000;
    m.insert(std::make_pair(key, std::to_string(key)));
    s.insert(std::make_pair(key, std::to_string(key)));
  }
  EXPECT_TRUE(MapEqual(m, s));

  const s21::map<int, std::string> cm = m;
  const std::map<int, std::string> cs = s;

  for (int i = 0; i < 10000; ++i) {
    int key = rand() / 100000;

    {
      bool res_s21 = m.contains(key);
      auto it = s.find(key);
      bool res_std = (it != cs.end());
      EXPECT_EQ(res_s21, res_std);
    }
    {
      bool res_s21 = cm.contains(key);
      auto it = cs.find(key);
      bool res_std = (it != cs.end());
      EXPECT_EQ(res_s21, res_std);
    }
  }
}

TEST_F(MapTest, InsertMany) {
  {
    s21::map<int, std::string> m = {{1, "1"}, {2, "2"}};

    m.insert_many(std::make_pair(5, std::string("5")),
                  std::make_pair(3, std::string("3")),
                  std::make_pair(3, std::string("3")),
                  std::make_pair(4, std::string("4")));

    std::map<int, std::string> std_m = {
        {1, "1"}, {2, "2"}, {3, "3"}, {4, "4"}, {5, "5"}};

    EXPECT_TRUE(MapEqual(m, std_m));
  }
  {
    s21::map<int, std::string> m = {{1, "1"}, {2, "2"}};

    m.insert_many(std::make_pair(5, std::string("5")));

    std::map<int, std::string> std_m = {{1, "1"}, {2, "2"}, {5, "5"}};

    EXPECT_TRUE(MapEqual(m, std_m));
  }
  {
    s21::map<int, std::string> m = {{1, "1"}, {2, "2"}};

    m.insert_many();

    std::map<int, std::string> std_m = {{1, "1"}, {2, "2"}};

    EXPECT_TRUE(MapEqual(m, std_m));
  }
}
