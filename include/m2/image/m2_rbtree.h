/****************************************************************************
**
** Copyright (C) 2023 MerlotRain
** Github:https://github.com/MerlotRain
**
** M2 is a cross platform C++basic library that encapsulates commonly 
** used C++ classes and functional modules, shields system functions from 
** the outside, and provides a unified interface.
**
** $M2_BEGIN_LICENSE:MIT$
** Permission is hereby granted, free of charge, to any person obtaining a 
** copy of this software and associated documentation files (the “Software”), 
** to deal in the Software without restriction, including without limitation 
** the rights to use, copy, modify, merge, publish, distribute, sublicense, 
** and/or sell copies of the Software, and to permit persons to whom the 
** Software is furnished to do so, subject to the following conditions:
**
** The above copyright notice and this permission notice shall be included 
** in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS 
** OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
** FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL 
** THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
** LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
** FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
** DEALINGS IN THE SOFTWARE.
** 
** $M2_END_LICENSE$
**
****************************************************************************/

#ifndef M2_RBTREE_H_
#define M2_RBTREE_H_

#include <preconfig.h>

namespace m2 {

template<typename T>
struct RBTree
{
    struct Node
    {
        inline Node() : parent(nullptr), left(nullptr), right(nullptr) {}
        inline ~Node()
        {
            if (left) delete left;
            if (right) delete right;
        }
        T data;
        Node *parent;
        Node *left;
        Node *right;
        bool red;
    };

    inline RBTree() : root(nullptr), freeList(nullptr) {}
    inline ~RBTree();
    inline void clear();

    void attachBefore(Node *parent, Node *child);
    void attachAfter(Node *parent, Node *child);

    inline Node *front(Node *node) const;
    inline Node *back(Node *node) const;
    Node *next(Node *node) const;
    Node *previous(Node *node) const;

    inline void deleteNode(Node *&node);
    inline Node *newNode();

    int order(Node *left, Node *right);
    inline bool validate() const;

    void rotateLeft(Node *node);
    void rotateRight(Node *node);
    void update(Node *node);

    inline void attachLeft(Node *parent, Node *child);
    inline void attachRight(Node *parent, Node *child);

    int blackDepth(Node *top) const;
    bool checkRedBlackProperty(Node *top) const;

    void swapNodes(Node *n1, Node *n2);
    void detach(Node *node);

    void rebalance(Node *node);


