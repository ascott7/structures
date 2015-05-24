/**
 * \file twothreefourtree-private.hpp
 * \author Rachel Lee
 *
 * \brief implementation of templated 2-3-4 tree class
 */

template<typename T>
twothreefourTree<T>::twothreefourTree()
            : root_{nullptr}
{
    //srand (time(NULL));
}

template<typename T>
twothreefourTree<T>::~twothreefourTree()
{
    delete root_;
}

template<typename T>
twothreefourTree<T>::twothreefourTree(const twothreefourTree<T>& orig)
            : root_{nullptr}
{
    for (iterator i = orig.begin(); i != orig.end(); ++i) {
        insert(*i);
    }
}

template<typename T>
twothreefourTree<T>& twothreefourTree<T>::operator=(const twothreefourTree<T>& rhs)
{
    twothreefourTree<T> copy{rhs};
    swap(copy);
    return *this;
}

template<typename T>
void twothreefourTree<T>::swap(twothreefourTree<T>& rhs)
{
    using std::swap;
    swap(root_, rhs.root_);
}

template<typename T>
void swap(twothreefourTree<T>& lhs, twothreefourTree<T>& rhs)
{
    lhs.swap(rhs);
}

template<typename T>
size_t twothreefourTree<T>::size() const
{
    return nodeSize(root_);
}

template<typename T>
size_t twothreefourTree<T>::height() const
{
    return subtreeHeight(root_);
}

template<typename T>
bool twothreefourTree<T>::empty()
{
    return root_ == nullptr;
}

template<typename T>
bool twothreefourTree<T>::operator==(const twothreefourTree<T>& rhs) const
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
bool twothreefourTree<T>::operator!=(const twothreefourTree<T>& rhs) const
{
    return !(*this == rhs);
}

template<typename T>
size_t twothreefourTree<T>::subtreeHeight(Node* here) const
{/*
    // recursive base case
    if (here == nullptr) {
        return 0;
    }
    // recursively get the left and right subtree heights
    size_t leftSize = subtreeHeight(here->left_);
    size_t rightSize = subtreeHeight(here->right_);

    // the taller of the two subtrees is the height of the overall subtree
    return 1 + std::max(leftSize, rightSize);
    */
    return 0;
}

template<typename T>
bool twothreefourTree<T>::contains(const T& element) const
{
    std::cout << "checking" << std::endl;
    
    if (findNode(root_, element) == nullptr) {
        std::cout << "hi" << std::endl;
        return false;
    } else {
        std::cout << "bye" << std::endl;
        return true;
    }
}

template<typename T>
typename twothreefourTree<T>::Node* twothreefourTree<T>::findNode(Node* here, const T& element) const
{
    std::cout << "findNode called" << std::endl;
    size_t index = belongs(here, element);
    std::cout << "successfully called belongs" << std::endl;
    
    if (index == 0) {
        std::cout << "seg fault here 1" << std::endl;
        return nullptr;
    }
    
    else if (index == 1 && here->firstElement_ == element) {
        std::cout << "seg fault here 2" << std::endl;
        return here;
    }
    else if (index == 1) {
        std::cout << "seg fault here 3" << std::endl;
        return findNode(here->first_, element);
    }
    
    else if (index == 2 && here->secondElement_ == element) {
        std::cout << "seg fault here 4" << std::endl;
        return here;
    }
    else if (index == 2) {
        std::cout << "seg fault here 5" << std::endl;
        return findNode(here->second_, element);
    }

    else if (index == 3 && here->thirdElement_ == element) {
        std::cout << "seg fault here 6" << std::endl;
        return here;
    }
    else if (index == 3) {
        std::cout << "seg fault here 7" << std::endl;
        return findNode(here->third_, element);
    }

    else if (index == 4) {
        std::cout << "seg fault here 8" << std::endl;
        return findNode(here->fourth_, element);
    }

    else { // index = 0
        std::cout << "seg fault here 9" << std::endl;
        return nullptr;
    }
}

template<typename T>
size_t twothreefourTree<T>::belongs(Node*& here, const T& element) const
{
    if (here == nullptr)
        return 0;

    std::cout << "belongs called" << std::endl;
    // Checking the element's 2-node index
    if (is2node(here)) {
        std::cout << "case: is2node" << std::endl; 
        if (element <= here->firstElement_) 
            return 1;
        else
            return 2;
    }
    // Checking the element's 3-node index
    else if (is3node(here)) {
        std::cout << "case: is3node" << std::endl; 
        if (element <= here->firstElement_) 
            return 1;
        else if (here->secondElement_ < element) // order matters
            return 3;
        else // first < elemenet <= second
            return 2;
    }
    // Checking the element's 4-node index
    else if (is4node(here)) {
        std::cout << "case: is4node" << std::endl; 
        if (element <= here->firstElement_) 
            return 1;
        else if (here->thirdElement_ < element)
            return 4;
        else if (here->secondElement_ < element)
            return 3;
        else // first < element <= second
            return 2;
    }
    // if here isn't a valid node (including nullptr)
    return 0;
}

