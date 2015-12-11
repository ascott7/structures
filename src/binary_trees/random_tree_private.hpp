/**
 * \file randomtree-private.hpp
 * \author Andrew Scott
 *
 * \brief implementation of templated random tree class
 */

template<typename T>
RandomTree<T>::RandomTree()
            : root_{nullptr}
{
    //srand (time(NULL));
}

template<typename T>
RandomTree<T>::~RandomTree()
{
    delete root_;
}

template<typename T>
RandomTree<T>::RandomTree(const RandomTree<T>& orig)
            : root_{nullptr}
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
}

template<typename T>
void swap(RandomTree<T>& lhs, RandomTree<T>& rhs)
{
    lhs.swap(rhs);
}

template<typename T>
size_t RandomTree<T>::size() const
{
    return nodeSize(root_);
}

template<typename T>
size_t RandomTree<T>::height() const
{
    return subtreeHeight(root_);
}

template<typename T>
bool RandomTree<T>::empty()
{
    return root_ == nullptr;
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
bool RandomTree<T>::contains(const T& element) const
{
    if (findNode(root_, element) == nullptr) {
        return false;
    } else {
        return true;
    }
}

template<typename T>
typename RandomTree<T>::Node* RandomTree<T>::findNode(Node* here, const T& element) const
{
    if (here == nullptr) {
        return nullptr;
    } 
    // continue searching to the left
    else if (element < here->element_) {
        return findNode(here->left_, element);
    }
    // continue searching to the right
    else if (element > here->element_) {
        return findNode(here->right_, element);
    } 
    // element is not less than or greater than here->element_, so it must
    // be equal to here->element_
    else {
        return here;
    }
}

template<typename T>
bool RandomTree<T>::insert(const T& element)
{
    if (insertNode(root_, element)) {
        return true;
    }
    return false;
}

template<typename T>
bool RandomTree<T>::insertNode(Node*& here, const T& element)
{
    // if we have an empty tree, make a new node
    if (here == nullptr) {
        here = new Node(element, nullptr, nullptr, nullptr);
        return true;
    } 
    // random check to insert at current node
    //if (rand() % here->size_ == 0) {
    if (rng(here->size_) == 0) {
        return insertNodeAtRoot(here, element);
    } 
    // otherwise go down to the next level in the tree
    else if (element < here->element_) {
        // if nothing to the left, insert there
        if (here->left_ == nullptr) {
            ++here->size_;
            here->left_ = new Node(element, nullptr, nullptr, here);
            return true;
        } 
        // otherwise go down another level in the tree
        else {
            if (insertNode(here->left_, element)) {
                ++here->size_;
                return true;
            }
            return false;
        }
    } else if (element > here->element_) {
        // if nothing to the right, insert there
        if (here->right_ == nullptr) {
            ++here->size_;
            here->right_ = new Node(element, nullptr, nullptr, here);
            return true;
        } 
        // otherwise go down another level in the tree
        else {
            if (insertNode(here->right_, element)) {
                ++here->size_;
                return true;
            }
            return false;
        }
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
    // if we are at a leaf, we are wrong
    if (here == nullptr) {
        //here = new Node(element, nullptr, nullptr);
        return false;
    } else if (element < here->element_) {
        if (here->left_ == nullptr) {
            here->left_ = new Node(element, nullptr, nullptr, here);
            ++here->size_;
            rightRotate(here);
            return true;
        } else if (insertNodeAtRoot(here->left_, element)) {
            ++here->size_;
            rightRotate(here);
            return true;
        }
        return false;
    } else if (element > here->element_) {
        if (here->right_ == nullptr) {
            here->right_ = new Node(element, nullptr, nullptr, here);
            ++here->size_;
            leftRotate(here);
            return true;
        }
        if (insertNodeAtRoot(here->right_, element)) {
            ++here->size_;
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
bool RandomTree<T>::deleteElement(const T& element)
{
    if (empty()) {
        return false;
    }
    if (nodeSize(root_) == 1) {
        return deleteOneElementTree(element);
    }
    Node* deletee;    // the node to delete
    if (root_->element_ == element) {
        deletee = getNextNode(root_);
        // set the root's value to be it's replacement's value, then proceed to
        // delete the old node containing the replacement
        root_->element_ = deletee->element_;
    } else {
        deletee = findNode(root_, element);
        // if we couldn't find a node holding the element, we can't delete
        if (deletee == nullptr) {
            return false;
        }
    }
    // if the element to delete is a leaf, just remove the leaf
    if (deletee->left_ == nullptr && deletee->right_ == nullptr) {
        deleteLeaf(deletee);
        return true;
    }
    // if the node to delete has one child, replace the node with its child
    else if (deletee->left_ == nullptr ^ deletee->right_ == nullptr) {
        deleteStick(deletee, deletee == deletee->parent_->left_);
        return true;
    }
    // if we get to this point, we know that our node to delete has two
    // children
    else {
        deleteTwoChildNode(deletee);
        return true;
    }
}

template<typename T>
typename RandomTree<T>::Node* RandomTree<T>::getNextNode(Node* here)
{
    iterator nextNode = Iterator(here);
    // go one to the right if we can
    if (++nextNode == end()) {
        // if we can't we go back one (we were at the last element so we can't
        // go to the right)
        nextNode = --(Iterator(root_));
    }
    return findNode(root_, *nextNode);
}


template<typename T>
bool RandomTree<T>::deleteOneElementTree(const T& element)
{
    if (root_->element_ == element) {
        delete root_;
        root_ = nullptr;
        return true;
    } else {
        return false;
    }
}

template<typename T>
void RandomTree<T>::deleteLeaf(Node* deletee)
{
    Node* parent = deletee->parent_;
    if (deletee->element_ < parent->element_) {
        delete parent->left_;
        parent->left_ = nullptr;
    } else if (deletee->element_ > parent->element_) {
        delete parent->right_;
        parent->right_ = nullptr;
    } 
    // if the deletee is equal to its parent (can happen when deleting root)
    else {
        if (parent->right_ == nullptr) {
            delete parent->left_;
            parent->left_ = nullptr;
        } else {
            delete parent->right_;
            parent->right_ = nullptr;
        }
    }
    // adjust size values of all the parents
    while (parent != nullptr) {
        --parent->size_;
        parent = parent->parent_;
    }
}

template<typename T>
void RandomTree<T>::deleteStick(Node* deletee, bool deleteLeft)
{
    Node* newChild;

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
        deletee->parent_->left_ = newChild;
    }
    // otherwise make it its parent's right node
    else {
        deletee->parent_->right_ = newChild;
    }
    newChild->parent_ = deletee->parent_;
    // set the deletee's children to nullptr so we don't delete any more nodes
    // when deleting the deletee
    deletee->left_ = nullptr;
    deletee->right_ = nullptr;
    delete deletee;
    // adjust size values of all the parents
    Node* parent = newChild->parent_;
    while (parent != nullptr) {
        --parent->size_;
        parent = parent->parent_;
    }
}

template<typename T>
void RandomTree<T>::deleteTwoChildNode(Node* deletee)
{
    // replace the node to delete with the next node, then delete that
    // replacement's old node location
    Node* newNode = getNextNode(deletee);
    deletee->element_ = newNode->element_;
    // if the old node's location is a leaf, delete it as a leaf
    if (newNode->left_ == nullptr && newNode->right_ == nullptr){
        deleteLeaf(newNode);
    }
    // otherwise it must be a stick, so delete it as a stick
    else {
        deleteStick(newNode, newNode->parent_->left_ == newNode);
    }
}


//   right rotation:
//      d            b
//     / \          / \
//    b   E  ->    A   d
//   / \              / \
//  A   C            C   E
template <typename T> 
void RandomTree<T>::rightRotate(Node* top)
{
    fixSizeRightRotate(top);
    Node* newRoot = top->left_;          // b is d's left child
    // if C exists, we need to change it's parent to be d
    if (newRoot->right_ != nullptr) {
        newRoot->right_->parent_ = top;
    }
    top->left_= newRoot->right_;      // C becomes left child of d
    Node* topParent = top->parent_;   // save d's parent value
    top->parent_ = newRoot;           // b is d's parent
    newRoot->right_= top;             // d becomes right child of b
    newRoot->parent_ = topParent;     // d's old parent is b's parent
    // we then need to update the node pointing to our new top
    if (newRoot->parent_ == nullptr) { 
        root_ = newRoot;
    } else {
        if (newRoot->element_ < newRoot->parent_->element_) {
            newRoot->parent_->left_ = newRoot;
        } else {
            newRoot->parent_->right_ = newRoot;
        }
    }
}

//   left rotation:
//      b               d
//     / \             / \
//    A   d     ->    b   E
//       / \         / \
//      C   E       A   C
template <typename T> 
void RandomTree<T>::leftRotate(Node* top) 
{
    fixSizeLeftRotate(top);
    Node* newRoot = top->right_;      // d is b's right child
    // if C exists, we need to change it's parent to be b
    if (newRoot->left_ != nullptr) {
        newRoot->left_->parent_ = top;
    }
    top->right_= newRoot->left_;      // C becomes right child of b
    Node* topParent = top->parent_;   // save b's parent value
    top->parent_ = newRoot;           // d is b's parent
    newRoot->left_= top;              // b becomes left child of d
    newRoot->parent_ = topParent;     // b's old parent is d's parent
    // we then need to update the node pointing to our new top
    if (newRoot->parent_ == nullptr) { 
        root_ = newRoot;
    } else {
        if (newRoot->element_ < newRoot->parent_->element_) {
            newRoot->parent_->left_ = newRoot;
        } else {
            newRoot->parent_->right_ = newRoot;
        }
    }
}

template <typename T> 
void RandomTree<T>::fixSizeRightRotate(Node* here)
{
    size_t hereSize = nodeSize(here);
    here->size_ = nodeSize(here->right_) + nodeSize(here->left_->right_) + 1;
    here->left_->size_ = hereSize;
}

template <typename T> 
void RandomTree<T>::fixSizeLeftRotate(Node* here)
{
    size_t hereSize = nodeSize(here);
    here->size_ = nodeSize(here->left_) + nodeSize(here->right_->left_) + 1;
    here->right_->size_ = hereSize;
}

template <typename T> 
size_t RandomTree<T>::nodeSize(Node* here) const
{
    if (!here)
        return 0;
    return here->size_;
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
        return Iterator(current);
    }
    while (current->left_ != nullptr) {
        parents.push(current);
        current = current->left_;
    }
    return Iterator(current);
}

template<typename T>
typename RandomTree<T>::iterator RandomTree<T>::end() const
{
    std::stack<Node*> parents;
    return Iterator(nullptr);
}

// --------------------------------------
//
// Implementation of Pretty Print
// (taken from http://articles.leetcode.com/2010/09/how-to-pretty-print-binary-tree.html)
//
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
    std::string parent;
    if (*iter != nullptr) {
        if ((*iter)->parent_ != nullptr) {
            parent = std::to_string((*iter)->parent_->element_);
        } else {
            parent = "-";
        }
    } else {
        parent = "-";
    }
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
//
// Implementation of RandomTree::Node
//
// --------------------------------------
template<typename T>
RandomTree<T>::Node::Node(const T& element, Node* left, Node* right, Node* parent)
    :element_{element}, left_{left}, right_{right}, parent_{parent}, size_{1}
{
    // nothing else to do
}

template<typename T>
RandomTree<T>::Node::~Node()
{
    delete left_;
    delete right_;
}

// --------------------------------------
//
// Implementation of RandomTree::Iterator
//
// --------------------------------------
template<typename T>
RandomTree<T>::Iterator::Iterator(Node* index)
    : current_{index}
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
    if (current_->left_ == nullptr && current_->right_ == nullptr && current_->parent_ == nullptr) {
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
        current_ = current_->right_;
        // go as far to the left as we can
        while (current_->left_ != nullptr) {
            current_ = current_->left_;
        }
    } 
    // nothing to the right and at the root node, which means we are at the
    // last element in the tree
    else if (current_->right_ == nullptr && current_->parent_ == nullptr) {
        current_ = nullptr;
        return *this;
    }
    // at this point we must go back up the tree to get to the next largest 
    // value
    // if stepping back up to the parent gives us a larger value, then we stop
    else if (current_->parent_->element_ > current_->element_) {
        current_ = current_->parent_;
    } 
    // if stepping back up to the parent gives us a smaller value, then we keep
    // going up until we hit a larger value
    else if (current_->parent_->element_ < current_->element_) {
        while (current_->parent_->element_ < current_->element_) {
            // step up to the parent of the current node
            current_ = current_->parent_;
            // if we have stepped all the way up to the root node and it is
            // less than the current node, we must have been coming from the
            // largest element, and thus we are at the end
            if (current_->parent_ == nullptr) {
                lastElement = true;
                break;
            }
        }
        // one more pop to get to the element that is greater than the current one
        if (!lastElement) {
            current_ = current_->parent_;
        } 
        // if we were at the last element, return the equivalent of the end()
        else {
            current_ = nullptr;
        }
    }
    return *this;
}

template<typename T>
typename RandomTree<T>::Iterator& RandomTree<T>::Iterator::operator--()
{
    // maybe something to handle -- on end()?

    bool firstElement = false;
    // empty tree
    if (current_ == nullptr) {
        return *this;
    }
    // tree of size 1
    else if (current_->left_ == nullptr && current_->right_ == nullptr && current_->parent_ == nullptr) {
        current_ = nullptr;
        //return *this;
    }
    // if there is something to the left, we go there and then go to the right
    // as far as we can
    else if (current_->left_ != nullptr) {
        current_ = current_->left_;
        while (current_->right_ != nullptr) {
            current_ = current_->right_;
        }
    }
    // nothing to the left and at the root node, which means we are at the
    // first element in the tree
    else if (current_->left_ == nullptr && current_->parent_ == nullptr) {
        current_ = nullptr;
        //return *this;
    }
    // at this point we must go back up the tree to get to the next smallest 
    // value
    // if stepping back up to the parent gives us a smaller value, then we stop
    else if (current_->parent_->element_ < current_->element_) {
        current_ = current_->parent_;
    }
    // if stepping back up to the parent gives us a larger value, then we keep
    // going up until we hit a smaller value
    else if (current_->parent_->element_ > current_->element_) {
        while (current_->parent_->element_ > current_->element_) {
            // step up to the parent of the current node
            current_ = current_->parent_;
            // if we have stepped all the way up to the root node and it is
            // less than the current node, we must have been coming from the
            // largest element, and thus we are at the end
            if (current_->parent_ == nullptr) {
                firstElement = true;
                break;
            }
        }
        // one more pop to get to the element that is greater than the current one
        if (!firstElement) {
            current_ = current_->parent_;
        } 
        // if we were at the first element, return null (-- on begin())
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

