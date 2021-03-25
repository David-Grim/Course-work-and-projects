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
    int s = 0;
    int d = 0;
    List L = newList();

    if (argc != 3) {
		exit(1);
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
    //read number of vertices
    fscanf(in, "%i", &n);
    Graph G = newGraph(n);

    //add the edges to those vertices
    while (fscanf(in, "%i %i", &u, &v) == 2 && v != 0 && u!=0){
        addEdge(G,u,v);
    }

     printGraph(out, G);

     while (fscanf(in, "%i %i", &s, &d) && s != 0 && d != 0){
        BFS(G, s);
        getPath(L, G, d);
        if (getDist(G, d) == -1){ //if dist is INF
            fprintf(out, "The distance from %i to %i is infinity \n", s, d);
            fprintf(out, "No %i-%i path exists\n", s, d);
        }
        else{//if dist is not INF
            fprintf(out, "The distance from %i to %i is %i \n", s, d, getDist(G, d));
            fprintf(out, "A shortest %i-%i path is: ", s, d);
            printList(out, L);
            fprintf(out,"%c", '\n');
        }
        clear(L);//clear list for next iteration
    }
    fclose(in);
    fclose(out);
    freeList(&L);
    freeGraph(&G);
    return 0;
}
