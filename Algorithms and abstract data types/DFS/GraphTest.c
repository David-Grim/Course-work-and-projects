#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(){

Graph G = newGraph(10);
Graph GT = NULL;
List L = newList();

for(int i = 1; i<=4; i++){
	append(L,i);
}
printList(stdout, L);

printf("&i",getSize(G));
addArc(G,1,2);
addArc(G,1,3);
addArc(G,1,4);
addArc(G,4,3);
addArc(G,4,1);
addArc(G,3,2);
addArc(G,3,4);
addArc(G,2,1);

DFS(G,S);
GT = transpose(G);
DFS(GT,s)

printGraph(stdout,G);


printGraph(stdout,GT);

system("pause");
return 0;
}
