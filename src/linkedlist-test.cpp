/**
 * \file linkedlist-test.cpp
 * \author Andrew Scott
 *
 * \brief Tests a LinkedList for correctness using multiple types
 *
 * \details
 *   Configured to use the templated linkedlist found in linkedlist.hpp as
 *   linked lists of different types
 *
 * \note
 *   deleteFront() is implicitly tested everywhere since it is used in the
 *   destructor
 */

#include "linkedlist.hpp"
#include <iostream>
//#include <cstddef>
#include <iterator>      // std::advance()
#include <stdlib.h>      // rand(), srand()
#include <time.h>       // time
#include <gtest/gtest.h>
#include "otter.hpp"

using std::string;

TEST(linkedListStringTest, insertFrontTests)
{
    LinkedList<string> stringList;
    string test = "hello world";
    EXPECT_FALSE(stringList.contains(test));
    stringList.insertFront(test);
    EXPECT_TRUE(stringList.contains(test));
    EXPECT_TRUE(stringList.size() == 1);
    string test2 = "hello again";
    stringList.insertFront(test2);
    EXPECT_TRUE(stringList.contains(test2));
    EXPECT_TRUE(stringList.size() == 2);
    for (int i = 0; i < 100; ++i) {
        string test = std::to_string(i);
        EXPECT_FALSE(stringList.contains(test));
        stringList.insertFront(test);
        EXPECT_TRUE(stringList.contains(test));
    }
}

TEST(linkedListStringTest, copyConstructorTests)
{
    LinkedList<string> stringList;
    string test = "hello world";
    stringList.insertFront(test);
    LinkedList<string> stringList2{stringList};
    EXPECT_TRUE(stringList == stringList2);
    string test2 = "hello again";
    stringList.insertFront(test2);
    EXPECT_TRUE(stringList != stringList2);
    for (int i = 0; i < 1000; ++i) {
        stringList2.insertFront(std::to_string(i));
    }
    LinkedList<string> stringList3{stringList2};
    EXPECT_TRUE(stringList2 == stringList3);
    stringList3.deleteFront();
    EXPECT_TRUE(stringList2 != stringList3);
}

TEST(linkedListStringTest, assignmentOperatorTests)
{
    LinkedList<string> stringList;
    string test = "hello world";
    stringList.insertFront(test);
    LinkedList<string> stringList2;
    ASSERT_NE(stringList, stringList2);
    stringList2 = stringList;
    ASSERT_EQ(stringList, stringList2);
    for (int i = 0; i < 1000; ++i) {
        stringList2.insertFront(std::to_string(i));
    }
    ASSERT_NE(stringList, stringList2);
    LinkedList<string> stringList3;
    ASSERT_NE(stringList2, stringList3);
    stringList3 = stringList2;
    ASSERT_EQ(stringList2, stringList3);
}

TEST(linkedListStringTest, insertBackTests)
{
    LinkedList<string> stringList;
    string test = "hello world";
    EXPECT_FALSE(stringList.contains(test));
    stringList.insertBack(test);
    EXPECT_TRUE(stringList.contains(test));
    EXPECT_TRUE(stringList.size() == 1);
    string test2 = "hello again";
    stringList.insertBack(test2);
    EXPECT_TRUE(stringList.contains(test2));
    EXPECT_TRUE(stringList.size() == 2);
    for (int i = 0; i < 100; ++i) {
        string test = std::to_string(i);
        EXPECT_FALSE(stringList.contains(test));
        stringList.insertBack(test);
        EXPECT_TRUE(stringList.contains(test));
    }
}

TEST(linkedListStringTest, insertAfterTests)
{
    srand (time(NULL));
    LinkedList<string> stringList;
    string test = "hello world";
    stringList.insertFront(test);
    EXPECT_TRUE(stringList.contains(test));
    for (int i = 0; i < 1000; ++i) {
        LinkedList<string>::iterator it = stringList.begin();
        string s = std::to_string(i);
        int advanceDist = rand() % stringList.size();
        std::advance(it, advanceDist);
        stringList.insertAfter(it, s);
        EXPECT_TRUE(stringList.contains(s));
    }
}

