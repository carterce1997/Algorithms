#include <stdlib.h>
#include <iostream>

using namespace std;

void naive_search( int buffer[], int curr_size, int & min, int & max, int & cost)
{
    // search for min, place at front of array
    min = buffer[0];
    int min_idx = 0;
    for (int i=1; i < curr_size; ++i) {
        if (buffer[i] < min) {
            min = buffer[i];
            min_idx = i;
        }
        ++cost;
    }
    swap(buffer[0], buffer[min_idx]);

    // search for max, place at front of array
    max = buffer[1];
    int max_idx = 1;
    for (int i=2; i < curr_size; ++i) {
        if (buffer[i] > max) {
            max = buffer[i];
            max_idx = i;
        }ssh
        ++cost;
    }
    swap(buffer[1], buffer[max_idx]);
}

void recursive_search( int buffer[], int curr_size, int & min, int & max, int & cost)
{

}

void iterative_search( int buffer[], int curr_size, int & min, int & max, int & cost)
{

}
