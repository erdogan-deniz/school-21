#include <list>
#include <queue>
#include <stack>

#include "s21_containers.h"

// // TEST
// //
// VECTOR----------------------------------------------------------------------------------------------------------

TEST(VectorTest, DefaultConstructor) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, ParameterizedConstructor) {
  s21::vector<int> s21_v(4);
  std::vector<int> std_v(4);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, InitializerListConstructor) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};
  EXPECT_EQ(s21_v.size(), std_v.size());
  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

TEST(VectorTest, CopyConstructor) {
  s21::vector<int> s21_v1 = {1, 2, 3};
  s21::vector<int> s21_v2(s21_v1);
  std::vector<int> std_v1 = {1, 2, 3};
  std::vector<int> std_v2(std_v1);
  EXPECT_EQ(s21_v1.size(), std_v1.size());
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  for (size_t i = 0; i < s21_v1.size(); ++i) {
    EXPECT_EQ(s21_v1[i], std_v1[i]);
    EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
}

TEST(VectorTest, MoveConstructor) {
  s21::vector<int> s21_v1 = {1, 2, 3};
  s21::vector<int> s21_v2 = std::move(s21_v1);
  std::vector<int> std_v1 = {1, 2, 3};
  std::vector<int> std_v2 = std::move(std_v1);
  EXPECT_EQ(s21_v1.size(), static_cast<size_t>(0));
  EXPECT_EQ(std_v1.size(), static_cast<size_t>(0));
  EXPECT_EQ(s21_v2.size(), std_v2.size());
  for (size_t i = 0; i < s21_v2.size(); ++i) {
    EXPECT_EQ(s21_v2[i], std_v2[i]);
  }
}

TEST(VectorTest, Insert) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  auto s21_it = s21_v.insert(s21_v.begin() + 1, 4);
  auto std_it = std_v.insert(std_v.begin() + 1, 4);

  EXPECT_EQ(*s21_it, *std_it);
  EXPECT_EQ(s21_v.size(), std_v.size());

  for (size_t i = 0; i < s21_v.size(); ++i) {
    EXPECT_EQ(s21_v[i], std_v[i]);
  }
}

// TEST(VectorTest, Erase) {
//   s21::vector<int> s21_v{1, 2, 3};
//   std::vector<int> std_v{1, 2, 3};
//   auto s21_it = s21_v.erase(s21_v.begin() + 1);
//   auto std_it = std_v.erase(std_v.begin() + 1);

//   EXPECT_EQ(*s21_it, *std_it);
//   EXPECT_EQ(s21_v.size(), std_v.size());
//   s21_it = s21_v.erase(s21_v.begin() + 1, s21_v.end());
//   std_it = std_v.erase(std_v.begin() + 1, std_v.end());

//   EXPECT_EQ(s21_it, s21_v.end());
//   EXPECT_EQ(std_it, std_v.end());
//   EXPECT_EQ(s21_v.size(), std_v.size());
// }

TEST(VectorTest, PushBack) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  for (int i = 1; i <= 3; ++i) {
    s21_v.push_back(i);
    std_v.push_back(i);

    EXPECT_EQ(s21_v.size(), std_v.size());
    EXPECT_EQ(s21_v.back(), std_v.back());
  }
}

TEST(VectorTest, PopBack) {
  s21::vector<int> s21_v = {1, 2, 3};
  std::vector<int> std_v = {1, 2, 3};

  for (int i = 3; i >= 1; --i) {
    s21_v.pop_back();
    std_v.pop_back();

    EXPECT_EQ(s21_v.size(), std_v.size());
  }

  EXPECT_TRUE(s21_v.empty());
  EXPECT_TRUE(std_v.empty());
}

TEST(VectorTest, Swap) {
  s21::vector<int> s21_v1 = {1, 2, 3};
  s21::vector<int> s21_v2 = {4, 5};
  std::vector<int> std_v1 = {1, 2, 3};
  std::vector<int> std_v2 = {4, 5};
  size_t s21_v1_size_before_swap = s21_v1.size();
  size_t s21_v2_size_before_swap = s21_v2.size();

  s21_v1.swap(s21_v2);

  EXPECT_EQ(s21_v1.size(), s21_v2_size_before_swap);
  EXPECT_EQ(s21_v2.size(), s21_v1_size_before_swap);

  auto it1 = s21_v1.begin();
  auto it2 = s21_v2.begin();
  auto it3 = std_v1.begin();
  auto it4 = std_v2.begin();

  while (it1 != s21_v1.end()) {
    EXPECT_EQ(*it1, *it4);
    ++it1, ++it4;
  }

  while (it2 != s21_v2.end()) {
    EXPECT_EQ(*it2, *it3);
    ++it2, ++it3;
  }
}

