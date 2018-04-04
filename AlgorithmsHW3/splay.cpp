#include <iostream>

using namespace std;

template<class T>
Splay<T> * insert( const T& v )
{
    if(v < this->value){// go left
        if(this->left == NULL){    
            this->setLeft(new Splay(v, NULL, NULL, this));
            return getRootTree(this);
        }
        else return (Splay*) this->left->insert(v);
    }
    else{
        if(this->right == NULL){
            this->setRight(new Splay(v, NULL, NULL, this));
            return getRootTree(this);
        }
        else return (Splay*) this->right->insert(v);
    }
}
