/*
Intro to Data Structures & Algorithms
Date: January 27, 2021
Name: Pablo Zepeda
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> // Prints diagnostics message if program assumptions are false
#include "List.h"
#include "Graph.h"

#define WHITE 0
#define GRAY 1
#define BLACK 2

// structs ---------------------------------------------------------------------
typedef struct GraphObj
{
    List* neighbors; // Adjacency list, array of lists
    int* color;      // Array: white = undiscovered, gray = frontier, black = discovered
    int* distance;   // Array: from most recent source to vertex i
    int* parent;     // Array: Parent vertex
    int* discover;
    int* finish;
    int order;       // # of vertices in the Graph
    int size;        // # of edges
    int source;      // starting vertex for BFS()
} GraphObj;

// Constructors-Destructors -----------------------------------------------------

// Returns a Graph pointing to a newly created GraphObj representing a graph having n vertices and no edges
Graph newGraph(int n)
{
    Graph newG = malloc(sizeof(GraphObj)); // Allocate memory block, in bytes, to the Heap & return an address
    newG->neighbors = malloc((n + 1) * sizeof(List)); // 0th index not used, so add one to vertex; this is the Adjacency list
    newG->color = malloc((n + 1) * sizeof(int)); // array of ints
    newG->distance = malloc((n + 1) * sizeof(int));
    newG->parent = malloc((n + 1) * sizeof(int));
    newG->discover = calloc(n + 1, sizeof(int)); // initialize array of ints to 0 & allocate it to memory
    newG->finish = calloc(n + 1, sizeof(int));
    newG->order = n; // # of vertices
    newG->size = NIL; // 0
    newG->source = NIL; // 0
    
    for(int i = 1; i <= n; i++)
    {
        newG->neighbors[i] = newList(); // Initialize the array of Lists with listObjs
        newG->color[i] = WHITE;         // Initialize array
        newG->distance[i] = INF;
        newG->parent[i] = NIL;
        newG->discover[i] = UNDEF;
        newG->finish[i] = UNDEF;
    }
    
    return newG;
}

// Frees all dynamic memory associated with the Graph *pG,then sets the handle *pG to NULL
void freeGraph(Graph* pG)
{
    for(int i = 1; i <= getOrder(*pG); i++) // start at index 1 & stop @ the end of array
    {
        freeList(& (*pG)-> neighbors[i]);  // pass in the address of list, listObj pointer, to free all the listObjs
        free((*pG)->neighbors[i]);        // Free the array of Lists allocated in Heap
    }
    free((*pG)->neighbors);              // free the 0th index List allocated in Heap
    (*pG)->neighbors = NULL;
    free((*pG)->color);                  // free int array allocated in the Heap
    (*pG)->color = NULL;
    free((*pG)->distance);
    (*pG)->distance = NULL;
    free((*pG)->parent);
    (*pG)->parent = NULL;
    free((*pG)->discover);
    (*pG)->discover = NULL;
    free((*pG)->finish);
    (*pG)->finish = NULL;
    free((*pG));
    *pG = NULL;
    
}

// Returns a reference to a new graph object representing the transpose of G
Graph transpose(Graph G)
{
    if(G == NULL)
    {
        printf("Error: calling transpose() on NULL Graph reference\n");
        exit(1);
    }
    Graph nG = newGraph(getOrder(G)); // new transposed Graph
    
    for(int i = 1; i <= getOrder(G); i++) // add opposite directed edges
    {
        moveFront(G->neighbors[i]); // move cursor to the front of each adjacency list in the array
        List listPtr = G->neighbors[i]; // access each List pointer
        if(index(listPtr) >= 0) // as long as the cursor is defined
        {
            while(index(listPtr) >= 0)
            {
                int k = get(listPtr);
                addArc(nG, k, i); // insert a new directed edge, k->i
                moveNext(listPtr);
            }
        }
        
    }
    return nG;
}

// Returns a reference to a new graph which is a copy of G
Graph copyGraph(Graph G)
{
    if(G == NULL)
    {
        printf("Error: calling transpose() on NULL Graph reference\n");
        exit(1);
    }
    Graph copyG = newGraph(getOrder(G)); // new empty graph
    for(int i = 1; i <= getOrder(G); i++)
    {
        moveFront(G->neighbors[i]);
        while(index(G->neighbors[i]) != -1) // As long as the cursor is defined
        {
            addArc(copyG, i, get(G->neighbors[i])); // copy the edges onto the new graph
            moveNext(G->neighbors[i]);
        }
    }
    return copyG;
}

// Access functions -------------------------------------------------------------

// Returns the "order" field value or the # of vertices
int getOrder(Graph G)
{
    if(G == NULL)
    {
        printf("Error: calling getOrder() on NULL Graph reference\n");
        exit(1);
    }
    return G->order;
}

// Returns the "size" field value or the the # of edges
int getSize(Graph G)
{
    if(G == NULL)
    {
        printf("Error: calling getSize() on NULL Graph reference\n");
        exit(1);
    }
    return G->size;
}

// Returns the source vertex most recently used in function BFS(), or NIL if BFS() has not yet been called.
int getSource(Graph G)
{
    if(G == NULL)
    {
        printf("Error: calling getSource() on NULL Graph reference\n");
        exit(1);
    }
    return G->source;
}

// Return the parent of vertex u in the Breadth- First tree created by BFS(), or NIL if BFS() has not yet been called
// Precondition: 1 ≤ u ≤ getOrder(G)
int getParent(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error: calling getParent() on NULL Graph reference\n");
        exit(1);
    }
    if(u >= 1 && u <= getOrder(G))
    {
        return G->parent[u];
    }
    else
    {
        printf("Error: calling getParent() & precondition not met\n");
        exit(1);
    }
}

// Returns the "discover" field value
// Precondition: 1 <= u <= getOrder(G)
int getDiscover(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error: calling getDiscover() on NULL Graph reference\n");
        exit(1);
    }
    if(u >= 1 && u <= getOrder(G))
    {
        return G->discover[u];
    }
    else
    {
        printf("Error: calling getDistance() & precondition not met\n");
        exit(1);
    }
}

// Returns the "finish" field value
// Precondition 1 <= u <= getOrder(G)
int getFinish(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error: calling getFinish() on NULL Graph reference\n");
        exit(1);
    }
    if(u >= 1 && u <= getOrder(G))
    {
        return G->finish[u];
    }
    else
    {
        printf("Error: calling getFinish() & precondition not met\n");
        exit(1);
    }
}

// Returns the distance from the most recent BFS source to vertex u, or INF if BFS() has not yet been called.
// Precondition: 1 ≤ u ≤ getOrder(G)
int getDist(Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error: calling getDist() on NULL Graph reference\n");
        exit(1);
    }
    if(u >=1 && u <= getOrder(G))
    {
        return G->distance[u];
    }
    else
    {
       printf("Error: calling getDist() & precondition not met\n");
       exit(1);
    }
    
}

// Appends to the List L the vertices of a shortest path in G from source to u, or appends to L the value NIL
// if no such path exists.
// Precondition getSource(G)!=NIL, so BFS() must be called before getPath().
// Precondition: 1 ≤ u ≤ getOrder(G)
void getPath(List L, Graph G, int u)
{
    if(G == NULL)
    {
        printf("Error: calling getPath() on NULL Graph reference\n");
        exit(1);
    }
    else if(L == NULL)
    {
        printf("Error: calling getPath() on NULL List reference\n");
        exit(1);
    }
    
    int temp = u; // Used to tranverse thru the vertices
    
    if(getDist(G, u) == INF) // no such path exits
    {
        append(L, NIL);
    }
    else if(getSource(G) != NIL && u >= 1 && u <= getOrder(G))
    {
        // Needs 2, 3, 7 update
        //2 3 7   temp = 2
        append(L, u); // Destination @ back
        moveBack(L);  // move cursor to the back
        
        for(; getParent(G, temp) != NIL;)
        {
            insertBefore(L, getParent(G, get(L))); // insert the parent of the cursor before the cursor
            
            if(getParent(G, temp) != NIL) // parent exists
            {
                movePrev(L);
                temp = get(L); // update the vertex value
            }
            
        }
    }
    else
    {
        printf("Error: calling getPath() and the Preconditions are not met\n");
        exit(1);
    }
}
// Manipulation procedures ------------------------------------------------------

// Deletes all edges of G, restoring it to its original (no edge) state.
void makeNull(Graph G)
{
    if(G == NULL)
       {
           printf("Error: calling makeNull() on NULL Graph reference\n");
           exit(1);
       }
    int arrSize = getOrder(G) - 1;  // last index of the Adjacency list
    for(;arrSize >= 1; arrSize--)
    {
        clear(G->neighbors[arrSize]); // Deletes all elements of the Adjacency list
    }
    G->size = 0;
    G->order = 0;
    G->source = NIL;
}

// Inserts a new edge joining u to v, i.e. u is added to the adjacency List of v, and v to the adjacency List of u.
// maintain these lists in sorted order by increasing labels.
// Precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addEdge(Graph G, int u, int v) // *
{
    if(G == NULL)
        {
            printf("Error: calling addEdge() on NULL Graph reference\n");
            exit(1);
        }
    if( u < 1 || u > getOrder(G))
    {
        printf("Error: calling addEdge() and the Preconditions are not met\n");
        exit(1);
    }
    else if(v < 1 || v > getOrder(G))
    {
        printf("Error: calling addEdge() and the Preconditions are not met\n");
        exit(1);
    }
    List tempU = G->neighbors[u];
    List tempV = G->neighbors[v];
    
    if(length(tempU) == 0 && length(tempV) == 0)  // tempU & tmepV are empty
    {
        append(tempU, v);
        append(tempV, u);
        G->size++;   // # of edges increase by one
    }
    else if(length(tempU) > 0 && length(tempV) > 0)  // tempU & tempV are NOT empty
    {
        moveFront(tempU); // move the cursor to the front for both of the lists
        moveFront(tempV);
        
        if(v < back(tempU)) // if v < than back element of U's Adjacency list
        {
            while(v > get(tempU)) // v > than list elements starting @ the front
            {
                moveNext(tempU); // find the correct position
            }
            insertBefore(tempU, v); // Add the edge to U's Adjacency list in the correct position
        }
        else  // v > than back element of U's Adjacency list
        {
            append(tempU, v);
        }
        if(u < back(tempV)) // if u < than back element of V's Adjacency list
        {
            while(u > get(tempV)) // u > than list elements starting @ the front
            {
                moveNext(tempV); // find the correct position
            }
            insertBefore(tempV, u); // Add the edge to V's Adjacency list in the correct position
        }
        else // u > than back element of V's Adjacency list
        {
            append(tempV, u);
        }
        G->size++;  // # of edges increase by one
    }
    else if(length(tempV) == 0 && length(tempU) > 0) // Adjacency list of V is empty, but the Adjacency list of U is not
    {
        append(tempV, u); // Add u into the empty Adjacency list of V
        moveFront(tempU);
        
        if(v < back(tempU)) // if v < than back element of U's Adjacency list
        {
            while(v > get(tempU)) // v > than list elements starting @ the front
            {
                moveNext(tempU); // find the correct position
            }
            insertBefore(tempU, v); // Add the edge to U's Adjacency list in the correct position
        }
        else // v > than back element of U's Adjacency list
        {
            append(tempU, v);
        }
        G->size++; // # of edges increase by one
    }
    else if(length(tempU) == 0 && length(tempV) > 0) // Ajacency list of U is empty, but the adjacency list of V is not
    {
        append(tempU, v);
        moveFront(tempV);
        
        if(u < back(tempV)) // if u < than back element of V's Adjacency list
        {
            while(u > get(tempV)) // u > than list elements starting @ the front
            {
                moveNext(tempV); // find the correct position
            }
            insertBefore(tempV, u); // Add the edge to V's Adjacency list in the correct position
        }
        else // u > than back element of V's Adjacency list
        {
            append(tempV, u);
        }
        G->size++;
    }
    
}

// Inserts a new directed edge from u to v, i.e. v is added to the adjacency List of u
// (but not u to the adjacency List of v).
// Precondition that their two int arguments must lie in the range 1 to getOrder(G)
void addArc(Graph G, int u, int v)
{
   if(G == NULL)
   {
       printf("Error: calling addArc() on NULL Graph reference\n");
       exit(1);
   }
   if( u < 1 || u > getOrder(G))
   {
       printf("Error: calling addEdge() and the Preconditions are not met\n");
       exit(1);
   }
   else if(v < 1 || v > getOrder(G))
   {
       printf("Error: calling addEdge() and the Preconditions are not met\n");
       exit(1);
   }
   else
   {
       List tempU = G->neighbors[u]; // Adajency list of U
       moveFront(tempU);
       //moveBack(tempU);
       
       if(length(tempU) > 0) // list is not empty
       {
           if(v < back(tempU)) // if v < than back element of U's Adjacency list
           {
               while(v > get(tempU)) // v > than list elements starting @ the front
               {
                   moveNext(tempU);
               }
               insertBefore(tempU, v);
               G->size++;
           }
           else // v > than back element of U's Adjacency list
           {
               append(tempU, v);
               G->size++;
           }
       }
       else // List is empty
       {
           append(tempU, v);
           G->size++;
       }
   }
}

// Runs the BFS algorithm on the Graph G with source s,
// setting the color, distance, parent, and source fields of G accordingly
void BFS(Graph G, int s)
{
    if(G == NULL)
        {
            printf("Error: calling BFS() on NULL Graph reference\n");
            exit(1);
        }
    //x != s &&
    for(int x = 1; x <= getOrder(G); x++) // for every vertex that is not the source
    {
        G->color[x] = WHITE;
        G->distance[x] = INF;
        G->parent[x] = NIL;
    }
    G->source = s;
    G->color[s] = GRAY; // discover the source s
    G->distance[s] = 0;
    G->parent[s] = NIL;
    List queueL = newList();  // new empty list that has queue functionality
    
    append(queueL, s); // add the source
    
    for(; length(queueL) != 0;)  // while the queue is not empty
    {
        int x = front(queueL); // Delete the front & store it into x
        deleteFront(queueL);
        
        List sourceList = G->neighbors[x]; // access the Adjacency list of the source
        moveFront(sourceList);
        
        for(; index(sourceList) != -1; ) // Iterate through the list
        {
            int y = get(sourceList); // for every value in the Adjacency list
            if(G->color[y] == WHITE) // y is undiscovered
            {
                G->color[y] = GRAY;  // discover y
                G->distance[y] = G->distance[x] + 1;
                G->parent[y] = x;
                append(queueL, y); // Add the discovered vertex to the queue
            }
            moveNext(sourceList); // Move to the next element of the Adjacency list of the source
        }
        G->color[x] = BLACK;
    }
    freeList(&queueL);  // free Heap memory
    
}

// Runs the DFS algorithm on the Graph G
// Precondition: length(S) == getOrder(G)
void DFS(Graph G, List S)
{
    if(G == NULL)
    {
        printf("Error: calling DFS() on NULL Graph reference\n");
        exit(1);
    }
    if(S == NULL)
    {
        printf("Error: calling DFS() on NULL List reference\n");
        exit(1);
    }
    if(length(S) != getOrder(G))
    {
        printf("Error: length(S) != getOrder(G) on DFS(), Precondition not met\n");
        exit(1);
    }
    if(length(S) == getOrder(G))
    {
        for(int i = 1; i <= getOrder(G); i++)
        {
            G->color[i] = WHITE;
            G->parent[i] = NIL;
        }
        int time = 0;
        moveFront(S);
        while(index(S) >= 0) // index is defined
        {
            int k = get(S);
            if(G->color[k] == WHITE) //unvisited
            {
                visit(G, S, k, &time);
            }
            moveNext(S);
        } // All vertices have been discovered
        for(int j = 0; j < getOrder(G); j++)
        {
            deleteBack(S); // delete the elements from the list
        }
    }
    
}

// Helper function for the DFS algorithm
void visit(Graph G, List S, int u, int *time)
{
    if(G == NULL)
       {
           printf("Error: calling visit() on NULL Graph reference\n");
           exit(1);
       }
    if(S == NULL)
       {
           printf("Error: calling visit() on NULL List reference\n");
           exit(1);
       }
    G->discover[u] = ++(*time);  // discover u
    G->color[u] = GRAY;
    moveFront(G->neighbors[u]); // move the cursor to the front for the Adajacency list
    while(index(G->neighbors[u]) >= 0) // crusor is defined
    {
        int y = get(G->neighbors[u]); //get every vertex from the adjacency list
        if(G->color[y] == WHITE)
        {
            G->parent[y] = u;
            visit(G, S, y, time); //Recursive call
        }
        moveNext(G->neighbors[u]); // move the cursor
    }
    G->color[u] = BLACK;
    G->finish[u] = ++(*time);      // finish u
    prepend(S, u); // add vertex to the list 
}

// Other Functions --------------------------------------------------------------

// prints the adjacency list representation of G to the file pointed to by out.
// The format of this representation should match the Handout examples,
// so all that is required by the client is a single call to printGraph().
void printGraph(FILE* out, Graph G)
{
    if(G == NULL)
       {
           printf("Error: calling printGraph() on NULL Graph reference\n");
           exit(1);
       }
    else if(out == NULL)
       {
           printf("Error: calling printGraph() on a NULL output file\n");
           exit(1);
       }
    for(int i = 1; i <= getOrder(G); i++)
    {
        List tempList = G->neighbors[i]; // Access each List in the Adjacency list
        fprintf(out, "%d:", i);
        moveFront(tempList);
        while(index(tempList) >= 0 )
        {
            fprintf(out, " %d", get(tempList)); // write vertices from Adjacency list to the output file
            moveNext(tempList);
        }
        fprintf(out, "\n");
    }
}
