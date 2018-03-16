#include "bst.h"
#include "avl.h"
#include "splay.h"
#include "node.h"
#include <iostream>

using namespace std;

int main() {
    Node parent = Node();
    Node left_child = Node(&parent, 1);
    parent.set_left(&left_child);


    Node* currnode = NULL;
    currnode = &parent;    
    cerr << currnode->get_value() << endl;
    
    currnode = currnode->get_left();
    cerr << currnode->get_value() << endl;

    return 0;
}
