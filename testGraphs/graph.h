#ifndef GRAPH_H
#define GRAPH_H

#include <sstream>
#include <vector>
#include <map>
using namespace std;

template <class T>
class Graph 
{
private:
	typedef typename std::map< T, vector<T> > AdjacencyList;
	AdjacencyList adjacency_list;
	int size;
	bool directed;

public:
	// constructors
	Graph():size(0), directed(true) { adjacency_list.clear(); }
		// for empty graph
	Graph( const vector<T> &vertex_set, bool is_directed );
		// for random graph
	Graph( const Graph<T> &g ):size(g.size), directed(g.directed)
		{ adjacency_list = g.adjacency_list; }
		// copy constructor

	// destructor
	~Graph() { adjacency_list.clear(); }

	// accessors
	int getSize() { return size; }
		// returns the number of vertices
	vector<T> vertices();	
		// returns all vertices in the graph

	// predicates
	bool is_vertex( const T &u ) const;				
		// true if u is a vertex in the graph
	bool is_edge( const T &u, const T &v ) const;	
		// true if (u,v) is an edge in the graph
	bool is_directed() const { return directed; }
		// true if the graph is directed

	// mutator(s)
	void setDirected(bool b) { directed = b; }
	void insert( const T &u, const T &v );
		// adds a new edge (u,v) to the graph


	// iterator for vertices
	//  reuses iterator for std::map
	typedef typename AdjacencyList::const_iterator vertex_iterator;
	vertex_iterator begin() const { return adjacency_list.begin(); }
	vertex_iterator end() const { return adjacency_list.end(); }


	// iterator for neighborhoods
	//  uses an inner iterator class
	class neighbor_iterator {
	public:
		neighbor_iterator( Graph<T> &g, T &v ) 
			{ alist = g.adjacency_list[v]; }
		T begin() 	{ it = alist.begin(); return *it; }
		bool end() 	{ return (it == alist.end()); }
		T next() 	{ return *(++it); }
	private:
		typedef typename vector<T>::const_iterator private_iterator;
		vector<T> alist;
		private_iterator it;
	};


	// overloaded output (generates graphviz format)
	friend ostream & operator<<(ostream &out, Graph<T> &graph) {
		// FILL IN

		// print header and brackets
		if ( !graph.is_directed() ){
			out << "undigraph {" << '\n';
		} else {
			out << "digraph {" << '\n';
		}

		// iterate though adjacency_list and print each value pair
		 for (typename AdjacencyList::const_iterator itKey = graph.begin(); itKey != graph.end(); ++itKey){
			for(typename vector<T>::const_iterator itVec = itKey->second.begin(); itVec != itKey->second.end(); ++itVec){
				out << '\t' << itKey->first << " -> " << *itVec << ';' << '\n';
			}
			out << '\n';
		}

		// close brackets
		out << "} \n";
		return out;
	}

	// overloaded input (assumes graphviz format)
	friend istream & operator>>(istream &in, Graph<T> &graph) {
		// FILL IN

		// will read in graph line by line
		char line[256];
		in.getline( line, 256 );

		// header determines if the graph is directed or undirected
		if ( line[0] == 'u'){
			graph.setDirected( false );
			// first line will be undigraph
		} else if ( line[0] == 'd'){
			graph.setDirected( true );
			// first line with be dirgraph
		} // input should be one of these

		// read the body
		while ( !in.eof() ){
			in.getline( line, 256 );

			// if line contains a digit or a tab it's declaring a new edge
			if ( isdigit(line[0]) ){
				// the 1st and 6th elements will be digits
				T value1 = line[0] - '0';
				T value2 = line[5] - '0';

				// insert the edge
				graph.insert( value1, value2 );
			} else if ( line[0] == '\t' ){
				// the 2nd and 7th elements will be digits
				T value1 = line[1] - '0';
				T value2 = line[6] - '0';

				// insert the edge
				graph.insert( value1, value2 );
			}
		}
		return in;
	}

	// graph searches
	Graph<T> BFS( const T &start_vertex );
	Graph<T> DFS();

};


#include "graph.cpp"

#endif

