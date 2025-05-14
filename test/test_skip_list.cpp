#include "gtest.h"
#include "skip_list.h"

TEST(SkipListTest, InsertAndFind)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(5);
    list.insert(15);

    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(5));
    EXPECT_TRUE(list.find(15));
    EXPECT_FALSE(list.find(20));
}

TEST(SkipListTest, RemoveLeaf)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(5);
    list.insert(15);

    list.remove(5);

    EXPECT_FALSE(list.find(5));
    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(15));
}

TEST(SkipListTest, RemoveNodeWithOneChild)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(5);
    list.insert(3);

    list.remove(5);

    EXPECT_FALSE(list.find(5));
    EXPECT_TRUE(list.find(3));
    EXPECT_TRUE(list.find(10));
}

TEST(SkipListTest, RemoveNodeWithTwoChildren)
{
    SkipList<int> list;

    list.insert(20);
    list.insert(10);
    list.insert(30);
    list.insert(25);
    list.insert(40);

    list.remove(30);

    EXPECT_FALSE(list.find(30));
    EXPECT_TRUE(list.find(25));
    EXPECT_TRUE(list.find(40));
    EXPECT_TRUE(list.find(20));
    EXPECT_TRUE(list.find(10));
}

TEST(SkipListTest, InsertNegativeValues)
{
    SkipList<int> list;

    list.insert(-10);
    list.insert(-20);
    list.insert(-5);

    EXPECT_TRUE(list.find(-10));
    EXPECT_TRUE(list.find(-20));
    EXPECT_TRUE(list.find(-5));
    EXPECT_FALSE(list.find(0));
}

TEST(SkipListTest, InsertMinMaxInt)
{
    SkipList<int> list;

    list.insert(INT_MIN);
    list.insert(INT_MAX);

    EXPECT_TRUE(list.find(INT_MIN));
    EXPECT_TRUE(list.find(INT_MAX));
}

TEST(SkipListTest, RemoveRootNode)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(5);
    list.insert(15);

    list.remove(10);

    EXPECT_FALSE(list.find(10));
    EXPECT_TRUE(list.find(5));
    EXPECT_TRUE(list.find(15));
}

TEST(SkipListTest, RemoveAllNodes)
{
    SkipList<int> list;

    list.insert(1);
    list.insert(2);
    list.insert(3);

    list.remove(1);
    list.remove(2);
    list.remove(3);

    EXPECT_FALSE(list.find(1));
    EXPECT_FALSE(list.find(2));
    EXPECT_FALSE(list.find(3));
}

TEST(SkipListTest, FindInEmptyList)
{
    SkipList<int> list;

    EXPECT_FALSE(list.find(100));
}

TEST(SkipListTest, RemoveFromEmptyList)
{
    SkipList<int> list;

    list.remove(42);

    EXPECT_FALSE(list.find(42));
}

TEST(SkipListTest, InsertMultipleAndCheckBalance)
{
    SkipList<int> list;

    for (int i = 1; i <= 100; ++i)
    {
        list.insert(i);
    }

    for (int i = 1; i <= 100; ++i)
    {
        EXPECT_TRUE(list.find(i));
    }
}

TEST(SkipListTest, InsertDuplicates)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(10);
    list.insert(10);

    EXPECT_TRUE(list.find(10));
}

TEST(SkipListTest, MassiveInsertRemove)
{
    SkipList<int> list;

    for (int i = 0; i < 1000; ++i)
    {
        list.insert(i);
    }

    for (int i = 0; i < 1000; i += 2)
    {
        list.remove(i);
    }

    for (int i = 0; i < 1000; ++i)
    {
        if (i % 2 == 0)
        {
            EXPECT_FALSE(list.find(i));
        }
        else
        {
            EXPECT_TRUE(list.find(i));
        }
    }
}

TEST(SkipListTest, FindSingleElementInEmptyList)
{
    SkipList<int> list;

    EXPECT_FALSE(list.find(10));
}

TEST(SkipListTest, InsertAndFindAtMultipleLevels)
{
    SkipList<int> list;

    for (int i = 1; i <= 10; ++i)
    {
        list.insert(i);
    }

    EXPECT_TRUE(list.find(1));
    EXPECT_TRUE(list.find(5));
    EXPECT_TRUE(list.find(10));
    EXPECT_FALSE(list.find(20));
}

TEST(SkipListTest, InsertAndCheckMultipleLevels)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(20);
    list.insert(5);
    list.insert(15);

    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(5));
    EXPECT_TRUE(list.find(20));
    EXPECT_TRUE(list.find(15));
}

TEST(SkipListTest, RemoveMiddleElement)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(20);
    list.insert(15);
    list.insert(25);

    list.remove(15);

    EXPECT_FALSE(list.find(15));
    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(20));
    EXPECT_TRUE(list.find(25));
}

TEST(SkipListTest, InsertInDescendingOrder)
{
    SkipList<int> list;

    for (int i = 10; i >= 1; --i)
    {
        list.insert(i);
    }

    EXPECT_TRUE(list.find(1));
    EXPECT_TRUE(list.find(5));
    EXPECT_TRUE(list.find(10));
    EXPECT_FALSE(list.find(11));
}

TEST(SkipListTest, CheckSkipListBalance)
{
    SkipList<int> list;

    for (int i = 1; i <= 100; ++i)
    {
        list.insert(i);
    }

    for (int i = 1; i <= 100; ++i)
    {
        EXPECT_TRUE(list.find(i));
    }

    EXPECT_EQ(list.size(), 100);
}

TEST(SkipListTest, RemoveFromMiddle)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(20);
    list.insert(15);
    list.insert(5);
    list.insert(25);

    list.remove(15);

    EXPECT_FALSE(list.find(15));
    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(20));
    EXPECT_TRUE(list.find(5));
    EXPECT_TRUE(list.find(25));
}

TEST(SkipListTest, LargeRangeInsert)
{
    SkipList<int> list;

    for (int i = 1; i <= 10000; ++i)
    {
        list.insert(i);
    }

    for (int i = 1; i <= 10000; ++i)
    {
        EXPECT_TRUE(list.find(i));
    }
}

TEST(SkipListTest, InsertRandomOrder)
{
    SkipList<int> list;

    list.insert(30);
    list.insert(10);
    list.insert(50);
    list.insert(20);
    list.insert(40);

    EXPECT_TRUE(list.find(30));
    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(50));
    EXPECT_TRUE(list.find(20));
    EXPECT_TRUE(list.find(40));
}

TEST(SkipListTest, RemoveNonExistentElement)
{
    SkipList<int> list;

    list.insert(10);
    list.insert(20);

    list.remove(30);

    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(20));
    EXPECT_EQ(list.size(), 2);
}

TEST(SkipListTest, LargeScaleInsertRemove)
{
    SkipList<int> list;

    for (int i = 0; i < 10000; ++i)
    {
        list.insert(i);
    }

    for (int i = 0; i < 10000; i += 2)
    {
        list.remove(i);
    }

    for (int i = 0; i < 10000; ++i)
    {
        if (i % 2 == 0)
        {
            EXPECT_FALSE(list.find(i));
        }
        else
        {
            EXPECT_TRUE(list.find(i));
        }
    }

    EXPECT_EQ(list.size(), 5000);
}