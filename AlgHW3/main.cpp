#include "bst.h"
#include "avl.h"
#include "splay.h"
#include "node.h"
#include <iostream>

using namespace std;

int main() {
    BST t = BST();
    t.insert(0);
    t.insert(1);
    t.insert(-1);
    t.insert(10);
    t.insert(-20);
    t.insert(1);
    t.insert(1);
    cerr << "Show tree" << endl;
    t.show_inorder(t.get_head());
    cerr << endl;
    return 0;
}
