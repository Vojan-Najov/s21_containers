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
