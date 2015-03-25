/**
 * \file linkedlist-private.hpp
 * \author Andrew Scott
 *
 * \brief implementation of templated linked list class
 */

template<typename T>
LinkedList<T>::LinkedList()
            : size_{0}, head_{nullptr}, tail_{nullptr}
{
    // nothing to do
}

template<typename T>
LinkedList<T>::~LinkedList<T>()
{
    while (!empty()) {
        deleteFront();
    }
}

template<typename T>
size_t LinkedList<T>::size()
{
    return size_;
}

template<typename T>
void LinkedList<T>::insertFront(const T& element)
{
    head_ = new Node(element, head_);
    if (size_ == 0) {
        tail_ = head_;
    }
    ++size_;
}


template<typename T>
void LinkedList<T>::insertBack(const T& element)
{
    if (size_ == 0) {
        insertFront(element);
    } else {
        Node* newBack = new Node(element, nullptr);
        tail_->next_ = newBack;
        tail_ = newBack;
        ++size_;
    }
}

template<typename T>
void LinkedList<T>::insertAfter(iterator where, const T& element)
{
    Node* currentNode = where.current_;
    if (currentNode == tail_) {
        insertBack(element);
    } else {
        currentNode->next_ = new Node(element, currentNode->next_);
        ++size_;
    }
}

template<typename T>
T LinkedList<T>::deleteFront()
{
    assert(!empty());

    T oldFrontVal = head_->element_;
    Node* newFront = head_->next_;
    delete head_;
    head_ = newFront;
    --size_;

    if (size_ == 0) {
        tail_ = head_ = nullptr;
    }
    return oldFrontVal;

}

template<typename T>
T LinkedList<T>::deleteBack()
{
    if (size_ == 0) {
        return NULL;
    }
    Node* oldBack = tail_;
    Node* currentNode = head_;
    while (currentNode->next_->element_ != oldBack->element_) {
        currentNode = currentNode->next_;
    }
    tail_ = currentNode;
    T oldBackVal = oldBack->element_;
    delete oldBack;
    --size_;
    return oldBackVal;

}

template<typename T>
bool LinkedList<T>::contains(const T& element)
{
    if (size_ == 0) {
        return false;
    }
    Node* currentNode = head_;

    while (currentNode != nullptr) {
        if (currentNode->element_ == element) {
            return true;
        }
        currentNode = currentNode->next_;
    }
    return false;
}

template<typename T>
bool LinkedList<T>::empty()
{
    return (size_ == 0);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::begin() const
{
    return Iterator(head_);
}

template<typename T>
typename LinkedList<T>::iterator LinkedList<T>::end() const
{
    return Iterator(nullptr);
}

// --------------------------------------
// Implementation of LinkedList::Node
// --------------------------------------
template<typename T>
LinkedList<T>::Node::Node(const T& element, Node* next)
    :element_{element}, next_{next}
{
    // nothing else to do
}


// --------------------------------------
// Implementation of LinkedList::Iterator
// --------------------------------------
template<typename T>
LinkedList<T>::Iterator::Iterator(Node* index)
    : current_{index}
{
    // Nothing else to do.
}

template<typename T>
typename LinkedList<T>::Iterator& LinkedList<T>::Iterator::operator++()
{
    current_ = current_->next_;
    return *this;
}

template<typename T>
T& LinkedList<T>::Iterator::operator*() const
{
    return current_->element_;
}

template<typename T>
bool LinkedList<T>::Iterator::operator==(const Iterator& rhs) const
{
    return (current_ == rhs.current_);
}

template<typename T>
bool LinkedList<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return !(*this == rhs);
}
