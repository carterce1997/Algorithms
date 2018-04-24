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
	// reuses iterator for std::map
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

		// print vertices with no attachments
		for (typename AdjacencyList::const_iterator itKey = graph.begin(); itKey != graph.end(); ++itKey){
			if ( *(itKey->second.begin()) == NULL ){
				out << '\t' << itKey->first << ';' << '\n';
				out << '\n';
			}
		}

		// iterate though adjacency_list and print each value pair
		for (typename AdjacencyList::const_iterator itKey = graph.begin(); itKey != graph.end(); ++itKey){
			if ( *(itKey->second.begin()) != NULL )
				for(typename vector<T>::const_iterator itVec = itKey->second.begin(); itVec != itKey->second.end(); ++itVec)
					out << '\t' << itKey->first << " -> " << *itVec << ';' << '\n';
				
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
		string line;
		getline( in, line );

		// header determines if the graph is directed or undirected
		if ( line[0] == 'u'){
			// first line is undigraph
			graph.setDirected( false );

		} else{
			// first line is digraph
			assert( line[0] == 'd' );
			graph.setDirected( true );
		}

		// read the body
		while ( getline( in, line ) ){

			stringstream sstream;
			sstream.str( line );
			
			T value1;
			T value2;
						
			sstream >> value1;
			if ( sstream ) { 

				if ( sstream.peek() != ';' ) {
					for ( int i = 0; i < 3; ++i ) sstream.get();
					sstream >> value2;
					assert( sstream );
					graph.insert( value1, value2 );
				} else {
					graph.insert( value1, NULL );
				}
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
