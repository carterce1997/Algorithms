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
    void del(int x);
    int search(int x);
    void show_inorder(Node* node);
    Node* get_head() { return head; };

};

#endif
