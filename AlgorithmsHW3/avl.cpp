#include <iostream>

using namespace std;

const int LEFT_HEAVY = 2;
const int RIGHT_HEAVY = -2;

// ****************************************************************************

// (re)compute height 
template <class T>
void AVL<T>::updateHeight()
{
	Tree<T>::updateHeight();
}

// ****************************************************************************

template<class T>
int balanceDiff(AVL<T> * tree){
	int rightHeight = tree->getRight() == NULL ? 0 : tree->getRight()->getHeight()+1;
	int leftHeight = tree->getLeft() == NULL ? 0 : tree->getLeft()->getHeight()+1;
	return leftHeight - rightHeight;
}

// ****************************************************************************

template<class T>
bool isLeftHeavy(AVL<T> * tree){
	if(tree == NULL) return false;
	return balanceDiff(tree) > 0;
}

// ****************************************************************************

template<class T>
AVL<T> * rightRotate(AVL<T> * root){
	AVL<T> * pivot = (AVL<T>*) root->getLeft();
	
	// set pivot's parent
	pivot->setParent( root->getParent() );
	if(pivot->getParent() != NULL){
		// check what side pivot is on of parent
		if(root->getParent()->getRight()->getValue() == root->getValue()) root->getParent()->setRight(pivot);
		else root->getParent()->setLeft(pivot);
	}

	// set up this's left child
	root->setLeft(pivot->getRight());
	if(pivot->getRight() != NULL) pivot->getRight()->setParent(root);

	// set pivot's right child
	pivot->setRight(root);
	root->setParent(pivot);

	((Tree<T>*)pivot)->updateHeight();
	return pivot;
}

// ****************************************************************************

template<class T>
AVL<T> * leftRotate(AVL<T> * root){
	AVL<T> * pivot = (AVL<T>*) root->getRight();

	// set pivot's parent
	pivot->setParent( root->getParent() );
	if(pivot->getParent() != NULL){
		// check what side pivot is on of parent
		if(root->getParent()->getRight()->getValue() == root->getValue()) root->getParent()->setRight(pivot);
		else root->getParent()->setLeft(pivot);
	}

	// set up this's right child
	root->setRight(pivot->getLeft());
	if(pivot->getLeft() != NULL) pivot->getLeft()->setParent(root);

	// set pivot's left child
	pivot->setLeft(root);
	root->setParent(pivot);

	((Tree<T>*)pivot)->updateHeight();
	return pivot;
}

// ****************************************************************************


// balance this node => return new root
template<class T>
AVL<T> * AVL<T>::balance(){
	Tree<T>::updateHeight();
	int balance = balanceDiff(this);
	
	//cout << "this->value: " << this->value << "\t" << "this->height: " << this->height <<"\t";
	//cout << "Balance: " << balance << endl;
	
	AVL<T> * pivot = NULL;
	if( balance >= LEFT_HEAVY ){
		
		if( isLeftHeavy((AVL<T>*)this->left) ){	// left left case
			pivot = rightRotate(this);
		}
		else{									// left right case
			pivot = leftRotate((AVL<T>*)this->left);
			pivot = rightRotate(this);
		}
		
		if(pivot->parent == NULL) return pivot;
		else return pivot->balance();
	}
	else if( balance <= RIGHT_HEAVY ){// right-left or right-right case

		if( isLeftHeavy((AVL<T>*)this->left) ){	// right-left case
			pivot = rightRotate((AVL<T>*)this->right);
			pivot = leftRotate(this);
		}
		else{									// right right case
			pivot = leftRotate(this);
		}
		
		if(pivot->parent == NULL) return pivot;
		else return pivot->balance();
	}
	
	// update height
	// balance parent;
	if(this->parent == NULL) return this;
	else return ((AVL<T>*)this->parent)->balance();
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