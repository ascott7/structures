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
    LinkedList<int> intList;
    for (int i = 0; i < 1000; ++i) {
        intList.insertFront(i);
    }

    int j = 999;
    for (LinkedList<int>::iterator i = intList.begin(); i != intList.end(); ++i) {
        EXPECT_TRUE(*i == j);
        --j;
    }
}

TEST(linkedListIntTest, insertFrontTests)
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

TEST(linkedListIntTest, insertBackTests)
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

TEST(linkedListIntTest, insertAfterTests)
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

TEST(linkedListIntTest, deleteFrontTests)
{

}

TEST(linkedListIntTest, deleteBackTests)
{

}

TEST(linkedListIntTest, iteratorTests)
{
    LinkedList<int> intList;
    for (int i = 0; i < 1000; ++i) {
        intList.insertFront(i);
    }

    int j = 999;
    for (LinkedList<int>::iterator i = intList.begin(); i != intList.end(); ++i) {
        EXPECT_TRUE(*i == j);
        --j;
    }
}

TEST(linkedListOtterTests, insertFrontTests)
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

TEST(linkedListOtterTests, insertBackTests)
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

TEST(linkedListOtterTests, insertAfterTests)
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

TEST(linkedListOtterTests, deleteFrontTests)
{

}

TEST(linkedListOtterTests, deleteBackTests)
{

}

TEST(linkedListOtterTests, iteratorTests)
{
    LinkedList<int> intList;
    for (int i = 0; i < 1000; ++i) {
        intList.insertFront(i);
    }

    int j = 999;
    for (LinkedList<int>::iterator i = intList.begin(); i != intList.end(); ++i) {
        EXPECT_TRUE(*i == j);
        --j;
    }
}

