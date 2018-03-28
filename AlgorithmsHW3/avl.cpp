#include <iostream>

using namespace std;

// ****************************************************************************

template<class T>
inline AVL<T> * getRootTree(AVL<T> * tree){
	if(tree->getParent() == NULL) return tree;
	else return getRootTree( (AVL<T>*) tree->getParent() );
}

// ****************************************************************************

template<class T>
AVL<T> * AVL<T>::insert(const T& x){
	if(x < this->value){// go left
		if(this->left == NULL){
			this->setLeft(new AVL(x, NULL, NULL, this));
			return getRootTree(this);
		}
		else return (AVL*) this->left->insert(x);
	}
	else{
		if(this->right == NULL){
			this->setRight(new AVL(x, NULL, NULL, this));
			return getRootTree(this);
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

			AVL<T> * root = getRootTree(this);
			//delete this;
			return root;
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
			return getRootTree(child);
		}
		// Case (3): 2 children
		else{
			// swap value of this node with successor, and remove successor node from tree
			AVL<T> * succ = (AVL<T>*) Tree<T>::successor();			
			int valueToReplace = succ->value;
			this->right->remove(valueToReplace);
			this->setValue(valueToReplace);
			return getRootTree(this);
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