// // TEST
// //
// ARRAY----------------------------------------------------------------------------------------------------------

TEST(MultisetTest, DefaultConstructor) {
  s21::multiset<int> ms;

  EXPECT_EQ(ms.size(), 0);
  EXPECT_TRUE(ms.empty());
}

TEST(MultisetTest, InitializerListConstructor) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_EQ(ms.size(), 4);
}

TEST(MultisetTest, CopyConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(ms1);

  EXPECT_EQ(ms2.size(), 3);
}

TEST(MultisetTest, MoveConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(std::move(ms1));

  EXPECT_EQ(ms2.size(), 3);
}

TEST(MultisetTest, Destructor) { s21::multiset<int> ms = {1, 2, 3}; }

TEST(MultisetTest, MoveAssignmentOperator) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2;
  ms2 = std::move(ms1);

  EXPECT_EQ(ms2.size(), 3);
}

TEST(MultisetTest, BeginEnd) {
  s21::multiset<int> ms = {1, 2, 3};

  int i = 1;
  for (auto it = ms.begin(); it != ms.end(); ++it) {
    EXPECT_EQ(*it, i);
    ++i;
  }
}

TEST(MultisetTest, Empty) {
  s21::multiset<int> ms;

  EXPECT_TRUE(ms.empty());

  ms.insert(1);

  EXPECT_FALSE(ms.empty());
}

TEST(MultisetTest, Size) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_EQ(ms.size(), 4);

  ms.erase(ms.begin());

  EXPECT_EQ(ms.size(), 3);
}

TEST(MultisetTest, MaxSize) {
  s21::multiset<int> ms;

  EXPECT_EQ(ms.max_size(), std::numeric_limits<size_t>::max());
}

TEST(MultisetTest, Clear) {
  s21::multiset<int> ms = {1, 2, 3};
  ms.clear();

  EXPECT_TRUE(ms.empty());
}

TEST(MultisetTest, Insert) {
  s21::multiset<int> ms;
  auto it = ms.insert(10);

  EXPECT_EQ(*it, 10);

  it = ms.insert(20);
  it = ms.insert(30);

  EXPECT_EQ(*it, 30);
}

TEST(MultisetTest, Erase) {
  s21::multiset<int> ms = {1, 2, 2, 3};
  ms.erase(ms.begin());

  EXPECT_EQ(ms.size(), 3);

  ms.erase(ms.find(2));

  EXPECT_EQ(ms.size(), 2);
}

TEST(MultisetTest, Swap) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {4, 5, 6};

  ms1.swap(ms2);

  EXPECT_EQ(ms1.size(), 3);
  EXPECT_EQ(ms2.size(), 3);
}

TEST(MultisetTest, Merge) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {4, 5, 6};

  ms1.merge(ms2);

  EXPECT_EQ(ms1.size(), 6);
  EXPECT_EQ(ms2.size(), 0);
}

TEST(MultisetTest, Count) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(4), 0);
  EXPECT_EQ(ms.count(1), 1);
  EXPECT_EQ(ms.count(3), 1);
}

TEST(MultisetTest, Find) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  auto it = ms.find(2);
  EXPECT_EQ(*it, 2);

  it = ms.find(4);
  EXPECT_EQ(it, ms.end());
}

TEST(MultisetTest, Contains) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

TEST(MultiSetTest, EqualRange) {
  s21::multiset<int> ms;
  ms.insert(1);
  ms.insert(2);
  ms.insert(2);
  ms.insert(3);
  ms.insert(4);

  auto range1 = ms.equal_range(5);
  EXPECT_EQ(range1.first, range1.second);
  EXPECT_EQ(range1.first, ms.end());

  auto range2 = ms.equal_range(2);
  EXPECT_EQ(*range2.first, 2);
  EXPECT_EQ(*range2.second, 3);

  s21::multiset<int> empty_ms;
  auto range3 = empty_ms.equal_range(1);
  EXPECT_EQ(range3.first, range3.second);
}

