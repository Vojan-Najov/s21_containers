#include "gtest/gtest.h"
#include "s21_list.h"

#include <cstdlib>
#include <vector>
#include <list>

class ListTest : public ::testing::Test {
 protected:
  void SetUp(void) override {
    std::srand(1);

    for (int i = 0; i < 10000; ++i) {
      int value = std::rand();
      l.push_back(value);
      s.push_back(value);
    }

    ll.push_back(v1); ll.push_back(v2);
    ss.push_back(v1); ss.push_back(v2);
  }
  template <typename T>
  void EqualList(s21::list<T> &lhs, std::list<T> &rhs) {
    EXPECT_EQ(lhs.size(), rhs.size());
    
    auto lhs_it = lhs.begin();
    auto lhs_last = lhs.end();
    auto rhs_it = rhs.begin();
    while (lhs_it != lhs_last) {
      EXPECT_EQ(*lhs_it, *rhs_it);
      ++lhs_it;
      ++rhs_it;
    }
  }

  s21::list<int> l; // size is 10000
  std::list<int> s; // size is 10000

  std::vector<int> v1 = {0, 1, 2, 3, 4 , 5, 6, 7, 8, 9};
  std::vector<int> v2{100, 1};

  s21::list<std::vector<int>> ll; // size is 2;
  std::list<std::vector<int>> ss; // size is 2
};

TEST_F(ListTest, DefaultCtor) {
  s21::list<int> l;
  EXPECT_TRUE(l.empty());
  EXPECT_EQ(l.size(), 0);

  const s21::list<int> cl;
  EXPECT_TRUE(cl.empty());
  EXPECT_EQ(cl.size(), 0);
}

TEST_F(ListTest, CastCtor) {
  s21::list<int> l1(0);
  EXPECT_TRUE(l1.empty());
  EXPECT_EQ(l1.size(), 0);

  s21::list<int> l2(10);
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(l2.size(), 10);

  s21::list<std::vector<int>> l3(14);
  EXPECT_FALSE(l3.empty());
  EXPECT_EQ(l3.size(), 14);

  const s21::list<int> l4(10);
  EXPECT_FALSE(l4.empty());
  EXPECT_EQ(l4.size(), 10);
}

TEST_F(ListTest, InitCtor) {
  s21::list<int> l1 = {};
  EXPECT_TRUE(l1.empty());
  EXPECT_EQ(l1.size(), 0);

  s21::list<int> l2 = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9};
  EXPECT_FALSE(l2.empty());
  EXPECT_EQ(l2.size(), 10);

  std::vector<int> v1(10);
  std::vector<int> v2 = {1, 2, 3};
  s21::list<std::vector<int>> l3 = {v1, v2};
  EXPECT_FALSE(l3.empty());
  EXPECT_EQ(l3.size(), 2);

  const s21::list<int> l4 = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9};
  EXPECT_FALSE(l4.empty());
  EXPECT_EQ(l4.size(), 10);
}

TEST_F(ListTest, CopyCtor) {
  {
    s21::list<int> copy = {};
    s21::list<int> l(copy);
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0);
  }
  {
    s21::list<int> copy = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9};
    s21::list<int> l(copy);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 10);
  }
  {
    std::vector<int> v1(10);
    std::vector<int> v2 = {1, 2, 3};
    s21::list<std::vector<int>> copy = {v1, v2};
    s21::list<std::vector<int>> l(copy);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 2);
  }
  {
    const s21::list<int> copy = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9};
    const s21::list<int> l(copy);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 10);
  }
}

TEST_F(ListTest, MoveCtor) {
  {
    s21::list<int> copy = {};
    s21::list<int> l(std::move(copy));
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0);
  }
  {
    s21::list<int> copy = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9};
    s21::list<int> l(std::move(copy));
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 10);
  }
  {
    std::vector<int> v1(10);
    std::vector<int> v2 = {1, 2, 3};
    s21::list<std::vector<int>> copy = {v1, v2};
    s21::list<std::vector<int>> l(std::move(copy));
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 2);
  }
  {
    s21::list<int> copy = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9};
    const s21::list<int> l(std::move(copy));
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 10);
  }
}

