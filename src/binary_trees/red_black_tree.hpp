/**
 * \file rbtree.hpp
 *
 * \author Andrew Scott
 *
 * \brief templated red black tree class
 *
 */

#ifndef RB_TREE_INCLUDED
#define RB_TREE_INCLUDED 1
#include "abstracttree.hpp"
#include <cstddef>
#include <cassert>
#include <iostream>
#include <time.h>       // time
#include <stdlib.h>     // rand(), srand()
#include <stack>        // std::stack
#include <list>
#include <iomanip>
#include <cmath>


#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define WHITE   "\033[37m"      /* White */

template <typename T>

/**
* \class RBTree
* \brief A templated random tree
*/

class RBTree : public AbstractTree<T>{

private:
   class Iterator; // Forward declaration1

public:
    typedef size_t              size_type;
    /**
    * \brief 
    * Default Constructor
    *
    */
    RBTree();

    /**
    * \brief
    * Copy Constructor
    *
    */
    RBTree<T>(const RBTree<T>& orig);

    /**
    * \brief
    * Assignment Operator
    *
    */
    RBTree<T>& operator=(const RBTree<T>& rhs);

    /**
    * \brief
    * Random Tree swap function
    *
    *
    */
    void swap(RBTree<T>& rhs);

    /**
    * \brief 
    * Default Destructor
    *
    */
    ~RBTree();

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
    bool insert(const T& element);

    /**
    * \brief 
    * Deletes a particular element in the tree
    *
    * \returns
    * true if the element was deleted, false otherwise
    *
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
    bool operator==(const RBTree<T>& rhs) const;

    /**
    * \brief
    * Random Tree inequality operator
    *
    */
    bool operator!=(const RBTree<T>& rhs) const;

    /**
    * \brief
    * returns true if the tree is empty, false otherwise
    */
    bool empty() const;

    /**
    * \brief returns true if the tree is balanced, false otherwise
    *
    */
    bool hasRBProperties() const;

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
        T element_;     ///> the element at this node
        Node* left_;    ///> this node's left child
        Node* right_;   ///> this node's right child
        Node* parent_;  ///> this node's parent
        bool isRed_;    ///> true if this node is red, false if black
        bool isDoubleBlack_;
        /**
        * \brief Node constructor
        *
        */
        Node(const T& element, Node* left, Node* right, Node* parent, bool isRed);
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

        size_t subtreeHeight() const;

        bool hasOneChild() const;

        bool isThreeNode() const;

        void pushUp();

        void makeThreeNode();

        bool hasRBProperties();

        size_t numBlackNodes();

        Node() = delete; // disable default constructor
        Node& operator=(const Node&) = delete; // disable assignment operator
    };
    size_t size_;
    Node* root_;

    /**
    * \brief pretty prints the tree
    *
    */
    void printPretty(Node* root, int level, int indentSpace, std::ostream& out) const;
    void printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const;
    void printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const;
    void printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const;

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

    void rebalanceAfterInsert(Node* here);

    void rebalanceAfterDelete(Node* here);

    void pushUp(Node* here);

    void pushDownBlackness(Node* here);

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
        friend class RBTree;
        Iterator(Node* index);
        Node* current_;
    };

};

template<typename T>
/// Provide a non-member version of swap to allow standard swap(x,y) usage.
void swap(RBTree<T>& lhs, RBTree<T>& rhs);

#include "RBTree-private.hpp"

#endif // RB_TREE_INCLUDED