TEST(MultisetTest, LowerBound) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  auto it = ms.lower_bound(2);
  EXPECT_EQ(*it, 2);

  it = ms.lower_bound(4);
  EXPECT_EQ(it, ms.end());
}

TEST(MultisetTest, UpperBound) {
  s21::multiset<int> ms = {1, 2, 2, 3};

  auto it = ms.upper_bound(2);
  EXPECT_EQ(*it, 3);

  it = ms.upper_bound(4);
  EXPECT_EQ(it, ms.end());
}

TEST(InsertManyTest, InsertMultipleElements) {
  s21::multiset<int> ms;
  insert_many(ms, 4, 2, 6, 2, 8);
  std::vector<int> expected = {2, 2, 4, 6, 8};
  ASSERT_EQ(ms.size(), expected.size());
  for (const auto &elem : expected) {
    ASSERT_TRUE(ms.contains(elem));
  }
}

TEST(InsertManyTest, InsertElementsOfDifferentTypes) {
  s21::multiset<std::string> ms;
  insert_many(ms, "cat", "dog", "elephant");
  std::vector<std::string> expected = {"cat", "dog", "elephant"};
  ASSERT_EQ(ms.size(), expected.size());
  for (const auto &elem : expected) {
    ASSERT_TRUE(ms.contains(elem));
  }
}

TEST(InsertManyTest, InsertSingleElement) {
  s21::multiset<double> ms;
  double num = 3.14;
  insert_many(ms, num);
  ASSERT_EQ(ms.size(), 1);
  ASSERT_TRUE(ms.contains(num));
}

TEST(InsertManyTest, InsertEmptyArguments) {
  s21::multiset<int> ms;
  insert_many(ms);
  ASSERT_EQ(ms.size(), 0);
}

// // TEST
// //
// ARRAY----------------------------------------------------------------------------------------------------------

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 3> arr = {1, 2, 3};
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(3, arr.size());
}

TEST(ArrayTest, ListConstructor) {
  s21::array<int, 5> arr = {1, 2, 3, 4, 5};
  EXPECT_FALSE(arr.empty());
  EXPECT_EQ(5, arr.size());
  EXPECT_EQ(1, arr.front());
  EXPECT_EQ(5, arr.back());
  EXPECT_EQ(1, arr[0]);
  EXPECT_EQ(5, arr[4]);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(arr1);
  EXPECT_EQ(3, arr2.size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(3, arr2[2]);
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2(std::move(arr1));
  EXPECT_FALSE(arr1.empty());
  EXPECT_EQ(3, arr1.size());
  EXPECT_EQ(3, arr2.size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(3, arr2[2]);
}

TEST(ArrayTest, Destructor) { s21::array<int, 3> arr = {1, 2, 3}; }

TEST(ArrayTest, AssignmentOperatorMove) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2;
  arr2 = std::move(arr1);
  EXPECT_FALSE(arr1.empty());
  EXPECT_EQ(3, arr1.size());
  EXPECT_EQ(3, arr2.size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(3, arr2[2]);
}

TEST(ArrayTest, AccessOperator) {
  s21::array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(1, arr.at(0));
  EXPECT_EQ(2, arr[1]);
  EXPECT_EQ(1, arr.front());
  EXPECT_EQ(3, arr.back());
}

TEST(ArrayTest, Iterator) {
  s21::array<int, 3> arr = {1, 2, 3};
  s21::array<int, 3>::iterator it = arr.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
  it++;
  EXPECT_EQ(3, *it);
  ++it;
  EXPECT_EQ(arr.end(), it);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 5> arr;
  arr.fill(42);
  EXPECT_EQ(42, arr[0]);
  EXPECT_EQ(42, arr[4]);
}

TEST(ArrayTest, Swap) {
  s21::array<int, 3> arr1 = {1, 2, 3};
  s21::array<int, 3> arr2 = {4, 5, 6};
  arr1.swap(arr2);
  EXPECT_EQ(3, arr1.size());
  EXPECT_EQ(4, arr1[0]);
  EXPECT_EQ(5, arr1[1]);
  EXPECT_EQ(3, arr2.size());
  EXPECT_EQ(1, arr2[0]);
  EXPECT_EQ(2, arr2[1]);
}

// // TEST
// //
// SET----------------------------------------------------------------------------------------------------------

TEST(SetTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0, s.size());
}

TEST(SetTest, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_FALSE(s.empty());
  EXPECT_EQ(3, s.size());
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(SetTest, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(3, s2.size());
  EXPECT_TRUE(s1.empty());
}

TEST(SetTest, Destructor) {
  s21::set<int> *s = new s21::set<int>({1, 2, 3});
  delete s;
  EXPECT_TRUE(true);
}

TEST(SetTest, MoveAssignmentOperator) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s2 = std::move(s1);
  EXPECT_EQ(3, s2.size());
  EXPECT_FALSE(s1.empty());
}

TEST(SetTest, Begin) {
  s21::set<int> s = {1, 2, 3};
  s21::set<int>::iterator it = s.begin();
  EXPECT_EQ(1, *it);
  ++it;
  EXPECT_EQ(2, *it);
}

TEST(SetTest, End) {
  s21::set<int> s = {1, 2, 3};
  s.end();
}

TEST(SetTest, Empty) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  s.insert(1);
  EXPECT_FALSE(s.empty());
}

