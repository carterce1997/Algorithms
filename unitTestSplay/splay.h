#ifndef SPLAY_H
#define SPLAY_H

#include "tree.h"

enum childType {LEFT, ROOT, RIGHT, UNDEFINED};

template <class T> 
class Splay : public Tree<T> {
public:
	// constructors
	Splay( const T &v ) 
		: Tree<T>(v), type(UNDEFINED) { root = this; }

	Splay( const T &v, childType t ) 
		: Tree<T>(v), type(t) { root = this; }

	Splay( const T &v, Splay<T> *l, Splay<T> *r ) 
		: Tree<T>(v,l,r,NULL), type(UNDEFINED) { root = this; }

	Splay( const T &v, Splay<T> *l, Splay<T> *r, Splay<T> *p ) 
		: Tree<T>(v,l,r,p), type(UNDEFINED) { root = this; }

	Splay( const T &v, Splay<T> *l, Splay<T> *r, Splay<T> *p, childType t )
		: Tree<T>(v,l,r,p), type(t) { root = this; }

	// cloners
	Splay( const Splay<T> &c ) 
		: Tree<T>(c.value, c.left, c.right, c.parent, c.height), type(c.type) {}

	Splay( Splay<T> *c ) 
		: Tree<T>(c->value, c->left, c->right, c->parent, c->height), type(c->type()) {}


	// accessors
	childType getType() { return type; }
	Splay<T> *getRoot() { return root; }; // returns root of splay tree

	// mutators
	void setType( childType c ) { type = c; }


	// unvirtualized utilities
	Splay<T> * search( const T &v );	
		// returns pointer to updated tree (after search): root contains value

	Splay<T> * insert( const T &v );	
		// returns pointer to updated tree (after insert): root contains value

	Splay<T> * remove( const T &v );	
		// returns pointer to updated tree (after deletion): root contains parent


	void splay();
		// perform a splay operation on tree

private:
	childType type; 
    Splay<T>* root;

	// hidden utilities
	void splay_search( const T & v );
	void splay_insert( const T & v );
	void splay_remove( const T & v, int side );
	Splay<T> * std_remove( const T & v );

	void updateSplayHeight();

	// hidden debug-helpers
	void splayPanic( string message );
	void debugPrint( string message );
};

#include "splay.cpp"

#endif

