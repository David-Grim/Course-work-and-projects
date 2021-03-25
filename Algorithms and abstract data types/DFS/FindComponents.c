//FindComponents.c
//David Grim
//dgrim

#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"
#include "List.h"

int main(int argc, char** argv) {
    FILE* in;
    FILE* out;
    int n = 0;
    int u = 0;
    int v = 0;
	int comp = 0;//components
	int x = 1;
	int temp = 0;
	int temp2 = 0;
    List L = newList();
	Graph GT = NULL;//graph transpose
	List* LC = NULL; //list of strongly connected components
	

    if (argc != 3) {
		exit(0);
	}

	in = fopen(argv[1], "r");
	out = fopen(argv[2], "w");

	if (in == NULL) {
		printf("ERROR: INPUT FILE NOT FOUND");
		exit(0);
	}
	if (out == NULL) {
		printf("ERROR: OUTPUT FILE NOT FOUND");
		exit(1);
	}
  
    fscanf(in, "%i", &n);//read number of vertices
    Graph G = newGraph(n);
	
	for(int i = 1; i < n + 1; i++){//create list of vertices
		append(L,i);
	}
	
	while (fscanf(in, "%i %i", &u, &v) == 2 && v != 0 && u!=0){//add the appropriate edges
        addArc(G,u,v);
    }
	fprintf(out,"%s", "Adjacency list representation of G: \n");
	printGraph(out,G);
	fprintf(out,"%c", '\n');
	
	
	//following algorithm from lecture for finding strongly connected components
	DFS(G,L);
	GT = transpose(G);
	DFS(GT,L);
	
	for(int i = 1; i < getOrder(GT) + 1; i++){//get the number of strongly connected components
		if(getParent(GT, i) == nil){
			comp++;
		}		
	}
	
	fprintf(out, "%s", "G contains ");
	fprintf(out, "%i", comp);
	fprintf(out, "%s"," strongly connected components:\n");
	
	LC = malloc(sizeof(List)*(comp+1));
	for(int i = 1; i < comp + 1; i++){
		LC[i] = newList();
	}
	
	temp = front(L);
	for(int i = 1; i < n; i++){
		temp2 = back(L);
		deleteBack(L);
		prepend(LC[x], temp2);
		if(getParent(GT, temp2) == nil)
			x++;
	}
	prepend(LC[x], temp);
	
	for(int i = 1; i < comp + 1; i++){
		fprintf(out, "%s", "Component ");
		fprintf(out, "%i", i);
		fprintf(out,"%c", ':');
		printList(out, LC[i]);
		fprintf(out,"%c", '\n');
	}
	
	fclose(in);
	fclose(out);
	freeGraph(&G);
	freeList(&L);
	
	
	return 0;
}