/**
 * \file randomtree-private.hpp
 * \author Andrew Scott
 *
 * \brief implementation of templated random tree class
 */

template<typename T>
RandomTree<T>::RandomTree()
            : size_{0}, root_{nullptr}
{
    srand (time(NULL));
}

template<typename T>
RandomTree<T>::~RandomTree()
{
    delete root_;
}

template<typename T>
RandomTree<T>::RandomTree(const RandomTree<T>& orig)
            : size_{orig.size()}
{
    root_ = copyNode(orig.root_);
}

template<typename T>
typename RandomTree<T>::Node* RandomTree<T>::copyNode(const RandomTree<T>::Node* node)
{
    if (node == nullptr) {
        return nullptr;
    }
    Node* left = copyNode(node->left_);
    Node* right = copyNode(node->right_);
    return new Node(node->element_, left, right);
}

template<typename T>
RandomTree<T>& RandomTree<T>::operator=(const RandomTree<T>& rhs)
{
    RandomTree<T> copy{rhs};
    swap(copy);
    return *this;
}

template<typename T>
void RandomTree<T>::swap(RandomTree<T>& rhs)
{
    using std::swap;
    swap(root_, rhs.root_);
    swap(size_, rhs.size_);
}

template<typename T>
void swap(RandomTree<T>& lhs, RandomTree<T>& rhs)
{
    lhs.swap(rhs);
}

template<typename T>
size_t RandomTree<T>::size() const
{
    return size_;
}

template<typename T>
size_t RandomTree<T>::height() const
{
    return subtreeHeight(root_);
}

template<typename T>
void RandomTree<T>::insert(const T& element)
{
    ++size_;
    insertNode(root_, element);
}

template<typename T>
bool RandomTree<T>::deleteElement(const T& element)
{
    assert(!empty());

}

template<typename T>
bool RandomTree<T>::contains(const T& element) const
{
    if (size_ == 0) {
        return false;
    }
    return existsNode(root_, element);
}

// Function taken from CS70 notes Week 13 Class 1, Spring 2014
template<typename T>
bool RandomTree<T>::existsNode(Node* here, const T& element) const
{
    if (here == nullptr) {
        return false;
    } else if (element < here->element_) {
        return existsNode(here->left_, element);
    } else if (element > here->element_) {
        return existsNode(here->right_, element);
    } else {
        return true;
    }
}

template<typename T>
bool RandomTree<T>::empty()
{
    return (size_ == 0);
}

template<typename T>
bool RandomTree<T>::operator==(const RandomTree<T>& rhs) const
{
    // if the sizes are different the trees are not equal
    if (size() != rhs.size()) {
        return false;
    }
    // if both trees are empty they are equal
    else if (root_ == nullptr && rhs.root_ == nullptr) {
        return true;
    }
    // if one tree is empty but not the other, the trees are not equal
    else if (root_ == nullptr && rhs.root_ != nullptr) {
        return false;
    } else if (root_ != nullptr && rhs.root_ == nullptr) {
        return false;
    }
    // if both trees are not empty we have to check the equality of their
    // root nodes using node equality
    else {
        return *root_ == *rhs.root_;
    }
}


template<typename T>
bool RandomTree<T>::operator!=(const RandomTree<T>& rhs) const
{
    return !(*this == rhs);
}

// Taken from CS70 notes Week 13 Class 1, Spring 2014
template <typename T> 
void RandomTree<T>::rightRotate(Node*& top) 
{
    Node* b = top->left_;       // b is d's left child 
    top->left_= b->right_;      // C becomes left child of d 
    b->right_= top;             // d becomes right child of b  
    top = b;                    // top is now b 
}    

// Taken from CS70 notes Week 13 Class 1, Spring 2014
template <typename T> 
void RandomTree<T>::leftRotate(Node*& top) 
{
    Node* d = top->right_;      // d is b's right child 
    top->right_= d->left_;      // C becomes right child of b 
    d->left_= top;              // b becomes left child of d  
    top = d;                    // top is now d 
}

