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
        if (m_rootNode != nullptr)
        {
            m_rootNode->print();
        }
        else
        {
            cerr << "Can't print. Tree is empty!\n";
        }
    }

    // Search with a key; default search() starts from root of BST
    Node<T>* search(int key, Node<T>* rootNode = nullptr)
    {
        // Exception empty tree
        try {
            if (m_rootNode == nullptr)
            {
                throw runtime_error("Failed to search. Tree is empty");
            }

        }  catch (runtime_error &e) {
            cerr << e.what() << '\n';
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
        // Check if key is already in the tree ; could do this without calling search since search gives an error message everytime node is not found
        if(search(key) != nullptr)
        {
            cerr << "Can't add another node with same key in the binary search tree!\n";
            return;
        }

        // New node is created
        Node<T>* node = new Node<T>(key, data);
        // If tree is empty node is the root node
        if(m_rootNode == nullptr)
        {
            m_rootNode = node;
            return;
        }

        Node<T>* prev = nullptr;
        Node<T>* temp = m_rootNode;

        // Traversing tree to an empty node to place new node as a leaf
        while (temp != nullptr)
        {
            // Root key greater than to be inserted key, go left
            if(temp->key() > key)
            {
                prev = temp;    // Save pointer to former root node
                temp = temp->leftChild();
            }
            // Root key smaller than to be inserted key, go right
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

        // Get the leftmost node which should be node with smallest key
        while (current && current->leftChild() != nullptr)
        {
            current = current->leftChild();
        }
        return current;
    }

    void deleteNode(int key)
    {

        try {
            // Empty tree; exception
            if (m_rootNode == nullptr)
            {
                throw runtime_error("Delete operation can't be executed. Tree is empty.");
            }
        }  catch (runtime_error &empty) {
            cerr << empty.what() << '\n';
        }

        Node<T>* toBeDeletedNode = search(key);

        try {
            if (toBeDeletedNode == nullptr)
            {
                throw runtime_error("To be deleted node not found with provided key!\n");
            }
        }  catch (runtime_error &notFound) {
            cerr << notFound.what() << '\n';
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

        //If xNode does not have a right child to rotate with
        try {
            if(yNode == nullptr)
            {
                throw runtime_error("Failed to rotate left because given node has no right child.");
            }
        }  catch (runtime_error &e) {
            cout << e.what() << '\n';
            return;
        }

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

        //If xNode does not have a left child to rotate with
        try {
            if(yNode == nullptr)
            {
                throw runtime_error("Failed to rotate right because given node has no left child.");
            }
        }  catch (runtime_error &e) {
            cout << e.what() << '\n';
            return;
        }

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

    void balance(Node<T>* toBeRotatedNode)
    {
        try {
            if (toBeRotatedNode == nullptr)
            {
                throw runtime_error("Balance failed. Node doesn't exist!");
            }
        }  catch (runtime_error &e) {
            cerr << e.what() << '\n';
            return;
        }
        int leftHeight {0};
        int rightHeight{0};

        // Height of left subtree
        if (m_rootNode->leftChild() != nullptr)
        {
        leftHeight = m_rootNode->leftChild()->getHeight();
        cout << leftHeight << '\n';
        }


        // Height of right subtree
        if (m_rootNode->rightChild() != nullptr)
        {
        rightHeight = m_rootNode->rightChild()->getHeight();
        cout << rightHeight << '\n';
        }

        // Condition for rotation
        int rotationThreshold {1};
        // If left subtree is bigger in height than right subtree by more than 1
        if(leftHeight - rightHeight > rotationThreshold)
        {
            // Keeps rotating right until difference isn't bigger than 1 anymore
            while(leftHeight - rightHeight > rotationThreshold){
                toBeRotatedNode = m_rootNode;                   // After rotation we have to get the new root node
                rightRotate(toBeRotatedNode->key());
                // Calculates new height after rotation
                leftHeight = m_rootNode->leftChild()->getHeight();
                rightHeight = m_rootNode->rightChild()->getHeight();
            }

        }
        // If right subtree is bigger in height than left subtree by more than 1
        else if (rightHeight - leftHeight > rotationThreshold)
        {
            // Keeps rotating left until difference isn't bigger than 1 anymore
            while(rightHeight - leftHeight > rotationThreshold){
                toBeRotatedNode = m_rootNode;                   // After rotation we have to get the new root node
                leftRotate(toBeRotatedNode->key());
                // Calculates new height after rotation
                rightHeight = m_rootNode->rightChild()->getHeight();
                leftHeight = m_rootNode->leftChild()->getHeight();
            }
        }
    }

    // Getter for root node
    Node<T>* getRootNode() const
    {
        return m_rootNode;
    }

    void destroyRecursive(Node<T>* node)
    {
        if(node != nullptr)
        {
            // Deletes deepest nodes in tree first
            destroyRecursive(node->leftChild());
            destroyRecursive(node->rightChild());
            delete node;        // Free dynamically allocated memory
            node = nullptr;     // Prevents that pointer points to garbage
        }
    }

    // DESTRUCTOR
    ~BinarySearchTree()
    {
       destroyRecursive(m_rootNode);
       m_rootNode = nullptr;
    }

    void menu()
    {
        do{
            int menuSelection;

            //Try and Catch, in case user enters an invalid number
            do{
                try
                {
                    cout << "*************MENU*************\n"
                         << "Please select an option from the menu by entering one of the following numbers\n"
                         << "(1) Insert a node\n"
                         << "(2) Delete a node\n"
                         << "(3) Print tree\n"
                         << "(4) Rotate left\n"
                         << "(5) Rotate right\n"
                         << "(6) Balance\n"
                         << "(7) Quit\n"
                         << "\nMenu selection: ";

                    cin >> menuSelection;
                    cin.ignore(numeric_limits<streamsize>::max(), '\n'); //In case we have extraneous inputs

                    if (cin.fail())
                    {
                        cin.clear(); //clears error flags
                        cin.ignore(numeric_limits<streamsize>::max(), '\n'); //removes bad input from stream
                        throw invalid_argument("Enter only valid numbers please!");
                    }
                    else if (menuSelection < 1 || menuSelection > 7)
                    {
                        throw invalid_argument("Please enter a valid number from 1-7!");
                    }

                }
                catch (invalid_argument &invalidNumber)
                {
                    cerr << invalidNumber.what() << '\n';
                    continue;
                }

                break;
            }while(true);

            switch (menuSelection) {
            // Insert node
            case 1:
                int insertKey;
                int insertData;
                cout << "Enter key for node: ";
                cin >> insertKey;
                cout << "Enter data for node: ";
                cin >> insertData;
                addNode(insertKey, insertData);
                break;
            // Delete node
            case 2:
                int deleteKey;
                cout << "Enter key for node to be deleted: ";
                cin >> deleteKey;
                deleteNode(deleteKey);
                break;
            // Print tree
            case 3:
                print();
                break;
            // Rotate left
            case 4:
                int leftRotateKey;
                cout << "Enter key of node to be rotated to the left: ";
                cin >> leftRotateKey;
                leftRotate(leftRotateKey);
                break;
            // Rotate right
            case 5:
                int rightRotateKey;
                cout << "Enter key of node to be rotated to the right: ";
                cin >> rightRotateKey;
                rightRotate(rightRotateKey);
                break;
            // Balance tree
            case 6:
                balance(m_rootNode);
                break;
            case 7:
                break;
            default:
                cerr << "ERROR\n";
                break;
            }

            //If user enters 6 loop is broken and user quits menu, otherwise menu opens again
            if(menuSelection == 7)
            {
                break;
            }

        }while(true);
    }
};

#endif // BINARYSEARCHTREE_H