template<typename T>
bool twothreefourTree<T>::insert(const T& element)
{
    return (insertNode(root_, element));
}

template<typename T>
bool twothreefourTree<T>::insertNode(Node*& here, const T& element)
{
    // if the tree is empty, make a new node
    if (!here) {
        root_ = new Node(element, nullptr, nullptr, nullptr, 2);
        return true;
    }

    // split 4-nodes on the way down
    if (is4node(here))
        split4node(here);

    size_t index = belongs(here, element);

    // if we reach a leaf, insert at the leaf
    if (isLeaf(here)) {
        if (index == 1 && here->firstElement_ != element) {
            here->thirdElement_ = here->secondElement_;
            here->secondElement_ = here->firstElement_;
            here->firstElement_ = element;
            ++here->nodeType_;
            return true;
        }
        else if (index == 2 && here->secondElement_ != element) {
            here->thirdElement_ = here->secondElement_;
            here->secondElement_ = element;
            ++here->nodeType_;
            return true;
        }
        else { // either index equals 3 (something went wrong with the top-down algorithm!)
               // or the element already exists
            return false;
        }
    }

    // if we're not at the leaf, go down to the appropriate subtree
    else if (index == 1) {
        return insertNode(here->first_, element);
    }
    else if (index == 2) {
        return insertNode(here->second_, element);
    }
    else if (index == 3) {
        return insertNode(here->third_, element);
    }
    else {
        return false;
    }
}

template<typename T>
bool twothreefourTree<T>::isLeaf(Node*& here) const
{
    if (here->first_ == nullptr)
        return false;
    if (here->second_ == nullptr)
        return false;
    if (here->third_ == nullptr)
        return false;
    if (here->fourth_ == nullptr)
        return false;
    return true;
}

template<typename T>
void twothreefourTree<T>::split4node(Node*& here)
{
    //assert(is4node(here));    
    
    T midKey = here->secondElement_;
    Node*& parent = here->parent_;

    // split into two 2-nodes
    Node* leftChild = new Node(here->firstElement_, here->first_, here->second_, parent, 2);
    Node* rightChild = new Node(here->thirdElement_, here->third_, here->fourth_, parent, 2);

    // if the root of the tree is a 4-node
    if (!parent) {
        root_ = new Node(midKey, leftChild, rightChild, nullptr, 2);
        ++here->size_; // growing up!
    }

    else if (isFirstChild(here)) {
        // fix the parent's pointers
        parent->first_ = leftChild;
        parent->second_ = rightChild;

        // fix the parent's elements
        parent->thirdElement_ = parent->secondElement_;
        parent->secondElement_ = parent->firstElement_;
        parent->firstElement_ = midKey;

        ++parent->nodeType_;
    }

    else if (isSecondChild(here)) {
        // fix the parent's pointers
        parent->second_ = leftChild;
        parent->third_ = rightChild;

        // fix the parent's elements
        parent->thirdElement_ = parent->secondElement_;
        parent->secondElement_ = midKey;

        ++parent->nodeType_;
    }

    else if (isThirdChild(here)) {
        // fix the parent's pointers
        parent->third_ = leftChild;
        parent->fourth_ = rightChild;

        // fix the parent's elements
        parent->thirdElement_ = midKey;

        ++parent->nodeType_;
    }

    // note: here can't be the fourth child, since that means the parent was a 4-node
}

template<typename T>
bool twothreefourTree<T>::isFirstChild(Node*& here) const
{

    if (!here)
        return false;
    
    return (here->firstElement_ < here->parent_->firstElement_);
}

template<typename T>
bool twothreefourTree<T>::isSecondChild(Node*& here) const
{

    if (!here)
        return false;
    
    return (here->parent_->firstElement_ < here->firstElement_ &&
        here->firstElement_ < here->parent_->secondElement_);
}

template<typename T>
bool twothreefourTree<T>::isThirdChild(Node*& here) const
{

    if (!here || (!is3node(here->parent_) && !is4node(here->parent_)))
        return false;
    
    return (here->parent_->secondElement_ < here->firstElement_ &&
        here->firstElement_ < here->parent_->thirdElement_);
}

