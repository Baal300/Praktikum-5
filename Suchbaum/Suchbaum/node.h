#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

template <class T>
class Node
{
private:
    int m_key;
    T m_data;
    Node<T>* m_leftChild {nullptr};
    Node<T>* m_rightChild {nullptr};

public:
    // Constructor
    Node(int key, T data) : m_key{key}, m_data{data}
    {
        cout << "Node created\n";
    }

    // Debug display of binary tree
    void print(int indent = 0)
    {
        int indentRightChild = indent;
        int indentLeftChild = indent;

        // Adds "|" according to number of indents
        for (int i{0}; i < indent; i++)
        {
            cout << '|';
        }

        cout << '>' << m_key << '\n';

        // Recursive call of print if there is a child
        if (leftChild() != nullptr)
        {
            m_leftChild->print(indentLeftChild+1);   // Indent increases
        }
        else if (rightChild() != nullptr)           // Check if there's right child to place indents for non-existing leftChild
        {
            for (int i{0}; i < indent+1; i++)
            {
                cout << '|';
            }
            cout << '\n';
        }


        if (rightChild() != nullptr)
        {
            m_rightChild->print(indentRightChild+1);
        }
        else if (leftChild() != nullptr)           // Check if there's right child to place indents for non-existing leftChild
        {
            for (int i{0}; i < indent+1; i++)
            {
                cout << '|';
            }
            cout << '\n';
        }

    }

    // Preorder output without structure
    void printPreorder()
    {
        cout << m_key << ' ';

        if (leftChild() != nullptr)
        {
            m_leftChild->printPreorder();
        }

        if (rightChild() != nullptr)
        {
            m_rightChild->printPreorder();;
        }
    }

    // Inorder output without structure
    void printInorder()
    {
        if (leftChild() != nullptr)
        {
            m_leftChild->printPreorder();
        }

        cout << m_key << ' ';

        if (rightChild() != nullptr)
        {
            m_rightChild->printPreorder();;
        }
    }

    // Postorder output without structure
    void printPostorder()
    {
        if (leftChild() != nullptr)
        {
            m_leftChild->printPreorder();
        }

        if (rightChild() != nullptr)
        {
            m_rightChild->printPreorder();;
        }

        cout << m_key << ' ';
    }

    // Getter for leftChild and rightChild
    Node<T>* leftChild() const{
        return m_leftChild;
    }

    Node<T>* rightChild() const{
        return m_rightChild;
    }

    // Getter for key
    int key() const
    {
        return m_key;
    }

    // Getter for data
    T data() const
    {
        return m_data;
    }



    // Setter for leftChild and rightChild
    void setLeftChild(Node<T>* leftChild)
    {
        m_leftChild = leftChild;
    }

    void setRightChild(Node<T>* rightChild)
    {
        m_rightChild = rightChild;
    }



    // DESTRUCTOR
    ~Node()
    {
        delete m_leftChild;
        delete m_rightChild;
    }

};




#endif // NODE_H
