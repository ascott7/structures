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
            : size_{0}, root_{nullptr}
{
    for (iterator i = orig.begin(); i != orig.end(); ++i) {
        insert(*i);
    }
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
bool RandomTree<T>::insert(const T& element)
{
    if (insertNode(root_, element)) {
        ++size_;
        return true;
    }
    return false;
}

template<typename T>
void RandomTree<T>::deleteRoot()
{
    Node* newRoot = root_->right_;
    Node* newRootParent = root_;
    // if the right side of the tree is empty, then we have to find the
    // next largest element in the tree after the current root
    if (newRoot == nullptr) {
        newRoot = root_->left_;
        while (newRoot->right_ != nullptr) {
            newRootParent = newRoot;
            newRoot = newRoot->right_;
        }
    }
    else {
        // otherwise find the root's inorder successor
        while (newRoot->left_ != nullptr) {
            newRootParent = newRoot;
            newRoot = newRoot->left_;
        }
    }
    root_->element_ = newRoot->element_;

    if (newRoot->left_ == nullptr && newRoot->right_ == nullptr) {
        //std::cout << "calling delete leaf with " << newRootParent->element_ << " " << root_->element_ << std::endl;
        deleteLeaf(newRootParent, root_->element_);
    }

    else if (newRoot->left_ == nullptr ^ newRoot->right_ == nullptr) {
        //std::cout << "calling delete root stick with " << newRootParent->element_ << " " << newRoot->element_ << std::endl;
        deleteStick(newRootParent, newRootParent->left_ == newRoot);
    }

    else {
        //std::cout << "calling delete two child node with " << newRoot->element_ << std::endl;
        deleteTwoChildNode(newRoot);
    }
}

template<typename T>
bool RandomTree<T>::deleteOneElementTree(const T& element)
{
    if (root_->element_ == element) {
        //std::cout << "deleting from tree of size 1" << std::endl;
        delete root_;
        root_ = nullptr;
        --size_;
        return true;
    } else {
        return false;
    }
}

template<typename T>
void RandomTree<T>::deleteLeaf(Node* parent, const T& element)
{
    if (element < parent->element_) {
        delete parent->left_;
        parent->left_ = nullptr;
    } else {
        delete parent->right_;
        parent->right_ = nullptr;
    }
    --size_;
}

template<typename T>
void RandomTree<T>::deleteStick(Node* parent, bool deleteLeft)
{
    Node* newChild;
    Node* deletee;

    if (deleteLeft) {
        deletee = parent->left_;
    } else {
        deletee = parent->right_;
    }

    // find the element to delete's child
    if (deletee->left_ == nullptr) {
        newChild = deletee->right_;
    }
    else {
        newChild = deletee->left_;
    }
    // if the node to delete was the left child of the parent, make the
    // node's child its parent's left node
    if (deleteLeft) {
        parent->left_ = newChild;
    }
    // otherwise make it its parent's right node
    else {
        parent->right_ = newChild;
    }
    // set the deletee's children to nullptr so we don't delete any more nodes
    // when deleting the deletee
    deletee->left_ = nullptr;
    deletee->right_ = nullptr;
    delete deletee;
    --size_;
}

template<typename T>
void RandomTree<T>::deleteTwoChildNode(Node* deletee)
{
    // replace the node to delete with the new min
    // then delete that min
    Node* newNode = deletee->right_;
    Node* newNodeParent = deletee;
    // find the deletee's inorder successor
    while (newNode->left_ != nullptr) {
        newNodeParent = newNode;
        newNode = newNode->left_;
    }
    deletee->element_ = newNode->element_;
    // if the new child to delete is a leaf, delete it as a leaf
    if (newNode->left_ == nullptr && newNode->right_ == nullptr){
        //std::cout << "calling delete leaf with " << newNodeParent->element_ << " " << deletee->element_ << std::endl;
        deleteLeaf(newNodeParent, deletee->element_);
    }
    // otherwise it must be a stick, so delete it as a stick
    else {
        //std::cout << "calling delete stick with " << newNodeParent->element_ << " " << newNode->element_ << " " << newNode->element_ << std::endl;
        deleteStick(newNodeParent, newNodeParent->left_ == newNode);
    }
}

template<typename T>
bool RandomTree<T>::deleteElement(const T& element)
{
    if (empty()) {
        return false;
    }
    if (size_ == 1) {
        return deleteOneElementTree(element);
    }

    Node* parent = root_;
    Node* deletee = nullptr;

    if (root_->element_ == element) {
        //std::cout << "deleting root" << std::endl;
        deleteRoot();
        return true;
    }
    // find the element to delete
    while (parent != nullptr) {
        // if we need to go left to find our element but we can't go left
        // then the element doesn't exist
        if (parent->left_ == nullptr && element < parent->element_) {
            return false;
        }
        // same thing going to the right
        if (parent->right_ == nullptr && element > parent->element_) {
            return false;
        }
        if (element < parent->element_) {
            // if we have found the element, exit the loop
            if (parent->left_->element_ == element) {
                deletee = parent->left_;
                break;
            }
            // otherwise keep going
            else {
                parent = parent->left_;
            }
        }
        else if (element > parent->element_) {
            // we have found the element, exit the loop
            if (parent->right_->element_ == element) {
                deletee = parent->right_;
                break;
            }
            // keep going
            else {
                parent = parent->right_;
            }
        }
    }
    // we exited the loop without finding the element
    if (parent == nullptr || deletee == nullptr) {
        return false;
    }
    // otherwise we now have to delete the element
    // if the element to delete is a leaf, just remove the leaf
    else if (deletee->left_ == nullptr && deletee->right_ == nullptr) {
        //std::cout << "deleting a leaf" << std::endl;
        deleteLeaf(parent, element);
        return true;
    }
    // if the node to delete has one child, replace the node with its child
    else if (deletee->left_ == nullptr ^ deletee->right_ == nullptr) {
        //std::cout << "deleting in a stick" << std::endl;
        deleteStick(parent, parent->left_ == deletee);
        return true;
    }
    // if we get to this point, we know that our node to delete has two
    // children
    else {
        //std::cout << "deleting a node with two children" << std::endl;
        deleteTwoChildNode(deletee);
        return true;
    }


}

template<typename T>
bool RandomTree<T>::contains(const T& element) const
{
    if (size_ == 0) {
        return false;
    }
    return existsNode(root_, element);
}

template<typename T>
bool RandomTree<T>::existsNode(Node* here, const T& element) const
{
    if (here == nullptr) {
        return false;
    } 
    // continue searching to the left
    else if (element < here->element_) {
        return existsNode(here->left_, element);
    }
    // continue searching to the right
    else if (element > here->element_) {
        return existsNode(here->right_, element);
    } 
    // element is not less than or greater than here->element_, so it must
    // be equal to here->element_
    else {
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

    iterator thisIter = begin();
    iterator rhsIter = rhs.begin();

    while (thisIter != end()) {
        if (*thisIter != *rhsIter) {
            return false;
        }
        ++thisIter;
        ++rhsIter;
    }
    return true;
}


template<typename T>
bool RandomTree<T>::operator!=(const RandomTree<T>& rhs) const
{
    return !(*this == rhs);
}

//      d            b
//     / \          / \
//    b   E  ->    A   d
//   / \              / \
//  A   C            C   E
template <typename T> 
void RandomTree<T>::rightRotate(Node*& top) 
{
    Node* newRoot = top->left_;       // b is d's left child 
    top->left_= newRoot->right_;      // C becomes left child of d 
    newRoot->right_= top;             // d becomes right child of b  
    top = newRoot;                    // top is now b 
}

//      b               d
//     / \             / \
//    A   d     ->     b   E
//       / \          / \
//      C   E        A   C
template <typename T> 
void RandomTree<T>::leftRotate(Node*& top) 
{
    Node* newRoot = top->right_;      // d is b's right child 
    top->right_= newRoot->left_;      // C becomes right child of b 
    newRoot->left_= top;              // b becomes left child of d  
    top = newRoot;                    // top is now d 
}

template<typename T>
bool RandomTree<T>::insertNode(Node*& here, const T& element)
{
    // if we are at a leaf, make a new node
    if (here == nullptr) {
        here = new Node(element, nullptr, nullptr);
        return true;
    } 
    // random check to insert at root (insert at current node)
    else if (rand() % here->size() == 0) {
        return insertNodeAtRoot(here, element);
    } 
    // otherwise go down to the next level in the tree
    else if (element < here->element_) {
        return insertNode(here->left_, element);
    } else if (element > here->element_) {
        return insertNode(here->right_, element);
    } 
    // if we aren't less than or greater than the element, we must be equal
    // and thus we can't insert
    else {
        return false;
    }
}

template<typename T>
bool RandomTree<T>::insertNodeAtRoot(Node*& here, const T& element)
{
    // if we are at a leaf, make a new node
    if (here == nullptr) {
        here = new Node(element, nullptr, nullptr);
        return true;
    } else if (element < here->element_) {
        if (insertNodeAtRoot(here->left_, element)) {
            rightRotate(here);
            return true;
        }
        return false;
    } else if (element > here->element_) {
        if (insertNodeAtRoot(here->right_, element)) {
            leftRotate(here); 
            return true;
        }
        return false;
    } 
    // if we aren't less than or greater than the element, we must be equal
    // and thus we can't insert
    else {
        return false;
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
    printPretty(root_, 1, 1, out);
    return out;
}

template<typename T>
typename RandomTree<T>::iterator RandomTree<T>::begin() const
{
    Node* current = root_;
    std::stack<Node*> parents;
    // if tree is empty, we don't want to dereference current
    if (current == nullptr) {
        return Iterator(current, parents);
    }
    while (current->left_ != nullptr) {
        parents.push(current);
        current = current->left_;
    }
    return Iterator(current, parents);
}

template<typename T>
typename RandomTree<T>::iterator RandomTree<T>::end() const
{
    std::stack<Node*> parents;
    return Iterator(nullptr, parents);
}

// --------------------------------------
// Implementation of Pretty Print
// --------------------------------------
template<typename T>
// Print the arm branches (eg, /    \ ) on a line
void RandomTree<T>::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
  typename std::deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {  
    out << ((i == 0) ? std::setw(startLen-1) : std::setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    out << std::setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  out << std::endl;
}

template<typename T>
// Print the branches and node (eg, ___10___ )
void RandomTree<T>::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
  typename std::deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left_) ? std::setfill('_') : std::setfill(' '));
    out << std::setw(branchLen+2) << ((*iter) ? std::to_string((*iter)->element_) : "");
    out << ((*iter && (*iter)->right_) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << "" << std::setfill(' ');
  }
  out << std::endl;
}

template<typename T>
// Print the leaves only (just for the bottom row)
void RandomTree<T>::printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
  typename std::deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? std::setw(indentSpace+2) : std::setw(2*level+2)) << ((*iter) ? std::to_string((*iter)->element_) : "");
  }
  out << std::endl;
}

