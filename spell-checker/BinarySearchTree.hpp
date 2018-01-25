//
// Created by ethan on 4/23/2017.
//

#ifndef SPELL_CHECKER_BINARYSEARCHTREE_HPP
#define SPELL_CHECKER_BINARYSEARCHTREE_HPP

#include "BinaryTreeNode.hpp"
#include <string>

template <typename T>
class BinarySearchTree
{
private:
    BinaryTreeNode<T>* m_pRoot;

public:
    ~BinarySearchTree() { destroy(m_pRoot); }
    bool insert(T value) { return insert(value, m_pRoot);}
    void remove(T value) { remove(value, m_pRoot); }
    bool search(T value) { return search(value, m_pRoot); }
    unsigned int numberNodes() { return numberNodes(m_pRoot); }
    unsigned int numberLeafNodes() { return numberLeafNodes(m_pRoot); }
    unsigned int height() { return height(m_pRoot); }
    void display() { display(m_pRoot); }

private:
    void destroy(BinaryTreeNode<T>*& pNode);
    bool insert(T value, BinaryTreeNode<T>*& pNode);
    void remove(T value, BinaryTreeNode<T>*& pNode);
    bool search(T value, BinaryTreeNode<T>*& pNode);
    unsigned int numberNodes(BinaryTreeNode<T>*& pNode);
    unsigned int numberLeafNodes(BinaryTreeNode<T>*& pNode);
    unsigned int height(BinaryTreeNode<T>*& pNode);
    void display(BinaryTreeNode<T>*& pNode);

    bool isLeafNode(BinaryTreeNode<T>*& pNode);
    unsigned int numChildren(BinaryTreeNode<T>*& pNode);
    T findMinimum(BinaryTreeNode<T>*& pNode);
};

template <typename T>
bool BinarySearchTree<T>::insert(T value, BinaryTreeNode<T>*& pNode)
{
    if (pNode == nullptr)
    {
        pNode = new BinaryTreeNode<T>(value, nullptr, nullptr);
        return true;
    }
    else if (pNode->value() == value)
    {
        return false;
    }
    else if (value < pNode->value())
    {
        return insert(value, pNode->left());
    }
    else
    {
        return insert(value, pNode->right());
    }
}

template <typename T>
void BinarySearchTree<T>::remove(T value, BinaryTreeNode<T>*& pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    else if (pNode->value() == value)
    {
        unsigned int children = numChildren(pNode);

        if (children == 0)
        {
            delete pNode;
            pNode = nullptr;
        }
        else if (children == 1)
        {
            BinaryTreeNode<T>* child;
            if (pNode->left() == nullptr)
            {
                child = pNode->right();
            }
            else
            {
                child = pNode->left();
            }

            delete pNode;
            pNode = child;
        }
        else
        {
            // Find minimum value of right tree
            T minimumRight = findMinimum(pNode->right());

            //set pNode's value to minimumRight
            pNode->setValue(minimumRight);

            //Delete minimumRight from right tree
            remove(minimumRight, pNode->right());
        }
    }
    else if (value < pNode->value())
    {
        remove(value, pNode->left());
    }
    else
    {
        remove(value, pNode->right());
    }
}

template <typename T>
bool BinarySearchTree<T>::search(T value, BinaryTreeNode<T>*& pNode)
{
    if (pNode == nullptr)
    {
        return false;
    }
    else if (value == pNode->value())
    {
        return true;
    }
    else if (value < pNode->value())
    {
        return search(value, pNode->left());
    }
    else
    {
        return search(value, pNode->right());
    }
}

template <typename T>
unsigned int BinarySearchTree<T>::numberNodes(BinaryTreeNode<T>*& pNode)
{
    if (pNode == nullptr)
    {
        return 0;
    }
    else
    {
        return 1 + numberNodes(pNode->left()) + numberNodes(pNode->right());
    }
}

template <typename T>
unsigned int BinarySearchTree<T>::numberLeafNodes(BinaryTreeNode<T>*& pNode)
{
    if (pNode == nullptr)
    {
        return 0;
    }
    else if (isLeafNode(pNode))
    {
        return 1;
    }
    else
    {
        return numberLeafNodes(pNode->left()) + numberLeafNodes(pNode->right());
    }
}

template <typename T>
unsigned int BinarySearchTree<T>::height(BinaryTreeNode<T>*& pNode)
{
    if (pNode == nullptr)
    {
        return 0;
    }
    else if (isLeafNode(pNode))
    {
        return 1;
    }
    else
    {
        unsigned int left = 1 + height(pNode->left());
        unsigned int right = 1 + height(pNode->right());

        if (left >= right)
        {
            return left;
        }
        else
        {
            return right;
        }
    }
}

template <typename T>
void BinarySearchTree<T>::display(BinaryTreeNode<T>*& pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    else
    {
        std::cout << pNode->value() << std::endl;
        display(pNode->left());
        display(pNode->right());
    }
}

template<typename T>
bool BinarySearchTree<T>::isLeafNode(BinaryTreeNode<T>*& pNode)
{
    return numChildren(pNode) == 0;
}

template <typename T>
unsigned int BinarySearchTree<T>::numChildren(BinaryTreeNode<T>*& pNode)
{
    if (pNode->left() == nullptr && pNode->right() == nullptr)
    {
        return 0;
    }
    else if (pNode->left() == nullptr || pNode->right() == nullptr)
    {
        return 1;
    }
    else
    {
        return 2;
    }
}

template <typename T>
T BinarySearchTree<T>::findMinimum(BinaryTreeNode<T>*& pNode)
{
    if (pNode->left() == nullptr)
    {
        return pNode->value();
    }
    else
    {
        return findMinimum(pNode->left());
    }
}

template <typename T>
void BinarySearchTree<T>::destroy(BinaryTreeNode<T>*& pNode)
{
    if (pNode == nullptr)
    {
        return;
    }
    else
    {
        BinaryTreeNode<T>* left = pNode->left();
        BinaryTreeNode<T>* right = pNode->right();

        delete pNode;
        pNode = nullptr;

        destroy(left);
        destroy(right);
    }
}

#endif //SPELL_CHECKER_BINARYSEARCHTREE_HPP
