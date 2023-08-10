#include "s21_set.h"

#include <string>
#include <set>
#include <algorithm>
#include <cstdlib>

#include <gtest/gtest.h>

class SetTest : public ::testing::Test {
 public:
	void SetUp(void) override {
		std::srand(42);

		int set_size = 1000;
		for (int i = 0; i < set_size; ++i) {
			int key = rand();
			std::string value = std::to_string(key + i);
			ss21.insert(value);
			sstd.insert(value);
		}
	}

	template <typename Key>
	bool SetEqual(const s21::set<Key>& lhs, const s21::set<Key>& rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
					 lhs.verify() == 0 &&
					 rhs.verify() == 0 &&
					 std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
	}
	template <typename Key>
	bool SetEqual(const s21::set<Key>& lhs, const std::set<Key>& rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
					 lhs.verify() == 0 &&
					 std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
	}
	template <typename Key>
	bool SetEqual(const std::set<Key>& lhs, const s21::set<Key>& rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
					 rhs.verify() == 0 &&
					 std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
	}

	s21::set<std::string> ss21;
	std::set<std::string> sstd;
};

TEST_F(SetTest, DefaultCtor) {
	{
		s21::set<int> m;
		EXPECT_TRUE(m.empty());
		EXPECT_EQ(m.size(), 0);
	}
	{
		const s21::set<int> m;
		EXPECT_TRUE(m.empty());
		EXPECT_EQ(m.size(), 0);
	}
	{
		s21::set<std::vector<int>> m;
		EXPECT_TRUE(m.empty());
		EXPECT_EQ(m.size(), 0);
	}
	{
		const s21::set<std::vector<int>> m;
		EXPECT_TRUE(m.empty());
		EXPECT_EQ(m.size(), 0);
	}
}

TEST_F(SetTest, InitializerCtor) {
	s21::set<std::string> s21_set = {
		std::to_string(123), std::string("abc"), std::string("Abc"),
		std::string("-123533.124"), std::to_string(1.233413)
	};
	std::set<std::string> std_set = {
		std::to_string(123), std::string("abc"), std::string("Abc"),
		std::string("-123533.124"), std::to_string(1.233413)
	};

	EXPECT_TRUE(SetEqual(s21_set, std_set));

	const s21::set<std::string> s21_cset = {
		std::to_string(123), std::string("abc"), std::string("Abc"),
		std::string("-123533.124"), std::to_string(1.233413),
		std::string("qiisq ksaksaaq"), std::string("abc")
	};
	const std::set<std::string> std_cset = {
		std::to_string(123), std::string("abc"), std::string("Abc"),
		std::string("-123533.124"), std::to_string(1.233413),
		std::string("qiisq ksaksaaq"), std::string("abc")
	};

	EXPECT_TRUE(SetEqual(s21_cset, std_cset));
}

TEST_F(SetTest, CopyCtor) {
	{
		s21::set<std::string> s21_empty_set;
		std::set<std::string> std_empty_set;
		s21::set<std::string> s21_set(s21_empty_set);
		std::set<std::string> std_set(std_empty_set);

		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		const s21::set<std::string> s21_empty_set;
		const std::set<std::string> std_empty_set;
		const s21::set<std::string> s21_set(s21_empty_set);
		const std::set<std::string> std_set(std_empty_set);

		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828) };
		std::set<std::string> std_tmp = { std::to_string(1828) };
		s21::set<std::string> s21_set(s21_tmp);
		std::set<std::string> std_set(std_tmp);

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828), "abc", "ABC" };
		std::set<std::string> std_tmp = { std::to_string(1828), "abc", "ABC" };
		s21::set<std::string> s21_set(s21_tmp);
		std::set<std::string> std_set(std_tmp);

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_set(ss21);
		std::set<std::string> std_set(sstd);

		EXPECT_TRUE(SetEqual(ss21, sstd));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		const s21::set<std::string> s21_set(ss21);
		const std::set<std::string> std_set(sstd);

		EXPECT_TRUE(SetEqual(ss21, sstd));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
}

TEST_F(SetTest, MoveCtor) {
	{
		s21::set<std::string> s21_empty_set;
		std::set<std::string> std_empty_set;
		s21::set<std::string> s21_set(std::move(s21_empty_set));
		std::set<std::string> std_set(std::move(std_empty_set));

		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		const s21::set<std::string> s21_empty_set;
		const std::set<std::string> std_empty_set;
		const s21::set<std::string> s21_set(std::move(s21_empty_set));
		const std::set<std::string> std_set(std::move(std_empty_set));

		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828) };
		std::set<std::string> std_tmp = { std::to_string(1828) };
		s21::set<std::string> s21_set(std::move(s21_tmp));
		std::set<std::string> std_set(std::move(std_tmp));

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828), "abc", "ABC" };
		std::set<std::string> std_tmp = { std::to_string(1828), "abc", "ABC" };
		s21::set<std::string> s21_set(std::move(s21_tmp));
		std::set<std::string> std_set(std::move(std_tmp));

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_set(std::move(ss21));
		std::set<std::string> std_set(std::move(sstd));

		EXPECT_TRUE(SetEqual(ss21, sstd));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		const s21::set<std::string> s21_set(std::move(ss21));
		const std::set<std::string> std_set(std::move(sstd));

		EXPECT_TRUE(SetEqual(ss21, sstd));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
}

