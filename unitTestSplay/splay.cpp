#include <iostream>

// ****************************** SPLAY/ROTATION METHODS ******************************

template <class T>
Splay<T>* Splay<T>::zig( Splay<T>* root ) { 
    // RIGHT ROTATION - BRINGS pivot TO ROOT OF SUBTREE

	Splay<T> * pivot = (Splay<T>*) root->getLeft();
	
	// set pivot's parent
	pivot->setParent( root->getParent() );
	if ( root->getParent() != NULL ) {
		// find which side pivot is on of parent
		if( pivot->getValue() < root->getParent()->getValue() )
			root->getParent()->setLeft(pivot);
		else root->getParent()->setRight(pivot);	
	}
	
	// set root's left child
	root->setLeft( pivot->getRight() );
	if ( pivot->getRight() != NULL ){
		pivot->getRight()->setParent(root);
        (( Splay<T>*) ( pivot->getRight() ))->setType(LEFT);
    }

	// set pivot's right child
	pivot->setRight( root );
	root->setParent( pivot );

    pivot->setType( root->getType() );
    root->setType( RIGHT );

	((Tree<T>*)pivot)->updateHeight();
	return pivot;
}

// **************************************************

template <class T>
Splay<T>* Splay<T>::zag( Splay<T>* root ) {
    // LEFT ROTATION - BRINGS pivot TO ROOT OF SUBTREE

	Splay<T> * pivot = (Splay<T>*) root->getRight();

	// set pivot's parent to be root's parent
	pivot->setParent( root->getParent() );
	if(root->getParent() != NULL){
		// find which side pivot is on of parent
		if( pivot->getValue() < pivot->getParent()->getValue() )
			pivot->getParent()->setLeft(pivot);
		else
			pivot->getParent()->setRight(pivot);	
	}

	// set up root's right child
	root->setRight( pivot->getLeft() );
	if( pivot->getLeft() != NULL ){
        pivot->getLeft()->setParent(root);
        (( Splay<T>*)( pivot->getLeft() ))->setType(RIGHT);
    }
	// set pivot's left child
	pivot->setLeft( root );
	root->setParent( pivot );

    pivot->setType( root->getType() );
    root->setType( LEFT );

	((Tree<T>*)pivot)->updateHeight();
	return pivot;
}

// **************************************************

template <class T>
Splay<T>* Splay<T>::zigzig( Splay<T>* nodeToSplay ) { // right right rotate
    return Splay<T>::zig( zig( (Splay<T>*) nodeToSplay->getParent()->getParent() ) );
}
// **************************************************
template <class T>
Splay<T>* Splay<T>::zigzag( Splay<T>* nodeToSplay ) { // left right rotate
    return Splay<T>::zig( (Splay<T> *) zag( (Splay<T>*) nodeToSplay->getParent() )->getParent() );
}
// **************************************************
template <class T>
Splay<T>* Splay<T>::zagzig( Splay<T>* nodeToSplay ) { // right left rotate
    return Splay<T>::zag( (Splay<T> *) zig( (Splay<T>*) nodeToSplay->getParent() )->getParent() );
}
// **************************************************
template <class T>
Splay<T>* Splay<T>::zagzag( Splay<T>* nodeToSplay ) { // left left rotate
    return Splay<T>::zag( zag( (Splay<T>*)nodeToSplay->getParent()->getParent() ) );
}

// **************************************************

