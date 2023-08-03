#include "s21_set.h"

#include <string>
#include <set>
#include <algorithm>
#include <cstdlib>

#include <gtest/gtest.h>

class SetTest : public ::testing::Test {
 public:
	void SetUp(void) override {
		int set_size = 1000;

		std::srand(42);
		for (int i = 0; i < set_size; ++i) {
			int key = rand();
			std::string value = std::to_string(key + i);
			ss21.insert(value);
			sstd.insert(value);
		}
	}

	template <typename Key>
	bool SetEqual(const s21::set<Key>&lhs, const s21::set<Key> rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
					 std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
	}
	template <typename Key>
	bool SetEqual(const s21::set<Key>&lhs, const std::set<Key> rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
					 std::equal(lhs.cbegin(), lhs.cend(), rhs.cbegin());
	}
	template <typename Key>
	bool SetEqual(const std::set<Key>&lhs, const s21::set<Key> rhs) {
		return lhs.empty() == rhs.empty() &&
					 lhs.size() == rhs.size() &&
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