TEST_F(SetTest, CopyOperatorAssign) {
	{
		s21::set<std::string> s21_empty_set;
		std::set<std::string> std_empty_set;
		s21::set<std::string> s21_set;
		std::set<std::string> std_set;

		s21_set = s21_empty_set;
		std_set = std_empty_set;

		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828) };
		std::set<std::string> std_tmp = { std::to_string(1828) };
		s21::set<std::string> s21_set;
		std::set<std::string> std_set;

		s21_set = s21_tmp;
		std_set = std_tmp;

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828), "abc", "ABC" };
		std::set<std::string> std_tmp = { std::to_string(1828), "abc", "ABC" };
		s21::set<std::string> s21_set = { "12345" };
		std::set<std::string> std_set = { "12345" };

		s21_set = s21_tmp;
		std_set = std_tmp;

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_set = { std::to_string(1828), "abc", "ABC" } ;
		std::set<std::string> std_set = { std::to_string(1828), "abc", "ABC" } ;

		s21_set = ss21;
		std_set = sstd;

		EXPECT_TRUE(SetEqual(ss21, sstd));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
		EXPECT_TRUE(SetEqual(s21_set, ss21));
	}

	{
		s21::set<std::string> s21_tmp = { std::to_string(1828), "abc", "ABC" };
		std::set<std::string> std_tmp = { std::to_string(1828), "abc", "ABC" };
		s21::set<std::string> s21_set = { "1234" } ;
		std::set<std::string> std_set = { "1234" } ;

		s21_set = ss21;
		std_set = sstd;

		EXPECT_TRUE(SetEqual(ss21, sstd));
		EXPECT_TRUE(SetEqual(s21_set, std_set));

		s21_set = s21_tmp;
		std_set = std_tmp;

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
		EXPECT_TRUE(SetEqual(s21_set, s21_tmp));
	}
}

TEST_F(SetTest, MoveOperatorAssign) {
	{
		s21::set<std::string> s21_empty_set;
		std::set<std::string> std_empty_set;
		s21::set<std::string> s21_set;
		std::set<std::string> std_set;

		s21_set = std::move(s21_empty_set);
		//std_set = std::move(std_empty_set);
		std_set.swap(std_empty_set);

		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828) };
		std::set<std::string> std_tmp = { std::to_string(1828) };
		s21::set<std::string> s21_set;
		std::set<std::string> std_set;

		s21_set = std::move(s21_tmp);
		//std_set = std::move(std_tmp);
		std_set.swap(std_tmp);

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828), "abc", "ABC" };
		std::set<std::string> std_tmp = { std::to_string(1828), "abc", "ABC" };
		s21::set<std::string> s21_set = { "12345" };
		std::set<std::string> std_set = { "12345" };

		s21_set = std::move(s21_tmp);
		//std_set = std::move(std_tmp);
		std_set.swap(std_tmp);

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_set = { std::to_string(1828), "abc", "ABC" } ;
		std::set<std::string> std_set = { std::to_string(1828), "abc", "ABC" } ;

		s21_set = std::move(ss21);
		//std_set = std::move(sstd);
		std_set.swap(sstd);

		EXPECT_TRUE(SetEqual(ss21, sstd));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
	{
		s21::set<std::string> s21_tmp = { std::to_string(1828), "abc", "ABC" };
		std::set<std::string> std_tmp = { std::to_string(1828), "abc", "ABC" };
		s21::set<std::string> s21_set = { "1234" } ;
		std::set<std::string> std_set = { "1234" } ;

		s21_set = std::move(ss21);
		//std_set = std::move(sstd);
		std_set.swap(sstd);

		EXPECT_TRUE(SetEqual(ss21, sstd));
		EXPECT_TRUE(SetEqual(s21_set, std_set));

		s21_set = std::move(s21_tmp);
		//std_set = std::move(std_tmp);
		std_set.swap(std_tmp);

		EXPECT_TRUE(SetEqual(s21_tmp, std_tmp));
		EXPECT_TRUE(SetEqual(s21_set, std_set));
	}
}

