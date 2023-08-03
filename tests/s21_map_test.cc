#include "s21_map.h"

#include <string>
#include <map>
#include <algorithm>
#include <cstdlib>

#include <gtest/gtest.h>

class MapTest : public ::testing::Test {
 public:
	void SetUp(void) override {
		int map_size = 1000;

		std::srand(42);
		for (int i = 0; i < map_size; ++i) {
			int key = rand();
			std::string value = std::to_string(key + i);
			ms21.insert(std::make_pair(key, value));
			mstd.insert(std::make_pair(key, value));
		}
	}

	template <typename Key, typename Value>
	bool MapEqual(const s21::map<Key, Value>&lhs, const s21::map<Key, Value> rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
					 std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
	}
	template <typename Key, typename Value>
	bool MapEqual(const s21::map<Key, Value>&lhs, const std::map<Key, Value> rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
					 std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
	}
	template <typename Key, typename Value>
	bool MapEqual(const std::map<Key, Value>&lhs, const s21::map<Key, Value> rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
					 std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
	}

	s21::map<int, std::string> ms21;
	std::map<int, std::string> mstd;
};

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
		std::make_pair(15, 78.1), std::make_pair(-100, 0.1),
		std::make_pair(158, 278.1), std::make_pair(254, 30.1),
		std::make_pair(1158, 178.1), std::make_pair(1254, 40.1),
		std::make_pair(-1158, -178.1), std::make_pair(-1254, -40.1),
		std::make_pair(1, -9178.1), std::make_pair(0, -40.1),
		std::make_pair(158, 21.3), std::make_pair(254, 31.1)
	};
	std::map<int, double> std_map = {
		std::make_pair(15, 78.1), std::make_pair(-100, 0.1),
		std::make_pair(158, 278.1), std::make_pair(254, 30.1),
		std::make_pair(1158, 178.1), std::make_pair(1254, 40.1),
		std::make_pair(-1158, -178.1), std::make_pair(-1254, -40.1),
		std::make_pair(1, -9178.1), std::make_pair(0, -40.1),
		std::make_pair(158, 21.3), std::make_pair(254, 31.1)
	};
	
	EXPECT_TRUE(MapEqual(s21_map, std_map));

	const s21::map<int, double> s21_cmap = {
		std::make_pair(15, 78.1), std::make_pair(-100, 0.1),
		std::make_pair(158, 278.1), std::make_pair(254, 30.1),
	};
	const std::map<int, double> std_cmap = {
		std::make_pair(15, 78.1), std::make_pair(-100, 0.1),
		std::make_pair(158, 278.1), std::make_pair(254, 30.1),
	};
	
	EXPECT_TRUE(MapEqual(s21_map, std_map));
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
		s21::map<int, int> s21_tmp = { std::make_pair(10, 1) };
		std::map<int, int> std_tmp = { std::make_pair(10, 1) };
		s21::map<int, int> s21_map(s21_tmp);
		std::map<int, int> std_map(std_tmp);

		EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(MapEqual(s21_map, std_map));
	}
	{
		s21::map<int, int> s21_tmp = {
				std::make_pair(10, 1), std::make_pair(5, 3), std::make_pair(15, 5)
		};
		std::map<int, int> std_tmp = {
				std::make_pair(10, 1), std::make_pair(5, 3), std::make_pair(15, 5)
		};
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
		s21::map<int, int> s21_tmp = { std::make_pair(10, 1) };
		std::map<int, int> std_tmp = { std::make_pair(10, 1) };
		s21::map<int, int> s21_map(s21_tmp);
		std::map<int, int> std_map(std_tmp);

		EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(MapEqual(s21_map, std_map));
	}
	{
		s21::map<int, int> s21_tmp = {
				std::make_pair(10, 1), std::make_pair(5, 3), std::make_pair(15, 5)
		};
		std::map<int, int> std_tmp = {
				std::make_pair(10, 1), std::make_pair(5, 3), std::make_pair(15, 5)
		};
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
		s21::map<int, int> s21_tmp = { std::make_pair(10, 1) };
		std::map<int, int> std_tmp = { std::make_pair(10, 1) };
		s21::map<int, int> s21_map;
		std::map<int, int> std_map;

		s21_map = s21_tmp;
		std_map = std_tmp;

		EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(MapEqual(s21_map, std_map));
	}
	{
		s21::map<int, int> s21_tmp = {
				std::make_pair(10, 1), std::make_pair(5, 3), std::make_pair(15, 5)
		};
		std::map<int, int> std_tmp = {
				std::make_pair(10, 1), std::make_pair(5, 3), std::make_pair(15, 5)
		};
		s21::map<int, int> s21_map = { std::make_pair(10, 1) };
		std::map<int, int> std_map = { std::make_pair(10, 1) };

		s21_map = s21_tmp;
		std_map = std_tmp;

		EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(MapEqual(s21_map, std_map));
	}
	{
		s21::map<int, std::string> s21_map = { std::make_pair(10, std::to_string(1)) };
		std::map<int, std::string> std_map = { std::make_pair(10, std::to_string(1)) };

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
		s21::map<int, int> s21_tmp = { std::make_pair(10, 1) };
		std::map<int, int> std_tmp = { std::make_pair(10, 1) };
		s21::map<int, int> s21_map(s21_tmp);
		std::map<int, int> std_map(std_tmp);

		s21_map = std::move(s21_tmp);
		//std_map = std::move(std_tmp);
		std_map.swap(std_tmp);

		EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(MapEqual(s21_map, std_map));
	}
	{
		s21::map<int, int> s21_tmp = {
				std::make_pair(10, 1), std::make_pair(5, 3), std::make_pair(15, 5)
		};
		std::map<int, int> std_tmp = {
				std::make_pair(10, 1), std::make_pair(5, 3), std::make_pair(15, 5)
		};
		s21::map<int, int> s21_map = { std::make_pair(10, 1) };
		std::map<int, int> std_map = { std::make_pair(10, 1) };

		s21_map = std::move(s21_tmp);
		//std_map = std::move(std_tmp);
		std_map.swap(std_tmp);

		EXPECT_TRUE(MapEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(MapEqual(s21_map, std_map));
	}
	{
		s21::map<int, std::string> s21_map = { std::make_pair(10, std::to_string(1)) };
		std::map<int, std::string> std_map = { std::make_pair(10, std::to_string(1)) };

		s21_map = std::move(ms21);
		//std_map = std::move(mstd);
		std_map.swap(mstd);

		EXPECT_TRUE(MapEqual(ms21, mstd));
		EXPECT_TRUE(MapEqual(s21_map, std_map));
	}
}

