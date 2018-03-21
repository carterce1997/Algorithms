#include <iostream>

using namespace std;

// ****************************************************************************
template<class T>
inline BST<T> * getRootTree(BST<T> * tree){
	if(tree->getParent() == NULL) return tree;
	else return getRootTree( (BST<T>*) tree->getParent() );
}

template<class T>
inline BST<T> * getMinTree(BST<T> * tree){
	if(tree->getLeft() == NULL) return tree;
	else return getMinTree( (BST<T>*) tree->getLeft() );
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
			if(this->getParent()->getLeft()->getValue() == x) this->parent->setLeft(NULL);
			else this->parent->setRight(NULL);

			BST<T> * root = getRootTree(this);
			delete this;
			return root;
		}

		// Case(2): 1 child
		else if(this->right == NULL && this->left != NULL){

			if(this->parent == NULL){// we are at root node
				BST<T> * newRoot = (BST<T>*) this->left;
				newRoot->parent = NULL;
				delete this;
				return newRoot;
			}

			else{
				if(this->getParent()->getLeft()->getValue() == x) this->parent->setLeft(this->left);
				else this->getParent()->setRight(this->left);

				this->getLeft()->setParent(this->parent);
				BST<T> * root = getRootTree(this);
				delete this;
				return root;
			}

		}
		// Case(2): 1 child
		else if(right != NULL && left == NULL){

			if(this->parent == NULL){// we are at root node
				BST<T> * newRoot = (BST<T>*) this->right;
				newRoot->parent = NULL;
				delete this;
				return newRoot;
			}

			else{
				if(this->getParent()->getLeft()->getValue() == x) this->getParent()->setLeft(this->right);
				else this->getParent()->setRight(this->right);

				this->getRight()->setParent(this->parent);
				BST<T> * root = getRootTree(this);
				delete this;
				return root;
			}

		}

		// Case (3): 2 children
		else{


		}



	}


}

// ****************************************************************************
template<class T>
BST<T> * BST<T>::search(const T& x) {

	if(this == NULL) return this;
    
	else if(x == this->value) return this;

	else if(x < this->value){
		if(this->left == NULL) return NULL;
		else return (BST<T>*) this->left->search(x);
	}

	else{
		if(this->right == NULL) return NULL;
		else return (BST<T>*) this->right->search(x);
	}
}

