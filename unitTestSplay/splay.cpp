#include <iostream>

using std::cerr;
using std::endl;

template <class T>
void Splay<T>::zig( Splay<T>* t ) { // right rotation
    Splay<T>* parent = (Splay<T>*) t->getParent();   

    Splay<T>* newRight = new Splay<T>(parent->getValue(), RIGHT);
    Splay<T>* newLeft = (Splay<T>*) t->getLeft();

    newRight->setRight(parent->getRight());
    newRight->setLeft(t->getRight());
    newRight->setParent(parent);

    newLeft->setParent(parent);
    newLeft->setType(LEFT);

    parent->setLeft(newLeft);
    parent->setRight(newRight);
    parent->setValue(t->getValue());

    delete t;
}

template <class T>
void Splay<T>::zag( Splay<T>* t ) { // left rotation
    Splay<T>* parent = (Splay<T>*) t->getParent();

    Splay<T>* newLeft = new Splay<T>(parent->getValue());
    Splay<T>* newRight = (Splay<T>*)t->getRight();
    newRight->setType(RIGHT);

    newLeft->setLeft(parent->getLeft());
    newLeft->setRight(t->getLeft());
    newLeft->setParent(parent);
    newLeft->setType(LEFT);

    newRight->setParent(parent);

    parent->setLeft(newLeft);
    parent->setRight(newRight);
    parent->setValue(t->getValue());

    delete t;
}

template <class T>
void Splay<T>::zigzig( Splay<T>* t ) { // right right rotate
    Splay<T>* parent = (Splay<T>*) t->getParent();
    Splay<T>::zig(t);
    Splay<T>::zig(parent);
}

template <class T>
void Splay<T>::zigzag( Splay<T>* t ) { // right left rotate
    Splay<T>* parent = (Splay<T>*) t->getParent();
    Splay<T>::zig(t);
    Splay<T>::zag(parent);
}

template <class T>
void Splay<T>::zagzig( Splay<T>* t ) {
    Splay<T>* parent = (Splay<T>*) t->getParent();
    Splay<T>::zag(t);
    Splay<T>::zig(parent);
}

template <class T>
void Splay<T>::zagzag( Splay<T>* t ) {
    Splay<T>* parent = (Splay<T>*) t->getParent();
    Splay<T>::zag(t);
    Splay<T>::zag(parent);
}


template <class T>
void Splay<T>::splay( Splay<T>* t ) {
    

}

template <class T>
Splay<T> * Splay<T>::insert( const T& v )
{
    if(v < this->value){// go left
        if(this->left == NULL){    
            this->setLeft(new Splay(v, NULL, NULL, this, LEFT));
            return getRoot();
        }
        else return (Splay*) this->left->insert(v);
    }
    else{
        if(this->right == NULL){
            this->setRight(new Splay(v, NULL, NULL, this, RIGHT));    
            return getRoot();
        }
        else return (Splay*) this->right->insert(v);
    }
}


template <class T>
Splay<T> * Splay<T>::search( const T& v ) {
    if(v == this->value) return this;
    else if(v < this->value){
        if(this->left == NULL) return NULL;
        else return (Splay<T>*) this->left->search(v);
    }
    else{
        if(this->right == NULL) return NULL;
        else return (Splay<T>*) this->right->search(v);
    }
}


template <class T>
Splay<T> * Splay<T>::remove( const T& v ) {
    if(v == this->value){

        // Case (0): 1 node in whole tree
        if(this->parent == NULL && this->left == NULL && this->right == NULL){
            // delete this;
            return NULL;
        }
        // Case (1): no children
        if(this->right == NULL && this->left == NULL){

            // make this parent point to null
            if(this->parent->getValue() > v) this->parent->setLeft(NULL);
            else this->parent->setRight(NULL);

            //delete this;
            return this;
        }
        // Case(2): 1 child
        else if((this->right == NULL && this->left != NULL) || (this->right != NULL && this->left == NULL)){
            // find if child is left or right
            Splay<T> * child = (Splay<T>*) this->right != NULL ? (Splay<T>*) this->right : (Splay<T>*) this->left;
            child->setParent(this->parent);

            // make parent point to child (if parent isn't null)
            if(this->parent != NULL){
                if(this->parent->getValue() > v)this->parent->setLeft(child);
                else this->parent->setRight(child);
            }

            // delete this;
            return this;
        }
        // Case (3): 2 children
        else{
            // swap value of this node with successor, and remove successor node from tree
            Splay<T> * succ = (Splay<T>*) Tree<T>::successor();
            int valueToReplace = succ->value;
            this->right->remove(valueToReplace);
            this->setValue(valueToReplace);
            return this;
        }
    }
    else if(v < this->value) return (Splay<T>*) this->left->remove(v);
    else return (Splay<T>*) this->right->remove(v);
}

