/**
 * \file rbtree-private.hpp
 * \author Andrew Scott
 *
 * \brief implementation of templated red-black tree class
 */

template<typename T>
RBTree<T>::RBTree()
            : size_{0}, root_{nullptr}
{
    // nothing else to do
}

template<typename T>
RBTree<T>::~RBTree()
{
    delete root_;
}

template<typename T>
RBTree<T>::RBTree(const RBTree<T>& orig)
            : size_{0}, root_{nullptr}
{
    for (iterator i = orig.begin(); i != orig.end(); ++i) {
        insert(*i);
    }
}

template<typename T>
RBTree<T>& RBTree<T>::operator=(const RBTree<T>& rhs)
{
    RBTree<T> copy{rhs};
    swap(copy);
    return *this;
}

template<typename T>
void RBTree<T>::swap(RBTree<T>& rhs)
{
    using std::swap;
    swap(root_, rhs.root_);
    swap(size_, rhs.size_);
}

template<typename T>
void swap(RBTree<T>& lhs, RBTree<T>& rhs)
{
    lhs.swap(rhs);
}

template<typename T>
size_t RBTree<T>::size() const
{
    return size_;
}

template<typename T>
size_t RBTree<T>::height() const
{
    return subtreeHeight(root_);
}

template<typename T>
bool RBTree<T>::insert(const T& element)
{
    if (insertNode(root_, element)) {
        ++size_;
        return true;
    }
    return false;
}

template<typename T>
void RBTree<T>::checkBalanced(Node* startingNode)
{
    if (startingNode == nullptr) {
        return;
    }
    //std::cout << "called checkBalanced on " << startingNode->element_;
    startingNode->updateBalance();
    //std::cout << "balance_ is " << startingNode->balance_ << std::endl;
    // left subtree has height 2 greater than right subtree
    if (startingNode->balance_ < -1) {
        if (startingNode->left_->balance_ == 1) {
            leftRotate(startingNode->left_);
            rightRotate(startingNode);
        }
        else if (startingNode->left_->balance_ == -1) {
            rightRotate(startingNode);
        }
        else if (startingNode->left_->balance_ == 0) {
            rightRotate(startingNode);
        }
        startingNode->updateBalance();
        if (startingNode->parent_ != nullptr) {
            startingNode->parent_->updateBalance();
            if (startingNode->parent_->balance_ != 0) {
                checkBalanced(startingNode->parent_);
            }
        }

        //leftRotate(startingNode);
        //checkBalanced(startingNode->parent_);
    }
    // right subtree has a height 2 greater than left subtree
    else if (startingNode->balance_ > 1) {
        //std::cout << "right child balance_ is " << startingNode->right_->balance_ << std::endl;
        if (startingNode->right_->balance_ == -1) {
            rightRotate(startingNode->right_);
            leftRotate(startingNode);
        }
        else if (startingNode->right_->balance_ == 1) {
            leftRotate(startingNode);
        }
        else if (startingNode->right_->balance_ == 0) {
            leftRotate(startingNode);
        }
        startingNode->updateBalance();
        if (startingNode->parent_ != nullptr) {
            startingNode->parent_->updateBalance();
            if (startingNode->parent_->balance_ != 0) {
                checkBalanced(startingNode->parent_);
            }
        }
    } //else if (startingNode->balance_ == 0) {
        // we are done
    //} 
    else {
        checkBalanced(startingNode->parent_);
    }
}

template<typename T>
void RBTree<T>::deleteRoot()
{
    Node* newRoot = root_->right_;
    // if the right side of the tree is empty, then we have to find the
    // next largest element in the tree after the current root
    if (newRoot == nullptr) {
        newRoot = root_->left_;
        while (newRoot->right_ != nullptr) {
            //newRootParent = newRoot;
            newRoot = newRoot->right_;
        }
    }
    else {
        // otherwise find the root's inorder successor
        while (newRoot->left_ != nullptr) {
            //newRootParent = newRoot;
            newRoot = newRoot->left_;
        }
    }
    root_->element_ = newRoot->element_;

    if (newRoot->left_ == nullptr && newRoot->right_ == nullptr) {
        //std::cout << "calling delete leaf with " << newRoot->element_ << " " << root_->element_ << std::endl;
        deleteLeaf(newRoot);
    }

    else if (newRoot->left_ == nullptr ^ newRoot->right_ == nullptr) {
        //std::cout << "calling delete root stick with " << newRootParent->element_ << " " << newRoot->element_ << std::endl;
        deleteStick(newRoot, newRoot->parent_->left_ == newRoot);
    }

    else {
        //std::cout << "calling delete two child node with " << newRoot->element_ << std::endl;
        deleteTwoChildNode(newRoot);
    }
}

template<typename T>
bool RBTree<T>::deleteOneElementTree(const T& element)
{
    if (root_->element_ == element) {
        delete root_;
        root_ = nullptr;
        --size_;
        return true;
    } else {
        return false;
    }
}

