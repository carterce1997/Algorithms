#include <iostream>

using namespace std;

// ***********************updateHeight*****************************************************

// recurse up tree fixing heights
template<class T>
AVL<T> * fixHeightTree(AVL<T> * tree){
	tree->updateHeight();
	
	int rightHeight = tree->getRight() == NULL ? 0 : tree->getRight()->getHeight();
	int leftHeight = tree->getLeft() == NULL ? 0 : tree->getLeft()->getHeight();
	
	if( (rightHeight-leftHeight) > 1){// right-left or right-right case
			
	}
	else if( (rightHeight-leftHeight) < -1){// left-heavy
	
	}
	
	return NULL;
}

// ****************************************************************************

template<class T>
AVL<T> * AVL<T>::insert(const T& x){
	if(x < this->value){// go left
		if(this->left == NULL){
			this->setLeft(new AVL(x, NULL, NULL, this));			
			return fixHeightTree(this);
		}
		else return (AVL*) this->left->insert(x);
	}
	else{
		if(this->right == NULL){
			this->setRight(new AVL(x, NULL, NULL, this));
			return fixHeightTree(this);
		}
		else return (AVL*) this->right->insert(x);
	}
	
	//adjust nodes
	
	
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