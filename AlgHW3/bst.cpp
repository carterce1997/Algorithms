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
                    new_node->set_parent(curr);
                    curr = NULL;
                    break;
                } else {
                    curr = curr->get_right();
                }
            } else {
                 if (curr->get_left() == NULL) { 
                    curr->set_left(new_node);
                    new_node->set_parent(curr);
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

void BST::delet(const int& x) {
    Node* curr = head;

    Node* left;
    Node* right;
    Node* parent;

    int value;
    bool is_right_child = NULL;
    while(true) {
        value = curr->get_value();
        if (x == value) {
            cerr << "Deleting node with value " << value << endl;
            left = curr->get_left();
            right = curr->get_right();
            parent = curr->get_parent();
            if ((left == NULL) && (right == NULL)) { // if current node has no children, just remove the node
                cerr << "Node has no children, deleting node..." << endl;
                if (is_right_child != NULL) {
                    is_right_child ? parent->set_right(NULL) : parent->set_left(NULL);
                }
            } else if (left == NULL) { // if current node has a child 
                cerr << "Node has a right child, deleting node and moving child..." << endl;
                is_right_child ? parent->set_right(curr->get_right()) : parent->set_left(curr->get_right());
            } else if (right == NULL) {
                cerr << "Node has a left child, deleting node and moving child..." << endl;
                is_right_child ? parent->set_right(curr->get_right()) : parent->set_left(curr->get_right());
                is_right_child ? parent->set_right(curr->get_left()) : parent->set_left(curr->get_left());
            } else { // find inorder successor of curr
                cerr << "Node has two children, finding successor and deleting node..." << endl;; 
                Node* successor = curr->get_right();
                while(successor->get_left() != NULL) {
                    successor = successor->get_left();
                }
                successor->get_parent()->set_left(NULL);

                is_right_child ? parent->set_right(successor) : parent->set_left(successor);
                left->set_parent(successor);
                right->set_parent(successor);
                successor->set_left(left);
                successor->set_right(right);

            }
            delete curr;
            break;
        } else if (x > value) {
            cerr << "Value is " << curr->get_value() << ". Moving right..." << endl;
            is_right_child = true;
            if (curr->get_right() != NULL) curr = curr->get_right();
            else {
                cerr << "Node with value " << x << " does not exist." << endl;
                return;
            }
        } else {
            cerr << "Value is " << curr->get_value() << ". Moving left..." << endl;
            is_right_child = false;
            if (curr->get_left() != NULL) curr = curr->get_left();
            else {
                cerr << "Node with value " << x << " does not exist." << endl;
                return;
            }
        }
    }
}

bool BST::search(const int& x) const {
    Node* curr = head;
    int value;
    while(true) {
        value = curr->get_value();
        if (x == value) {
            return true;
        } else if ((x > value) && (curr->get_right() != NULL)) {
            curr = curr->get_right();
        } else if ((x <= value) && (curr->get_left() != NULL)) {
            curr = curr->get_left();
        } else {
            return false;
        }
    }
}

