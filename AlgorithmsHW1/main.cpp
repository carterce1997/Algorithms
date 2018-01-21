#include <stdlib.h>
#include <iostream>
#include <fstream>


using namespace std;

// prototypes
void show( int[], int );
void shuffle( int[], int );
void swap( int&, int& );
void search( int[], int, int& );
void search( int[], int, int&, int& );

int cost;

// main driver
int main( int argc, char *argv[] )
{
	// check inputs
	if ( argc < 3 ) {
		cerr << "Usage: ./test_me <size> <filename>" << endl;
		exit(1);
	}

	// read size
	int size;
	size = atoi( argv[1] );
	cerr << "Size = " << size << endl;

	// create an array of integers of length size
	int buffer[size];
	for (int i=0; i<size; i++) {
		buffer[i] = i;
	}

	// check array
	show( buffer, size );

	// shuffle array
	shuffle( buffer, size );

	// check array
	show( buffer, size );

	// search for minimum
	int min, max;
	cost = 0;
	search( buffer, size, min, max );
	cerr << "Min = " << min << endl;
	cerr << "Max = " << max << endl;
	cerr << "Cost = " << cost << endl;

	// open outputfile
	ofstream outfile;
	outfile.open( argv[2] );
	outfile << size << endl;
	outfile.close();	
}


// minimum finding
void search( int buffer[], int size, int& min )
{
	min = buffer[0];
	for (int i=1; i<size; i++) {
		cost++;
		if ( buffer[i] < min ) {
			min = buffer[i];
		}
	}
}

// minmax finding
void search( int buffer[], int size, int& min, int& max )
{
	for (int i=1; i<size; i++) {
		cost++;
		if ( buffer[i] < buffer[0] ) {
			swap( buffer[0], buffer[i] );
		}
	}
	min = buffer[0];

	for (int i=2; i<size; i++) {
		cost++;
		if ( buffer[i] > buffer[1] ) {
			swap( buffer[1], buffer[i] );
		}
	}
	max = buffer[1];
}


// show array
void show( int buffer[], int size )
{
	cerr << "[";
	for (int i=0; i<size; i++) {
		cerr << buffer[i] << " ";
	}
	cerr << "]" << endl;
}


// swap two integers
void swap( int& a, int& b )
{
	int tmp;
	tmp = a;
	a = b;
	b = tmp;
}





