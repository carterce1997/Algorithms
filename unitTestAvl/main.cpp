#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <iostream>            
#include <fstream>
#include <string>

#include "avl.h"

using namespace std; 

int main(){
 	AVL<int>* tree = new AVL<int>(1); 

	tree = tree->insert(139);
	tree = tree->insert(149);
	tree = tree->insert(159);
	tree = tree->insert(169);
	tree = tree->insert(179);
	tree = tree->insert(189);
	tree = tree->insert(199);
	tree = tree->insert(2);
	
	tree = tree->insert(3);
	tree = tree->insert(5);
	tree = tree->insert(6);
	tree = tree->insert(9);
	tree = tree->insert(-9);
	tree = tree->insert(-39);
	tree = tree->insert(93);
	tree = tree->insert(92);
	tree = tree->insert(19);
	tree = tree->insert(109);
	tree = tree->insert(119);
	
	tree->show();
	cout<<"\n\n";
	
	vector<int> inOrder1;
	tree->inOrder(inOrder1);
	
	
	for(int i = 0; i < inOrder1.size(); ++i) {
		cout << inOrder1[i] << " ";
	}
	cout<<endl;
	return 0;
}

