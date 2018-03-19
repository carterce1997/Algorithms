#include <iostream>

using namespace std;

// ****************************************************************************
template<class T>
inline BST<T> * getRootTree(BST<T> * tree){
	if(tree->getParent() == NULL) return tree;
	else return getRootTree( tree->getParent() );
}

template<class T>
inline BST<T> * getMinTree(BST<T> * tree){
	if(tree->getLeft() == NULL) return tree;
	else return getMinTree( tree->getLeft() );
}


// ****************************************************************************

template<class T>
BST<T> * BST<T>::insert(const T& x){
	if(x < this->value){// go left
		if(left == NULL){
			setRight(x);
			return getRootTree(this);
		}
		else return this->left->insert(x);
	}

	else{
		if(right == NULL){
			setRight(x);
			return getRootTree(this);
		}
		else return this->right->insert(x);
	}
}

// ****************************************************************************
template<class T>
BST<T> * BST<T>::remove(const T& x) {

	if(x == this->value){
		// Case (0): 1 node in whole tree
		if(this->parent == NULL && left == NULL && right == NULL){
			delete this;
			return NULL;
		}

		// Case (1): no children
		if(right == NULL && left == NULL){
			if(this->parent->left->value == x) this->parent->left = NULL;
			else this->parent->right = NULL;

			BST<T> * root = getRootTree(this);
			delete this;
			return root;
		}

		// Case(2): 1 child
		else if(right == NULL && left != NULL){

			if(this->parent == NULL){// we are at root node
				BST<T> * newRoot = left;
				newRoot->parent = NULL;
				delete this;
				return newRoot;
			}

			else{
				if(this->parent->left->value == x) this->parent->left = left;
				else this->parent->right = left;

				this->left->parent = this->parent;
				BST<T> * root = getRootTree(this);
				delete this;
				return root;
			}

		}
		// Case(2): 1 child
		else if(right != NULL && left == NULL){

			if(this->parent == NULL){// we are at root node
				BST<T> * newRoot = right;
				newRoot->parent = NULL;
				delete this;
				return newRoot;
			}

			else{
				if(this->parent->left->value == x) this->parent->left = right;
				else this->parent->right = right;

				this->right->parent = this->parent;
				BST<T> * root = getRootTree(this);
				delete this;
				return root;
			}

		}

		// Case (3): 2 children
		else{
			
			
			// incomplete


		}



	}


}

// ****************************************************************************
template<class T>
BST<T> * BST<T>::search(const T& x) {

    if(x == this->value) return this;

	else if(x < this->value){
		if(this->left == NULL) return NULL;
		else return this->left->search(x);
	}

	else{
		if(this->right == NULL) return NULL;
		else return this->right->search(x);
	}
}

