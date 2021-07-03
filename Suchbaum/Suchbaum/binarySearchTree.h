#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "node.h"

template <class T>
class BinarySearchTree {
private:
    Node<T>* m_rootNode;

    // For recursive calls of search() given the subtree's root node
    Node<T>* searchWithRootNode(Node<T>* rootNode, int key)
    {
        // Key found
        if (rootNode->key() == key)
        {
            cout << rootNode->data() << '\n';
            return rootNode;
        }

        // Key is greater than root key -> recursion for right subtree
        if (rootNode->key() < key && rootNode->rightChild() != nullptr)
        {
           searchWithRootNode(rootNode->rightChild(), key);
        }

        // Key is smaller than root key -> recursion for left subTree
        if (rootNode->key() > key && rootNode->leftChild() != nullptr)
        {
            searchWithRootNode(m_rootNode->leftChild(), key);
        }

        // ERROR
        cerr << "ERROR --- node with provided key not found \n";
        return nullptr;
    }

public:
    BinarySearchTree(Node <T>* rootNode) : m_rootNode{rootNode}
    {

    }

    // Print the BST
    void print()
    {
        m_rootNode->print();
    }

    // Search with a key; default search() starts from root of BST
    Node<T>* search(int key, Node<T>* rootNode = nullptr)
    {
        if (rootNode != nullptr){
            // Key found
            if (rootNode->key() == key)
            {
                cout << rootNode->data() << '\n';
                return rootNode;
            }

            // Key is greater than root key -> recursion for right subtree
            if (rootNode->key() < key && rootNode->rightChild() != nullptr)
            {
               return search(key, rootNode->rightChild());
            }

            // Key is smaller than root key -> recursion for left subTree
            if (rootNode->key() > key && rootNode->leftChild() != nullptr)
            {
               return search(key, rootNode->leftChild());
            }
        }
        else
        {
            if (m_rootNode->key() == key)
            {
                cout << m_rootNode->data() << '\n';
                return m_rootNode;
            }

            // Key is greater than root key -> recursion for right subtree
            if (m_rootNode->key() < key && m_rootNode->rightChild() != nullptr)
            {
               return search(key, m_rootNode->rightChild());
            }

            // Key is smaller than root key -> recursion for left subTree
            if (m_rootNode->key() > key && m_rootNode->leftChild() != nullptr)
            {
                return search(key,m_rootNode->leftChild());
            }
        }

        // ERROR
        cerr << "ERROR --- node with provided key not found \n";    //TRY, THROW AND CATCH HERE INSTEAD
        return nullptr;
    }

    void addNode(int key, T data)
    {
        //Check if key is already in the tree
        if(search(key) != nullptr)
        {
            cerr << "Can't add another node with same key in the binary search tree!\n";
            return;
        }

        //READ THE SOLUTION
        Node<T>* node = new Node<T>(key, data);
        if(m_rootNode == nullptr)
        {
            m_rootNode = node;
            return;
        }

        Node<T>* prev = nullptr;
        Node<T>* temp = m_rootNode;

        //
        while (temp != nullptr){
            // Root key greater than to be inserted key
            if(temp->key() > key){
                prev = temp;    // Save pointer to former root node
                temp = temp->leftChild();
            }
            // Root key smaller than to be inserted key
            else if (temp->key() < key){
                 prev = temp;
                 temp = temp->rightChild();
            }
        }

        //If inserted node's key is smaller it becomes left child of prev, otherwise it becomes right child
        if(prev->key() > key)
            prev->setLeftChild(node);
        else
            prev->setRightChild(node);
    }

    /*
    // DESTRUCTOR
    ~BinarySearchTree()
    {
        //Traverse tree Inorder
        if (m_rootNode->leftChild() != nullptr)
        {
            m_leftChild->deleteInorder();
        }

        if (rightChild() != nullptr)
        {
            m_rightChild->deInorder();;
        }

        cout << m_key << ' ';
    }
    */

};
#endif // BINARYSEARCHTREE_H
