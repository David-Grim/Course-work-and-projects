#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(){

Graph G = newGraph(10);
printf("&i",getSize(G));
addEdge(G,1,2);
addEdge(G,1,3);
addEdge(G,1,4);
printGraph(stdout,G);

system("pause");
return 0;
}