template<typename T>
void RandomTree<T>::insertNode(Node*& here, const T& element)
{
    // if we are at a leaf, make a new node
    if (here == nullptr) {
        here = new Node(element, nullptr, nullptr);
    } 
    // random check to insert at root (insert at current node)
    else if (rand() % (here->size() + 1) == 0) {
        insertNodeAtRoot(here, element);
    } 
    // otherwise go down to the next level in the tree
    else if (element < here->element_) {
        insertNode(here->left_, element);
    } else {
        insertNode(here->right_, element);
    }
}

template<typename T>
void RandomTree<T>::insertNodeAtRoot(Node*& here, const T& element)
{
    // if we are at a leaf, make a new node
    if (here == nullptr) {
        here = new Node(element, nullptr, nullptr);
    } else if (element < here->element_) {
        insertNodeAtRoot(here->left_, element);
        rightRotate(here);
    } else {
        insertNodeAtRoot(here->right_, element);
        leftRotate(here); 
    }
}

template<typename T>
size_t RandomTree<T>::subtreeHeight(Node* here) const
{
    // recursive base case
    if (here == nullptr) {
        return 0;
    }
    // recursively get the left and right subtree heights
    size_t leftSize = subtreeHeight(here->left_);
    size_t rightSize = subtreeHeight(here->right_);

    // the taller of the two subtrees is the height of the overall subtree
    return 1 + std::max(leftSize, rightSize);
}

template<typename T>
std::ostream& RandomTree<T>::printStatistics(std::ostream& out) const
{
    out << "height " << height() << std::endl;
    return out;
}

template <typename T>
std::ostream& RandomTree<T>::print(std::ostream& out) const
{
    if(root_ == nullptr) {
        out << "(-)";
    } else {
        root_->print(out);
    }
    return out;
}

// --------------------------------------
// Implementation of RandomTree::Node
// --------------------------------------
template<typename T>
RandomTree<T>::Node::Node(const T& element, Node* left, Node* right)
    :element_{element}, left_{left}, right_{right}
{
    // nothing else to do
}

template<typename T>
RandomTree<T>::Node::~Node()
{
    delete left_;
    delete right_;
}

template<typename T>
size_t RandomTree<T>::Node::size() const
{
    size_t size = 1;

    if (left_ != nullptr) {
        size += left_->size();
    }
    if (right_ != nullptr) {
        size += right_->size();
    }
    return size;
}

template<typename T>
bool RandomTree<T>::Node::operator==(const RandomTree::Node& rhs) const
{
    // if the elements in the two nodes aren't the same, we are done
    if (element_ != rhs.element_) {
        return false;
    }

    // we then do a series of checks on if we have a nullptr for one child
    // where the other node actually has a node for the same child, in which
    // case the nodes are not even
    if (left_ == nullptr && rhs.left_ != nullptr) {
        return false;
    } else if (left_ != nullptr && rhs.left_ == nullptr) {
        return false;
    } else if (right_ == nullptr && rhs.right_ != nullptr) {
        return false;
    } else if (right_ != nullptr && rhs.right_ == nullptr) {
        return false;
    } 
    // we are now sure that both lefts are either nullptr or both not nullptr
    // and both rights are either nullptr or both not nullptr

    // if they are all nullptr, both nodes are leaves and thus we are at our
    // recursive base case
    else if (left_ == nullptr && right_ == nullptr) {
        return true;
    }
    // if the lefts are both nullptr, recursively check the equality of
    // the rights
    else if (left_ == nullptr) {
        return *right_ == *rhs.right_;
    }
    // if the rights are both nullptr, recursively check the equality of
    // the lefts
    else if (right_ == nullptr) {
        return *left_ == *rhs.left_;
    } 
    // if neither the lefts nor the rights are nullptr, we have to check
    // the equality of both
    else {
        return *left_ == *rhs.left_ && *right_ == *rhs.right_;
    }
}

template<typename T>
std::ostream& RandomTree<T>::Node::print(std::ostream& out) const
{
        out << "(";
    if (left_ == nullptr) {
        out << "-";
    } else {
        left_->print(out);
    }

    out << ", " << element_ << ", ";

    if (right_ == nullptr) {
        out << "-";
    } else {
        right_->print(out);
    }
    out << ")";
    return out;
}
