/**
 * \file stdset.hpp
 *
 * \author Andrew Scott
 *
 * \brief templated tree set wrapper class using std set
 *
 */
#ifndef STDSET_HPP_INCLUDED
#define STDSET_HPP_INCLUDED 1

#include <climits>
#include <cassert>
#include <set>
#include "abstracttree.hpp" 

template <typename T>

/**
* \class StdSet
* \brief uses std::set to satisfy the functions promised by AbstractSet
*/
class StdSet : public AbstractTree<T> {

public:

    /**
     * \brief 
     * Default Constructor
     *
     * \note constant time
     */
    StdSet<T>();

    /**
     * \brief
     * Default Destructor
     *
     */
    ~StdSet<T>();

    /**
     * \brief
     * Size function
     *
     * \returns the number of elements in the set
     *
     * \note constant time
     */
    size_t size() const override;

    /**
     * \brief
     * Inserts an element into the set
     *
     * \param element The element to be inserted
     */
    bool insert(const T& element) override;

    /**
     * \brief
     * Checks if an element is in the set
     *
     * \param element The element to check
     * 
     * \returns true if the element is in the set, false if otherwise
     */
    bool contains(const T& element) const override;

    bool deleteElement(const T& element);

    /**
    * \brief
    * Print the statistics for the set
    *
    * \param out The ostream to print to
    *
    * \returns An ostream saying "No statistics available"
    */
    std::ostream& printStatistics(std::ostream& out) const;


private:

    std::set<T> data_; ///< the set to store data

};

#include "stdset-private.hpp"

#endif // STDET_HPP_INCLUDED