TEST(SetTest, Size) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(3, s.size());
}

TEST(SetTest, MaxSize) {
  s21::set<int> s;
  EXPECT_GE(s.max_size(), 0);
}

TEST(SetTest, Clear) {
  s21::set<int> s = {1, 2, 3};
  s.clear();
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(0, s.size());
}

TEST(SetTest, Insert) {
  s21::set<int> s;
  std::pair<s21::set<int>::iterator, bool> result = s.insert(1);
  EXPECT_TRUE(result.second);
  EXPECT_TRUE(s.contains(1));
  EXPECT_EQ(1, *(result.first));
  result = s.insert(1);
  EXPECT_FALSE(result.second);
  EXPECT_EQ(1, *(result.first));
}

TEST(SetTest, Erase) {
  s21::set<int> s = {1, 2, 3};
  s21::set<int>::iterator it = s.find(2);
  s.erase(it);
  EXPECT_FALSE(s.contains(2));
}

TEST(SetTest, Swap) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s1.swap(s2);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}

TEST(SetTest, Merge) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2 = {4, 5, 6};
  s1.merge(s2);
  EXPECT_TRUE(s1.contains(1));
  EXPECT_TRUE(s1.contains(2));
  EXPECT_TRUE(s1.contains(3));
  EXPECT_TRUE(s1.contains(4));
  EXPECT_TRUE(s1.contains(5));
  EXPECT_TRUE(s1.contains(6));
  EXPECT_TRUE(s2.empty());
}

TEST(SetTest, Find) {
  s21::set<int> s = {1, 2, 3};
  s21::set<int>::iterator it = s.find(2);
  EXPECT_EQ(2, *it);
}

TEST(SetTest, Contains) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_TRUE(s.contains(1));
  EXPECT_FALSE(s.contains(4));
}

TEST(InsertManyTest, Empty) {
  s21::set<int> s;
  insert_many(s);
  EXPECT_TRUE(s.empty());
}

TEST(InsertManyTest, SingleElement) {
  s21::set<int> s;
  insert_many(s, 1);
  EXPECT_EQ(s.size(), 1);
}

TEST(InsertManyTest, MultipleElements) {
  s21::set<int> s;
  insert_many(s, 1, 2, 3);
  EXPECT_EQ(s.size(), 3);
}

TEST(InsertManyTest, DifferentTypes) {
  s21::set<std::string> s;
  insert_many(s, "hello", "world", "!");
  EXPECT_EQ(s.size(), 3);
}

// // TEST
// //
// MAP----------------------------------------------------------------------------------------------------------

TEST(MapTest, DefaultConstructor) {
  s21::map<int, int> m;
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, InitializerListConstructor) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.size(), 3);
  EXPECT_EQ(m[1], 10);
  EXPECT_EQ(m[2], 20);
  EXPECT_EQ(m[3], 30);
  EXPECT_THROW(m.at(4), std::out_of_range);
}

