#include <iostream>

using std::cerr;
using std::endl;

// VALID
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
	
	// set up root's left child
	root->setLeft(pivot->getRight());
	if (pivot->getRight() != NULL){
		pivot->getRight()->setParent(root);
        (( Splay<T>*)( pivot->getRight() ))->setType(LEFT);
    }
	// set pivot's right child
	pivot->setRight(root);
	root->setParent(pivot);

    pivot->setType( root->getType() );
    root->setType( RIGHT );

	((Tree<T>*)pivot)->updateHeight();
	return pivot;
}

template <class T>
Splay<T>* Splay<T>::zag( Splay<T>* root ) { // left rotation
    // LEFT ROTATION - BRINGS pivot TO ROOT OF SUBTREE
    cout<<"FSAFSDFSDFSDA\n";

	Splay<T> * pivot = (Splay<T>*) root->getRight();

    cout<< pivot->getValue()<<endl;

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
	if(pivot->getLeft() != NULL){
        pivot->getLeft()->setParent(root);
        (( Splay<T>*)( pivot->getLeft() ))->setType(RIGHT);
    }
	// set pivot's left child
	pivot->setLeft(root);
	root->setParent(pivot);

    pivot->setType( root->getType() );
    root->setType( LEFT );

	((Tree<T>*)pivot)->updateHeight();
	return pivot;
}

template <class T>
Splay<T>* Splay<T>::zigzig( Splay<T>* nodeToSplay ) { // right right rotate
    return Splay<T>::zig( (Splay<T> *) zig(nodeToSplay)->getParent() ); // rotate node right
}

template <class T>
Splay<T>* Splay<T>::zigzag( Splay<T>* nodeToSplay ) { // right left rotate
    return Splay<T>::zig( (Splay<T> *) zag(nodeToSplay)->getParent() ); // rotate node right
}

template <class T>
Splay<T>* Splay<T>::zagzig( Splay<T>* nodeToSplay ) { // left right rotate
    return Splay<T>::zag( (Splay<T> *) zig(nodeToSplay)->getParent() ); // rotate node right
}

template <class T>
Splay<T>* Splay<T>::zagzag( Splay<T>* nodeToSplay ) { // left left rotate
    return Splay<T>::zag( (Splay<T> *) zag(nodeToSplay)->getParent() ); // rotate node right
}


template <class T>
Splay<T>* Splay<T>::splay( Tree<T>* nodeToSplay ) {
    // check if nodeToSplay has a parent

    nodeToSplay->show();

    if ( nodeToSplay->getParent() != NULL ) {
        
        Splay<T>* nodeToSplayRoot = (Splay<T>*) nodeToSplay->getParent();

        // check if nodeToSplay has a grandparent
        if ( nodeToSplay->getParent()->getParent() != NULL ) {

            cout << (( Splay<T>*) nodeToSplay->getParent() )->getType() <<"\n";
            cout << ((Splay<T>*) nodeToSplay)->getType() <<"\n";

            // case 1: Zig-Zig LEFT-LEFT
            if ( (( Splay<T>*) nodeToSplay->getParent() )->getType() != RIGHT && ((Splay<T>*) nodeToSplay)->getType() == LEFT ){
                cout << "zigzig "<< nodeToSplay->getValue()<<endl<<endl; 
                return splay( zigzig( nodeToSplayRoot ) );
            }
            // case 2: Zig-Zig RIGHT-RIGHT
            else if ( (( Splay<T>*) nodeToSplay->getParent() )->getType() != LEFT && ((Splay<T>*) nodeToSplay)->getType() == RIGHT ){
                cout << "zagzag "<< nodeToSplay->getValue()<<endl<<endl; 
                return splay( zagzag( nodeToSplayRoot ) );
            }
            // case 3: Zig-Zag LEFT-RIGHT
            else if ( (( Splay<T>*) nodeToSplay->getParent() )->getType() != RIGHT && ((Splay<T>*) nodeToSplay)->getType() == RIGHT ){
                cout << "zigzag "<< nodeToSplay->getValue()<<endl<<endl; 
                return splay( zigzag( nodeToSplayRoot ) );
            }
            // case 4: Zig-Zig RIGHT-LEFT
            else {
                assert( (( Splay<T>*) nodeToSplay->getParent() )->getType() != LEFT && ((Splay<T>*) nodeToSplay)->getType() == LEFT );
                cout << "zagzig "<< nodeToSplay->getValue()<<endl<<endl; 
                return splay( zagzig( nodeToSplayRoot ) );
            }

        }
        else {
            // nodeToSplay's parent is root
            if( ((Splay<T>*) nodeToSplay)->getType() == LEFT ){
                cout << "zig "<< nodeToSplay->getValue()<<endl; 
                return zig( (Splay<T>*) nodeToSplay->getParent() );
            }
            else{
                cout << "zag "<< nodeToSplay->getValue()<<endl; 
                assert( ((Splay<T>*) nodeToSplay)->getType() == RIGHT );
                return zag( (Splay<T>*) nodeToSplay->getParent() );
            }
        }

    }
    else return (Splay<T>*) nodeToSplay;// we are at root
}

template <class T>
Splay<T> * Splay<T>::insert( const T& x )
{
	if(x < this->value){// go left
		if(this->left == NULL){
            cout<<"inserting: "<<x<<endl;
			this->setLeft(new Splay(x, NULL, NULL, this, LEFT));			
			return splay(this->left);// go up the tree fixing nodes
		}
		else return (Splay*) this->left->insert(x);
	}
	else{
		if(this->right == NULL){
            cout<<"inserting: "<<x<<endl;
			this->setRight(new Splay(x, NULL, NULL, this, RIGHT));
			return splay(this->right);
		}
		else return (Splay*) this->right->insert(x);
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

