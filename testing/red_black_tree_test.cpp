/**
 * \file rbtree-test.cpp
 * \author Andrew Scott
 *
 * \brief Tests an RBTree for correctness using multiple types
 *
 * \details
 *   Configured to use the templated RBTree found in rbtree.hpp as
 *   avl trees of different types
 *
 */

#include "rbtree.hpp"
#include <iostream>
#include <stdlib.h>      // rand(), srand()
#include <time.h>       // time
#include <gtest/gtest.h>
#include "otter.hpp"

TEST(rbTreeIntTest, insertTests)
{
    RBTree<int> intTree;
    int test = 0;
    EXPECT_FALSE(intTree.contains(test));
    bool inserted = intTree.insert(test);
    EXPECT_TRUE(intTree.contains(test));
    EXPECT_TRUE(intTree.size() == 1);
    EXPECT_TRUE(inserted);
    int test2 = 1;
    inserted = intTree.insert(test2);
    EXPECT_TRUE(intTree.contains(test2));
    EXPECT_TRUE(intTree.size() == 2);
    EXPECT_TRUE(inserted);
    EXPECT_TRUE(intTree.hasRBProperties());
    // check that inserting again returns false
    EXPECT_FALSE(intTree.insert(test));
    for (int i = 2; i < 21; ++i) {
        EXPECT_FALSE(intTree.contains(i));
        intTree.insert(i);
        EXPECT_TRUE(intTree.contains(i));
        EXPECT_TRUE(intTree.hasRBProperties());
    }
    intTree.print(std::cout);

    RBTree<int> intTree2;
    for (int i = 0; i < 200; ++i) {
        int intToInsert = rand() % 200;
        //EXPECT_FALSE(intTree2.contains(intToInsert));
        intTree2.insert(intToInsert);
        EXPECT_TRUE(intTree2.contains(intToInsert));
        EXPECT_TRUE(intTree.hasRBProperties());
    }
}

TEST(rbTreeIntTest, basicEqualityTests)
{
    RBTree<int> intTree;
    RBTree<int> intTree2;
    // check that empty trees are equal
    EXPECT_TRUE(intTree == intTree2);
    int test = 120;
    intTree.insert(test);
    // check that different size trees are not equal
    ASSERT_NE(intTree, intTree2);
    intTree2.insert(test);
    // check that equality works with one element trees
    ASSERT_EQ(intTree, intTree2);
    for (int i = 0; i < 100; ++i) {
        intTree.insert(i);
        intTree2.insert(i);
    }
    // check that equality works for larger trees
    ASSERT_EQ(intTree, intTree2);
    intTree.insert(100);
    // check that inequality works with larger trees
    ASSERT_NE(intTree, intTree2);
}

TEST(rbTreeIntTest, copyConstructorTests)
{
    RBTree<int> intTree;
    int test = 120;
    intTree.insert(test);
    RBTree<int> intTree2{intTree};
    // tests copy constructor copying one element tree
    ASSERT_EQ(intTree, intTree2);
    int test2 = 220;
    intTree.insert(test2);
    // make sure the copied tree is different after adding an element to it
    ASSERT_NE(intTree, intTree2);
    for (int i = 0; i < 100; ++i) {
        intTree2.insert(i);
    }
    RBTree<int> intTree3{intTree2};
    // test copying a larger tree
    // also tests equality operator on larger trees
    ASSERT_EQ(intTree2, intTree3);
    ASSERT_NE(intTree, intTree3);
}

TEST(rbTreeIntTest, assignmentOperatorTests)
{
    RBTree<int> intTree;
    int test = 1234;
    intTree.insert(test);
    RBTree<int> intTree2;
    ASSERT_NE(intTree, intTree2);
    intTree2 = intTree;
    ASSERT_EQ(intTree, intTree2);
    for (int i = 0; i < 1000; ++i) {
        intTree2.insert(i);
    }
    
    ASSERT_NE(intTree, intTree2);
    RBTree<int> intTree3;
    ASSERT_NE(intTree2, intTree3);
    intTree3 = intTree2;
    ASSERT_EQ(intTree2, intTree3);
    intTree3.insert(12345);
    ASSERT_NE(intTree2, intTree3);
}