TEST_F(MapTest, Iterator) {
	{
		s21::map<int, std::string>::iterator s21_it = ms21.begin();
		std::map<int, std::string>::iterator std_it = mstd.begin();

		++s21_it; ++s21_it;
		++std_it; ++std_it;
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
		++s21_tmp; ++std_tmp;
		EXPECT_TRUE(s21_tmp == s21_it);
		EXPECT_TRUE(std_tmp == std_it);
		EXPECT_FALSE(s21_tmp != s21_it);
		EXPECT_FALSE(std_tmp != std_it);
	}
	{
		s21::map<int, std::string>::iterator s21_it = ms21.end();
		std::map<int, std::string>::iterator std_it = mstd.end();
		--s21_it; --s21_it;
		--std_it; --std_it;
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

		++s21_it; ++s21_it;
		++std_it; ++std_it;
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
		++s21_tmp; ++std_tmp;
		EXPECT_TRUE(s21_tmp == s21_it);
		EXPECT_TRUE(std_tmp == std_it);
		EXPECT_FALSE(s21_tmp != s21_it);
		EXPECT_FALSE(std_tmp != std_it);
	}
	{
		s21::map<int, std::string>::const_iterator s21_it = cms21.end();
		std::map<int, std::string>::const_iterator std_it = cmstd.end();
		--s21_it; --s21_it;
		--std_it; --std_it;
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
		s21::map<int, std::vector<double>> s21_m {
			std::make_pair(10, std::vector<double>{1.0, 2.0})
		};
		std::map<int, std::vector<double>> std_m {
			std::make_pair(10, std::vector<double>{1.0, 2.0})
		};

		EXPECT_EQ(s21_m.empty(), std_m.empty());
		EXPECT_EQ(s21_m.size(), std_m.size());
		EXPECT_EQ(s21_m.max_size(), std_m.max_size());
	}
	{
		s21::map<int, std::vector<double>> s21_m {
			std::make_pair(10, std::vector<double>{1.0, 2.0}),
			std::make_pair(19, std::vector<double>{10.0, 20.0}),
			std::make_pair(-19, std::vector<double>{100.0, 200.0})
		};
		std::map<int, std::vector<double>> std_m {
			std::make_pair(10, std::vector<double>{1.0, 2.0}),
			std::make_pair(19, std::vector<double>{10.0, 20.0}),
			std::make_pair(-19, std::vector<double>{100.0, 200.0})
		};

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

