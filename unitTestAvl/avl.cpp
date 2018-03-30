#include <iostream>

using namespace std;

const int LEFT_HEAVY = 2;
const int RIGHT_HEAVY = -2;

// ****************************************************************************

template<class T>
int balanceDiff(AVL<T> * tree){
	int rightHeight = tree->getRight() == NULL ? 0 : tree->getRight()->getHeight();
	int leftHeight = tree->getLeft() == NULL ? 0 : tree->getLeft()->getHeight();
	return leftHeight - rightHeight;
}

// ****************************************************************************

template<class T>
bool isLeftHeavy(AVL<T> * tree){
	return balanceDiff(tree) > 0;
}

// ****************************************************************************

// balance this node => return new root
template<class T>
AVL<T> * AVL<T>::balance(){
	Tree<T>::updateHeight();
	int balance = balanceDiff(this);
	
	if( balance >= LEFT_HEAVY ){// left-left or left-right case
		
		AVL<T> * pivot = NULL;
		if( isLeftHeavy((AVL<T>*)this->left) ){// left left case => right rotation
			 pivot = (AVL<T>*) this->left;
			
			// set pivot's parent
			pivot->parent = this->parent;
			if(pivot->parent != NULL){
				// check what side pivot is on of parent
				if(pivot->parent->getRight()->getValue() == this->value) pivot->getParent()->setRight(pivot);
				else pivot->getParent()->setLeft(pivot);
			}
			
			// set up this's left child
			this->left = pivot->right;
			if(pivot->right != NULL) pivot->right->setParent(this);
			
			// set pivot's right child
			pivot->right = this;
			this->parent = pivot;

			((Tree<T>*)pivot)->updateHeight();
		}
		else{
			// left left case => left rotation then right rotation
		}
		
		if(pivot->parent == NULL) return pivot;
		else return pivot->balance();
	}
	else if( balance <= RIGHT_HEAVY ){// right-left or right-right case
		if( 0 ){
			// right left case
		}
		else{
			// right right case
		}
	}
	
	// update height
	// balance parent;
	if(this->parent == NULL) return this;
	else return balance();
}

// ****************************************************************************

template<class T>
AVL<T> * AVL<T>::insert(const T& x){
	if(x < this->value){// go left
		if(this->left == NULL){
			this->setLeft(new AVL(x, NULL, NULL, this));			
			return this->balance();// go up the tree fixing nodes
		}
		else return (AVL*) this->left->insert(x);
	}
	else{
		if(this->right == NULL){
			this->setRight(new AVL(x, NULL, NULL, this));
			return this->balance();
		}
		else return (AVL*) this->right->insert(x);
	}
}

// ****************************************************************************

/* NOTE: This method does not currently delete (free) any nodes. This is because the 
		 first node created in the constructor is created on the stack (not dynamic).
         Cannot delete (free) data on the stack. Memory leak is caused here.
*/

template<class T>
AVL<T> * AVL<T>::remove(const T& x) {

	
	
}

// ****************************************************************************

template<class T>
AVL<T> * AVL<T>::search(const T& x){
	if(x == this->value) return this;
	else if(x < this->value){
		if(this->left == NULL) return NULL;
		else return (AVL<T>*) this->left->search(x);
	}
	else{
		if(this->right == NULL) return NULL;
		else return (AVL<T>*) this->right->search(x);
	}
}