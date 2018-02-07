#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>


using namespace std;

// prototypes
void show( int[], int );
void shuffle( int[], int );
void swap( int&, int& );

void bsort(int[], int, int&);
void isort(int[], int, int&); // insertion sort
void ssort(int[], int, int&); // selection sort
void msort(int[], int, int&); // mergesort
//void my_qsort(int[], int, int (*choose_pivot)(int [], int)); // quicksort

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
        shuffle(buffer, curr_size);
        show(buffer, curr_size);
        
        // do bubble sort
        int bcost = 0;
        bsort(buffer, curr_size, bcost);
        show(buffer, curr_size);
        cerr << "Bubble Sort Cost = " << bcost << endl;
		
        int icost = 0;
        shuffle(buffer, curr_size);
        isort(buffer, curr_size, icost);
        show(buffer, curr_size);
        cerr << "Insertion Sort Cost = " << icost << endl;

        int scost = 0;
        shuffle(buffer, curr_size);
        ssort(buffer, curr_size, scost);
        show(buffer, curr_size);
        cerr << "Selection Sort Cost = " << scost << endl;

	}

	// closing output file
	outfile.close();

}
