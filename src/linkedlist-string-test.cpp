/**
* \file linkedlist-test.cpp
* \author Andrew Scott
*
* \brief Tests a LinkedList for correctness using multiple types
*
* \details
*   Configured to use the templated linkedlist found in linkedlist.hpp as
*   linked lists of different types
*/

#include "linkedlist.hpp"
#include <iostream>
#include <cstddef>
#include <cassert>
#include <iterator>
#include <stdlib.h>
#include <gtest/gtest.h>

using std::string;

TEST(linkedListTest, basicStringTests)
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
    string out1 = stringList.deleteFront();
    EXPECT_TRUE(stringList.size() == 1);
    EXPECT_TRUE(out1 == test2);
    string out2 = stringList.deleteFront();
    EXPECT_TRUE(stringList.size() == 0);
    EXPECT_TRUE(out2 == test);
}
/*
TEST(linkedListTest, insertBackTests)
{
    LinkedList<Otter> otterList;
    Otter phokey{"phokey"};
    EXPECT_FALSE(otterList.contains(phokey));
    otterList.insertBack(phokey);
    EXPECT_TRUE(otterList.contains(phokey));
    Otter otter2{"otter2"};
    otter2.cleanFur();
    EXPECT_FALSE(otterList.contains(otter2));
    otterList.insertBack(otter2);
    EXPECT_TRUE(otterList.contains(otter2));
    EXPECT_TRUE(otterList.size() == 2);
}*/

TEST(linkedListTest, insertAfterTests)
{
    LinkedList<string> stringList;
    string test = "hello world";
    stringList.insertFront(test);
    EXPECT_TRUE(stringList.contains(test));
    for (int i = 0; i < 1000; ++i) {
        LinkedList<string>::iterator it = stringList.begin();
        string s = std::to_string(i);
        std::advance(it, stringList.size() / 2);
        stringList.insertAfter(it, s);
        EXPECT_TRUE(stringList.contains(s));
    }

    LinkedList<int> intList;
    for (int i = 0; i < 1000; ++i) {
        LinkedList<int>::iterator it = intList.begin();
        intList.insertAfter(it, i);
        EXPECT_TRUE(intList.contains(i));
    }
}

TEST(linkedListTest, iteratorTests)
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

TEST(linkedListTest, basicTests)
{
    string test = "hello";
    LinkedList<string> stringList;
    EXPECT_FALSE(stringList.contains(test));
    stringList.insertFront(test);
    EXPECT_TRUE(stringList.contains(test));
}



