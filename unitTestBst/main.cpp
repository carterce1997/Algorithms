  #include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <iostream>            
#include <fstream>
#include <string>

#include "bst.h"

using namespace std; 

int main(){
	
	BST<int> bst(4);
	BST<int>* tree;
	tree = bst.insert(9);      
	tree = bst.insert(2);      
	tree = bst.insert(8);      
	tree = bst.insert(11);      
	tree = bst.insert(29);      
	tree = bst.insert(18);      
 
	bst.show();

	tree = bst.remove(9);
	tree = bst.remove(8);
	tree = bst.remove(4);
	bst.show();  
	
	vector<int> vec;
 	tree->inOrder(vec);
	
	for(int i = 0; i < vec.size(); ++i) cout<< vec[i] << " "; 
	cout<<endl;
	tree = bst.remove(2);
	tree = bst.remove(11);
	tree = bst.remove(18);
	tree = bst.remove(29);
	assert(tree == NULL);

	return 0;
}

