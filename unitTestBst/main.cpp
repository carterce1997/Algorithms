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
	
	BST<int> bst(8);
	bst.insert(7);      
	bst.insert(10);  
	bst.insert(9);
	bst.insert(11); 
		  
	bst.show();
	//int show = bst.search(5)->getValue();
	//int show = bst.search(10) == NULL;
	//cout << show << endl; 	
	//out << tree->getValue() << endl; 	
	  
	bst = *bst.remove(8);  
	bst = *bst.remove(9);  
	bst = *bst.remove(11);   
	bst = *bst.remove(10); 
	
	bst.insert(12); 
	bst.insert(132); 
	bst.insert(-12); 

	bst.show();  
	vector<int> vec;
 	bst.inOrder(vec);
	for(int i = 0; i < vec.size(); ++i) cout<< vec[i] << " "; 
	cout<<endl;
	return 0;
}

