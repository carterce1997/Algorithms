#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <cassert>
using namespace std;

void show(int[],int);

//***********************************************************************************************************
// BUBBLE SORT

void bsort(int array[], int size, int& cost){
    for (int pass = 0; pass < size-1; ++pass){ // need n-1 passes
        for (int i = 1; i < size; ++i){ // bubble sort on each pass
            if (array[i] < array[i-1]){
                swap(array[i], array[i-1]);
            }
            ++cost;
        }
    }
}

//***********************************************************************************************************
// INSERTION SORT

void isort(int array[], int size, int& cost){
    for (int i = 1; i < size; ++i){
        int j = i-1;
        int tmp = array[i];
        while(j >=0 & array[j] > tmp){
            array[j+1] = array[j];
            j--; 
            cost++;
        }
        array[j+1] = tmp;
    }
}

//***********************************************************************************************************
// SELECTION SORT

void ssort(int array[], int size, int& cost){
    int imin;
    for (int i = 0; i < size; ++i){
        imin = i;  
        for (int j = i+1; j < size; ++j){
            if (array[j] < array[imin] ){
                imin = j;
            }
            ++cost;
        }
        swap(array[i], array[imin]);
    }   
}

//***********************************************************************************************************
// MERGE SORT

void merge(int *array, int *left, int left_size, int *right, int right_size, int& cost){
    int i, j, k;
    i = j = k = 0;

    while (i < left_size && j < right_size){
        if (left[i] < right[j]) array[k++] = left[i++];
        else array[k++] = right[j++];
        ++cost;
    }
    while (i < left_size) array[k++] = left[i++];
    while (j < right_size) array[k++] = right[j++];
}

void merge_sort(int *array, int size, int& cost){
    if (size < 2) return;
    int mid = size/2;

    int* left = (int*)malloc(mid*sizeof(int));
    int* right = (int*)malloc((size-mid)*sizeof(int));

    for(int i = 0; i<mid; ++i) left[i] = array[i];
    for(int i = mid; i<size; ++i) right[i-mid] = array[i];

    merge_sort(left, mid, cost);
    merge_sort(right, size-mid, cost);

    merge(array, left, mid, right, size-mid, cost);
}


void msort(int array[], int size, int& cost){
    merge_sort(array, size, cost);
}

//***********************************************************************************************************
// QUICK SORT

int fixed_pivot(int array[], int size){
	assert(size > 0);
    return array[0];
}

int select_pivot(int array[], int size){
   	assert(size > 0);

	if (size <= 5){
		int constantCost = 0;
		merge_sort(array, size, constantCost);
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
		
		medians[i] = select_pivot(tempArray, sizeTemp);
	}

    return select_pivot(medians, sizeMedians);
}

void my_qsort(int array[], int size, int (*choose_pivot)(int [], int), int& cost){
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
		
		my_qsort(leftArr, lSize, choose_pivot, cost );
		my_qsort(rightArr, rSize, choose_pivot, cost);
		
		int i;
		for(i = 0; i < lSize; ++i) array[i] = leftArr[i];
		array[i] = pivot;
		++lSize;// to compensate for pivot element
		for(i = 0; i < rSize; ++i) array[i+lSize] = rightArr[i];
	}
}