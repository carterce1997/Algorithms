#include <iostream>
#include <stdlib.h>

using namespace std;

// swap two elements
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// shuffle array
void shuffle( int buffer[], int size )
{
	srand( time(0) );
	int j;
	for (int i=size-1; i>0; i--) {
		j = rand() % (i+1);
		swap( buffer[j], buffer[i] );
	}
}

// show array
void show( int buffer[], int size )
{
	cerr << "[ ";
	for (int i=0; i<size; i++) {
		cerr << buffer[i] << " ";
	}
	cerr << "]" << endl;
}

void copy(int array[], int new_array[], int size) {
    for (int i=0; i < size; ++i) {
        new_array[i] = array[i];
    }
}
