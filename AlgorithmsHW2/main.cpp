#include <stdlib.h>
#include <assert.h>
#include <iostream>
#include <fstream>

using namespace std;

// prototypes
void show( int[], int );
void shuffle( int[], int );
void swap( int&, int& );
void copy( int[], int[], int);

void bsort(int[], int, int&);
void isort(int[], int, int&); // insertion sort
void ssort(int[], int, int&); // selection sort
void msort(int[], int, int&); // mergesort
void my_qsort(int[], int, int(*choose_pivot)(int [], int), int&); // quicksort

int fixed_pivot(int[], int);
int select_pivot(int[], int);

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
	cerr << "Output file = " << argv[2] << endl <<  endl;
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
        int bbuffer[curr_size];
        copy(buffer, bbuffer, curr_size);
        bsort(bbuffer, curr_size, bcost);
        cerr << "Bubble Sort Sorted Array: ";
        show(bbuffer, curr_size);
        cerr << "Bubble Sort Cost = " << bcost << endl;
		
        int icost = 0;
        int ibuffer[curr_size];
        copy(buffer, ibuffer, curr_size);
        isort(ibuffer, curr_size, icost);
        cerr << "Insertion Sort Sorted Array: ";
        show(ibuffer, curr_size);
        cerr << "Insertion Sort Cost = " << icost << endl;

        int scost = 0;
        int sbuffer[curr_size];
        copy(buffer, sbuffer, curr_size);
        ssort(sbuffer, curr_size, scost);
        cerr << "Selection Sort Sorted Array: ";
        show(sbuffer, curr_size);
        cerr << "Selection Sort Cost = " << scost << endl;

        int mcost = 0;
        int mbuffer[curr_size];
        copy(buffer, mbuffer, curr_size);    
        msort(mbuffer, curr_size, mcost);
        cerr << "Merge Sort Sorted Array: ";
        show(mbuffer, curr_size);
        cerr << "Merge Sort Cost = " << mcost << endl;

        int qcost = 0;
        int qbuffer[curr_size];
        copy(buffer, qbuffer, curr_size);    
        my_qsort(qbuffer, curr_size, fixed_pivot, qcost);
        cerr << "Fixed Pivot Quick Sort Sorted Array: ";
        show(qbuffer, curr_size);
        cerr << "Quick Sort Cost = " << qcost << endl;

        int qcostm = 0;
        int qbufferm[curr_size];
        copy(buffer, qbufferm, curr_size); 
        my_qsort(qbufferm, curr_size, select_pivot, qcostm);
        cerr << "Median Pivot Quick Sort Sorted Array: ";
        show(qbufferm, curr_size);
        cerr << "Quick Sort Cost = " << qcostm << endl;
			
        cerr << endl;
	}

	// closing output file
	outfile.close();
}