TEST(rbTreeIntTest, iteratorTests)
{
    RBTree<int> intTree;
    for (int i = 0; i < 100; ++i) {
        intTree.insert(i);
    }
    int num = 0;
    for (RBTree<int>::iterator i = intTree.begin(); i != intTree.end(); ++i) {
        ASSERT_EQ(num, *i);
        ++num;
    }
}

TEST(rbTreeIntTest, deleteElementTests) {
    RBTree<int> intTree;
    intTree.insert(5);
    // just an assurance that the delete is actually changing the value of
    // contains(5)
    EXPECT_TRUE(intTree.contains(5));
    intTree.deleteElement(5);
    // check that the tree is now empty
    ASSERT_EQ(intTree.size(), 0);
    EXPECT_FALSE(intTree.contains(5));
    for (int i = 0; i < 5; ++i) {
        intTree.insert(i);
    }
    intTree.print(std::cout);
    // 0 will be a leaf, so we are testing the case where we delete a leaf
    bool deleted = intTree.deleteElement(0);
    EXPECT_FALSE(intTree.contains(0));
    ASSERT_EQ(intTree.size(), 4);
    ASSERT_EQ(deleted, true);
    EXPECT_TRUE(intTree.hasRBProperties());
    // put 0 back in the tree
    intTree.print(std::cout);
    /*intTree.insert(0);
    for (int i = 0; i < 5; ++i) {
        // check that several deletes work
        EXPECT_TRUE(intTree.contains(i));
        bool deleted = intTree.deleteElement(i);
        EXPECT_FALSE(intTree.contains(i));
        EXPECT_TRUE(deleted);
        ASSERT_EQ(intTree.size(), 4 - i);
        EXPECT_TRUE(intTree.hasRBProperties());
    }

    for (int i = 0; i < 30; ++i) {
        intTree.insert(i);
    }
    for (int i = 29; i >=0; --i) {
        // check that lots of deletes work
        EXPECT_TRUE(intTree.contains(i)) << "list should contain " << i;
        bool deleted = intTree.deleteElement(i);
        EXPECT_FALSE(intTree.contains(i));
        EXPECT_TRUE(deleted);
        ASSERT_EQ(intTree.size(), i);
        EXPECT_TRUE(intTree.hasRBProperties());
        intTree.print(std::cout);
    }*/
}
/*
TEST(rbTreeOtterTest, insertTests)
{
    RBTree<Otter> otterTree;
    Otter phokey = Otter{"phokey"};
    EXPECT_FALSE(otterTree.contains(phokey));
    bool inserted = otterTree.insert(phokey);
    EXPECT_TRUE(otterTree.contains(phokey));
    EXPECT_TRUE(otterTree.size() == 1);
    EXPECT_TRUE(inserted);
    Otter test2 = Otter{"another otter"};
    inserted = otterTree.insert(test2);
    EXPECT_TRUE(otterTree.contains(test2));
    EXPECT_TRUE(otterTree.size() == 2);
    EXPECT_TRUE(inserted);
    // check that inserting again returns false
    EXPECT_FALSE(otterTree.insert(phokey));
    for (int i = 0; i < 100; ++i) {
        Otter o{std::to_string(i)};
        EXPECT_FALSE(otterTree.contains(o));
        inserted = otterTree.insert(o);
        EXPECT_TRUE(otterTree.contains(o));
        EXPECT_TRUE(inserted);
    }
}

TEST(rbTreeOtterTest, basicEqualityTests)
{
    RBTree<Otter> otterTree;
    RBTree<Otter> otterTree2;
    // check that empty trees are equal
    EXPECT_TRUE(otterTree == otterTree2);
    Otter phokey = Otter{"phokey"};
    otterTree.insert(phokey);
    // check that different size trees are not equal
    ASSERT_NE(otterTree, otterTree2);
    otterTree2.insert(phokey);
    // check that equality works with one element trees
    ASSERT_EQ(otterTree, otterTree2);
    for (int i = 0; i < 100; ++i) {
        Otter o = Otter{std::to_string(i)};
        otterTree.insert(o);
        otterTree2.insert(o);
    }
    // check that equality works for larger trees
    ASSERT_EQ(otterTree, otterTree2);
    otterTree.insert(Otter{"another"});
    // check that inequality works with larger trees
    ASSERT_NE(otterTree, otterTree2);
}

TEST(rbTreeOtterTest, copyConstructorTests)
{
    RBTree<Otter> otterTree;
    Otter phokey = Otter{"phokey"};
    otterTree.insert(phokey);
    RBTree<Otter> otterTree2{otterTree};
    // tests copy constructor copying one element tree
    ASSERT_EQ(otterTree, otterTree2);
    Otter test2 = Otter{"another"};
    otterTree.insert(test2);
    // make sure the copied tree is different after adding an element to it
    ASSERT_NE(otterTree, otterTree2);
    for (int i = 0; i < 100; ++i) {
        Otter o{std::to_string(i)};
        otterTree2.insert(o);
    }
    RBTree<Otter> otterTree3{otterTree2};
    // test copying a larger tree
    // also tests equality operator on larger trees
    ASSERT_EQ(otterTree2, otterTree3);
    ASSERT_NE(otterTree, otterTree3);
}

TEST(rbTreeOtterTest, assignmentOperatorTests)
{
    RBTree<Otter> otterTree;
    Otter phokey = Otter{"phokey"};
    otterTree.insert(phokey);
    RBTree<Otter> otterTree2;
    ASSERT_NE(otterTree, otterTree2);
    otterTree2 = otterTree;
    ASSERT_EQ(otterTree, otterTree2);
    for (int i = 0; i < 1000; ++i) {
        Otter o{std::to_string(i)};
        otterTree2.insert(o);
    }
    
    ASSERT_NE(otterTree, otterTree2);
    RBTree<Otter> otterTree3;
    ASSERT_NE(otterTree2, otterTree3);
    otterTree3 = otterTree2;
    ASSERT_EQ(otterTree2, otterTree3);
    otterTree3.insert(Otter{"another"});
    ASSERT_NE(otterTree2, otterTree3);
}

TEST(rbTreeOtterTest, iteratorTests)
{
    RBTree<Otter> otterTree;
    for (int i = 0; i < 100; ++i) {
        otterTree.insert(Otter{std::to_string(i)});
    }
    int num = 0;
    for (RBTree<Otter>::iterator i = otterTree.begin(); i != otterTree.end(); ++i) {
        *i;
        ++num;
    }
}

TEST(rbTreeOtterTest, deleteElementTests) {
    RBTree<Otter> otterTree;
    Otter phokey = Otter{"phokey"};
    otterTree.insert(phokey);
    // just an assurance that the delete is actually changing the value of
    // contains(phokey)
    EXPECT_TRUE(otterTree.contains(phokey));
    otterTree.deleteElement(phokey);
    // check that the tree is now empty
    ASSERT_EQ(otterTree.size(), 0);
    EXPECT_FALSE(otterTree.contains(phokey));


    for (int i = 0; i < 200; ++i) {
        Otter o{std::to_string(i)};
        otterTree.insert(o);
    }
    for (int i = 199; i >=0; --i) {
        Otter o{std::to_string(i)};
        // check that lots of deletes work
        EXPECT_TRUE(otterTree.contains(o)) << "list should contain " << i;
        bool deleted = otterTree.deleteElement(o);
        EXPECT_FALSE(otterTree.contains(o));
        EXPECT_TRUE(deleted);
        ASSERT_EQ(otterTree.size(), i);
    }
}*/