TEST_F(ListTest, CopyOperatorAssign) {
  {
    s21::list<int> copy = {};
    s21::list<int> l = {1, 2};
    l = copy;
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0);
  }
  {
    s21::list<int> copy = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9};
    s21::list<int> l = {1, 2};
    l = copy;
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 10);
  }
  {
    std::vector<int> v1(10);
    std::vector<int> v2 = {1, 2, 3};
    s21::list<std::vector<int>> copy = {v1, v2};
    s21::list<std::vector<int>> l;
    l = copy;
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 2);
  }
}

TEST_F(ListTest, MoveOperatorAssign) {
  {
    s21::list<int> copy = {};
    s21::list<int> l = {1, 2};
    l = std::move(copy);
    EXPECT_TRUE(l.empty());
    EXPECT_EQ(l.size(), 0);
  }
  {
    s21::list<int> copy = {0, 1, 2, 3, 4, 5, 6, 7 ,8 , 9};
    s21::list<int> l = {1, 2};
    l = std::move(copy);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 10);
  }
  {
    std::vector<int> v1(10);
    std::vector<int> v2 = {1, 2, 3};
    s21::list<std::vector<int>> copy = {v1, v2};
    s21::list<std::vector<int>> l;
    l = std::move(copy);
    EXPECT_FALSE(l.empty());
    EXPECT_EQ(l.size(), 2);
  }
}

TEST_F(ListTest, ElementAccess) {
  EXPECT_EQ(l.front(), s.front());
  EXPECT_EQ(l.back(), s.back());

  EXPECT_EQ(ll.front(), ss.front());
  EXPECT_EQ(ll.back(), ss.back());

  const s21::list<int> cl = l;
  const std::list<int> cs = s;
  const s21::list<std::vector<int>> cll = ll;
  const std::list<std::vector<int>> css = ss;
 
  EXPECT_EQ(cl.front(), cs.front());
  EXPECT_EQ(cl.back(), cs.back());

  EXPECT_EQ(cll.front(), css.front());
  EXPECT_EQ(cll.back(), css.back());
}

TEST_F(ListTest, Iterators) {
  {
    auto lit = l.begin();
    auto lend = l.end();
    auto sit = s.begin();
    auto send = s.end();
    while (sit != send) {
      EXPECT_EQ(*lit, *sit);
      ++lit; ++sit;
    }
    EXPECT_EQ(lit, lend);

    auto llit = ll.begin();
    auto llend = ll.end();
    auto ssit = ss.begin();
    auto ssend = ss.end();
    while (ssit != ssend) {
      EXPECT_EQ(*llit++, *ssit++);
    }
    EXPECT_EQ(llit, llend);
  }
  {
    auto lit = l.end();
    auto lfirst = l.begin();
    auto sit = s.end();
    auto sfirst = s.begin();
    while (sit != sfirst) {
      EXPECT_EQ(*--lit, *--sit);
    }
    EXPECT_EQ(lit--, lfirst);
    EXPECT_EQ(lit, l.end());

    auto llit = ll.begin();
    auto llend = ll.end();
    auto ssit = ss.begin();
    auto ssend = ss.end();
    while (ssit != ssend) {
      EXPECT_EQ(llit->size(), ssit->size());
      ++llit; ++ssit;
    }
    EXPECT_EQ(llit, llend);
  }
}

