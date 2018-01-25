#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>

using namespace std;

// prototypes
void show( int[], int );
void shuffle( int[], int );
void swap( int&, int& );
void min_search( int[], int, int&, int& );
void naive_search( int[], int, int&, int&, int& );
void recursive_search( int[], int, int&, int&, int& );
void iterative_search( int[], int, int&, int&, int& );

// main driver
int main( int argc, char *argv[] )
{
	// check inputs
	if ( argc < 3 ) {
		cerr << "Usage: ./run <size> <filename>" << endl;
		exit(1);
	}

	// read size
	int size;
	size = atoi( argv[1] ) + 1;
	cerr << "Size = " << size << endl;

	// open outputfile
	ofstream outfile;
	cerr << "Output file = " << argv[2] << endl;
	outfile.open( argv[2] );

    outfile << "Size,NaiveCost,RecursiveCost,IterativeCost" << endl;

	for (int curr_size = 2; curr_size < size; curr_size++) {
        
      cout << "Current Size = " << curr_size << endl;
		// create an array of integers
		int buffer[curr_size];
		for (int i = 0; i < curr_size; i++) {
			buffer[i] = i;
		}

		// shuffle array
        show(buffer, curr_size);
		
        // search for minmax while tracking cost
		int min, max;
		int naive_cost = 0;

        shuffle(buffer, curr_size);
		naive_search( buffer, curr_size, min, max, naive_cost );
        cout << "Naive Cost = " << naive_cost << endl;

        shuffle(buffer, curr_size);
        int recursive_cost = 0;
        recursive_search(buffer, curr_size, min, max, recursive_cost);
        cout << "Recursive Cost = " << recursive_cost << endl;

        shuffle(buffer, curr_size);
        int iterative_cost = 0;
        iterative_search(buffer, curr_size, min, max, iterative_cost);
        cout << "Iterative Cost = " << iterative_cost << endl << endl;

		assert( min == 0 && max == curr_size - 1 );
		outfile << curr_size << "," << naive_cost << "," << recursive_cost << "," << iterative_cost << endl;
	}

	// closing output file
	outfile.close();

}
