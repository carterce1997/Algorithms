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
	vector<int> inOrder;
 	AVL<int>* tree = new AVL<int>(3); 

	tree = tree->insert(5);
	tree = tree->insert(7);
	tree->show();
	
	tree = tree->insert(149);
	tree = tree->remove(149);
	tree = tree->insert(2);
	
	tree = tree->insert(3);
	tree = tree->insert(5);
	tree = tree->insert(6);
	tree = tree->insert(9);
	tree = tree->insert(-9);
	tree = tree->insert(-39);
	tree = tree->insert(93);
	
	tree = tree->insert(159);
	tree = tree->insert(169);
	tree = tree->insert(179);
	tree = tree->insert(189);
	tree = tree->insert(199);
	tree = tree->insert(92);
	
	tree->inOrder(inOrder);
	tree->show();

	//for(int i = 0; i < inOrder1.size(); ++i) {
	//	cout << inOrder1[i] << " ";
	//}cout<<endl;
	
	tree = tree->insert(19);
	tree = tree->insert(-109);
	tree = tree->insert(-119);
	tree = tree->insert(-159);
	tree = tree->insert(-169);
	tree = tree->insert(-179);
	tree = tree->insert(-189);
	tree = tree->insert(-199);
	tree = tree->insert(-299);
	tree->inOrder(inOrder);
	tree = tree->insert(-399);
	tree = tree->insert(-499);
	tree = tree->insert(-599);
	tree = tree->insert(-699);
	tree = tree->insert(699);
	
	tree->inOrder(inOrder);
	tree->show();
	
	for(int i = 3000; i < 3500; ++i){
		tree = tree->insert(i);
	}
	
	for(int i = -1300; i > -1800; --i){
		tree = tree->insert(i);
	}
	
	tree->inOrder(inOrder);
	tree->show();
	
	for(int i = 3000; i < 3500; ++i){
		tree = tree->remove(i);
	}
	
	tree->inOrder(inOrder);
	tree->show();
	
	for(int i = -1300; i > -1800; --i){
		tree = tree->remove(i);
	}
	
	tree->inOrder(inOrder);
	tree->show();
	
	cout<<endl;
	return 0;
}

