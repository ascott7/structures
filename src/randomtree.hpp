/**
 * \file randomtree.hpp
 *
 * \author Andrew Scott
 *
 * \brief templated random tree class
 *
 */

#ifndef RANDOM_TREE_INCLUDED
#define RANDOM_TREE_INCLUDED 1
#include <cstddef>
#include <cassert>
#include <iostream>
#include <time.h>       // time
#include <stdlib.h>     // rand(), srand()
#include <stack>        // std::stack

template <typename T>

/**
* \class RandomTree
* \brief A templated random tree
*/

class RandomTree {

private:
   class Iterator; // Forward declaration1

public:
    typedef size_t              size_type;
    /**
    * \brief 
    * Default Constructor
    *
    */
    RandomTree();

    /**
    * \brief
    * Copy Constructor
    *
    */
    RandomTree<T>(const RandomTree<T>& orig);

    /**
    * \brief
    * Assignment Operator
    *
    */
    RandomTree<T>& operator=(const RandomTree<T>& rhs);

    /**
    * \brief
    * Random Tree swap function
    *
    *
    */
    void swap(RandomTree<T>& rhs);

    /**
    * \brief 
    * Default Destructor
    *
    */
    ~RandomTree();

    // Allow users to iterate over the contents of the list. 
    using iterator = Iterator; 
    iterator begin() const; ///< An iterator that refers to the first element
    iterator end() const;   ///< A "past-the-end" iterator

    /**
    * \brief 
    * Size function
    *
    * \returns the number of elements in the tree
    */
    size_t size() const;

    /**
    * \brief Determines the height of the tree
    */
    size_t height() const;

    /**
    * \brief 
    * Inserts an element into the tree
    *
    */
    void insert(const T& element);

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

    /**
    * \brief
    * Random Tree equality operator
    *
    */
    bool operator==(const RandomTree<T>& rhs) const;

    /**
    * \brief
    * Random Tree inequality operator
    *
    */
    bool operator!=(const RandomTree<T>& rhs) const;

    /**
    * \brief
    * returns true if the tree is empty, false otherwise
    */
    bool empty();

        /**
     * \brief
     * Prints the tree in a readable form
     *
     * \param out the output stream to print to
     * 
     * \returns the output stream after printing
     */
    std::ostream& print(std::ostream& out) const;

    /**
     * \brief
     * Prints the height of the tree
     *
     * \param out the output stream to print to
     * 
     * \returns the output stream after printing
     */
    std::ostream& printStatistics(std::ostream& out) const;

private:
    struct Node {
        T element_;    ///> the element at this node
        Node* left_;   ///> this node's left child
        Node* right_;  ///> this node's right child
        /**
        * \brief Node constructor
        *
        */
        Node(const T& element, Node* left, Node* right);
        /**
        * \brief default destructor
        *
        */
        ~Node();

        /**
        * \brief Size function
        * \returns the size of this node (sum of its children's size)
        */
        size_t size() const;

        //bool operator==(const RandomTree::Node& rhs) const;

        /**
        * \brief Print a node
        * \param out An output stream to print to
        * \returns the output stream with the node printed to it
        */
        std::ostream& print(std::ostream& out) const;

        Node() = delete; // disable default constructor
        Node& operator=(const Node&) = delete; // disable assignment operator
    };
    size_t size_;
    Node* root_;

    /**
     * \brief
     * Rotates the tree to the right
     *
     * \param top The node to rotate about
     * 
     */
    void rightRotate(Node*& top);

    /**
     * \brief
     * Rotates the tree to the left
     *
     * \param top The node to rotate about
     * 
     */
    void leftRotate(Node*& top);


    /**
     * \brief
     * Inserts a node into the tree
     *
     * \param here The node to insert at
     * \param element The element to insert
     */
    void insertNode(Node*& here, const T& element);

    /**
    * \brief
    * inserts an node into the root of the tree
    * 
    * \param here The node to insert at
    * \param element The element to insert
    *
    */
    void insertNodeAtRoot(Node*& here, const T& element);

    /**
     * \brief
     * Tells whether a element is present in the tree
     *
     * \param here The node start checking at
     * \param element The element to check if present
     *
     * \returns True if the element is present in the tree, false if otherwise
     */
    bool existsNode(Node* here, const T& element) const;

    /**
    * \brief returns the height of the subtree with the given node as the root
    *
    */
    size_t subtreeHeight(Node* here) const;

    /**
    * \brief returns a copy of a node
    *
    */
    //Node* copyNode(const Node* node);

    class Iterator
    {
    public:
        // Definitions that are required for this class to be a well-behaved
        // STL-style iterator that moves forward through a collection of T's.
        using value_type = T;
        using reference = value_type&;
        using pointer = value_type*;
        using difference_type = ptrdiff_t;
        using iterator_category = std::forward_iterator_tag;

        // Iterator operations
        Iterator& operator++();
        T& operator*() const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        friend class RandomTree;
        Iterator(Node* index, std::stack<Node*> parents);
        Node* current_;
        std::stack<Node*> parents_;
    };

};

template<typename T>
/// Provide a non-member version of swap to allow standard swap(x,y) usage.
void swap(RandomTree<T>& lhs, RandomTree<T>& rhs);

#include "randomtree-private.hpp"

#endif // RANDOM_TREE_INCLUDED