template<typename T>
// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void RandomTree<T>::printPretty(Node* root, int level, int indentSpace, std::ostream& out) const {
  int h = subtreeHeight(root_); //maxHeight(root);
  int nodesInThisLevel = 1;

  int branchLen = 2*((int)std::pow(2.0,h)-1) - (3-level)*(int)std::pow(2.0,h-1);  // eq of the length of branch for each node of each level
  int nodeSpaceLen = 2 + (level+1)*(int)std::pow(2.0,h);  // distance between left neighbor node's right arm and right neighbor node's left arm
  int startLen = branchLen + (3-level) + indentSpace;  // starting space to the first node to print of each level (for the left most node of each level only)
    
  std::deque<Node*> nodesQueue;
  nodesQueue.push_back(root);
  for (int r = 1; r < h; r++) {
    printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
    branchLen = branchLen/2 - 1;
    nodeSpaceLen = nodeSpaceLen/2 + 1;
    startLen = branchLen + (3-level) + indentSpace;
    printNodes(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);

    for (int i = 0; i < nodesInThisLevel; i++) {
      Node *currNode = nodesQueue.front();
      nodesQueue.pop_front();
      if (currNode) {
          nodesQueue.push_back(currNode->left_);
          nodesQueue.push_back(currNode->right_);
      } else {
        nodesQueue.push_back(NULL);
        nodesQueue.push_back(NULL);
      }
    }
    nodesInThisLevel *= 2;
  }
  printBranches(branchLen, nodeSpaceLen, startLen, nodesInThisLevel, nodesQueue, out);
  printLeaves(indentSpace, level, nodesInThisLevel, nodesQueue, out);
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