TEST_F(SetTest, Iterator) {
	{
		s21::set<std::string>::iterator s21_it = ss21.begin();
		std::set<std::string>::iterator std_it = sstd.begin();

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
		EXPECT_EQ(s21_it++->size(), std_it++->size());

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
		s21::set<std::string>::iterator s21_it = ss21.end();
		std::set<std::string>::iterator std_it = sstd.end();
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
		EXPECT_EQ(s21_it--->size(), std_it--->size());
	}
}

TEST_F(SetTest, ConstIterator) {
	const s21::set<std::string> css21 = ss21;
	const std::set<std::string> csstd = sstd;

	{
		s21::set<std::string>::const_iterator s21_it = css21.begin();
		std::set<std::string>::const_iterator std_it = csstd.begin();

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
		EXPECT_EQ(s21_it++->size(), std_it++->size());

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
		s21::set<std::string>::const_iterator s21_it = css21.end();
		std::set<std::string>::const_iterator std_it = csstd.end();
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
		EXPECT_EQ(s21_it->size(), std_it->size());
	}
}

TEST_F(SetTest, Capacity) {
	{
		s21::set<std::vector<double>> s21_s;
		std::set<std::vector<double>> std_s;

		EXPECT_EQ(s21_s.empty(), std_s.empty());
		EXPECT_EQ(s21_s.size(), std_s.size());
		EXPECT_EQ(s21_s.max_size(), std_s.max_size());
	}
	{
		s21::set<std::vector<double>> s21_s {
			std::vector<double>{1.0, 2.0}
		};
		std::set<std::vector<double>> std_s {
			std::vector<double>{1.0, 2.0}
		};

		EXPECT_EQ(s21_s.empty(), std_s.empty());
		EXPECT_EQ(s21_s.size(), std_s.size());
		EXPECT_EQ(s21_s.max_size(), std_s.max_size());
	}
	{
		s21::set<std::vector<double>> s21_s {
			std::vector<double>{1.0, 2.0},
			std::vector<double>{10.0, 20.0},
			std::vector<double>{100.0, 200.0}
		};
		std::set<std::vector<double>> std_s {
			std::vector<double>{1.0, 2.0},
			std::vector<double>{10.0, 20.0},
			std::vector<double>{100.0, 200.0}
		};

		EXPECT_EQ(s21_s.empty(), std_s.empty());
		EXPECT_EQ(s21_s.size(), std_s.size());
		EXPECT_EQ(s21_s.max_size(), std_s.max_size());
	}
	{
		EXPECT_EQ(ss21.empty(), sstd.empty());
		EXPECT_EQ(ss21.size(), sstd.size());
		EXPECT_EQ(ss21.max_size(), sstd.max_size());
	}
	{
		const s21::set<std::string> css21 = ss21;
		const std::set<std::string> csstd = sstd;

		EXPECT_EQ(css21.empty(), csstd.empty());
		EXPECT_EQ(css21.size(), csstd.size());
		EXPECT_EQ(css21.max_size(), csstd.max_size());
	}
}

TEST_F(SetTest, Clear) {
	{
		s21::set<std::string> s_s21;
		std::set<std::string> s_std;

		s_s21.clear();
		s_std.clear();

		EXPECT_TRUE(SetEqual(s_s21, s_std));
	}
	{
		s21::set<std::string> s_s21 = ss21;
		std::set<std::string> s_std = sstd;

		s_s21.clear();
		s_std.clear();

		EXPECT_TRUE(SetEqual(s_s21, s_std));
	}
	{
		s21::set<std::string> s_s21;
		std::set<std::string> s_std;

		for (int i = 0; i < 10000; ++i) {
			s_s21.insert(std::to_string(i));
			s_std.insert(std::to_string(i));
		}

		s_s21.clear();
		s_std.clear();

		EXPECT_TRUE(SetEqual(s_s21, s_std));
	}
}

TEST_F(SetTest, Insert) {
	s21::set<double> s_s21;
	std::set<double> s_std;

	for (int i = 0; i < 100000; ++i) {
		int key = rand() / 100000;
		auto ps21 = s_s21.insert(static_cast<double>(key));
		auto pstd = s_std.insert(static_cast<double>(key));

		EXPECT_EQ(*ps21.first, *pstd.first);
		EXPECT_EQ(ps21.second, pstd.second);
	}

	EXPECT_TRUE(SetEqual(s_s21, s_std));
}

TEST_F(SetTest, Erase) {
	s21::set<int> s_s21;
	std::set<int> s_std;

	for (int i = 0; i < 100000; ++i) {
		int key = rand() / 100000;
		auto ps21 = s_s21.insert(key);
		auto pstd = s_std.insert(key);

		EXPECT_EQ(*ps21.first, *pstd.first);
		EXPECT_EQ(ps21.second, pstd.second);
	}

	for (int i = 0; i < 100000; ++i) {
		int key = rand() / 100000;
		auto it_s21 = s_s21.find(key);
		auto it_std = s_std.find(key);

		if (it_std != s_std.end()) {
			EXPECT_NE(it_s21, s_s21.end());
			s_s21.erase(it_s21);
			s_std.erase(it_std);
		} else {
			EXPECT_EQ(it_s21, s_s21.end());
		}
	}

	EXPECT_TRUE(SetEqual(s_s21, s_std));
}