TEST(linkedListStringTest, deleteBackTests)
{
  LinkedList<string> stringList;
    for (int i = 0; i < 1000; ++i) {
        stringList.insertFront(std::to_string(i));
    }
    for (int i = 0; i < 1000; ++i) {
        string deletee = stringList.deleteBack();
        ASSERT_EQ(deletee, std::to_string(i));
        ASSERT_EQ(stringList.size(), 999 - i);
    }
}

TEST(linkedListStringTest, iteratorTests)
{
    LinkedList<string> stringList;
    for (int i = 0; i < 1000; ++i) {
        stringList.insertFront(std::to_string(i));
    }

    int j = 999;
    for (LinkedList<string>::iterator i = stringList.begin(); i != stringList.end(); ++i) {
        EXPECT_TRUE(*i == std::to_string(j));
        --j;
    }
}

TEST(linkedListStringTest, deleteElementTests)
{
    srand (time(NULL));
    LinkedList<string> stringList;
    string test = "hello world";
    stringList.insertFront(test);
    EXPECT_TRUE(stringList.contains(test));
    stringList.deleteElement(test);
    EXPECT_FALSE(stringList.contains(test));
    for (int i = 0; i < 1000; ++i) {
        string test = std::to_string(i);
        stringList.insertFront(test);
        EXPECT_TRUE(stringList.contains(test));
    }
    ASSERT_EQ(stringList.size(), 1000) << "list should have 1000 elements";
    for (int i = 0; i < 1000; ++i) {
        string test = std::to_string(rand() % 1000);
        stringList.deleteElement(test);
        EXPECT_FALSE(stringList.contains(test)) << "list should no longer have element";
    }
    EXPECT_TRUE(stringList.size() < 1000) << "list should have deleted at least one element";
}

TEST(linkedListOtterTest, insertFrontTests)
{
    LinkedList<Otter> otterList;
    Otter phokey = Otter{"phokey"};
    EXPECT_FALSE(otterList.contains(phokey));
    otterList.insertFront(phokey);
    EXPECT_TRUE(otterList.contains(phokey));
    EXPECT_TRUE(otterList.size() == 1);
    Otter test2 = Otter{"river otter"};
    otterList.insertFront(test2);
    EXPECT_TRUE(otterList.contains(test2));
    EXPECT_TRUE(otterList.size() == 2);
    for (int i = 0; i < 100; ++i) {
        Otter test = Otter{std::to_string(i)};
        EXPECT_FALSE(otterList.contains(test));
        otterList.insertFront(test);
        EXPECT_TRUE(otterList.contains(test));
    }
}

TEST(linkedListOtterTest, copyConstructorTests)
{
    LinkedList<Otter> otterList;
    Otter phokey = Otter{"phokey"};
    otterList.insertFront(phokey);
    LinkedList<Otter> otterList2{otterList};
    EXPECT_TRUE(otterList == otterList2);
    Otter test2 = Otter{"river otter"};
    otterList.insertFront(test2);
    EXPECT_TRUE(otterList != otterList2);
    for (int i = 0; i < 1000; ++i) {
        Otter test = Otter{std::to_string(i)};
        otterList2.insertFront(test);
    }
    LinkedList<Otter> otterList3{otterList2};
    EXPECT_TRUE(otterList2 == otterList3);
    otterList3.deleteFront();
    EXPECT_TRUE(otterList2 != otterList3);
}

