#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <queue>
#include <stack>
#include <assert.h>
#include <time.h>
using namespace std;


/////////////////////////////////////////////////////////
// constructors
/////////////////////////////////////////////////////////

// construct a random graph
template <class T>
Graph<T>::Graph( const vector<T> &vertex_set, bool is_directed )
{
	// FILL IN

	// establish size and directedness
	size = vertex_set.size();
	directed = is_directed;

	// seed random 
	srand (time(NULL));

	// for each element in the input vector, create a vector of random size and add to it a random connection
	for ( typename vector<T>::const_iterator itKey = vertex_set.begin(); itKey != vertex_set.end(); ++itKey ){

		// get key value and create new vector
		T valueKey = *itKey;
		vector<T> adjacentVertices;

		// generate random value within the input vector
		int randomVal = rand() % size;
		
		// This random value will be connected to the key value
		T valueConnected = vertex_set.at(randomVal);
		adjacentVertices.push_back(valueConnected);

		// Add to the adjacency list
		adjacency_list.insert(pair< T,vector<T> >(valueKey,adjacentVertices));
	}
	
}

/////////////////////////////////////////////////////////
// accessors
/////////////////////////////////////////////////////////

template <class T>
vector<T> Graph<T>::vertices()
{
	vector<T> vertex_set;

	for (vertex_iterator i = begin(); i != end(); i++) {
		vertex_set.push_back(i->first);
	}
	return vertex_set;
}



/////////////////////////////////////////////////////////
// mutators
/////////////////////////////////////////////////////////

// insert edge
template <class T>
void Graph<T>::insert( const T &u, const T &v )
{
	adjacency_list[u].push_back(v);
}



/////////////////////////////////////////////////////////
// predicates
/////////////////////////////////////////////////////////

template <class T>
bool Graph<T>::is_vertex( const T &u ) const
{
	return (adjacency_list.find(u) != end());
}

template <class T>
bool Graph<T>::is_edge( const T &u, const T &v ) const
{
	vertex_iterator i = adjacency_list.find(u);
	if (i == end()) {
		return false;
	}
	assert( i->first == u );

	typedef typename std::vector<T> NeighborList;
	typedef typename NeighborList::const_iterator neighbor_iterator;

	NeighborList neighbors = i->second;
	neighbor_iterator j = find( neighbors.begin(), neighbors.end(), v );
	return (j != neighbors.end()) ? true : false;
}


////////////////////////////////////////////////////////////
// Breadth First Search 
////////////////////////////////////////////////////////////
#define INFINITY	-1
enum COLOR {WHITE, GRAY, BLACK};

template <class T>
struct BFS_Vertex {
	COLOR color;
	int distance;
	T previous;
};


template <class T>
Graph<T> Graph<T>::BFS( const T & start_vertex )
{
	map<T, BFS_Vertex<T> > BFS_Tree;
	Graph<T> outputTree;
	queue<T> BFS_Queue;

	// FILL IN

	// get vertex list 
	vector<T> allVertices = vertices();

	BFS_Vertex<T> s;
	BFS_Vertex<T> u;

	// iterate over the vertex list to initialize the BFS_Tree
	for ( unsigned i = 0; i < allVertices.size(); i++ ){
		// set the start vertex to gray, 0 and null
		if (allVertices.at(i) == start_vertex){
			s.color = GRAY;
			s.distance = 0;
			s.previous = NULL;
			BFS_Tree.insert( pair< T, BFS_Vertex<T> >(allVertices.at(i), s) );
		// Set anything else to white, infinity and null
		} else {
			u.color = WHITE;
			u.distance = INFINITY;
			u.previous = NULL;
			BFS_Tree.insert( pair< T, BFS_Vertex<T> >(allVertices.at(i), u) );
		}
	}

	// enqueue s
	BFS_Queue.push( start_vertex );

	// while the queue is not empty
    bool isempty = false;
	
	while ( !isempty ){
		// get the next element in the queue and get its attributes from BFS_Tree, label this u
        isempty = BFS_Queue.empty();
        if ( isempty ) break;

        // dequeue
		T keyVertex = BFS_Queue.front();
        BFS_Queue.pop();

        BFS_Vertex<T> u = BFS_Tree.find( keyVertex )->second;

		// find the adjacencies of the current element
		vector<T> adjacencies = adjacency_list.find( keyVertex )->second;

    	// iterate through the adjacencies of the current element
		for ( unsigned i = 0; i < adjacencies.size(); i ++){
			
			// get the current element in the adjacency list and get its attributes, label this v
			T adjacentVertex = adjacencies.at(i); 
			BFS_Vertex<T> v = BFS_Tree.find( adjacentVertex )->second;
    
			// if v hasn't been discovered, turn it grey, increment its distance, point to u and push it onto the queue
			if ( v.color == WHITE ){
                v.color = GRAY;
				v.distance = u.distance + 1;
				v.previous = keyVertex;
				
                BFS_Queue.push( adjacentVertex );
				BFS_Tree.at( adjacentVertex ) = v;
                
                // adds the edge (u, v) to the BFS tree 
                outputTree.insert( keyVertex, adjacentVertex );            
			}
		}

		// label u black
		u.color = BLACK;

	}
	
    return outputTree;
}




