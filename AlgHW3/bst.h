#ifndef BST_H
#define BST_H

#include "node.h"

using namespace std;

class BST {
private:
    Node* head;
    int height; // tree height
    int size; // tree size

public:
    BST() {
        size = 0;
        head = NULL;
    }

    void insert(int x);
    void delet(const int& x);
    bool search(const int& x) const;
    void show_inorder(Node* node);
    inline Node* get_head() const { return head; };

};

#endif