template<typename T>
void RBTree<T>::deleteLeaf(Node* deletee)
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
    checkBalanced(parent);
    --size_;
}

template<typename T>
void RBTree<T>::deleteStick(Node* deletee, bool deleteLeft)
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
    checkBalanced(newChild->parent_);
    --size_;
}

template<typename T>
void RBTree<T>::deleteTwoChildNode(Node* deletee)
{
    // replace the node to delete with the new min
    // then delete that min
    Node* newNode = deletee->right_;
    // find the deletee's inorder successor
    while (newNode->left_ != nullptr) {
        //newNodeParent = newNode;
        newNode = newNode->left_;
    }
    deletee->element_ = newNode->element_;
    // if the new child to delete is a leaf, delete it as a leaf
    if (newNode->left_ == nullptr && newNode->right_ == nullptr){
        //std::cout << "calling delete leaf with " << newNodeParent->element_ << " " << deletee->element_ << std::endl;
        deleteLeaf(newNode);
    }
    // otherwise it must be a stick, so delete it as a stick
    else {
        //std::cout << "calling delete stick with " << newNodeParent->element_ << " " << newNode->element_ << " " << newNode->element_ << std::endl;
        deleteStick(newNode, newNode->parent_->left_ == newNode);
    }
}

template<typename T>
bool RBTree<T>::deleteElement(const T& element)
{
    if (empty()) {
        return false;
    }
    if (size_ == 1) {
        return deleteOneElementTree(element);
    }

    if (root_->element_ == element) {
        //std::cout << "deleting root" << std::endl;
        deleteRoot();
        return true;
    }

    Node* deletee = root_;
    // find the element to delete
    while (deletee != nullptr && deletee->element_ != element) {
        // if we need to go left to find our element but we can't go left
        // then the element doesn't exist
        if (element < deletee->element_) {
            if (deletee->left_ == nullptr) {
                return false;
            } else {
                deletee = deletee->left_;
            }
        } else if (element > deletee->element_) {
            if (deletee->right_ == nullptr) {
                return false;
            } else {
                deletee = deletee->right_;
            }
        }
    }
    // otherwise we now have to delete the element
    // if the element to delete is a leaf, just remove the leaf
    if (deletee->left_ == nullptr && deletee->right_ == nullptr) {
        //std::cout << "deleting a leaf" << std::endl;
        deleteLeaf(deletee);
        return true;
    }
    // if the node to delete has one child, replace the node with its child
    else if (deletee->left_ == nullptr ^ deletee->right_ == nullptr) {
        //std::cout << "deleting in a stick" << std::endl;
        deleteStick(deletee, deletee == deletee->parent_->left_);
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
bool RBTree<T>::contains(const T& element)
{
    if (size_ == 0) {
        return false;
    }
    return existsNode(root_, element);
}

template<typename T>
bool RBTree<T>::existsNode(Node* here, const T& element)
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
        //splayToRoot(here);
        return true;
    }
}

template<typename T>
bool RBTree<T>::empty()
{
    return (size_ == 0);
}

template<typename T>
bool RBTree<T>::operator==(const RBTree<T>& rhs) const
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
bool RBTree<T>::operator!=(const RBTree<T>& rhs) const
{
    return !(*this == rhs);
}

//      d            b
//     / \          / \
//    b   E  ->    A   d
//   / \              / \
//  A   C            C   E
template <typename T> 
void RBTree<T>::rightRotate(Node* top)
{
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
    top = newRoot;                    // top is now b
}

//      b               d
//     / \             / \
//    A   d     ->    b   E
//       / \         / \
//      C   E       A   C
template <typename T> 
void RBTree<T>::leftRotate(Node* top) 
{
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
    top = newRoot;                    // top is now d 
}

template<typename T>
bool RBTree<T>::insertNode(Node*& here, const T& element)
{
    // if we have an empty tree, make a new node
    if (here == nullptr) {
        here = new Node(element, nullptr, nullptr, nullptr);
        return true;
    }
    // otherwise go down to the next level in the tree
    else if (element < here->element_) {
        if (here->left_ == nullptr) {
            here->left_ = new Node(element, nullptr, nullptr, here);
            //here->updateBalance);
            here->updateBalance();
            checkBalanced(here->parent_);
            //splayToRoot(here->left_);
            return true;
        } else {
            return insertNode(here->left_, element);
        }
    } else if (element > here->element_) {
        if (here->right_ == nullptr) {
            here->right_ = new Node(element, nullptr, nullptr, here);
            here->updateBalance();
            checkBalanced(here->parent_);
            //splayToRoot(here->right_);
            return true;
        } else {
            return insertNode(here->right_, element);
        }
    } 
    // if we aren't less than or greater than the element, we must be equal
    // and thus we can't insert
    else {
        return false;
    }
}

template<typename T>
size_t RBTree<T>::subtreeHeight(Node* here) const
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
bool RBTree<T>::isBalanced()
{
    return isBalancedNode(root_);
}

