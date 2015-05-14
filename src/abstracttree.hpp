/**
 * \file abstractset.hpp
 *
 * \author Andrew Scott
 *
 * \brief abstract tree class
 *
 * \note any class conforming to the abstract set class will implement a size,
 * insert, and exists function so that they execute in O(log n) expected
 * amortized time, given n items in the set.
 */

#ifndef ABSTRACTTREE_HPP_INCLUDED
#define ABSTRACTTREE_HPP_INCLUDED 1
#include <cstddef>
#include <iostream>

template <typename T>
    class AbstractTree {
    public:
        typedef size_t              size_type;

        /**
        * \brief
        * Default Destructor
        *
        */
        virtual ~AbstractTree() = default; 

        /**
        * \brief
        * Get the size of the AbstractTree
        *
        * \returns the number of elements in the AbstractTree
        */
        virtual size_t size() const = 0;

        /**
        * \brief
        * Insert an element into the AbstractTree
        *
        * \param element The element to insert
        *
        * \warning inserting an element already present is undefined behavior
        */
        virtual bool insert(const T& element) = 0;

        /**
        * \brief
        * Check if an element is present in the AbstractTree
        *
        * \param element The element to check
        *
        * \returns true if the element is in the AbstractTree, false if not
        */
        virtual bool contains(const T& element) const = 0;

        /**
        * \brief
        * Deletes an element from the AbstractTree
        *
        * \param element The element to delete
        */
        virtual bool deleteElement(const T& element) = 0;

        /**
        * \brief
        * Print the statistics for the AbstractTree
        *
        * \param out The ostream to print to
        *
        * \returns An ostream with the apropriate statistics printed out
        * (see individual trees to see what statistics are printed)
        */
        virtual std::ostream& printStatistics(std::ostream& out) const = 0;
    };

#endif // ABSTRACTTREE_HPP_INCLUDED

