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
    swap(buffer[min_idx], buffer[0]);
    // search for max, place at front of array
    max = buffer[1];
    for (int i=2; i < curr_size; ++i) {
        if (buffer[i] > max) {
            max = buffer[i];
        } 
        ++cost;
    }
}

pair<int,int> recursive_helper( int buffer[], int left, int right, int & cost){
	
	if( right == left ){
		return pair<int,int>(buffer[left], buffer[right]);
	}	
	else if( (right - left) == 1 ){
		++cost;
		return (buffer[left] < buffer[right]) ? 
			pair<int,int>(buffer[left], buffer[right]) : pair<int,int>(buffer[right],buffer[left]);
	}	
	else{
		int middle = (left+right) / 2;
//		cout << "Left: " << left << "     middle: "<<(right + left)/2<<"     right: "<<right<<endl;
		pair<int,int> search_left = recursive_helper(buffer, left, middle, cost );
		pair<int,int> search_right = recursive_helper(buffer, middle+1, right, cost );
		
		// compare min's and max's
		cost += 2;
		int min = (search_left.first < search_right.first) ? 
			search_left.first : search_right.first;
		int max = (search_left.second > search_right.second) ? 
			search_left.second : search_right.second;
		return pair<int,int>(min, max);
	}
}


void recursive_search( int buffer[], int curr_size, int & min, int & max, int & cost)
{
	pair<int,int> min_max = recursive_helper(buffer, 0, curr_size -1, cost);
	min = min_max.first;
	max = min_max.second;
}


void iterative_search( int buffer[], int curr_size, int & min, int & max, int & cost)
{

}
