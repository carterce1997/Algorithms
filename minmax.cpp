#include <stdlib.h>
#include <iostream>
#include <fstream>

using namespace std;

void show( int[], int );
void shuffle( int[], int );
void search(int[], int, int&, int&);

int main(int argc, char const *argv[]) {

  // check inputs
  if (argc < 3) {
    cerr << "Usage: ./minmax <size> <filename>" << endl;
    exit(1);
  }

  // read user data
  int size = atoi(argv[1]);
  ofstream outfile;

  // create an array of integers of length "size"
  int buffer[size];
  for (int i  = 0; i < size; ++i) {
    buffer[i] = i;
  }
  show(buffer, size);

  // shuffle array
  shuffle(buffer, size);

  // check array
  show(buffer, size);

  // find min
  int min;
  int cost = 0;
  search(buffer, size, min, cost);

  //check
  cout << min << endl;
  cout << cost << endl;

  return 0;
}

void show(int buffer[], int size) {
  cerr << "[ ";
  for (int i=0; i < size; ++i){
    cerr << buffer[i] << " ";
  }
  cerr << "]" << endl;
}

void shuffle(int buffer[], int size) {
  srand( time(0) );
  int index;
  for (int i=size-1; i>=0; --i) {
    index = rand() % size;
    swap(buffer[index], buffer[i]);
  }
}

void search(int buffer[], int size, int& min, int& cost) {
  min = buffer[0];
  for (int i=1; i<size; ++i) {
    ++cost;
    if (buffer[i] < min) {
      min = buffer[i];
    }
  }
}