template <class T>
Splay<T>* Splay<T>::splay( Tree<T>* nodeToSplay ) {

    // first check if nodeToSplay has a parent
    if ( nodeToSplay->getParent() != NULL ) {
        
        // check if nodeToSplay has a grandparent
        if ( nodeToSplay->getParent()->getParent() != NULL ) {

            childType parentT = (( Splay<T>*) nodeToSplay->getParent() )->getType();
            childType curType = ((Splay<T>*) nodeToSplay)->getType();
            
            // case 1: Zig-Zig LEFT-LEFT
            if ( (( Splay<T>*) nodeToSplay->getParent() )->getType() != RIGHT && ((Splay<T>*) nodeToSplay)->getType() == LEFT ){
                return splay( zigzig( (Splay<T>*) nodeToSplay ) );
            }
            // case 2: Zag-Zag RIGHT-RIGHT
            else if ( (( Splay<T>*) nodeToSplay->getParent() )->getType() != LEFT && ((Splay<T>*) nodeToSplay)->getType() == RIGHT ){
                return splay( zagzag( (Splay<T>*) nodeToSplay ) );
            }
            // case 3: Zig-Zag LEFT-RIGHT
            else if ( (( Splay<T>*) nodeToSplay->getParent() )->getType() != RIGHT && ((Splay<T>*) nodeToSplay)->getType() == RIGHT ){
                return splay( zigzag( (Splay<T>*) nodeToSplay ) );
            }
            // case 4: Zag-Zig RIGHT-LEFT
            else {
                assert( (( Splay<T>*) nodeToSplay->getParent() )->getType() != LEFT && ((Splay<T>*) nodeToSplay)->getType() == LEFT );
                return splay( zagzig( (Splay<T>*) nodeToSplay ) );
            }
        }
        else {// nodeToSplay's parent is root

            if ( ((Splay<T>*) nodeToSplay)->getType() == LEFT ){
                return zig( (Splay<T>*) nodeToSplay->getParent() );
            }
            else{
                assert( ((Splay<T>*) nodeToSplay)->getType() == RIGHT );
                return zag( (Splay<T>*) nodeToSplay->getParent() );
            }
        }
    }
    else return (Splay<T>*) nodeToSplay;// nodeToSplay is at root
}

// ********************************** INSERT METHOD ***********************************

template <class T>
Splay<T> * Splay<T>::insert( const T& x ) {
    if ( x == this->value ) {
		return splay(this);
    }
	else if ( x < this->value ) {// go left
		if ( this->left == NULL ) {
			this->setLeft(new Splay(x, NULL, NULL, this, LEFT));			
			return splay(this->left);
		}
		else return (Splay*) this->left->insert(x);
	}
	else{
		if(this->right == NULL){
			this->setRight(new Splay(x, NULL, NULL, this, RIGHT));
			return splay(this->right);
		}
		else return (Splay*) this->right->insert(x);
	}
}

// ********************************** SEARCH METHOD ***********************************

template <class T>
Splay<T> * Splay<T>::search( const T& x ) {
    if(x == this->value) return splay(this);
    else if (x< this->value) { // if x less than value, value is in left subtree
        if(this->left == NULL) return splay(this);
        else return (Splay<T>*) this->left->search(x);
    }
    else { // if x greater than value,  value is in right subtree
        if(this->right == NULL) return splay(this);
        else return (Splay<T>*) this->right->search(x);
    }
}

// *********************************** REMOVE METHOD + HELPER *************************

// helper to splay max node in a subtree
template <class T>
Splay<T> * splayMax( Splay<T> * root ) {
    Splay<T> * rightSub =  (Splay<T> *) root->getRight();
    if ( rightSub != NULL ) return splayMax(rightSub);
    else return root->splay( root );
}

template <class T>
Splay<T> * Splay<T>::remove( const T& x ) {
	// splay node with x to root (search for x)
    Splay<T> * searchRoot = this->search(x);

    Splay<T> * leftSub = (Splay<T>*) searchRoot->getLeft();
    Splay<T> * rightSub = (Splay<T>*) searchRoot->getRight();
    
    if ( searchRoot->getValue() == x ) {
        // no children
        if ( leftSub == NULL && rightSub == NULL ) {
            return NULL;
        }
        // 2 children
        else if ( leftSub != NULL && rightSub != NULL ) {
            leftSub->setType(ROOT);
            leftSub->setParent(NULL);

            Splay<T> * newRoot = splayMax( leftSub );
            newRoot->setRight(rightSub);
            rightSub->setParent(newRoot);
            
            return newRoot;
        }
        // 1 child
        else {
            assert( leftSub != NULL || rightSub != NULL );
            Splay<T> * newRoot = (leftSub != NULL ? leftSub : rightSub);
            newRoot->setParent(NULL);
            newRoot->setType(ROOT);
            return newRoot;
        }
    }
    else return searchRoot;
}

// *********************************** UTILITIES **************************************

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