TEST(MapTest, CopyConstructor) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> m2(m1);
  EXPECT_EQ(m1.size(), m2.size());
  EXPECT_EQ(m1[1], m2[1]);
  EXPECT_EQ(m1[2], m2[2]);
  EXPECT_EQ(m1[3], m2[3]);
}

TEST(MapTest, MoveConstructor) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> m2(std::move(m1));
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
  EXPECT_EQ(m2[3], 30);
  EXPECT_TRUE(m1.empty());
  EXPECT_EQ(m1.size(), 0);
}

TEST(MapTest, Destructor) {
  s21::map<int, int> *m = new s21::map<int, int>{{1, 10}, {2, 20}, {3, 30}};
  delete m;
}

TEST(MapTest, AssignmentOperatorMove) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int> m2;
  m2 = std::move(m1);
  EXPECT_EQ(m2.size(), 3);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
  EXPECT_EQ(m2[3], 30);
  EXPECT_TRUE(m1.empty());
  EXPECT_EQ(m1.size(), 0);
}

TEST(MapTest, At) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(m.at(1), 10);
  EXPECT_EQ(m.at(2), 20);
  EXPECT_EQ(m.at(3), 30);
  EXPECT_THROW(m.at(4), std::out_of_range);
}

TEST(MapTest, IndexOperator) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_EQ(m[1], 10);
  EXPECT_EQ(m[2], 20);
  EXPECT_EQ(m[3], 30);
  m[1] = 100;
  m[4] = 40;
  EXPECT_EQ(m[1], 100);
  EXPECT_EQ(m[4], 40);
}

TEST(MapTest, Iterator) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  s21::map<int, int>::iterator it = m.begin();
  EXPECT_EQ((*it).first, 1);
  EXPECT_EQ((*it).second, 10);
  ++it;
  EXPECT_EQ((*it).first, 2);
  EXPECT_EQ((*it).second, 20);
  ++it;
  EXPECT_EQ((*it).first, 3);
  EXPECT_EQ((*it).second, 30);
  ++it;
  EXPECT_EQ(it, m.end());
}

TEST(MapTest, Empty) {
  s21::map<int, int> m;
  EXPECT_TRUE(m.empty());
  m.insert({1, 10});
  EXPECT_FALSE(m.empty());
  m.erase(m.begin());
  EXPECT_TRUE(m.empty());
}

TEST(MapTest, Size) {
  s21::map<int, int> m;
  EXPECT_EQ(m.size(), 0);
  m.insert({1, 10});
  m.insert({2, 20});
  m.insert({3, 30});
  EXPECT_EQ(m.size(), 3);
  m.erase(m.begin());
  EXPECT_EQ(m.size(), 2);
  m.clear();
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, MaxSize) {
  s21::map<int, int> m;
  EXPECT_GT(m.max_size(), 0);
}

TEST(MapTest, Clear) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.size(), 3);
  m.clear();
  EXPECT_TRUE(m.empty());
  EXPECT_EQ(m.size(), 0);
}

TEST(MapTest, InsertValue) {
  s21::map<int, int> m;
  auto res = m.insert({1, 10});
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
  res = m.insert({1, 20});
  EXPECT_FALSE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
}

TEST(MapTest, InsertKeyValue) {
  s21::map<int, int> m;
  auto res = m.insert(1, 10);
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
  res = m.insert(1, 20);
  EXPECT_FALSE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, int> m;
  auto res = m.insert_or_assign(1, 10);
  EXPECT_TRUE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 10);
  res = m.insert_or_assign(1, 20);
  EXPECT_FALSE(res.second);
  EXPECT_EQ(res.first->data.first, 1);
  EXPECT_EQ(res.first->data.second, 20);
}

TEST(MapTest, Erase) {
  s21::map<int, int> m;
  m.insert({1, 10});
  m.insert({2, 20});
  m.insert({3, 30});
  EXPECT_EQ(m.size(), 3);
  m.erase(m.begin());
  EXPECT_EQ(m.size(), 2);
}

TEST(MapTest, Swap) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}};
  s21::map<int, int> m2 = {{3, 30}, {4, 40}};
  m1.swap(m2);
  EXPECT_EQ(m1.size(), 2);
  EXPECT_EQ(m1[3], 30);
  EXPECT_EQ(m1[4], 40);
  EXPECT_EQ(m2.size(), 2);
  EXPECT_EQ(m2[1], 10);
  EXPECT_EQ(m2[2], 20);
}

