#include <gtest/gtest.h>
#include "array.hpp"

TEST(IntArrayTest, SizeIsZeroForEmptyArray) {
  int_array a(100);
  EXPECT_EQ(a.size(), 0);
}

TEST(IntArrayTest, SizeIncreasedWhenElementAdded) {
  int_array a(100);
  a.push_back(1);
  EXPECT_EQ(a.size(), 1);
}

TEST(IntArrayTest, AbortOnPopFromEmptyArray) {
  int_array a(100);
  ASSERT_DEATH(a.pop_back(), "Assertion failed.*");
}

TEST(IntArrayTest, SizeDecreasedWhenPopFromNonEmptyArray) {
  int_array a(100);
  a.push_back(1);
  a.push_back(2);
  EXPECT_EQ(a.size(), 2);
  a.pop_back();
  EXPECT_EQ(a.size(), 1);
}

TEST(IntArrayTest, OriginalArrayIsNotChangedOnCopyChange) {
  int_array a(1);
  a.push_back(1);
  int_array b(2);
  b.push_back(2);
  a = b;
  EXPECT_EQ(a.at(0), 1);
  EXPECT_EQ(b.at(0), 2);
  a.pop_back();
  EXPECT_EQ(a.size(), 0);
  a.push_back(42);
  EXPECT_EQ(a.size(), 1);
  EXPECT_EQ(a.at(0), 42);
  EXPECT_EQ(b.size(), 1);
  EXPECT_EQ(b.at(0), 2);
}
