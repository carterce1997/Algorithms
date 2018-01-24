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

	for (int curr_size = 2; curr_size < size; curr_size++) {
        
        cout << "Current Size = " << curr_size << endl;
		// create an array of integers
		int buffer[curr_size];
		for (int i = 0; i < curr_size; i++) {
			buffer[i] = i;
		}

		// shuffle array
		shuffle( buffer, curr_size );
        show(buffer, curr_size);
		
        // search for minmax while tracking cost
		int min, max, cost;
		cost = 0;

		naive_search( buffer, curr_size, min, max, cost );
        cout << "Min = " << min << endl;
        cout << "Max = " << max << endl;
        cout << "Cost = " << cost << endl;
        cout << endl;

        recursive_search( buffer, curr_size, min, max, cost )

		assert( min == 0 && max == curr_size - 1 );
		outfile << curr_size << " " << cost << endl;
	}

	// closing output file
	outfile.close();

}