TEST_F(ListTest, ConstIterators) {
  s21::list<int> cl = l;
  std::list<int> cs = s;
  s21::list<std::vector<int>> cll = ll;
  std::list<std::vector<int>> css = ss;
  {
    auto lit = cl.cbegin();
    auto lend = cl.cend();
    auto sit = cs.cbegin();
    auto send = cs.cend();
    while (sit != send) {
      EXPECT_EQ(*lit, *sit);
      ++lit; ++sit;
    }
    EXPECT_EQ(lit, lend);

    auto llit = cll.begin();
    auto llend = cll.end();
    auto ssit = css.begin();
    auto ssend = css.end();
    while (ssit != ssend) {
      EXPECT_EQ(*llit++, *ssit++);
    }
    EXPECT_EQ(llit, llend);
  }
  {
    auto lit = cl.cend();
    auto lfirst = cl.cbegin();
    auto sit = cs.cend();
    auto sfirst = cs.cbegin();
    while (sit != sfirst) {
      EXPECT_EQ(*--lit, *--sit);
    }
    EXPECT_EQ(lit--, lfirst);
    EXPECT_EQ(lit, cl.end());

    auto llit = cll.cbegin();
    auto llend = cll.cend();
    auto ssit = css.cbegin();
    auto ssend = css.cend();
    while (ssit != ssend) {
      EXPECT_EQ(llit->size(), ssit->size());
      ++llit; ++ssit;
    }
    EXPECT_EQ(llit, llend);
  }
}

TEST_F(ListTest, Capacity) {
  s21::list<int> cl = l;
  std::list<int> cs = s;
  s21::list<std::vector<int>> cll = ll;
  std::list<std::vector<int>> css = ss;

  EXPECT_EQ(l.empty(), s.empty());
  EXPECT_EQ(ll.empty(), ss.empty());
  EXPECT_EQ(cl.empty(), cs.empty());
  EXPECT_EQ(cll.empty(), css.empty());

  EXPECT_EQ(l.size(), s.size());
  EXPECT_EQ(ll.size(), ss.size());
  EXPECT_EQ(cl.size(), cs.size());
  EXPECT_EQ(cll.size(), css.size());

  EXPECT_EQ(l.max_size(), s.max_size());
  EXPECT_EQ(ll.max_size(), ss.max_size());
  EXPECT_EQ(cl.max_size(), cs.max_size());
  EXPECT_EQ(cll.max_size(), css.max_size());
}

TEST_F(ListTest, Clear) {
  l.clear();
  s.clear();
  ll.clear();
  ss.clear();
  EXPECT_EQ(l.empty(), s.empty());
  EXPECT_EQ(ll.empty(), ss.empty());
  EXPECT_EQ(l.size(), s.size());
  EXPECT_EQ(ll.size(), ss.size());
}

TEST_F(ListTest, Insert) {
  int value = std::rand();
  l.insert(l.begin(), value);
  s.insert(s.begin(), value);
  value = std::rand();
  l.insert(++l.begin(), value);
  s.insert(++s.begin(), value);
  value = std::rand();
  l.insert(++(++l.begin()), value);
  s.insert(++(++s.begin()), value);
  value = std::rand();
  l.insert(++l.begin(), value);
  s.insert(++s.begin(), value);
  value = std::rand();
  l.insert(l.end(), value);
  s.insert(s.end(), value);
  value = std::rand();
  l.insert(--(--l.end()), value);
  s.insert(--(--s.end()), value);
  value = std::rand();
  l.insert(--(--l.end()), value);
  s.insert(--(--s.end()), value);
  EqualList(l, s);

  s21::list<double> l1;
  std::list<double> l2;
  value = rand();
  l1.insert(l1.begin(), value);
  l2.insert(l2.begin(), value);
  l1.clear(); l2.clear();
  value = rand();
  l1.insert(l1.end(), value);
  l2.insert(l2.end(), value);
  l1.insert(l1.begin(), value);
  l2.insert(l2.begin(), value);
  l1.insert(++l1.begin(), value);
  l2.insert(++l2.begin(), value);
  EqualList(l, s);
}

