void swap(int & a, int & b) {
    int temp = a;
    b = temp;
    a = b;
}

// shuffle array
void shuffle( int buffer[], int size )
{
	srand( time(0) );
	int index;
	for (int i=size-1; i>0; i--) {
		index = rand() % size;
		swap( buffer[index], buffer[i] );
	}
}
