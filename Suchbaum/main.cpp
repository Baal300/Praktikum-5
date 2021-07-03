#include <iostream>
#include "node.h"

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
    Node<int> six(6,1);
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

    return 0;
}
