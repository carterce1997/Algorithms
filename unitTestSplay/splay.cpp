#include <iostream>

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
            return root;
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
            return root;
        }
        // Case (3): 2 children
        else{
            // swap value of this node with successor, and remove successor node from tree
            Splay<T> * succ = (Splay<T>*) Tree<T>::successor();
            int valueToReplace = succ->value;
            this->right->remove(valueToReplace);
            this->setValue(valueToReplace);
            return root;
        }
    }
    else if(v < this->value) return (Splay<T>*) this->left->remove(v);
    else return (Splay<T>*) this->right->remove(v);
}

