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
	
	BST<int> * tree = new BST<int>(1);
	tree = tree->insert(5);      
	tree = tree->insert(3);      
	tree = tree->insert(0);      
	tree = tree->insert(6);      
	tree = tree->insert(4);      
	tree = tree->insert(2);      
	tree = tree->insert(1);      
      
   

	//bst.show();  
	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;
	
//	vector<int> vec;
// 	tree->inOrder(vec);
	
//	for(int i = 0; i < vec.size(); ++i) cout<< vec[i] << " "; 
//	cout<<endl;
		
	tree->show();  

	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;
	
	tree = tree->remove(1);
	
	tree->show();  
	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;
	
	tree = tree->remove(5);
	tree->show();  
	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;
	
	tree = tree->remove(3);
	tree->show(); 
	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;
	
	tree = tree->remove(0);
	tree->show(); 
	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;
	
	tree = tree->remove(6);
	tree->show(); 
	cout<<endl<<endl;
	cout<<endl<<endl;
	cout<<endl<<endl;
	


	return 0;
}