TEST(MapTest, Merge) {
  s21::map<int, int> m1 = {{1, 10}, {2, 20}};
  s21::map<int, int> m2 = {{2, 30}, {3, 40}};
  m1.merge(m2);
  EXPECT_EQ(m1.size(), 3);
  EXPECT_EQ(m1[1], 10);
  EXPECT_EQ(m1[2], 20);
  EXPECT_EQ(m1[3], 40);
  EXPECT_EQ(m2.size(), 0);
}

TEST(MapTest, Contains) {
  s21::map<int, int> m = {{1, 10}, {2, 20}, {3, 30}};
  EXPECT_TRUE(m.contains(1));
  EXPECT_TRUE(m.contains(2));
  EXPECT_TRUE(m.contains(3));
  EXPECT_FALSE(m.contains(4));
}

TEST(MapTest, InsertManyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(1, "one"), std::make_pair(2, "two"),
              std::make_pair(3, "three"));

  EXPECT_EQ(myMap.size(), 3);
  EXPECT_EQ(myMap[1], "one");
  EXPECT_EQ(myMap[2], "two");
  EXPECT_EQ(myMap[3], "three");
}

TEST(MapTest, InsertManyDuplicateTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(1, "one"), std::make_pair(1, "uno"),
              std::make_pair(2, "two"));

  EXPECT_EQ(myMap.size(), 2);
  EXPECT_EQ(myMap[1], "one");
  EXPECT_EQ(myMap[2], "two");
}

TEST(MapTest, InsertManyDuplicateKeyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(1, "one"), std::make_pair(1, "uno"),
              std::make_pair(2, "two"));

  EXPECT_EQ(myMap.size(), 2);
  EXPECT_EQ(myMap[1], "one");
  EXPECT_EQ(myMap[2], "two");
}

TEST(MapTest, InsertManyEmptyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap);

  EXPECT_TRUE(myMap.empty());
}

TEST(MapTest, InsertManyEmptyKeyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(1, "one"), std::make_pair(2, "two"),
              std::make_pair(0, "zero"));

  EXPECT_EQ(myMap.size(), 3);
  EXPECT_EQ(myMap[0], "zero");
}

TEST(MapTest, InsertManyLargeKeyTest) {
  s21::map<int, std::string> myMap;
  insert_many(myMap, std::make_pair(999999999, "large"),
              std::make_pair(1000000000, "huge"));

  EXPECT_EQ(myMap.size(), 2);
  EXPECT_EQ(myMap[999999999], "large");
  EXPECT_EQ(myMap[1000000000], "huge");
}

TEST(MapTest, InsertManyRvalueTest) {
  s21::map<int, std::string> myMap;
  std::string value = "test";
  insert_many(myMap, std::make_pair(1, std::move(value)));

  EXPECT_EQ(myMap.size(), 1);
  EXPECT_EQ(myMap[1], "test");
  EXPECT_TRUE(value.empty());
}

TEST(MapTest, InsertManyEmptyTest_2) {
  s21::map<int, std::string> myMap;
  insert_many(myMap);

  EXPECT_TRUE(myMap.empty());
}

// // TEST
// //
// QUEUE----------------------------------------------------------------------------------------------------------

