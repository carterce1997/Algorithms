#include <stdlib.h>
#include <iostream>

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

//void my_qsort(int array[], int size, int (*choose_pivot)(int [], int)); // quicksort
