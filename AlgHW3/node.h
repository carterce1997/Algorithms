#ifndef NODE_H
#define NODE_H

#include <iostream>

using namespace std;

class Node
{
private:
    int value; // value stored in node

    Node* left; //pointer to left node
    Node* right; //pointer to right node
    Node* parent; //pointer to parent node

public:
    Node(int v) {
        value = v;
        left = NULL;
        right = NULL;
        parent = NULL;
    }

    Node* get_left() { return left; };
    Node* get_right() { return right; };
    Node* get_parent() { return parent; };

    void set_left(Node* l) { left = l; };
    void set_right(Node* r) { right = r; };
    void set_parent(Node* p) { parent = p; };

    int get_value() { return value; };
    void set_value(int x) { value = x; };
};


#endif 