// --------------------------------------
// Implementation of RandomTree::Iterator
// --------------------------------------
template<typename T>
RandomTree<T>::Iterator::Iterator(Node* index, std::stack<Node*> parents)
    : current_{index}, parents_{parents}
{
    // Nothing else to do.
}

template<typename T>
typename RandomTree<T>::Iterator& RandomTree<T>::Iterator::operator++()
{
    bool lastElement = false;
    // empty tree
    if (current_ == nullptr) {
        return *this;
    }
    // tree of size 1
    if (current_->left_ == nullptr && current_->right_ == nullptr && parents_.size() == 0) {
        current_ = nullptr;
        return *this;
    }
    // if there's something to the right, we go there then go as far to the left
    // as we can, for example to get from 10 to 11 in this tree
    //            10
    //           /  \
    //          5    15
    //              /
    //             12
    //            /
    //           11
    if (current_->right_ != nullptr) {
        // one step to the right
        parents_.push(current_);
        current_ = current_->right_;
        // go as far to the left as we can
        while (current_->left_ != nullptr) {
            parents_.push(current_);
            current_ = current_->left_;
        }
    } 
    // nothing to the right and at the root node, which means we are at the
    // last element in the tree
    else if (current_->right_ == nullptr && parents_.size() == 0) {
        current_ = nullptr;
        return *this;
    }
    // at this point we must go back up the tree to get to the next largest 
    // value
    // if stepping back up to the parent gives us a larger value, then we stop
    else if (parents_.top()->element_ > current_->element_) {
        current_ = parents_.top();
        parents_.pop();
    } 
    // if stepping back up to the parent gives us a smaller value, then we keep
    // going up until we hit a larger value
    else if (parents_.top()->element_ < current_->element_) {
        while (parents_.top()->element_ < current_->element_) {
            // step up to the parent of the current node
            current_ = parents_.top();
            parents_.pop();
            // if we have stepped all the way up to the root node and it is
            // less than the current node, we must have been coming from the
            // largest element, and thus we are at the end
            if (parents_.size() == 0) {
                lastElement = true;
                break;
            }
        }
        // one more pop to get to the element that is greater than the current one
        if (!lastElement) {
            current_ = parents_.top();
            parents_.pop();
        } 
        // if we were at the last element, return the equivalent of the end()
        else {
            current_ = nullptr;
        }
    }
    return *this;
}

template<typename T>
T& RandomTree<T>::Iterator::operator*() const
{
    return current_->element_;
}

template<typename T>
bool RandomTree<T>::Iterator::operator==(const Iterator& rhs) const
{
    return (current_ == rhs.current_);
}

template<typename T>
bool RandomTree<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return !(*this == rhs);
}

