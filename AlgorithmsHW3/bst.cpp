#include <iostream>

using namespace std;

// ****************************************************************************

template<class T>
inline BST<T> * getRootTree(BST<T> * tree){
	if(tree->getParent() == NULL) return tree;
	else return getRootTree( (BST<T>*) tree->getParent() );
}

// ****************************************************************************

template<class T>
BST<T> * BST<T>::insert(const T& x){
	if(x < this->value){// go left
		if(this->left == NULL){
			this->setLeft(new BST(x, NULL, NULL, this));
			return getRootTree(this);
		}
		else return (BST*) this->left->insert(x);
	}
	else{
		if(this->right == NULL){
			this->setRight(new BST(x, NULL, NULL, this));
			return getRootTree(this);
		}
		else return (BST*) this->right->insert(x);
	}
}

// ****************************************************************************

/* NOTE: This method does not currently delete (free) any nodes. This is because the 
		 first node created in the constructor is created on the stack (not dynamic).
         Cannot delete (free) data on the stack. Memory leak is caused here. No bueno
*/

template<class T>
BST<T> * BST<T>::remove(const T& x) {
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

			BST<T> * root = getRootTree(this);
			//delete this;
			return root;
		}
		// Case(2): 1 child
		else if((this->right == NULL && this->left != NULL) || (this->right != NULL && this->left == NULL)){
			// find if child is left or right
			BST<T> * child = (BST<T>*) this->right != NULL ? (BST<T>*) this->right : (BST<T>*) this->left;
			child->setParent(this->parent);
			
			// make parent point to child (if parent isn't null)
			if(this->parent != NULL){
				if(this->parent->getValue() > x)this->parent->setLeft(child);
				else this->parent->setRight(child);
			}
			
			// delete this;
			return getRootTree(child);
		}
		// Case (3): 2 children
		else{
			// swap value of this node with successor, and remove successor node from tree
			BST<T> * succ = (BST<T>*) Tree<T>::successor();			
			int valueToReplace = succ->value;
			this->right->remove(valueToReplace);
			this->setValue(valueToReplace);
			return getRootTree(this);
		}
	}
	else if(x < this->value) return (BST<T>*) this->left->remove(x);
	else return (BST<T>*) this->right->remove(x);
}

// ****************************************************************************

template<class T>
BST<T> * BST<T>::search(const T& x){
	if(x == this->value) return this;
	else if(x < this->value){
		if(this->left == NULL) return NULL;
		else return (BST<T>*) this->left->search(x);
	}
	else{
		if(this->right == NULL) return NULL;
		else return (BST<T>*) this->right->search(x);
	}
}