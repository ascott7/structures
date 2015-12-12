/**
 * \file splaytree.hpp
 *
 * \author Andrew Scott
 *
 * \brief templated splay tree class
 *
 */

#ifndef SPLAY_TREE_INCLUDED
#define SPLAY_TREE_INCLUDED 1
#include "binary_tree.hpp"
#include <cstddef>
#include <cassert>
#include <iostream>
#include <time.h>       // time
#include <stdlib.h>     // rand(), srand()
#include <stack>        // std::stack
#include <list>
#include <iomanip>
#include <cmath>

template <typename T>

/**
* \class SplayTree
* \brief A templated splay tree
*/

class SplayTree : public BinaryTree<T> {

public:
    /**
     * \brief 
     * Default Constructor
     *
     */
    SplayTree();


    /**
     * \brief 
     * Default Destructor
     *
     */
    ~SplayTree();

    /**
     * \brief 
     * Inserts an element into the tree
     *
     */
    bool insert(const T& element);

    /**
     * \brief 
     * Deletes a particular element in the tree
     *
     * \returns
     * true if the element was deleted, false otherwise
     *
     * \note log(n) time
     */
    bool deleteElement(const T& element);

    /**
     * \brief 
     * Checks if an element is in the tree
     *
     */
    bool contains(const T& element) const;

private:

    /**
     * \brief
     * Inserts a node into the tree
     *
     * \param here The node to insert at
     * \param element The element to insert
     */
    bool insertNode(Node*& here, const T& element);

    /**
    * \brief
    * inserts an node into the root of the tree
    * 
    * \param here The node to insert at
    * \param element The element to insert
    *
    */
    bool insertNodeAtRoot(Node*& here, const T& element);

    /**
     * \brief splays the specified element to the root of the tree
     *
     */
    void splayToRoot(Node* newRoot) const;

};

#include "splay_tree_private.hpp"

#endif // SPLAY_TREE_INCLUDED
