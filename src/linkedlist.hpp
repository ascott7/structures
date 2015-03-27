/**
 * \file linkedlist.hpp
 *
 * \author Andrew Scott
 *
 * \brief templated linked list class
 *
 */

#ifndef LINKEDLIST_HPP_INCLUDED
#define LINKEDLIST_HPP_INCLUDED 1
#include <cstddef>
#include <cassert>
#include <iostream>

template <typename T>

/**
* \class LinkedList
* \brief A templated linked list
*/

class LinkedList {

private:
    class Iterator; // Forward declaration

public:
    typedef size_t              size_type;
    /**
    * \brief 
    * Default Constructor
    *
    */
    LinkedList();

    /**
    * \brief
    * Copy Constructor
    *
    */
    LinkedList<T>(const LinkedList<T>& orig);

    /**
    * \brief
    * Assignment Operator
    *
    */
    LinkedList<T>& operator=(const LinkedList<T>& rhs);

    /**
    * \brief
    * Linked List swap function
    *
    *
    */
    void swap(LinkedList<T>& rhs);

    /**
    * \brief 
    * Default Destructor
    *
    */
    ~LinkedList();

    /**
    * \brief 
    * Size function
    *
    * \returns the number of elements in the list
    */
    size_t size() const;

    // Allow users to iterate over the contents of the list. 
    using iterator = Iterator; 
    iterator begin() const; ///< An iterator that refers to the first element
    iterator end() const;   ///< A "past-the-end" iterator

    /**
    * \brief 
    * Inserts an element to the front of the list
    *
    * \note constant time
    */
    void insertFront(const T& element);

    /**
    * \brief 
    * Inserts an element to the back of the list
    *
    * \note constant time
    */
    void insertBack(const T& element);

    /**
    * \brief 
    * Inserts an element to the list after the specified iterator
    *
    * \note constant time
    *
    * \details The iterator cannot be end()
    */
    void insertAfter(iterator where, const T& element);

    /**
    * \brief 
    * Deletes the first element of the list
    *
    * \note constant time
    */
    T deleteFront();


    /**
    * \brief 
    * Deletes the last element of the list
    *
    * \note linear time
    */
    T deleteBack();

    /**
    * \brief 
    * Deletes a particular element in the list
    *
    * \returns
    * true if the element was deleted, false otherwise
    *
    * \note linear time
    */
    bool deleteElement(const T& element);

    /**
    * \brief 
    * Checks if an element is in the list
    *
    */
    bool contains(const T& element);

    /**
    * \brief
    * Linked List equality operator
    *
    */
    bool operator==(const LinkedList<T>& rhs) const;

    /**
    * \brief
    * Linked List inequality operator
    *
    */
    bool operator!=(const LinkedList<T>& rhs) const;

    /**
    * \brief
    * returns true if the list is empty, false otherwise
    */
    bool empty();

private:
    struct Node {
        T element_;
        Node* next_;
        Node(const T& element, Node* next);

        Node() = delete;
        Node& operator=(const Node&) = delete;
    };
    size_t size_;
    Node* head_;
    Node* tail_;

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
        friend class LinkedList;
        Iterator(Node* index);
        Node* current_;
    };
};

template<typename T>
/// Provide a non-member version of swap to allow standard swap(x,y) usage.
void swap(LinkedList<T>& lhs, LinkedList<T>& rhs);

#include "linkedlist-private.hpp"

#endif // LINKEDLIST_HPP_INCLUDED
