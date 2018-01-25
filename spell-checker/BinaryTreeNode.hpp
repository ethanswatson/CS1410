//
// Created by ethan on 4/23/2017.
//

#ifndef SPELL_CHECKER_BINARYTREENODE_H
#define SPELL_CHECKER_BINARYTREENODE_H

template <typename T>
class BinaryTreeNode
{
private:
    T m_data;
    BinaryTreeNode<T>* m_pLeft;
    BinaryTreeNode<T>* m_pRight;

public:
    BinaryTreeNode(T data, BinaryTreeNode<T>* pLeft, BinaryTreeNode* pRight)
        : m_data(data),
          m_pLeft(pLeft),
          m_pRight(pRight)
    {
    }

    T value()
    {
        return m_data;
    }

    void setValue(T value)
    {
        m_data = value;
    }

    BinaryTreeNode<T>*& left()
    {
        return m_pLeft;
    }

    BinaryTreeNode<T>*& right()
    {
        return m_pRight;
    }
};

#endif //SPELL_CHECKER_BINARYTREENODE_H
