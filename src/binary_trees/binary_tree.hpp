/**
 * \file base_binary_tree.hpp
 *
 * \author Andrew Scott
 *
 * \brief Base binary search tree class, contains code common to all binary
 * trees
 *
 */

#ifndef BINARY_TREE_INCLUDED
#define BINARY_TREE_INCLUDED 1
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
* \class BinaryTree
* \brief A base binary tree class, containing code that is common to all binary trees
*/

public BinaryTree<T>{

private:
   class Iterator; // Forward declaration

public:

   
    /**
    * \brief 
    * Destructor
    *
    */
    ~BinaryTree();
   
    /**
    * \brief
    * Copy Constructor
    *
    */
    BinaryTree<T>(const BinaryTree<T>& orig);

    /**
    * \brief
    * Assignment Operator
    *
    */
    BinaryTree<T>& operator=(const BinaryTree<T>& rhs);

    /**
    * \brief
    * Tree swap function
    *
    *
    */
    void swap(BinaryTree<T>& rhs);


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
    * 
    * \note runs in O(n) time
    */
    size_t height() const;

    /**
    * \brief 
    * Inserts an element into the tree
    *
    * \returns true if the element did not exist in the tree already and
    * therefore was inserted, false otherwise
    *
    * \note runs in O(log(n)) time
    */
    virtual bool insert(const T& element) = 0;

    /**
    * \brief 
    * Deletes a particular element in the tree
    *
    * \returns
    * true if the element was deleted, false otherwise
    *
    * \note runs in log(n) time
    */
    virtual bool deleteElement(const T& element) = 0;

    /**
    * \brief 
    * Checks if an element is in the tree
    *
    * \returns true if the element is in the tree, false otherwise
    *
    * \note runs in O(log(n)) time
    */
    virtual bool contains(const T& element) const = 0;

    /**
    * \brief
    * Binary Tree equality operator
    *
    * \returns true if the tree rhs is equal to the current tree, false
    * otherwise
    *
    */
    bool operator==(const BinaryTree<T>& rhs) const;

    /**
    * \brief
    * Binary Tree inequality operator
    *
    * \returns true if the tree rhs is not equal to the current tree, false
    * otherwise
    */
    bool operator!=(const BinaryTree<T>& rhs) const;

    /**
    * \brief
    * returns true if the tree is empty, false otherwise
    */
    bool empty();

    /**
    * \brief returns true if the tree is balanced, false otherwise
    *
    */
    //bool isBalanced();

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
        T element_;            ///> the element at this node
        Node* left_;           ///> this node's left child
        Node* right_;          ///> this node's right child
        Node* parent_;         ///> this node's parent
        int height_;           ///> this node's height
        //size_t leftHeight_;  ///> this node's right subtree's height
        //size_t rightHeight_; ///> this node's left subtree's height
        /**
        * \brief Node constructor
        *
        */
        Node(const T& element, Node* left, Node* right, Node* parent);
        /**
        * \brief Node default destructor
        *
        */
        ~Node();

        /**
        * \brief Size function
        * \returns the size of this node (sum of its children's size)
        */
        size_t size() const;

        int getBalance();

        void updateHeight();

        //size_t subtreeHeight() const;

        Node() = delete; // disable default constructor
        Node& operator=(const Node&) = delete; // disable assignment operator
    };
    size_t size_;
    Node* root_;

    /**
    * \brief prints the tree to the terminal so it actually looks like a tree
    * 
    *
    */
    void printPretty(Node* root, int level, int indentSpace,
                     std::ostream& out) const;
    void printLeaves(int indentSpace, int level, int nodesInThisLevel,
                     const std::deque<Node*>& nodesQueue,
                     std::ostream& out) const;
    void printNodes(int branchLen, int nodeSpaceLen, int startLen,
                    int nodesInThisLevel, const std::deque<Node*>& nodesQueue,
                    std::ostream& out) const;
    void printBranches(int branchLen, int nodeSpaceLen, int startLen,
                       int nodesInThisLevel,
                       const std::deque<Node*>& nodesQueue,
                       std::ostream& out) const;

    /**
     * \brief
     * Rotates the tree to the right
     *
     * \param top The node to rotate about
     * 
     */
    void rightRotate(Node* top);

    /**
     * \brief
     * Rotates the tree to the left
     *
     * \param top The node to rotate about
     * 
     */
    void leftRotate(Node* top);


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
     * \brief
     * Tells whether a element is present in the tree
     *
     * \param here The node start checking at
     * \param element The element to check if present
     *
     * \returns True if the element is present in the tree, false if otherwise
     */
    Node* findNode(Node* here, const T& element) const;

    Node* getNextNode(Node* here);

    static int nodeHeight(Node* here);

    /**
    * \brief returns the height of the subtree with the given node as the root
    *
    */
    size_t subtreeHeight(Node* here) const;

    /**
    * \brief deletes a leaf
    *
    */
    void deleteLeaf(Node* deletee);

    /**
    * \brief deletes a stick
    *
    */
    void deleteStick(Node* deletee, bool deleteLeft);

    /**
    * \brief deletes a node with two children
    *
    */
    void deleteTwoChildNode(Node* deletee);

    /**
    * \brief deletes a tree with one element
    *
    */
    bool deleteOneElementTree(const T& element);

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
        Iterator& operator--();
        T& operator*() const;
        bool operator==(const Iterator& other) const;
        bool operator!=(const Iterator& other) const;

    private:
        friend class AvlTree;
        Iterator(Node* index);
        Node* current_;
    };

};

template<typename T>
/// Provide a non-member version of swap to allow standard swap(x,y) usage.
void swap(BinaryTree<T>& lhs, BinaryTree<T>& rhs);

#include "binary_tree_private.hpp"

#endif // BINARY_TREE_INCLUDED