template<typename T>
bool RBTree<T>::isBalancedNode(Node* here)
{
    if (here == nullptr) {
        return true;
    }
    here->updateBalance();
    if (std::abs(here->balance_) > 1) {
        return false;
    }
    return isBalancedNode(here->left_) && isBalancedNode(here->right_);
}

template<typename T>
std::ostream& RBTree<T>::printStatistics(std::ostream& out) const
{
    out << "height " << height() << std::endl;
    return out;
}

template <typename T>
std::ostream& RBTree<T>::print(std::ostream& out) const
{
    printPretty(root_, 1, 1, out);
    return out;
}

template<typename T>
typename RBTree<T>::iterator RBTree<T>::begin() const
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
typename RBTree<T>::iterator RBTree<T>::end() const
{
    std::stack<Node*> parents;
    return Iterator(nullptr);
}

// --------------------------------------
// Implementation of Pretty Print
// --------------------------------------
template<typename T>
// Print the arm branches (eg, /    \ ) on a line
void RBTree<T>::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
  typename std::deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {  
    out << ((i == 0) ? std::setw(startLen-1) : std::setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    out << std::setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  out << std::endl;
}

template<typename T>
// Print the branches and node (eg, ___10___ )
void RBTree<T>::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
  typename std::deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? std::setw(startLen) : std::setw(nodeSpaceLen)) << "" << ((*iter && (*iter)->left_) ? std::setfill('_') : std::setfill(' '));
    /*std::string parent;
    if (*iter != nullptr) {
        if ((*iter)->parent_ != nullptr) {
            parent = std::to_string((*iter)->parent_->element_);
        } else {
            parent = "-";
        }
    } else {
        parent = "-";
    }*/
    out << std::setw(branchLen+2) << ((*iter) ? std::to_string((*iter)->element_) : "");// + ":" + std::to_string((*iter)->balance_) : "");
    out << ((*iter && (*iter)->right_) ? std::setfill('_') : std::setfill(' ')) << std::setw(branchLen) << "" << std::setfill(' ');
  }
  out << std::endl;
}

template<typename T>
// Print the leaves only (just for the bottom row)
void RBTree<T>::printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
  typename std::deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel; i++, iter++) {
    out << ((i == 0) ? std::setw(indentSpace+2) : std::setw(2*level+2)) << ((*iter) ? std::to_string((*iter)->element_) : "");// + ":" + std::to_string((*iter)->balance_) : "");
  }
  out << std::endl;
}

template<typename T>
// Pretty formatting of a binary tree to the output stream
// @ param
// level  Control how wide you want the tree to sparse (eg, level 1 has the minimum space between nodes, while level 2 has a larger space between nodes)
// indentSpace  Change this to add some indent space to the left (eg, indentSpace of 0 means the lowest level of the left node will stick to the left margin)
void RBTree<T>::printPretty(Node* root, int level, int indentSpace, std::ostream& out) const {
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
// Implementation of RBTree::Node
// --------------------------------------
template<typename T>
RBTree<T>::Node::Node(const T& element, Node* left, Node* right, Node* parent)
    :element_{element}, left_{left}, right_{right}, parent_{parent}, balance_{0}
{
    // nothing else to do
}

template<typename T>
RBTree<T>::Node::~Node()
{
    delete left_;
    delete right_;
}

template<typename T>
size_t RBTree<T>::Node::size() const
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
void RBTree<T>::Node::updateBalance()
{
    int leftHeight = 0;
    if (left_ != nullptr) {
        leftHeight = left_->subtreeHeight();
    } 
    int rightHeight = 0;
    if (right_ != nullptr) {
        rightHeight = right_->subtreeHeight();
    }
    balance_ = rightHeight - leftHeight;
}

template<typename T>
size_t RBTree<T>::Node::subtreeHeight() const
{
    // recursive base case (at a leaf)
    if (left_ == nullptr && right_ == nullptr) {
        return 1;
    }
    // recursively get the left and right subtree heights
    size_t leftSize = 0;
    if (left_ != nullptr) {
        leftSize = left_->subtreeHeight();
    }
    size_t rightSize = 0;
    if (right_ != nullptr) {
        rightSize = right_->subtreeHeight();
    }

    // the taller of the two subtrees is the height of the overall subtree
    return 1 + std::max(leftSize, rightSize);
}

template<typename T>
std::ostream& RBTree<T>::Node::print(std::ostream& out) const
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
// Implementation of RBTree::Iterator
// --------------------------------------
template<typename T>
RBTree<T>::Iterator::Iterator(Node* index)
    : current_{index}
{
    // Nothing else to do.
}

template<typename T>
typename RBTree<T>::Iterator& RBTree<T>::Iterator::operator++()
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
T& RBTree<T>::Iterator::operator*() const
{
    return current_->element_;
}

template<typename T>
bool RBTree<T>::Iterator::operator==(const Iterator& rhs) const
{
    return (current_ == rhs.current_);
}

template<typename T>
bool RBTree<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return !(*this == rhs);
}