TEST(linkedListOtterTest, assignmentOperatorTests)
{
    LinkedList<Otter> otterList;
    Otter phokey = Otter{"phokey"};
    otterList.insertFront(phokey);
    LinkedList<Otter> otterList2;
    ASSERT_NE(otterList, otterList2);
    otterList2 = otterList;
    ASSERT_EQ(otterList, otterList2);
    for (int i = 0; i < 1000; ++i) {
        Otter test = Otter{std::to_string(i)};
        otterList2.insertFront(test);
    }
    ASSERT_NE(otterList, otterList2);
    LinkedList<Otter> otterList3;
    ASSERT_NE(otterList2, otterList3);
    otterList3 = otterList2;
    ASSERT_EQ(otterList2, otterList3);
}

TEST(linkedListOtterTest, insertBackTests)
{
    LinkedList<Otter> otterList;
    Otter phokey = Otter{"phokey"};
    EXPECT_FALSE(otterList.contains(phokey));
    otterList.insertBack(phokey);
    EXPECT_TRUE(otterList.contains(phokey));
    EXPECT_TRUE(otterList.size() == 1);
    Otter test2 = Otter{"river otter"};
    otterList.insertBack(test2);
    EXPECT_TRUE(otterList.contains(test2));
    EXPECT_TRUE(otterList.size() == 2);
    for (int i = 0; i < 100; ++i) {
        Otter test = Otter{std::to_string(i)};
        EXPECT_FALSE(otterList.contains(test));
        otterList.insertBack(test);
        EXPECT_TRUE(otterList.contains(test));
    }
}

TEST(linkedListOtterTest, insertAfterTests)
{
    srand (time(NULL));
    LinkedList<Otter> otterList;
    Otter phokey = Otter{"phokey"};
    otterList.insertFront(phokey);
    EXPECT_TRUE(otterList.contains(phokey));
    for (int i = 0; i < 1000; ++i) {
        LinkedList<Otter>::iterator it = otterList.begin();
        Otter o = Otter{std::to_string(i)};
        int advanceDist = rand() % otterList.size();
        std::advance(it, advanceDist);
        otterList.insertAfter(it, o);
        EXPECT_TRUE(otterList.contains(o));
    }
}

TEST(linkedListOtterTest, deleteBackTests)
{
  LinkedList<Otter> otterList;
    for (int i = 0; i < 1000; ++i) {
        otterList.insertFront(Otter{std::to_string(i)});
    }
    for (int i = 0; i < 1000; ++i) {
        Otter deletee = otterList.deleteBack();
        ASSERT_EQ(deletee, Otter{std::to_string(i)});
        ASSERT_EQ(otterList.size(), 999 - i);
    }
}

TEST(linkedListOtterTest, iteratorTests)
{
    LinkedList<Otter> otterList;
    for (int i = 0; i < 1000; ++i) {
        otterList.insertFront(Otter{std::to_string(i)});
    }

    int j = 999;
    for (LinkedList<Otter>::iterator i = otterList.begin(); i != otterList.end(); ++i) {
        EXPECT_TRUE(*i == Otter{std::to_string(j)});
        --j;
    }
}

TEST(linkedListOtterTest, deleteElementTests)
{
    srand (time(NULL));
    LinkedList<Otter> otterList;
    Otter phokey = Otter{"phokey"};
    otterList.insertFront(phokey);
    EXPECT_TRUE(otterList.contains(phokey));
    otterList.deleteElement(phokey);
    EXPECT_FALSE(otterList.contains(phokey));
    for (int i = 0; i < 1000; ++i) {
        Otter test = Otter{std::to_string(i)};
        otterList.insertFront(test);
        EXPECT_TRUE(otterList.contains(test));
    }
    ASSERT_EQ(otterList.size(), 1000) << "list should have 1000 elements";
    for (int i = 0; i < 1000; ++i) {
        Otter test = Otter{std::to_string(rand() % 1000)};
        otterList.deleteElement(test);
        EXPECT_FALSE(otterList.contains(test)) << "list should no longer have element";
    }
    EXPECT_TRUE(otterList.size() < 1000) << "list should have deleted at least one element";
}

