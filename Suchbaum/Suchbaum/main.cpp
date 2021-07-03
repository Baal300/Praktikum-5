#include <iostream>
#include "node.h"
#include "binarySearchTree.h"

using namespace std;

int main()
{
    // Listing 1 structure
    Node<int> zero(0,1);
    Node<int> one(1,1);
    Node<int> two(2,1);
    Node<int> three(3,1);
    Node<int> four(4,1);
    Node<int> five(5,1);
    Node<int> six(6,5);
    Node<int> seven(7,1);
    Node<int> eight(8,1);

    one.setLeftChild(&zero);
    one.setRightChild(&three);
    three.setLeftChild(&two);
    three.setRightChild(&seven);
    seven.setLeftChild(&four);
    seven.setRightChild(&eight);
    four.setRightChild(&five);
    eight.setLeftChild(&six);

    one.print(0);

    BinarySearchTree<int> bst(&one);
    bst.print();

    // Preorder print
    one.printPreorder();
    cout << '\n';

    // Inorder print
    one.printInorder();
    cout << '\n';

    // Postorder print
    one.printPostorder();

    // Search
    bst.search(6);  //Da der Suchbaum aus Listing 1 nicht richtig geordnet ist (Eigenschaft eines BST nicht erfüllt), wird ein Fehler ausgegeben

    // Search with real BST
    eight.setLeftChild(nullptr);
    five.setRightChild(&six);
    bst.print();
    bst.search(6);

    //Add node with a key already in BST
    bst.addNode(6, 100);

    //Add node
    bst.addNode(11, 100);
    bst.print();

    bst.addNode(9, 100);
    bst.print();

    return 0;
}
