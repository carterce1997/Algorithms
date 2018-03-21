
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
	
	BST<int> bst(1);
	bst.insert(2);
	bst.insert(5);
	bst.insert(3);
	bst.insert(-1);
	BST<int>* tree = bst.insert(-1);
		
	bst.show();
//	int show = bst.search(5)->getValue();
//	int show = bst.search(10) == NULL;
//	cout << show << endl; 	
	cout << tree->getValue() << endl; 	
	return 0;
}