TEST_F(ListTest, Erase) {
  l.erase(l.begin());
  s.erase(s.begin());
  EqualList(l, s);

  l.erase(--l.end());
  s.erase(--s.end());
  EqualList(l, s);

  auto lit = l.begin();
  auto sit = s.begin();
  for (int i = 0; i < 5; ++i) {
    ++lit; ++sit;
  }
  l.erase(lit);
  s.erase(sit);
  EqualList(l, s);

  l.erase(l.begin());
  s.erase(s.begin());
  EqualList(l, s);

  ll.erase(ll.begin());
  ss.erase(ss.begin());
  EqualList(l, s);
  ll.insert(ll.end(), v2);
  ss.insert(ss.end(), v2);
  ll.erase(--ll.end());
  ss.erase(--ss.end());
  EqualList(l, s);
}

TEST_F(ListTest, PushPopBack) {
  s21::list<int> l;
  std::list<int> s;

  for (size_t i = 0; i < 10000; ++i) {
    int value = std::rand();
    l.push_back(value);
    s.push_back(value);
    if (i % 2) {
      l.pop_back();
      s.pop_back();
    }
  }

  EqualList(l, s);

  ll.push_back(v1);
  ss.push_back(v1);
  ll.push_back(v2);
  ss.push_back(v2);
  ll.pop_back();
  ss.pop_back();

  EqualList(ll, ss);
}

TEST_F(ListTest, PushPopFront) {
  s21::list<int> l;
  std::list<int> s;

  for (size_t i = 0; i < 10000; ++i) {
    int value = std::rand();
    l.push_front(value);
    s.push_front(value);
    if (i % 2) {
      l.pop_front();
      s.pop_front();
    }
  }

  EqualList(l, s);

  ll.push_front(v1);
  ss.push_front(v1);
  ll.push_front(v2);
  ss.push_front(v2);
  ll.pop_front();
  ss.pop_front();

  EqualList(ll, ss);
}

TEST_F(ListTest, Swap) {
  s21::list<int> l1;
  s21::list<int> l2;
  std::list<int> s1;
  std::list<int> s2;

  for (size_t i = 0; i < 1000; ++i) {
    int value = std::rand();
    l1.push_front(value);
    s1.push_front(value);
    value = std::rand();
    l2.push_front(value);
    s2.push_front(value);
  }

  EqualList(l1, s1);
  EqualList(l2, s2);
  l1.swap(l2);
  s1.swap(s2);
  EqualList(l1, s1);
  EqualList(l2, s2);
}

TEST_F(ListTest, Merge) {
  int size1 = 1000, size2 = 2000;
  int size3 = 3000, size4 = 4000;
  s21::list<int> l1;
  s21::list<int> l2;
  std::list<int> s1;
  std::list<int> s2;

  for (int i = 0; i < size1; ++i) {
    if (i % 2 == 0) {
      l1.push_back(i);
      s1.push_back(i);
    } else {
      l2.push_back(i);
      s2.push_back(i);
    }
  }
  for (int i = size1; i < size2; ++i) {
    if (i % 3 == 0) {
      l1.push_back(i);
      s1.push_back(i);
    } else {
      l2.push_back(i);
      s2.push_back(i);
    }
  }
  for (int i = size2; i < size3; ++i) {
    if (i % 4) {
      l1.push_back(i);
      s1.push_back(i);
    } else {
      l2.push_back(i);
      s2.push_back(i);
    }
  }
  for (int i = size3; i < size4; ++i) {
    l2.push_back(i);
    s2.push_back(i);
  }
 
  l1.merge(l2);
  s1.merge(s2);
  EqualList(l1, s1);
  EqualList(l2, s2);

  l1.merge(l2);
  s1.merge(s2);
  EqualList(l1, s1);
  EqualList(l2, s2);

  l2.merge(l1);
  s2.merge(s1);
  EqualList(l1, s1);
  EqualList(l2, s2);
}

