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
    int n = 10;
    List S = newList();
    Graph G = newGraph(n);
    
    for(int i = 1; i <= n; i++)
    {
        append(S, i);
    }
    
    addArc(G, 1, 3);
    addArc(G, 1, 2);
    addArc(G, 2, 4);
    addArc(G, 2, 5);
    addArc(G, 2, 6);
    addArc(G, 3, 7);
    addArc(G, 3, 8);
    addArc(G, 4, 9);
    addArc(G, 4, 10);
    addArc(G, 5, 2);
    addArc(G, 6, 3);
    addArc(G, 7, 1);

    Graph tG = transpose(G);
    Graph C = copyGraph(G);
    
    fprintf(stdout, "\n");
    fprintf(stdout, "Adjacency list representation of G:\n");
    printGraph(stdout, C);
    
    DFS(G, S);
    fprintf(stdout, "\n");
    
    fprintf(stdout, "call DFS() \n");
    fprintf(stdout, "x: discover finish parent\n");
    for(int i = 1; i <= n; i++)
    {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(G, i), getFinish(G, i), getParent(G, i));
    }
    
    fprintf(stdout, "\n");
    fprintf(stdout, "List S after DFS()\n");
    fprintf(stdout, S);
    fprintf(stdout, "\n");

    fprintf(stdout, "\n");
    fprintf(stdout, "Adjacency List representation of Transpose(G):\n");
    fprintf(stdout, tG);
    fprintf(stdout, "\n");
    
    DFS(tG, S);
    fprintf(stdout, "Second call DFS() \n");
    fprintf(stdout, "x: discover finish parent\n");
    for(int i = 1; i <= n; i++)
    {
        fprintf(stdout, "%d: %2d %2d %2d\n", i, getDiscover(tG, i), getFinish(tG, i), getParent(tG, i));
    }
    
    fprintf(stdout, "\n");
    fprintf(stdout, "List S after Second call DFS()\n");
    fprintf(stdout, S);
    fprintf(stdout, "\n");

    freeList(&S);
    freeGraph(&G);
    freeGraph(&tG);
    freeGraph(&C);
    
    return(0);
}
