//------------------------------------------------------------------------------
// Pablo Zepeda
// Graph.h
// Header file for Graph ADT
//------------------------------------------------------------------------------
#include "List.h"
#ifndef Graph_H_INCLUDE
#define Graph_H_INCLUDE

#define NIL 0
#define INF -1
#define UNDEF -1

// Exported type ---------------------------------------------------------------
typedef struct GraphObj* Graph;  // Define an alias, Graph, that points to GraphObj struct

/*** Constructors-Destructors ***/

// Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n);

// Frees all dynamic memory associated with the Graph *pG,then sets the handle *pG to NULL
void freeGraph(Graph* pG);

// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G);

// Returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G);

/*** Access functions ***/

// Returns the "order" field value or the # of vertices
int getOrder(Graph G);

// Returns the "size" field value or the the # of edges
int getSize(Graph G);

// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G);

// Return the parent of vertex u in the Breadth- First tree created by BFS(), or NIL if BFS() has not yet been called
// Precondition: 1 ≤ u ≤ getOrder(G)
int getParent(Graph G, int u);

// Returns the "discover" field value
// Precondition: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u);

// Returns the "finish" field value
// Precondition 1 <= u <= getOrder(G)
int getFinish(Graph G, int u);

// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
// Precondition: 1 ≤ u ≤ getOrder(G)
int getDist(Graph G, int u);

// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL
// if no such path exists.
// Precondition getSource(G)!=NIL, so BFS() must be called before getPath().
// Precondition: 1 ≤ u ≤ getOrder(G)
void getPath(List L, Graph G, int u);

/*** Manipulation procedures ***/

// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G);

// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
// maintain these lists in sorted order by increasing labels.
// Precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v);

// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u
// (but not u to the adjacency List of v).
// Precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v);

// Runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s);

// Runs the DFS algorithm on the Graph G
// Precondition: length(S) == getOrder(G)
void DFS(Graph G, List S);

// Helper function for the DFS algorithm
void visit(Graph G, List S, int u, int *time);

/*** Other operations ***/

// prints the adjacency list representation of G to the file pointed to by out.
// The format of this representation should match the Handout examples,
// so all that is required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G);



#endif // End of include guard