    Node *root;
    Node *freeList;
};

template<class T>
inline RBTree<T>::~RBTree()
{
    clear();
    while (freeList)
    {
        Node *next = freeList->right;
        freeList->right = nullptr;
        delete freeList;
        freeList = next;
    }
}

template<class T>
inline void RBTree<T>::clear()
{
    if (root) delete root;
    root = nullptr;
}

template<class T>
void RBTree<T>::rotateLeft(Node *node)
{
    //   |            |      //
    //   N            B      //
    //  / \          / \     //
    // A   B  --->  N   D    //
    //    / \      / \       //
    //   C   D    A   C      //

    Node *&ref =
            (node->parent ? (node == node->parent->left ? node->parent->left
                                                        : node->parent->right)
                          : root);
    ref = node->right;
    node->right->parent = node->parent;

    //   :        //
    //   N        //
    //  / :|      //
    // A   B      //
    //    / \     //
    //   C   D    //

    node->right = ref->left;
    if (ref->left) ref->left->parent = node;

    //   :   |     //
    //   N   B     //
    //  / \ : \    //
    // A   C   D   //

    ref->left = node;
    node->parent = ref;

    //     |       //
    //     B       //
    //    / \      //
    //   N   D     //
    //  / \        //
    // A   C       //
}

template<class T>
void RBTree<T>::rotateRight(Node *node)
{
    //     |            |        //
    //     N            A        //
    //    / \          / \       //
    //   A   B  --->  C   N      //
    //  / \              / \     //
    // C   D            D   B    //

    Node *&ref =
            (node->parent ? (node == node->parent->left ? node->parent->left
                                                        : node->parent->right)
                          : root);
    ref = node->left;
    node->left->parent = node->parent;

    node->left = ref->right;
    if (ref->right) ref->right->parent = node;

    ref->right = node;
    node->parent = ref;
}

template<class T>
void RBTree<T>::update(Node *node)// call this after inserting a node
{
    for (;;)
    {
        Node *parent = node->parent;

        // if the node is the root, color it black
        if (!parent)
        {
            node->red = false;
            return;
        }

        // if the parent is black, the node can be left red
        if (!parent->red) return;

        // at this point, the parent is red and cannot be the root
        Node *grandpa = parent->parent;
        assert(grandpa);

        Node *uncle =
                (parent == grandpa->left ? grandpa->right : grandpa->left);
        if (uncle && uncle->red)
        {
            // grandpa's black, parent and uncle are red.
            // let parent and uncle be black, grandpa red and recursively update grandpa.
            assert(!grandpa->red);
            parent->red = false;
            uncle->red = false;
            grandpa->red = true;
            node = grandpa;
            continue;
        }

        // at this point, uncle is black
        if (node == parent->right && parent == grandpa->left)
            rotateLeft(node = parent);
        else if (node == parent->left && parent == grandpa->right)
            rotateRight(node = parent);
        parent = node->parent;

        if (parent == grandpa->left)
        {
            rotateRight(grandpa);
            parent->red = false;
            grandpa->red = true;
        }
        else
        {
            rotateLeft(grandpa);
            parent->red = false;
            grandpa->red = true;
        }
        return;
    }
}

template<class T>
inline void RBTree<T>::attachLeft(Node *parent, Node *child)
{
    assert(!parent->left);
    parent->left = child;
    child->parent = parent;
    update(child);
}

template<class T>
inline void RBTree<T>::attachRight(Node *parent, Node *child)
{
    assert(!parent->right);
    parent->right = child;
    child->parent = parent;
    update(child);
}

template<class T>
void RBTree<T>::attachBefore(Node *parent, Node *child)
{
    if (!root) update(root = child);
    else if (!parent)
        attachRight(back(root), child);
    else if (parent->left)
        attachRight(back(parent->left), child);
    else
        attachLeft(parent, child);
}

template<class T>
void RBTree<T>::attachAfter(Node *parent, Node *child)
{
    if (!root) update(root = child);
    else if (!parent)
        attachLeft(front(root), child);
    else if (parent->right)
        attachLeft(front(parent->right), child);
    else
        attachRight(parent, child);
}

template<class T>
void RBTree<T>::swapNodes(Node *n1, Node *n2)
{
    // Since iterators must not be invalidated, it is not sufficient to only swap the data.
    if (n1->parent == n2)
    {
        n1->parent = n2->parent;
        n2->parent = n1;
    }
    else if (n2->parent == n1)
    {
        n2->parent = n1->parent;
        n1->parent = n2;
    }
    else { std::swap(n1->parent, n2->parent); }

    std::swap(n1->left, n2->left);
    std::swap(n1->right, n2->right);
    std::swap(n1->red, n2->red);

    if (n1->parent)
    {
        if (n1->parent->left == n2) n1->parent->left = n1;
        else
            n1->parent->right = n1;
    }
    else { root = n1; }

    if (n2->parent)
    {
        if (n2->parent->left == n1) n2->parent->left = n2;
        else
            n2->parent->right = n2;
    }
    else { root = n2; }

    if (n1->left) n1->left->parent = n1;
    if (n1->right) n1->right->parent = n1;

    if (n2->left) n2->left->parent = n2;
    if (n2->right) n2->right->parent = n2;
}

template<class T>
void RBTree<T>::detach(Node *node)// call this before removing a node.
{
    if (node->right) swapNodes(node, front(node->right));

    Node *child = (node->left ? node->left : node->right);

    if (!node->red)
    {
        if (child && child->red) child->red = false;
        else
            rebalance(node);
    }

    Node *&ref =
            (node->parent ? (node == node->parent->left ? node->parent->left
                                                        : node->parent->right)
                          : root);
    ref = child;
    if (child) child->parent = node->parent;
    node->left = node->right = node->parent = nullptr;
}

// 'node' must be black. rebalance will reduce the depth of black nodes by one in the sibling tree.
template<class T>
void RBTree<T>::rebalance(Node *node)
{
    assert(!node->red);
    for (;;)
    {
        if (!node->parent) return;

        // at this point, node is not a parent, it is black, thus it must have a sibling.
        Node *sibling = (node == node->parent->left ? node->parent->right
                                                    : node->parent->left);
        assert(sibling);

        if (sibling->red)
        {
            sibling->red = false;
            node->parent->red = true;
            if (node == node->parent->left) rotateLeft(node->parent);
            else
                rotateRight(node->parent);
            sibling = (node == node->parent->left ? node->parent->right
                                                  : node->parent->left);
            assert(sibling);
        }

        // at this point, the sibling is black.
        assert(!sibling->red);

        if ((!sibling->left || !sibling->left->red) &&
            (!sibling->right || !sibling->right->red))
        {
            bool parentWasRed = node->parent->red;
            sibling->red = true;
            node->parent->red = false;
            if (parentWasRed) return;
            node = node->parent;
            continue;
        }

        // at this point, at least one of the sibling's children is red.

        if (node == node->parent->left)
        {
            if (!sibling->right || !sibling->right->red)
            {
                assert(sibling->left);
                sibling->red = true;
                sibling->left->red = false;
                rotateRight(sibling);

                sibling = sibling->parent;
                assert(sibling);
            }
            sibling->red = node->parent->red;
            node->parent->red = false;

            assert(sibling->right->red);
            sibling->right->red = false;
            rotateLeft(node->parent);
        }
        else
        {
            if (!sibling->left || !sibling->left->red)
            {
                assert(sibling->right);
                sibling->red = true;
                sibling->right->red = false;
                rotateLeft(sibling);

                sibling = sibling->parent;
                assert(sibling);
            }
            sibling->red = node->parent->red;
            node->parent->red = false;

            assert(sibling->left->red);
            sibling->left->red = false;
            rotateRight(node->parent);
        }
        return;
    }
}

template<class T>
inline typename RBTree<T>::Node *RBTree<T>::front(Node *node) const
{
    while (node->left) node = node->left;
    return node;
}

template<class T>
inline typename RBTree<T>::Node *RBTree<T>::back(Node *node) const
{
    while (node->right) node = node->right;
    return node;
}

template<class T>
typename RBTree<T>::Node *RBTree<T>::next(Node *node) const
{
    if (node->right) return front(node->right);
    while (node->parent && node == node->parent->right) node = node->parent;
    return node->parent;
}

template<class T>
typename RBTree<T>::Node *RBTree<T>::previous(Node *node) const
{
    if (node->left) return back(node->left);
    while (node->parent && node == node->parent->left) node = node->parent;
    return node->parent;
}

template<class T>
int RBTree<T>::blackDepth(Node *top) const
{
    if (!top) return 0;
    int leftDepth = blackDepth(top->left);
    int rightDepth = blackDepth(top->right);
    if (leftDepth != rightDepth) return -1;
    if (!top->red) ++leftDepth;
    return leftDepth;
}

template<class T>
bool RBTree<T>::checkRedBlackProperty(Node *top) const
{
    if (!top) return true;
    if (top->left && !checkRedBlackProperty(top->left)) return false;
    if (top->right && !checkRedBlackProperty(top->right)) return false;
    return !(top->red && ((top->left && top->left->red) ||
                          (top->right && top->right->red)));
}

template<class T>
inline bool RBTree<T>::validate() const
{
    return checkRedBlackProperty(root) && blackDepth(root) != -1;
}

template<class T>
inline void RBTree<T>::deleteNode(Node *&node)
{
    assert(node);
    detach(node);
    node->right = freeList;
    freeList = node;
    node = nullptr;
}

template<class T>
inline typename RBTree<T>::Node *RBTree<T>::newNode()
{
    if (freeList)
    {
        Node *node = freeList;
        freeList = freeList->right;
        node->parent = node->left = node->right = nullptr;
        node->red = true;
        return node;
    }
    return new Node;
}

// Return 1 if 'left' comes after 'right', 0 if equal, and -1 otherwise.
// 'left' and 'right' cannot be null.
template<class T>
int RBTree<T>::order(Node *left, Node *right)
{
    assert(left && right);
    if (left == right) return 0;

    std::list<Node *> leftAncestors;
    std::list<Node *> rightAncestors;
    while (left)
    {
        leftAncestors.push_back(left);
        left = left->parent;
    }
    while (right)
    {
        rightAncestors.push_back(right);
        right = right->parent;
    }
    assert(leftAncestors.back() == root && rightAncestors.back() == root);

    while (!leftAncestors.empty() && !rightAncestors.empty() &&
           leftAncestors.back() == rightAncestors.back())
    {
        leftAncestors.pop_back();
        rightAncestors.pop_back();
    }

    if (!leftAncestors.empty())
        return (leftAncestors.back() == leftAncestors.back()->parent->left ? -1
                                                                           : 1);

    if (!rightAncestors.empty())
        return (rightAncestors.back() == rightAncestors.back()->parent->right
                        ? -1
                        : 1);

    // The code should never reach this point.
    assert(!leftAncestors.empty() || !rightAncestors.empty());
    return 0;
}


}// namespace m2

#endif//M2_RBTREE_H_