#include <iostream>

using namespace std;

const int HEAVY = 2;
const int LEFT_HEAVY = 2;
const int RIGHT_HEAVY = -2;

// ****************************************************************************

template<class T>
inline AVL<T> * getRootTree(AVL<T> * tree){
	if(tree->getParent() == NULL) return tree;
	else return getRootTree( (AVL<T>*) tree->getParent() );
}

// ****************************************************************************

// (re)compute height 
template <class T>
void AVL<T>::updateHeight()
{
	Tree<T>::updateHeight();
}

// ****************************************************************************

template<class T>
inline bool getBalance(AVL<T> * tree, int& balance){
	int rightHeight = tree->getRight() == NULL ? 0 : tree->getRight()->getHeight()+1;
	int leftHeight = tree->getLeft() == NULL ? 0 : tree->getLeft()->getHeight()+1;
	balance = leftHeight - rightHeight;
	return abs(balance) >= HEAVY;
}

// ****************************************************************************

template<class T>
inline bool isLeftHeavy(AVL<T> * tree){
	if(tree == NULL) return false;
	int balance;
	getBalance(tree, balance);
	return balance > 0;
}

// ****************************************************************************

template<class T>
AVL<T> * rightRotate(AVL<T> * root){
	AVL<T> * pivot = (AVL<T>*) root->getLeft();
	
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

	((Tree<T>*)pivot)->updateHeight();
	return pivot;
}

// ****************************************************************************

template<class T>
AVL<T> * leftRotate(AVL<T> * root){
	AVL<T> * pivot = (AVL<T>*) root->getRight();

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

	((Tree<T>*)pivot)->updateHeight();
	return pivot;
}

// ****************************************************************************

// balance this node => return new root
template<class T>
AVL<T> * AVL<T>::balance(){
	Tree<T>::updateHeight();
	int balance;
	bool heavy;
	bool needRotation = getBalance(this, balance);
	
	if(needRotation){
		AVL<T> * pivot = NULL;
		if( balance >= LEFT_HEAVY ){// left-right OR left-left case

			// left left case
			if( isLeftHeavy( (AVL<T>*)this->left ) ){
				pivot = rightRotate(this);
			}
			// left right case
			else{									
				pivot = leftRotate((AVL<T>*)this->left);
				pivot = rightRotate(this);
			}

			AVL<T>::updateHeight();
			if(pivot->parent == NULL) return pivot;
			else return ((AVL<T>*)pivot->parent)->balance();
		}
		else{// right-left OR right-right case

			assert(balance <= RIGHT_HEAVY);

			// right-left case
			if( isLeftHeavy( (AVL<T>*)this->right ) ){
				pivot = rightRotate((AVL<T>*)this->right);
				pivot = leftRotate(this);
			}
			// right right case
			else{
				pivot = leftRotate(this);
			}

			AVL<T>::updateHeight();
			if(pivot->parent == NULL) return pivot;
			else return ((AVL<T>*)(pivot->parent))->balance();
		}
	}
	
	AVL<T>::updateHeight();
	if(this->parent == NULL) return this;
	else return ((AVL<T>*)this->parent)->balance();
}

// ****************************************************************************

template<class T>
AVL<T> * AVL<T>::insert(const T& x){
	
	if(x == this->value) return getRootTree(this);

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
         Cannot delete (free) data on the stack. Memory leak is caused here. No bueno
*/

template<class T>
AVL<T> * AVL<T>::remove(const T& x) {
	if(x == this->value){
		// Case (0): 1 node in whole tree
		if(this->parent == NULL && this->left == NULL && this->right == NULL){
			// delete this;
			return NULL;
		}
		// Case (1): no children
		if(this->right == NULL && this->left == NULL){
			
			// make this parent point to null
			if(this->parent->getValue() > x) this->parent->setLeft(NULL);
			else this->parent->setRight(NULL);

			//delete this;
			return ((AVL<T>*)(this->parent))->balance();
		}
		// Case(2): 1 child
		else if((this->right == NULL && this->left != NULL) || (this->right != NULL && this->left == NULL)){
			// find if child is left or right
			AVL<T> * child = (AVL<T>*) this->right != NULL ? (AVL<T>*) this->right : (AVL<T>*) this->left;
			child->setParent(this->parent);
			
			// make parent point to child (if parent isn't null)
			if(this->parent != NULL){
				if(this->parent->getValue() > x)this->parent->setLeft(child);
				else this->parent->setRight(child);
			}
			
			// delete this;
			return child->balance();
		}
		// Case (3): 2 children
		else{
			// swap value of this node with successor, and remove successor node from tree
			AVL<T> * succ = (AVL<T>*) Tree<T>::successor();			
			int valueToReplace = succ->value;
			this->right->remove(valueToReplace);
			this->setValue(valueToReplace);
			return this->balance();
		}
	}
	else if(x < this->value) return (AVL<T>*) this->left->remove(x);
	else return (AVL<T>*) this->right->remove(x);	
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