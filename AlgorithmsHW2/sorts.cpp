#include <stdlib.h>
#include <iostream>
#include <algorithm>

using namespace std;

void bsort(int array[], int size, int& cost) {
    for (int pass = 0; pass < size-1; ++pass) { // need n-1 passes
        for (int i = 1; i < size; ++i) { // bubble sort on each pass
            if (array[i] < array[i-1]) {
                swap(array[i], array[i-1]);
            }
            ++cost;
        }
    }
}

void isort(int array[], int size, int& cost) {
    for (int i = 1; i < size; ++i) {
        int j = i-1;
        int tmp = array[i];
        while(j >=0 & array[j] > tmp) {
            array[j+1] = array[j];
            j--; 
            cost++;
        }
        array[j+1] = tmp;
    }
}

void ssort(int array[], int size, int& cost) {
    int imin;
    for (int i = 0; i < size; ++i) {
        imin = i;  
        for (int j = i+1; j < size; ++j) {
            if (array[j] < array[imin] ) {
                imin = j;
            }
            ++cost;
        }
        swap(array[i], array[imin]);
    }   
}

void merge(int *array, int *left, int left_size, int *right, int right_size, int& cost) {
    int i, j, k;
    i = j = k = 0;

    while (i < left_size && j < right_size) {
        if (left[i] < right[j]) array[k++] = left[i++];
        else array[k++] = right[j++];
        ++cost;
    }
    while (i < left_size) array[k++] = left[i++];
    while (j < right_size) array[k++] = right[j++];
}

void merge_sort(int *array, int size, int& cost) {
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


void msort(int array[], int size, int& cost) {
    merge_sort(array, size, cost);
}

int partition(int array[], const int& left, const int& right, int& cost, int(*choose_pivot)(int [], int, int) ){
	int pivot = choose_pivot(array, left, right);
	int i = left-1;
	for(int j = left; j < right; ++j){
		++cost;
		if(array[j] < array[pivot]){
			++i;
			swap(array[i], array[j]);
		}				
	}
	swap(array[pivot], array[i+1]);
	return i+1;
}

void quickSort(int array[], int left, int right, int& cost, int (*choose_pivot)(int [], int, int)){
	if(left<right){
		int p = partition(array, left, right, cost, choose_pivot);
		quickSort(array, left, p-1, cost, choose_pivot);
		quickSort(array, p+1, right, cost, choose_pivot);
	}
}

int fixed_pivot(int array[], int left, int right) {
    return right;
}

void copy(int[], int[], int);

int my_median_pivot(int array[], int left, int right) { // this causes a segfault at n=6
    int buffer[right - left + 1];
    
    copy(array, buffer, right - left + 1);

    int k = (right - left + 1) / 2;
    while (left < right) {
        int pivot = buffer[left + k];
        swap(buffer[left + k], buffer[right]);
        int i;
        int pos;
        for (i = pos = left; i < right; ++i) {
            if (buffer[i] < pivot) {
                swap(buffer[i], buffer[pos]);
                ++pos;
            }
        }
        swap(buffer[right], buffer[pos]);
        if (pos == left + k) break;
        if (pos < left + k) left = pos + 1;
        else right = pos - 1;
    }
    int median = buffer[left + k];
    for (int i = left; i < right; ++i) {
        if (buffer[i] == median) {
            return i;
        }
    }
    return left; // just in case
}

void my_qsort(int array[], int size, int (*choose_pivot)(int [], int, int), int & cost) {
    quickSort(array, 0, size, cost, choose_pivot);
}