TEST_F(SetTest, SieveOfEratosthenes) {
	s21::set<int> s_s21;
	std::set<int> s_std;

	for (int i = 2; i < 1000000; ++i) {
		auto ps21 = s_s21.insert(i);
		auto pstd = s_std.insert(i);

		EXPECT_EQ(*ps21.first, *pstd.first);
		EXPECT_EQ(ps21.second, pstd.second);
	}

	for (int i = 2; i <= 1000; ++i) {
		auto it_s21 = s_s21.begin();
		auto it_std = s_std.begin();
		while (it_s21 != s_s21.end()) {
			if (*it_s21 % i == 0) {
				s_s21.erase(it_s21++);
				s_std.erase(it_std++);
			} else {
				++it_s21;
				++it_std;
			}
		}
	}

	EXPECT_TRUE(SetEqual(s_s21, s_std));
}

TEST_F(SetTest, Swap) {
	s21::set<std::string> s_s21 = { "123", "abc", "q" };
	std::set<std::string> s_std = { "123", "abc", "q" };

	s_s21.swap(ss21);
	s_std.swap(sstd);

	EXPECT_TRUE(SetEqual(s_s21, s_std));
	EXPECT_TRUE(SetEqual(ss21, sstd));
}

TEST_F(SetTest, Merge) {
	{
		s21::set<std::string> s_s21 = { "123", "abc", "q" };
		s21::set<std::string> source_s21 =
			{ "0", "123", "abc", "q", "qwerty", "90" };
		std::set<std::string> s_std = { "123", "abc", "q" };
		std::set<std::string> source_std =
			{ "0", "123", "abc", "q", "qwerty", "90" };

		s_s21.merge(source_s21);
		s_std.merge(source_std);

		EXPECT_TRUE(SetEqual(s_s21, s_std));
		EXPECT_TRUE(SetEqual(source_s21, source_std));
	}
	{
		s21::set<std::string> s_s21 = ss21;
		s21::set<std::string> source_s21 =
			{ "0", "123", "abc", "q", "qwerty", "90" };
		std::set<std::string> s_std = sstd;
		std::set<std::string> source_std =
			{ "0", "123", "abc", "q", "qwerty", "90" };

		s_s21.merge(source_s21);
		s_std.merge(source_std);

		EXPECT_TRUE(SetEqual(s_s21, s_std));
		EXPECT_TRUE(SetEqual(source_s21, source_std));
	}
}

TEST_F(SetTest, Find) {
	s21::set<int> s_s21;
	std::set<int> s_std;

	for (int i = 0; i < 1000000; ++i) {
		int key = rand() / 100000;
		s_s21.insert(key);
		s_std.insert(key);
	}

	for (int i = 0; i < 100000; ++i) {
		int key = rand() / 100000;
		auto it1 = s_s21.find(key);
		auto it2 = s_std.find(key);
		if (it2 != s_std.end()) {
			EXPECT_EQ(*it1, *it2);
		} else {
			EXPECT_EQ(it1, s_s21.end());
		}
	}
}

TEST_F(SetTest, ConstFind) {
	s21::set<int> s_s21;
	std::set<int> s_std;

	for (int i = 0; i < 1000000; ++i) {
		int key = rand() / 100000;
		s_s21.insert(key);
		s_std.insert(key);
	}

	const s21::set<int> cs_s21 = std::move(s_s21);
	const std::set<int> cs_std = std::move(s_std);

	for (int i = 0; i < 100000; ++i) {
		int key = rand() / 100000;
		auto it1 = cs_s21.find(key);
		auto it2 = cs_std.find(key);
		if (it2 != cs_std.end()) {
			EXPECT_EQ(*it1, *it2);
		} else {
			EXPECT_EQ(it1, cs_s21.end());
		}
	}
}

TEST_F(SetTest, Contains) {
	s21::set<int> s_s21;
	std::set<int> s_std;

	for (int i = 0; i < 1000000; ++i) {
		int key = rand() / 100000;
		s_s21.insert(key);
		s_std.insert(key);
	}

	const s21::set<int> cs_s21 = std::move(s_s21);
	const std::set<int> cs_std = std::move(s_std);

	for (int i = 0; i < 100000; ++i) {
		int key = rand() / 100000;
		bool res_s21 = cs_s21.contains(key);
		auto it = cs_std.find(key);
		bool res_std = (it != cs_std.end());
		EXPECT_EQ(res_s21, res_std);
	}
}
