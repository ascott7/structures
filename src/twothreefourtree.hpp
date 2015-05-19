/**
 * \file 234tree.hpp
 *
 * \author Rachel Lee
 *
 * \brief templated 2-3-4 tree class
 *
 */

#ifndef TWOTHREEFOUR_TREE_INCLUDED
#define TWOTHREEFOUR_TREE_INCLUDED 1
#include "abstracttree.hpp"
//#include <cstddef>
//#include <cassert>
//#include <iostream>
#include <time.h>       // time
#include <stack>        // std::queue
//#include <list>
#include <iomanip>
#include <cmath>

template <typename T>

/**
* \class
* \brief A templated 2-3-4 tree
*
*/

class twothreefourTree : public AbstractTree<T> {

private:
   class Iterator; // Forward declaration1

public:
    typedef size_t size_type;

    /**
    * Default Constructor
    */
    twothreefourTree();

    /**
    * Copy Constructor
    */
    twothreefourTree<T>(const twothreefourTree<T>& orig);

    /**
    * Assignment Operator
    */
    twothreefourTree<T>& operator=(const twothreefourTree<T>& rhs);

    /**
    * 2-3-4 Tree swap function
    */
    void swap(twothreefourTree<T>& rhs);

    /**
    * Default Destructor
    */
    ~twothreefourTree();

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
    size_t size() const override;

    /**
    * \brief Determines the height of the tree
    */
    size_t height() const;

    /**
    * \brief 
    * Inserts an element into the tree
    */
    bool insert(const T& element) override;

    /**
    * \brief 
    * Deletes a particular element in the tree
    *
    * \returns
    * true if the element was deleted, false otherwise
    */
    //bool delete(const T& element) override;

    /**
    * Checks if an element is in the tree
    */
    bool contains(const T& element) const override;

    /**
    * 2-3-4 Tree equality operator
    */
    bool operator==(const twothreefourTree<T>& rhs) const;

    /**
    * \brief
    * 2-3-4 Tree inequality operator
    */
    bool operator!=(const twothreefourTree<T>& rhs) const;

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
        T firstElement_;     ///< the left element at this node
        T secondElement_;    ///< the middle element at this node
        T thirdElement_;     ///< the right element at this node
        Node* first_;        ///< this node's first child
        Node* second_;       ///< this node's second child
        Node* third_;        ///< this node's third child
        Node* fourth_;       ///< this node's fourth child
        Node* parent_;       ///< this node's parent
        size_t size_;        ///< this node's size
        size_t nodeType_;        ///< this node's type

        /**
         * \brief Node constructor
         */
        Node(const T& firstElement, Node* first, Node* second, Node* parent, size_t nodeType);
        
        /**
         * \brief default destructor
         */
        ~Node();

        Node() = delete; // disable default constructor
        Node& operator=(const Node&) = delete; // disable assignment operator
    };

    //size_t size_;
    Node* root_;

    /**
     * pretty prints the tree
     */
    void printPretty(Node* root, int level, int indentSpace, std::ostream& out) const;
    void printLeaves(int indentSpace, int level, int nodesInThisLevel, 
        const std::deque<Node*>& nodesQueue, std::ostream& out) const;
    void printNodes(int branchLen, int nodeSpaceLen, int startLen, 
        int nodesInThisLevel, const std::deque<Node*>& nodesQueue,
         std::ostream& out) const;
    void printBranches(int branchLen, int nodeSpaceLen, int startLen,
     int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const;

    bool is2node(Node*& here); ///< Checks if the node is a 2-node

    bool is3node(Node*& here); ///< Checks if the node is a 3-node

    bool is4node(Node*& here); ///< Checks if the node is a 4-node

    bool isLeaf(Node*& here); ///< Checks if here is a leaf

    /**
     * \brief Checks if here is the first child of its parent
     *
     * \note Also checks if here is a valid node
     */
    bool isFirstChild(Node*& here);

    /**
     * \brief Checks if here is the second child of its parent
     *
     * \note Also checks if here is a valid node
     */
    bool isSecondChild(Node*& here);

    /**
     * \brief Checks if here is the third child of its parent
     *
     * \note Also checks if here is a valid node
     *       and if here's parent is a 3- or a 4- node (i.e. legal to have a third child)
     */
    bool isThirdChild(Node*& here);

    /**
     * \brief Checks if here is the fourth child of its parent
     *
     * \note Also checks if here is a valid node
     *       and if here's parent is a 4-node (i.e. legal to have a fourth child)
     */
    bool isFourthChild(Node*& here);

    /* \brief Compares element to a 2-node's elements
     *
     * \returns The index to which the element belongs in a 2-node (starting from 1)
     *
     * \note For example, compareElement(here, 5) where here is a 2-node with its element {8} returns 1
     *       Also checks if here is a 2-node
     */
    size_t twoNodeIndex(Node*& here, const T& element);

    /* \brief Compares element to a 3-node's elements
     *
     * \returns The index to which the element belongs in a 3-node (starting from 1)
     *
     * \note For example, compareElement(here, 5) where here is a 3-node with its elements {2, 7} returns 2
     *       and compareElement(here, 5) where here is a 3-node with its elements {1, 3} returns 3
     *       Also checks if here is a 3-node
     */
    size_t threeNodeIndex(Node*& here, const T& element);

    /*
     * Splits a 4-node into two 2-nodes and pushes the middle key up to its parent
     */
    void split4node(Node*& here);

    /**
     * Returns the size of the node's subtree
     */
    size_t nodeSize(Node* here) const;

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
    * inserts a node into the root of the tree
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
     */
    Node* findNode(Node* here, const T& element) const;

    /**
    * \brief returns the height of the subtree with the given node as the root
    *
    */
    size_t subtreeHeight(Node* here) const;

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
        friend class twothreefourTree;
        Iterator(Node* index);
        Node* current_;
    };

};

template<typename T>
/// Provide a non-member version of swap to allow standard swap(x,y) usage.
void swap(twothreefourTree<T>& lhs, twothreefourTree<T>& rhs);

#include "twothreefourtree-private.hpp"

#endif // TWOTHREEFOUR_TREE_INCLUDED
