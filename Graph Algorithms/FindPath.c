/*
Intro to Data Structures & Algorithms
Date: January 20, 2021
Name: Pablo Zepeda
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h> // Prints diagnostics message if program assumptions are false
#include "List.h"
#include "Graph.h"

void closeFile(Graph G, FILE* in, FILE* out); //func prototype

void printOutput(Graph G, FILE* in, FILE* out, int src, int dest)
{
    // Print out the distance from the Source vertex and the Destination vertex
    // Print out the shortest path
    
    for(; fgetc(in) != -1;)     // gets the next char from input file
    {
        fscanf(in, "%d", &src); // reads integer input from file & stores it into src
        fscanf(in, "%d", &dest);
        
        List tempList = newList(); // Used for getPath(), will contain the vertices of the shortest path
        
        if(src == 0)
        {
            if(dest == 0)
            {
                break;  // dummy line detected, it's the end of the 1st part of the input file or the end of the 2nd part of the input file
            }
            else
            {
                continue;
            }
        }
        else
        {
            BFS(G, src); // Sets the color, distance, parent, and source fields of G & G is ready for getPath()
            if(getDist(G, dest) != INF) // the shortest path is defined
            {
                getPath(tempList, G, dest); // vertices of the shortest path from src to dest are appended to tempList
                
                fprintf(out, "The distance from %d to %d is %d\n", src, dest, (getDist(G, dest))); // Print out the source, destination & the distance
                fprintf(out, "A shortest %d-%d path is: ", src, dest);
                printList(out, tempList);  // print out the vertices of the shortest path
                fprintf(out, "\n");
                fprintf(out, "\n");
            }
            if(getDist(G, dest) == INF) // the shortest path is NOT defined
            {
                getPath(tempList, G, dest); // vertices of the shortest path from src to dest are appended to tempList
                
                fprintf(out, "The distance from %d to %d is infinity\n", src, dest);
                fprintf(out, "No %d-%d path exists\n", src, dest);
                fprintf(out, "\n");
                fprintf(out, "\n");
                
            }
            
        }
        freeList(&tempList); // free Heap memory allocated by the List
    }
    
    closeFile(G, in, out); // close file
}

int main(int argc, char* argv[])
{
    FILE* in = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");
    
    int size = 0;  // number of vertices
    int tempSrc = 0;
    int tempDest = 0;
    int src = 0;
    int dest = 0;
    
    if(argc != 3) // There aren't 3 arguments in the command line
    {
        printf("Error: Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    if(out == NULL || in == NULL)
    {
        printf("File Error: cannot read or write file %s\n", argv[1]);
        exit(1);
    }
    
    fscanf(in, "%d", &size); // store the # of vertices of the graph from the file
    Graph G = newGraph(size);// Create a new Graph with "size" vertices
    
    for(; fgetc(in) != -1;) // gets the next char from input file
    {
        fscanf(in, "%d", &tempSrc);  // reads integer input from file & stores it into tempSrc
        fscanf(in, "%d", &tempDest); // stores destination from file
        
        if(tempSrc != 0)
        {
            if(tempDest != 0)
            {
                addEdge(G, tempSrc, tempDest); // Build the edges of the given Graph
            }
        }
        else
        {
            break; // dummy line detected, it's the end of the 1st part of the input file or the end of the 2nd part of the input file
        }
    }
    printGraph(out, G); // prints the adjacency list representation of G to the file pointed to by out.
    fprintf(out, "\n");
    printOutput(G, in, out, src, dest); // Print out the distance from the Source vertex and the Destination vertex
                                        // Print out the shortest path
    return 0;
}

void closeFile(Graph G, FILE* in, FILE* out)
{
    freeGraph(&G); // free Heap memory allocated by the Graph ADT
    fclose(in);  // Close input & output files
    fclose(out);
    
}
