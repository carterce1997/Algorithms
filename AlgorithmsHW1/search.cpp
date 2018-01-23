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
        } 
        ++cost;
    }
    swap(buffer[1], buffer[max_idx]);
}

pair<int,int> recursive_helper( int buffer[], int left, int right, int & cost){
	
	if( right == left ){
		cout << "Left: " << left << "     middle: "<<(right + left)/2<<"     right: "<<right<<endl;
		return pair<int,int>(left,right);
	}	
	else if( (right - left) == 1 ){
		++cost;
		cout << "Left: " << left << "     middle: "<<(right + left)/2<<"     right: "<<right<<endl;
		return (buffer[left] < buffer[right]) ? pair<int,int>(left,right) : pair<int,int>(right,left);
	}	
	else{
		int middle = (left+right) / 2;
		cout << "Left: " << left << "     middle: "<<(right + left)/2<<"     right: "<<right<<endl;
		pair<int,int> search_left = recursive_helper(buffer, left, middle, cost );
		pair<int,int> search_right = recursive_helper(buffer, middle+1, right, cost );
		
		// compare min's and max's
		cost += 2;
		int min_index = (buffer[search_left.first] < buffer[search_right.first]) ? search_left.first : search_right.first;
		int max_index = (buffer[search_left.second] > buffer[search_right.second]) ? search_left.second : search_right.second;
		return pair<int,int>(min_index, max_index);
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
