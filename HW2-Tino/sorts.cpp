#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

extern int cost;
void show(int[],int);

//***********************************************************************************************************
// BUBBLE SORT

void bsort( int array[], int size ) {
    for (int pass = 0; pass < size-1; ++pass) { // need n-1 passes
        for (int i = 1; i < size; ++i ) { // bubble sort on each pass
            if (array[i] < array[i-1]) 
                swap( array[i], array[i-1] );
            ++cost;
        }
    }
}

//***********************************************************************************************************
// INSERTION SORT

void isort( int array[], int size ) {
    for (int i = 1; i < size; ++i) {
        int j = i-1;
        int tmp = array[i];
        while (j >= 0 && array[j] > tmp) {
            array[j+1] = array[j];
            j--; 
            cost++;
        }
        array[j+1] = tmp;
    }
}

//***********************************************************************************************************
// SELECTION SORT

void ssort( int array[], int size ) {
    int imin;
    for (int i = 0; i < size; ++i) {
        imin = i;  
        for (int j = i+1; j < size; ++j) {
            if (array[j] < array[imin]) {
                imin = j;
            }
            ++cost;
        }
        swap( array[i], array[imin] );
    }   
}

//***********************************************************************************************************
// MERGE SORT

void merge( int *array, int *left, int left_size, int *right, int right_size ) {
    int arrayItr, leftItr, rightItr;
    arrayItr = leftItr = rightItr = 0;

    while (leftItr < left_size && rightItr < right_size){
        if (left[leftItr] < right[rightItr]) array[arrayItr++] = left[leftItr++];
        else array[arrayItr++] = right[rightItr++];
        ++cost;
    }
    while (leftItr < left_size) array[arrayItr++] = left[leftItr++];
    while (rightItr < right_size) array[arrayItr++] = right[rightItr++];
}

void merge_sort( int *array, int size ){
    if (size < 2) return;
    int mid = size/2;

    int* left = (int*)malloc(mid*sizeof(int));
    int* right = (int*)malloc((size-mid)*sizeof(int));

    for(int i = 0; i<mid; ++i) left[i] = array[i];
    for(int i = mid; i<size; ++i) right[i-mid] = array[i];

    merge_sort(left, mid );
    merge_sort(right, size-mid );

    merge( array, left, mid, right, size-mid );
}


void msort(int array[], int size){
    merge_sort( array, size );
}

//***********************************************************************************************************
// QUICK SORT

int median(int array[], int size){
   assert(size > 0);

	if (size <= 5){
		isort( array, size );
		return array[size/2];
	}

	int sizeMedians = size % 5 == 0 ? (size/5) : (size/5)+1;
	
    int medians[sizeMedians];
    for (int i = 0; i < sizeMedians; ++i){
        int subLeft = i* 5;
        int subRight = subLeft+4;

		if ( subRight > (size-1) ) subRight = size-1;
		
		int sizeTemp = subRight-subLeft + 1;
        int tempArray[sizeTemp];
		
		for(int j = 0; j < sizeTemp; ++j) tempArray[j] = array[subLeft+j];
		
		medians[i] = median(tempArray, sizeTemp);
	}

    return median(medians, sizeMedians);
}

void select(int array[], int size, int K, int& answer)
{
	answer = median(array, size);
}

void my_qsort( int array[], int size, int (*choose_pivot)(int [], int) ){
	if(size > 1){
		int pivot = choose_pivot(array, size);// pivot is value (not index)
		
		int leftArr[size];
		int rightArr[size];

		bool duplicatePivot = false;
		int lSize = 0, rSize = 0;
		
		for(int i = 0; i < size; ++i){
			if(!duplicatePivot && array[i] == pivot){
				duplicatePivot = true;
				continue;
			}

			if(array[i] < pivot){
				leftArr[lSize] = array[i];
				++lSize;
			}
			else{
				rightArr[rSize] = array[i];
				++rSize;
			}
			++cost;
		}
		
		my_qsort(leftArr, lSize, choose_pivot );
		my_qsort(rightArr, rSize, choose_pivot );
		
		int i;
		for(i = 0; i < lSize; ++i) array[i] = leftArr[i];
		array[i] = pivot;
		++lSize;// to compensate for pivot element
		for(i = 0; i < rSize; ++i) array[i+lSize] = rightArr[i];
	}
}