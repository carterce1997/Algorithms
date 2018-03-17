#include "bst.h"
#include "avl.h"
#include "splay.h"
#include "node.h"
#include <iostream>

using namespace std;

int main() {
    BST t = BST();
    int n = 8;
    int elements[n] = {7, 8, 3, 5, 4, 6, 2, 1};
    for (int i=0; i < n; ++i) {
        t.insert(elements[i]);
    }
    cerr << "Show tree" << endl;
    t.show_inorder(t.get_head());
    cerr << endl;

    t.delet(8);    
    t.show_inorder(t.get_head());
    cerr << endl;

    t.delet(2);
    t.show_inorder(t.get_head());
    cerr << endl;

    t.delet(3);
    t.show_inorder(t.get_head());
    cerr << endl;

    t.delet(11);
    t.show_inorder(t.get_head());
    cerr << endl;
    return 0;
}