TEST(Queue, Constructor_Default) {
  s21::Queue<int> our_queue;
  std::queue<int> std_queue;
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(Queue, Constructor_List) {
  s21::Queue<int> our_queue;
  our_queue.push(1);
  our_queue.push(2);
  our_queue.push(3);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  EXPECT_EQ(our_queue.front(), std_queue.front());
  EXPECT_EQ(our_queue.back(), std_queue.back());
}

TEST(Queue, Constructor_Copy) {
  s21::Queue<int> our_queue;
  our_queue.push(1);
  our_queue.push(2);
  our_queue.push(3);
  s21::Queue<int> our_copy(our_queue);
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_copy(std_queue);
  EXPECT_EQ(our_copy.front(), std_copy.front());
  EXPECT_EQ(our_copy.back(), std_copy.back());
}

TEST(Queue, Operator_Copy) {
  s21::Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::Queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  our_queue_empty = our_queue_int;
  std_queue_empty = std_queue_int;
  EXPECT_EQ(our_queue_empty.front(), std_queue_empty.front());
  EXPECT_EQ(our_queue_empty.back(), std_queue_empty.back());
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

TEST(Queue, Constructor_Move) {
  s21::Queue<int> our_queue;
  our_queue.push(1);
  our_queue.push(2);
  our_queue.push(3);
  s21::Queue<int> our_move(std::move(our_queue));
  std::queue<int> std_queue;
  std_queue.push(1);
  std_queue.push(2);
  std_queue.push(3);
  std::queue<int> std_move(std::move(std_queue));
  EXPECT_EQ(our_move.front(), std_move.front());
  EXPECT_EQ(our_move.back(), std_move.back());
  EXPECT_EQ(our_queue.empty(), std_queue.empty());
}

TEST(Queue, FrontAndBack) {
  s21::Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  s21::Queue<double> our_queue_double;
  our_queue_double.push(1.1f);
  our_queue_double.push(2.1f);
  our_queue_double.push(3.1f);
  std::queue<double> std_queue_double;
  std_queue_double.push(1.1f);
  std_queue_double.push(2.1f);
  std_queue_double.push(3.1f);
  s21::Queue<std::string> our_queue_string;
  our_queue_string.push("abc");
  our_queue_string.push("def");
  our_queue_string.push("ghf");
  std::queue<std::string> std_queue_string;
  std_queue_string.push("abc");
  std_queue_string.push("def");
  std_queue_string.push("ghf");
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_double.front(), std_queue_double.front());
  EXPECT_EQ(our_queue_string.front(), std_queue_string.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  EXPECT_EQ(our_queue_double.back(), std_queue_double.back());
  EXPECT_EQ(our_queue_string.back(), std_queue_string.back());
}

TEST(Queue, Empty) {
  s21::Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
  s21::Queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.empty(), std_queue_empty.empty());
}

TEST(Queue, Size) {
  s21::Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.size(), std_queue_int.size());
  s21::Queue<int> our_queue_empty;
  std::queue<int> std_queue_empty;
  EXPECT_EQ(our_queue_empty.size(), std_queue_empty.size());
}

TEST(Queue, Push) {
  s21::Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
}

TEST(Queue, Pop) {
  s21::Queue<int> our_queue_int;
  our_queue_int.push(1);
  our_queue_int.push(2);
  our_queue_int.push(3);
  our_queue_int.pop();
  std::queue<int> std_queue_int;
  std_queue_int.push(1);
  std_queue_int.push(2);
  std_queue_int.push(3);
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.front(), std_queue_int.front());
  EXPECT_EQ(our_queue_int.back(), std_queue_int.back());
  our_queue_int.pop();
  our_queue_int.pop();
  std_queue_int.pop();
  std_queue_int.pop();
  EXPECT_EQ(our_queue_int.empty(), std_queue_int.empty());
}

// // TEST
// //
// STACK----------------------------------------------------------------------------------------------------------

TEST(Stack, Constructor_Default) {
  s21::Stack<int> our_stack;
  std::stack<int> std_stack;
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(Stack, Constructor_List) {
  s21::Stack<int> our_stack;
  our_stack.push(1);
  our_stack.push(2);
  our_stack.push(3);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  EXPECT_EQ(our_stack.top(), std_stack.top());
}

TEST(Stack, Constructor_Copy) {
  s21::Stack<int> our_stack;
  our_stack.push(1);
  our_stack.push(2);
  our_stack.push(3);
  s21::Stack<int> our_copy(our_stack);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_copy(std_stack);
  EXPECT_EQ(our_copy.top(), std_copy.top());
}

TEST(Stack, Operator_Copy) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  our_stack_empty = our_stack_int;
  std_stack_empty = std_stack_int;
  EXPECT_EQ(our_stack_empty.top(), std_stack_empty.top());
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

TEST(Stack, Constructor_Move) {
  s21::Stack<int> our_stack;
  our_stack.push(1);
  our_stack.push(2);
  our_stack.push(3);
  s21::Stack<int> our_move(std::move(our_stack));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_move(std::move(std_stack));
  EXPECT_EQ(our_move.top(), std_move.top());
  EXPECT_EQ(our_stack.empty(), std_stack.empty());
}

TEST(Stack, Top) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  s21::Stack<double> our_stack_double;
  our_stack_double.push(1.1f);
  our_stack_double.push(2.1f);
  our_stack_double.push(3.1f);
  std::stack<double> std_stack_double;
  std_stack_double.push(1.1f);
  std_stack_double.push(2.1f);
  std_stack_double.push(3.1f);
  s21::Stack<std::string> our_stack_string;
  our_stack_string.push("abc");
  our_stack_string.push("def");
  our_stack_string.push("ghf");
  std::stack<std::string> std_stack_string;
  std_stack_string.push("abc");
  std_stack_string.push("def");
  std_stack_string.push("ghf");
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  EXPECT_EQ(our_stack_double.top(), std_stack_double.top());
  EXPECT_EQ(our_stack_string.top(), std_stack_string.top());
}