////////////////////////////////////////////////////////////
// Depth First Search 
////////////////////////////////////////////////////////////
template <class T>
struct DFS_Vertex {
	COLOR color;
	int discover_time, finish_time;
	T previous;
};


template <class T>
Graph<T> Graph<T>::DFS()
{
	map<T, DFS_Vertex<T> > DFS_Tree;
	Graph<T> outputTree;
	stack<T> DFS_Stack;

	// FILL IN

	// get vertex list 
	vector<T> allVertices = vertices();

	// iterate over the vertex list to initialize the DFS_Tree
	for ( unsigned i = 0; i < allVertices.size(); i++ ){
		// Set everything to white and null
		DFS_Vertex<T> u;
		u.color = WHITE;
		u.previous = NULL;
		DFS_Tree.insert( pair< T,DFS_Vertex<T> >(allVertices.at(i),u));
	}

	// initialize time
	int discoverTime = 0;

	// iterate over the vertex list
	for ( unsigned i = 0; i < allVertices.size(); i++ ){

		// get the starting vertex
		T startVertex = allVertices.at(i);
		DFS_Vertex<T> s = DFS_Tree.find( startVertex )->second;

		// indicates the vertex has not yet been visited
		if ( s.color == WHITE ){

			// invcrement discover time 
			discoverTime++;

			// push the start vertex onto the stack
			DFS_Stack.push(startVertex);

			// change vertex color and time
			s.color = GRAY;
			s.discover_time = discoverTime;

			while ( !DFS_Stack.empty() ){

				// access the next element on the stack and get its attributes (dont erase from stack)
				T keyVertex = DFS_Stack.top();
				DFS_Vertex<T> u = DFS_Tree.find( keyVertex )->second;

				// get its adjacencies 
				vector<T> adjacencies = adjacency_list.find( keyVertex )->second;

				// indicates if the vertex has any previously undiscovered adjacencies
				bool verticesLeft = false;

				// iterate through the adjacencies of the current element
				for ( unsigned i = 0; i < adjacencies.size(); i ++){
					
					// get the current element in the adjacency list and get its attributes, label this v
					T adjacentVertex = adjacencies.at(i); 
					DFS_Vertex<T> v = DFS_Tree.find( adjacentVertex )->second;
							
					// adds the edge (u, v) to the BFS tree 
					outputTree.insert( keyVertex, adjacentVertex );   

					// if v hasn't been discovered, turn it grey
					if ( v.color == WHITE ){

						// increment discover time
						discoverTime++;

						// turn the newly discovered vertex grey and mark the time
						v.color = GRAY;
						v.discover_time = discoverTime;
						v.previous = keyVertex;
						DFS_Stack.push( adjacentVertex );

						DFS_Tree.at( adjacentVertex ) = v;

						// bcause if was hit, vertex had previously undiscovered adjacencies
						verticesLeft = true;
					}
				}

				// if vertex had no previously undiscovered adjacencies
				if ( !verticesLeft ){

					// increment discover time
					discoverTime++;

					// label vertex as done
					u.color = BLACK;
					u.finish_time = discoverTime;

					// remove from stack
					DFS_Stack.pop();
				}
			}
		}
	}

	// what is this supposed to return?
	return outputTree;
	
}


