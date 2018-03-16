#include <iostream>
#include "node.h"
#include "bst.h"

using namespace std;

void BST::insert(int x) {
    Node* new_node = new Node(x);
    if (size == 0) {   
        head = new_node;
        ++size;
    } else {
        Node* curr = BST::get_head();
        int value;
        while (true) {
            value = curr->get_value();
            if (x > value) {
                if (curr->get_right() == NULL) { 
                    curr->set_right(new_node);
                    curr = NULL;
                    break;
                } else {
                    curr = curr->get_right();
                }
            } else {
                 if (curr->get_left() == NULL) { 
                    curr->set_left(new_node);
                    curr = NULL;
                    break;
                } else {
                    curr = curr->get_left();
                }
            }
        }   
    }
    ++size;
}

void BST::show_inorder(Node* node) {
    if (node == NULL) return;
    BST::show_inorder(node->get_left());
    cerr << node->get_value() << " ";
    BST::show_inorder(node->get_right());
}
