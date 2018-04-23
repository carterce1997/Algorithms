#include <iostream>

using std::cerr;
using std::endl;

// VALID
template <class T>
Splay<T>* Splay<T>::zig( Splay<T>* pivot ) { 
    /*
    * RIGHT ROTATION - BRINGS t TO ROOT OF SUBTREE
    */

   Splay<T> * root = (Splay<T>*) pivot->getParent();
	
	// set pivot's parent
	pivot->setParent( root->getParent() );
	if(root->getParent() != NULL){
		// find which side pivot is on of parent
		if( pivot->getValue() < root->getParent()->getValue() )
			root->getParent()->setLeft(pivot);
		else root->getParent()->setRight(pivot);	
	}
	
	// set up root's left child
	root->setLeft(pivot->getRight());
	if(pivot->getRight() != NULL) 
		pivot->getRight()->setParent(root);

	// set pivot's right child
	pivot->setRight(root);
	root->setParent(pivot);

	//((Tree<T>*)pivot)->updateHeight();
	return pivot;

    /*
    if (t->getParent() == NULL) return t;

    Splay<T>* parent = (Splay<T>*) t->getParent();  // parent of the node to be splayed 

    // right subtree created
    Splay<T>* newRight = new Splay<T>(parent->getValue(), RIGHT);
    Splay<T>* newLeft = (Splay<T>*) t->getLeft();

    // right rotation occurs here
    newRight->setRight(parent->getRight());
    newRight->setLeft(t->getRight());
    newRight->setParent(parent);

    if (newLeft != NULL) {
        newLeft->setParent(parent);
        newLeft->setType(LEFT);
    }
    
    // clean up pointers
    parent->setLeft(newLeft);
    parent->setRight(newRight);
    parent->setValue(t->getValue());

    newLeft = NULL;
    newRight = NULL;

    //if (parent->getParent() == NULL) parent->setType(ROOT); 
    // delete old node (replaced with new node)
    t->setParent(NULL);
    t->setRight(NULL);
    t->setLeft(NULL);

    delete t;
    t = NULL;
    
    return parent;*/
}

template <class T>
Splay<T>* Splay<T>::zag( Splay<T>* pivot ) { // left rotation
    /*
    * LEFT ROTATION - BRINGS t TO ROOT OF SUBTREE
    */

   	Splay<T> * root = (Splay<T>*) pivot->getParent();

	// set pivot's parent to be root's parent
	pivot->setParent( root->getParent() );
	if(root->getParent() != NULL){
		// find which side pivot is on of parent
		if( pivot->getValue() < pivot->getParent()->getValue() )
			pivot->getParent()->setLeft(pivot);
		else 
			pivot->getParent()->setRight(pivot);	
	}

	// set up this's right child
	root->setRight(pivot->getLeft());
	if(pivot->getLeft() != NULL) pivot->getLeft()->setParent(root);

	// set pivot's left child
	pivot->setLeft(root);
	root->setParent(pivot);

	//((Tree<T>*)pivot)->updateHeight();
	return pivot;

    /*
    if (t->getParent() == NULL) return t;

    Splay<T>* parent = (Splay<T>*) t->getParent(); // parent of the node to be splayed

    // new left subtree created
    Splay<T>* newLeft = new Splay<T>(parent->getValue(), LEFT);
    Splay<T>* newRight = (Splay<T>*)t->getRight();

    // left rotation occurs here
    newLeft->setLeft(parent->getLeft());
    newLeft->setRight(t->getLeft());
    newLeft->setParent(parent);

    if (newRight != NULL) {
        newRight->setParent(parent);
        newRight->setType(RIGHT);
    }

    // clean up pointers
    parent->setLeft(newLeft);
    parent->setRight(newRight);
    parent->setValue(t->getValue());

    newLeft = NULL;
    newRight = NULL;

    //if (parent->getParent() == NULL) parent->setType(ROOT); 
    // delete old node (replaced with new node)
    t->setParent(NULL);
    t->setLeft(NULL);
    t->setRight(NULL);
    delete t;
    t = NULL;

    return parent; // splayed node*/

}

template <class T>
Splay<T>* Splay<T>::zigzig( Splay<T>* t ) { // right right rotate
    return Splay<T>::zig(Splay<T>::zig(t)); // rotate node right
}

template <class T>
Splay<T>* Splay<T>::zigzag( Splay<T>* t ) { // right left rotate
    return Splay<T>::zag(Splay<T>::zig(t)); // rotate node right
    //t = Splay<T>::zig(t);
    //t = Splay<T>::zag(t); // rotate node right
    //return t;
}

template <class T>
Splay<T>* Splay<T>::zagzig( Splay<T>* t ) { // left right rotate
    return Splay<T>::zig(Splay<T>::zag(t)); // rotate node right
    //t = Splay<T>::zag(t);
    //t = Splay<T>::zig(t); // rotate node right
    //return t;
}