template<typename T>
bool twothreefourTree<T>::isFourthChild(Node*& here) const
{

    if (!here || !is4node(here->parent_))
        return false;
    
    return (here->parent_->thirdElement_ < here->firstElement_);
}

template<typename T>
bool twothreefourTree<T>::is2node(Node*& here) const
{
    std::cout << "is2node called" << std::endl; 
    if (here->nodeType_ == 2) {
        std::cout << "returning true for is2node" << std::endl; 
        return true;
    }

    std::cout << "returning false for is2node" << std::endl; 
    return false;
}

template<typename T>
bool twothreefourTree<T>::is3node(Node*& here) const
{
    if (here->nodeType_ == 3)
        return true;
    return false;
}

template<typename T>
bool twothreefourTree<T>::is4node(Node*& here) const
{
    if (here->nodeType_ == 4)
        return true;
    return false;
}
/*
template<typename T>
typename twothreefourTree<T>::Node* twothreefourTree<T>::getNextNode(Node* here)
{
    iterator nextNode = Iterator(here);
    // go one to the right if we can
    if (++nextNode == end()) {
        // if we can't we go back one (we were at the last element so we can't
        // go to the right)
        nextNode = --(Iterator(root_));
    }
    return findNode(root_, *nextNode);
}*/

template <typename T> 
size_t twothreefourTree<T>::nodeSize(Node* here) const
{
    if (!here)
        return 0;
    return here->size_;
}

template <typename T>
bool twothreefourTree<T>::deleteElement(const T& element)
{
    return false;
}

template<typename T>
std::ostream& twothreefourTree<T>::printStatistics(std::ostream& out) const
{
    out << "height " << height() << std::endl;
    return out;
}

template <typename T>
std::ostream& twothreefourTree<T>::print(std::ostream& out) const
{
    printPretty(root_, 1, 1, out);
    return out;
}

template<typename T>
typename twothreefourTree<T>::iterator twothreefourTree<T>::begin() const
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
typename twothreefourTree<T>::iterator twothreefourTree<T>::end() const
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
void twothreefourTree<T>::printBranches(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
  typename std::deque<Node*>::const_iterator iter = nodesQueue.begin();
  for (int i = 0; i < nodesInThisLevel / 2; i++) {  
    out << ((i == 0) ? std::setw(startLen-1) : std::setw(nodeSpaceLen-2)) << "" << ((*iter++) ? "/" : " ");
    out << std::setw(2*branchLen+2) << "" << ((*iter++) ? "\\" : " ");
  }
  out << std::endl;
}

template<typename T>
// Print the branches and node (eg, ___10___ )
void twothreefourTree<T>::printNodes(int branchLen, int nodeSpaceLen, int startLen, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
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
void twothreefourTree<T>::printLeaves(int indentSpace, int level, int nodesInThisLevel, const std::deque<Node*>& nodesQueue, std::ostream& out) const{
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
void twothreefourTree<T>::printPretty(Node* root, int level, int indentSpace, std::ostream& out) const {
/*  int h = subtreeHeight(root_); //maxHeight(root);
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
*/}

// --------------------------------------
//
// Implementation of twothreefourTree::Node
//
// --------------------------------------
template<typename T>
twothreefourTree<T>::Node::Node(const T& firstElement, Node* first, Node* second, Node* parent, size_t nodeType)
                : firstElement_{firstElement}, first_{first}, second_{second}, size_{1}, parent_{parent}, nodeType_{nodeType}
{
    // nothing else to do
}

template<typename T>
twothreefourTree<T>::Node::~Node()
{
    delete first_;
    delete second_;
    delete third_;
    delete fourth_;
}

// --------------------------------------
//
// Implementation of twothreefourTree::Iterator
//
// --------------------------------------
template<typename T>
twothreefourTree<T>::Iterator::Iterator(Node* index)
    : current_{index}
{
    // Nothing else to do.
}

template<typename T>
typename twothreefourTree<T>::Iterator& twothreefourTree<T>::Iterator::operator++()
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
typename twothreefourTree<T>::Iterator& twothreefourTree<T>::Iterator::operator--()
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
T& twothreefourTree<T>::Iterator::operator*() const
{
    return current_->element_;
}

template<typename T>
bool twothreefourTree<T>::Iterator::operator==(const Iterator& rhs) const
{
    return (current_ == rhs.current_);
}

template<typename T>
bool twothreefourTree<T>::Iterator::operator!=(const Iterator& rhs) const
{
    return !(*this == rhs);
}