TEST(Stack, Empty) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.empty(), std_stack_empty.empty());
}

TEST(Stack, Size) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.size(), std_stack_int.size());
  s21::Stack<int> our_stack_empty;
  std::stack<int> std_stack_empty;
  EXPECT_EQ(our_stack_empty.size(), std_stack_empty.size());
}

TEST(Stack, Push) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
}

TEST(Stack, Pop) {
  s21::Stack<int> our_stack_int;
  our_stack_int.push(1);
  our_stack_int.push(2);
  our_stack_int.push(3);
  our_stack_int.pop();
  std::stack<int> std_stack_int;
  std_stack_int.push(1);
  std_stack_int.push(2);
  std_stack_int.push(3);
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.top(), std_stack_int.top());
  our_stack_int.pop();
  our_stack_int.pop();
  std_stack_int.pop();
  std_stack_int.pop();
  EXPECT_EQ(our_stack_int.empty(), std_stack_int.empty());
}

// // TEST
// //
// LIST----------------------------------------------------------------------------------------------------------

TEST(List, Constructor_Default) {
  s21::List<int> our_list;
  std::list<int> std_list;
  EXPECT_EQ(our_list.empty(), std_list.empty());
}

TEST(List, Constructor_List) {
  s21::List<int> our_list;
  our_list.push_back(1);
  our_list.push_back(2);
  our_list.push_back(3);
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Size) {
  s21::List<int> our_list;
  our_list.push_back(1);
  our_list.push_back(2);
  our_list.push_back(3);
  std::list<int> std_list = {1, 2, 3};
  EXPECT_EQ(our_list.size(), std_list.size());
}

TEST(List, Push_Front) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.push_front(1);
  std_list.push_front(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(2);
  std_list.push_front(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_front(3);
  std_list.push_front(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Push_Back) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Pop_Front) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_front();
  std_list.pop_front();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Pop_Back) {
  s21::List<int> our_list;
  std::list<int> std_list;
  our_list.push_back(1);
  std_list.push_back(1);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(2);
  std_list.push_back(2);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.push_back(3);
  std_list.push_back(3);
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
  our_list.pop_back();
  std_list.pop_back();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

TEST(List, Merge) {
  s21::List<int> our_list_first;
  our_list_first.push_back(1);
  s21::List<int> our_list_second;
  our_list_second.push_back(2);
  our_list_second.push_back(3);
  our_list_second.push_back(4);
  our_list_second.push_back(5);
  std::list<int> std_list_first = {1};
  std::list<int> std_list_second = {2, 3, 4, 5};
  our_list_first.merge(our_list_second);
  std_list_first.merge(std_list_second);
  EXPECT_EQ(our_list_first.front(), std_list_first.front());
  EXPECT_EQ(our_list_first.back(), std_list_first.back());
  EXPECT_EQ(our_list_second.empty(), std_list_second.empty());
}

TEST(List, Reverse) {
  s21::List<int> our_list;
  our_list.push_back(1);
  our_list.push_back(2);
  our_list.push_back(3);
  our_list.push_back(4);
  our_list.push_back(5);
  std::list<int> std_list = {1, 2, 3, 4, 5};
  our_list.reverse();
  std_list.reverse();
  EXPECT_EQ(our_list.front(), std_list.front());
  EXPECT_EQ(our_list.back(), std_list.back());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}