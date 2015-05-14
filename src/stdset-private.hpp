/**
 * \file stdset-private.hpp
 * \author Andrew Scott
 *
 * \brief implementation of templated tree set class using std set
 */


template <typename T>
StdSet<T>::StdSet()
{
    // default constructor for std::set is ok
}

template <typename T>
StdSet<T>::~StdSet()
{
    // default destructor for std::set is ok
}

template <typename T>
size_t StdSet<T>::size() const
{
    return data_.size();
}

template <typename T>
bool StdSet<T>::insert(const T& element)
{
    data_.insert(element);
}

template <typename T>
bool StdSet<T>::contains(const T& element) const
{
    return (data_.find(element) != data_.end());
}

template <typename T>
bool StdSet<T>::deleteElement(const T& element)
{
    return (data_.erase(element) == 1);
}

template <typename T>
std::ostream& StdSet<T>::printStatistics(std::ostream& out) const
{
    out << "No statistics available" << std::endl;
    return out;
}