template <class T>
Splay<T>* Splay<T>::zagzag( Splay<T>* t ) { // left left rotate
    return Splay<T>::zag(Splay<T>::zag(t)); // rotate node right
}


template <class T>
Splay<T>* Splay<T>::splay( Tree<T>* t ) {
    Splay<T>* ts = (Splay<T>*) t;
    if (ts == this) { 
        cerr << "same" << endl;
        // Case: input is equal to this
        return (Splay<T>*)this;
    } else if (ts->getType() == RIGHT && ((Splay<T>*)(ts->getParent()))->getType() == ROOT) { 
        // Case: input is right and parent is root
        ts->show();
        cerr << "zag" << endl;
        zag(ts);
        return (Splay<T>*)this;
    } else if (ts->getType() == LEFT && ((Splay<T>*)(ts->getParent()))->getType() == ROOT) {
        // Case: input is left and parent is root
        cerr << "zig" << endl;
        zig(ts);
        return (Splay<T>*)this;
    } else if (ts->getType() == RIGHT && ((Splay<T>*)(ts->getParent()))->getType() != RIGHT) {
        // Case: input is right and parent is left or root
        cerr << "zag zig" << endl;
        ts = zagzig(ts);
        return splay(ts);
    } else if (ts->getType() == LEFT && ((Splay<T>*)(ts->getParent()))->getType() != LEFT) {
        // Case: input is left and parent is right or root
        cerr << "zig zag" << endl;
        ts = zigzag(ts);
        return splay(ts);
    } else if (ts->getType() == LEFT && ((Splay<T>*)(ts->getParent()))->getType() != RIGHT) {
        // Case: input is left and parent is left or root
        cerr << "zig zig" << endl;
        ts = zigzig(ts);
        return splay(ts);
    } else if (ts->getType() == RIGHT && ((Splay<T>*)(ts->getParent()))->getType() != LEFT) {
        // Case: input is right and parent is right or root
        cerr << "zag zag" << endl;
        //cerr << "this:" << endl;
        //this->show();
        //cerr << "ts:" << endl;
        //ts->show();
        //cerr <<  ((ts->getParent()))->getValue() << endl;
        //cerr <<  ((ts->getParent())->getParent())->getValue() << endl;
        //cerr <<  (((ts->getParent())->getParent())->getLeft())->getValue() << endl;
        ts = zag(ts);
        //this->show();
        //ts->show();
        return splay(ts);
    }
}

template <class T>
Splay<T> * Splay<T>::insert( const T& v )
{
    if ( this->getParent() == NULL ) {
        if( v < this->value ){// go left
            if(this->left == NULL){
                this->setLeft(new Splay(v, NULL, NULL, this, LEFT));
                this->show();
                this->splay(this->getLeft());
            } else {
                this->left->insert(v);
                this->show();
                this->splay(this->search(v));
            } 
            return getRoot();
        }
        else if ( v > this->value ){ // go right
            if(this->right == NULL){
                this->setRight(new Splay(v, NULL, NULL, this, RIGHT));  
                this->show();
                this->splay(this->getRight());    
            } else {
                this->right->insert(v);
                this->show();
                this->splay(this->search(v));
            } 
            return getRoot();
        } 
    } else {
        if( v < this->value ){// go left
            if(this->left == NULL){
                this->setLeft(new Splay(v, NULL, NULL, this, LEFT));
                return getRoot();
            }
            else return (Splay*) this->left->insert(v);
        }
        else if ( v > this->value ){ // go right
            if(this->right == NULL){
                this->setRight(new Splay(v, NULL, NULL, this, RIGHT));    
                return getRoot();
            }
            else return (Splay*) this->right->insert(v);
        }
    }
    
}


template <class T>
Splay<T> * Splay<T>::search( const T& v ) {

    // if root equals value return 
    if(v == this->value) return this;

    else if (v < this->value) { // if v less than value, return search on left tree
        if(this->left == NULL) return NULL;
        else return (Splay<T>*) this->left->search(v);
    } else { // if v greater than value, return search on right tree
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
        else if(this->right == NULL && this->left == NULL){

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

template <class T>
void Splay<T>::shows( int spaces, int side ) const
{
    for (int i = 0; i < spaces; i++)
    {
        cerr << " ";
    }

    if (side < 0)
    {
        cerr << "<" << this->value << type << "]" << endl;
    }
    else if (side > 0)
    {
        cerr << "[" << this->value << type  << ">" << endl;
    }
    else
    {
        cerr << "[" << this->value << type << "]" << endl;
    }

    if (left != NULL)
    {
        ((Splay<T>*)(this->left))->shows( spaces+4, -1 );
    }

    if (right != NULL)
    {
        ((Splay<T>*)(this->right))->shows( spaces+4, +1 );
    }

}

