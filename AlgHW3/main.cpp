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
        cerr << "Inserting " << elements[i] << endl;
        t.insert(elements[i]);
    }
    cerr << "Complete tree" << endl;
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

    cerr << "There is a  5: " << t.search(5) << endl;
    cerr << "There is a 132: " << t.search(132) << endl; 

    return 0;
}