TEST_F(ListTest, Splice) {
  s21::list<int> l;
  std::list<int> s;
  s21::list<int> ll;
  std::list<int> ss;

  for(int i = 0; i < 1000; ++i) {
    int value = rand();
    ll.push_back(value);
    ss.push_back(value);
  }
  l.splice(l.cbegin(), ll);
  s.splice(s.cbegin(), ss);
  EqualList(l, s);
  EqualList(ll, ss);

  for(int i = 0; i < 1000; ++i) {
    int value = rand();
    ll.push_back(value);
    ss.push_back(value);
  }
  auto lit = l.cbegin();
  auto sit = s.cbegin();
  std::advance(lit, 500);
  std::advance(sit, 500);
  l.splice(lit, ll);
  s.splice(sit, ss);
  EqualList(l, s);
  EqualList(ll, ss);
}




/*
TEST(tmp, tmp8) {
	s21::list<int> l1 = {1, 2, 3, 4, 5, 6};
	const s21::list<int> l2 = {-1, -2, -3};

	EXPECT_EQ(l1.front(), 1);
	EXPECT_EQ(l2.front(), -1);
	EXPECT_EQ(l1.back(), 6);
	EXPECT_EQ(l2.back(), -3);
}

TEST(tmp, tmp9) {
	int a[] = {1, 2, 3, 4, 5, 6};
	s21::list<int> l = {1, 2, 3, 4, 5, 6};

	for (int i = 5; i >= 0; --i) {
		EXPECT_EQ(l.back(), a[i]);
		l.pop_back();
		EXPECT_EQ(l.size(), i);
    }
}

TEST(tmp, tmp10) {
	int a[] = {1, 2, 3, 4, 5, 6};
	s21::list<int> l = {1, 2, 3, 4, 5, 6};

	for (size_t i = 0; i < 6; ++i) {
		EXPECT_EQ(l.front(), a[i]);
		l.pop_front();
		EXPECT_EQ(l.size(), (size_t) 5 - i);
    }
}

TEST(tmp, tmp11) {
	int a[] = {1, 2, 3, 4, 5, 6};
	s21::list<int> l = {1, 2, 3, 4, 5, 6};

	int i = 0;
	s21::list<int>::iterator it = l.begin();
	while (it != l.end()) {
		EXPECT_EQ(*it,  a[i++]);
		++it;
	}
}

TEST(tmp, tmp12) {
	int a[] = {1, 2, 3, 4, 5, 6};
	s21::list<int> l = {1, 2, 3, 4, 5, 6};

	int i = 6;
	l.reverse();
	s21::list<int>::iterator it = l.begin();
	while (it != l.end()) {
		EXPECT_EQ(*it,  a[--i]);
		++it;
	}
}

TEST(tmp, tmp13) {
	int a[] = {1, 2, 3, 4, 5, 6};
	s21::list<int> l = {1, 1, 2, 3, 3, 3, 4, 4, 4, 4, 5, 6, 6};

	int i = 0;
	l.unique();
	s21::list<int>::iterator it = l.begin();
	while (it != l.end()) {
		EXPECT_EQ(*it,  a[i++]);
		++it;
	}
}

TEST(tmp, tmp14) {
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	s21::list<int> l1 = {1, 3, 6};
	s21::list<int> l2 = {2, 4, 5, 7, 8, 9};

	int i = 0;
	l1.merge(l2);
	s21::list<int>::iterator it = l1.begin();
	while (it != l1.end()) {
		EXPECT_EQ(*it,  a[i++]);
		++it;
	}
}

TEST(tmp, tmp16) {
	s21::list<int> l = {6, 1, 4, 2, 3, 5, 8, 9, 7};

	int i = 0;
	l.sort();
	s21::list<int>::iterator it = l.begin();
	while (it != l.end()) {
		EXPECT_EQ(*it,  ++i);
		++it;
	}
}
*/

