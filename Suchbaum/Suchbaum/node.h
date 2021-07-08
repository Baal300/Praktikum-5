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
    Node<T>* m_parent {nullptr};        // Is not necessary for a BST, you lose memory but looking up parent doesn't need to be done per algorithm

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
    void printPreorder() const
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
    void printInorder() const
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
    void printPostorder() const
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

    // Getter for leftChild and rightChild and parent
    Node<T>* leftChild() const{
         return m_leftChild;
    }

    Node<T>* rightChild() const{
        return m_rightChild;
    }

    Node<T>* parent() const
    {
        return m_parent;
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



    // Setter for leftChild and rightChild and parent
    void setLeftChild(Node<T>* leftChild)
    {
        m_leftChild = leftChild;
    }

    void setRightChild(Node<T>* rightChild)
    {
        m_rightChild = rightChild;
    }

    void setParent(Node<T> *parent)
    {
        m_parent = parent;
    }

    void setData(const T &data)
    {
        m_data = data;
    }

    void setKey(int key)
    {
        m_key = key;
    }

    // Returns height of a node's subtree
    int getHeight()
    {
        // Exception if node doesn't exist
        try {
            if (this == nullptr)
            {
                throw runtime_error("Failed to calculate height of node. Node doesn't exist.");
            }
        }  catch (runtime_error &e) {
            cerr << e.what() << '\n';
            return 0;
        }


        // Start with height 1
        int height{1};
        // Node has no children
        if (m_leftChild == nullptr && m_rightChild == nullptr)
        {
            return height;
        }
        // If it has children -> height+1
        else
        {
            int leftHeight {0};
            int rightHeight {0};
            // Recursion to left subtree
            if (m_leftChild != nullptr)
            {
                leftHeight = m_leftChild->getHeight();
            }
            // Recursion to right subtree
            if (m_rightChild != nullptr)
            {
                rightHeight = m_rightChild->getHeight();
            }

            // If left subtree is deeper than right subtree, add leftHeight to height
            if(leftHeight > rightHeight)
            {
                height += leftHeight;
            }
            // Else add rightHeight
            else
            {
                height += rightHeight;
            }

            return height;
        }

    }


    // DESTRUCTOR
    ~Node()
    {

    }
};








#endif // NODE_H
