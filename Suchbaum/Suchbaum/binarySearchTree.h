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
    // Default constructor; creates empty tree
    BinarySearchTree() : m_rootNode{nullptr}
    {

    }

    // Constructor with provided root node
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
        // Exception empty tree
        if (m_rootNode == nullptr)
        {
            cout << "Failed to search. Tree is empty\n";
            return nullptr;
        }

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

        // Not found
        cerr << "Node with provided key not found \n";    //TRY, THROW AND CATCH HERE INSTEAD
        return nullptr;
    }

    void addNode(int key, T data)
    {
        // Check if key is already in the tree        
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

        // Traversing tree to an empty node
        while (temp != nullptr)
        {
            // Root key greater than to be inserted key
            if(temp->key() > key)
            {
                prev = temp;    // Save pointer to former root node
                temp = temp->leftChild();
            }
            // Root key smaller than to be inserted key
            else if (temp->key() < key)
            {
                 prev = temp;
                 temp = temp->rightChild();
            }
        }

        // If inserted node's key is smaller it becomes left child of prev, otherwise it becomes right child
        if(prev->key() > key)
        {
            prev->setLeftChild(node);
            node->setParent(prev);
        }
        else
        {
            prev->setRightChild(node);
            node->setParent(prev);
        }
    }

    Node<T>* minKeyNode(Node<T>* root)
    {
        Node<T>* current = root;

        /* loop down to find the leftmost leaf */
        while (current && current->leftChild() != nullptr)
        {
            current = current->leftChild();
        }
        return current;
    }

    void deleteNode(int key)
    {
        // Empty tree; exception
        if (m_rootNode == nullptr)
        {
            cerr << "Delete operation can't be executed. Tree is empty.\n";
        }

        Node<T>* toBeDeletedNode = search(key);

        // Add exception handling here
        if (toBeDeletedNode == nullptr)
        {
            cerr << "To be deleted node not found with provided key!\n";
        }

        // Node is a leave (no childs)
        if (toBeDeletedNode->leftChild() == nullptr && toBeDeletedNode->rightChild() == nullptr)
        {
            //Pointer of its parent needs to be set to nullptr
            if( toBeDeletedNode->key() > toBeDeletedNode->parent()->key())
            {
                toBeDeletedNode->parent()->setRightChild(nullptr);     // Greater -> right child
            }
            else
            {
                toBeDeletedNode->parent()->setLeftChild(nullptr);                    // Smaller -> left child
            }
            delete toBeDeletedNode;     // Delete dynamically allocated memory of node
            return;
        }
        // With only one child (left child)
        else if (toBeDeletedNode->leftChild() != nullptr && toBeDeletedNode->rightChild() == nullptr)
        {
            Node<T>* replacementNode = toBeDeletedNode->leftChild();  // Save left child of toBeDeletedNode as its replacement
            replacementNode->setParent(toBeDeletedNode->parent());    // Parent of toBeDeletedNode becomes parent of its replacement
            // replacementNode should keep its old children independent if there are any or not
            // now the child pointer of the parent of toBeDeletedNode needs to be set to the replacement, so we check if the node was left or right child by comparing their key values
            if( toBeDeletedNode->key() > toBeDeletedNode->parent()->key())
            {
                toBeDeletedNode->parent()->setRightChild(replacementNode);     // Greater than parent means replacementNode becomes right child
            }
            else
            {
                toBeDeletedNode->parent()->setLeftChild(replacementNode);                    // Smaller -> left child
            }
            delete toBeDeletedNode;     // Delete dynamically allocated memory of node
            return;
        }
        // With only one child (right child)
        else if (toBeDeletedNode->rightChild() != nullptr && toBeDeletedNode->leftChild() == nullptr)
        {
            Node<T>* replacementNode = toBeDeletedNode->rightChild();  // Save left child of toBeDeletedNode as its replacement
            replacementNode->setParent(toBeDeletedNode->parent());    // Parent of toBeDeletedNode becomes parent of its replacement
            // replacementNode should keep its old children independent if there are any or not
            // now the child pointer of the parent of toBeDeletedNode needs to be set to the replacement, so we check if the node was left or right child by comparing their key values
            if(toBeDeletedNode->key() > toBeDeletedNode->parent()->key())
            {
                toBeDeletedNode->parent()->setRightChild(replacementNode);     // Greater than parent means replacementNode becomes right child
            }
            else
            {
                toBeDeletedNode->parent()->setLeftChild(replacementNode);                    // Smaller -> left child
            }
            delete toBeDeletedNode;     // Delete dynamically allocated memory of node
            return;
        }
        // Two children
        else
        {
            // Inorder (left - root - right) successor (from right subtree) replaces the toBeDeletedNode; so the minimum node / leftmost leaf of the right subtree
            // node with two children:
            // Get the inorder successor
            // (smallest in the right subtree)
            Node<T>* temp = minKeyNode(toBeDeletedNode->rightChild());

            // Parent of leftmost leave of the right subtree has to set it's child pointer to nullptr
            if( temp->key() > temp->parent()->key())
            {
                temp->parent()->setRightChild(nullptr);     // Greater -> right child
            }
            else
            {
                temp->parent()->setLeftChild(nullptr);                    // Smaller -> left child
            }

            // Copy the inorder
            // successor's content to this node
            toBeDeletedNode->setKey(temp->key());
            toBeDeletedNode->setData(temp->data());


            // Delete the inorder successor
            delete temp;
        }       
    }

    void leftRotate(int xNodeKey)
    {
        // x is the root node we want to rotate around
        Node <T>* xNode = search(xNodeKey);
        // y is x's right child
        Node <T>* yNode = xNode->rightChild();
        // y's left subtree becomes x's right subtree
        xNode->setRightChild(yNode->leftChild());
        // if y had a left child, its new parent is x
        if (yNode->leftChild() != nullptr)
        {
            yNode->leftChild()->setParent(xNode);
        }
        // x's parent is y's parent now
        yNode->setParent(xNode->parent());
        if (xNode->parent() == nullptr)
        {
            // if x was the root node y becomes root node
            m_rootNode = yNode;
        }
        // if x was a left child, y becomes left child of x's former parent
        else if (xNode == xNode->parent()->leftChild())
        {
            xNode->parent()->setLeftChild(yNode);
        }
        // y becomes right child
        else
        {
            xNode->parent()->setRightChild(yNode);
        }

        // x is y's left child now
        yNode->setLeftChild(xNode);
        // x's parent is y
        xNode->setParent(yNode);
    }

    void rightRotate(int xNodeKey)
    {
        // x is the root node we want to rotate around
        Node <T>* xNode = search(xNodeKey);
        // y is x's left child
        Node <T>* yNode = xNode->leftChild();
        // y's right subtree becomes x's left subtree
        xNode->setLeftChild(yNode->rightChild());
        // if y had a right child, its new parent is x
        if (yNode->rightChild() != nullptr)
        {
            yNode->rightChild()->setParent(xNode);
        }
        // x's parent is y's parent now
        yNode->setParent(xNode->parent());
        if (xNode->parent() == nullptr)
        {
            // if x was the root node y becomes root node
            m_rootNode = yNode;
        }
        // if x was a left child, y becomes left child of x's former parent
        else if (xNode == xNode->parent()->leftChild())
        {
            xNode->parent()->setLeftChild(yNode);
        }
        // y becomes right child
        else
        {
            xNode->parent()->setRightChild(yNode);
        }

        // x is y's right child now
        yNode->setRightChild(xNode);
        // x's parent is y
        xNode->setParent(yNode);
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
