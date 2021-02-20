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

int main(int argc, char* argv[])
{
    
    if(argc > 3 || argc < 3)
    {
        printf("Error: Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }
    
    FILE *input;
    FILE *output;
    
    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");
    
    if(input == NULL)
    {
        printf("Error: can't open file %s for reading\n", argv[1]);
        exit(1);
    }
    
    
    if(output == NULL)
       {
           printf("Error: can't open file %s for writing\n", argv[2]);
           exit(1);
       }
    int vertCount;
    fscanf(input, "%d", &vertCount); // read # of vertices for Graph
    Graph G = newGraph(vertCount); // create Graph
    
    int vertOne;
    int vertTwo;
    
    while(1)
    {
        fscanf(input, "%d", &vertOne); // read in vertices
        fscanf(input, "%d", &vertTwo);
        
        if(vertOne == 0 && vertTwo == 0) // End of input file is reached
        {
            break;
        }
        
        addArc(G, vertOne, vertTwo); // create directed edges
    }
    
    fprintf(output, "Adjacency list representation of G:\n");
    printGraph(output, G);
    
    // Build the list for DFS
    List L = newList();
    for(int i = 1; i <= vertCount; i++)
    {
        append(L, i);
    }
    
    // 1st call to DFS
    DFS(G, L);
    
    // Transpose G
    Graph tG = transpose(G);
    
    // Call DFS() on transpose of G
    DFS(tG, L);
    
    int scc = 0;
    moveFront(L);
    
    while(index(L) != -1) // the cursor is defined
    {
        if(getParent(tG, get(L)) == NIL)
        {
            scc++; // # of strongly connected components
        }
        moveNext(L);
    }
    
    fprintf(output, "G contains %d strongly connected components:", scc);
    
    List C = newList();
    moveBack(L);
    
    for(int i = 1; i <= scc; i++)
    {
        fprintf(output, "\nComponent %d: ", i);
        
        while(1)
        {
            prepend(C, get(L));
            
            if(getParent(tG, get(L)) == NIL)
            {
                printList(output, C); // @ NIL parent, so print the SCC
                break;
            }
            
            movePrev(L);
        }
        movePrev(L); // move cursor from NIL parent
        clear(C);
    }
    
    fclose(input);
    fclose(output);
    
    freeList(&L);
    freeList(&C);
    freeGraph(&G);
    freeGraph(&tG);
    
    return 0;
}
