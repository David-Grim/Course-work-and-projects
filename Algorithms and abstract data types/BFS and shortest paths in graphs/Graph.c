#include<stdio.h>
#include<stdlib.h>
#include "List.h"
#include "Graph.h"

#define nil 0
#define inf -1
#define gray 1
#define black 2
#define white 0
#define NIL 0
#define INF -1
#define UNDEF -1


typedef struct GraphObj {
	List* adj;
	int* color;
	int* parent;
	int* dist;
	int order;
	int size;
	int source;


}GraphObj;

/*** Constructors-Destructors ***/
Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->adj = malloc(sizeof(List) * (n+1));
	G->color = malloc(sizeof(int) * (n+1));
	G->parent = malloc(sizeof(int) * (n+1));
	G->dist = malloc(sizeof(int) * (n+1));
	G->order = n;
	G->size = 0;
	G->source = nil;

	for (int i = 0; i < (n+1); i++) {
		G->color[i] = white;
		G->parent[i] = nil;
		G->dist[i] = inf;
		G->adj[i] = newList();

	}
	return G;
}
void freeGraph(Graph* pG) {
	for (int i = 0; i < (*pG)->order; i++) {
		freeList(&(*pG)->adj[i]);
	}
	free((*pG)->color);
	free((*pG)->adj);
	free((*pG)->dist);
	free((*pG)->parent);
	free(*pG);

}
/*** Access functions ***/
int getOrder(Graph G) {
	if (G == NULL) {
		printf("ERROR: function getOrder was called on a graph that was null");
		exit(0);
	}
	return G->order;
}
int getSize(Graph G) {
	if (G == NULL) {
		printf("ERROR: function getSize was called on a graph that was null");
		exit(0);
	}
	return G->size;
}
int getSource(Graph G) {
	if (G == NULL) {
		printf("ERROR: function getSource was called on a graph that was null");
		exit(0);
	}
	return G->source;
}
int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("ERROR: function getParent was called on a graph that was null");
		exit(0);
	}
	if (u > G->order || u < 1)
		exit(1);
	return G->parent[u];
}
int getDist(Graph G, int u) {
	if (G == NULL) {
		printf("ERROR: function getDist was called on a graph that was null");
		exit(0);
	}
	if (u > G->order || u < 1)
		exit(1);
	if (G->source == nil)
		return inf;
	else
		return G->dist[u];
}
//Based upon printPath function from textbook
void getPath(List L, Graph G, int u) {
	if (G->source == nil) {
		printf("getPath was called on a nil source");
		exit(0);
	}
	if (u > G->order || u < 1) {
		printf("invalid u in getPath");
		exit(1);
	}
	if(u == G->source){
        append(L,G->source);
	}
	else if(G->parent[u] == nil){
        append(L,nil);
	}
	else{
        getPath(L,G,G->parent[u]);
        append(L,u);
	}
}
/*** Manipulation procedures ***/
void makeNull(Graph G) {
	G->size = 0;
	G->source = nil;
	for (int i = 0; i < G->order; i++) {
		G->color[i] = white;
		G->dist[i] = nil;
		G->parent[i] = inf;
		clear(G->adj[i]);
	}
}
void addEdge(Graph G, int u, int v) {
	if (u > G->order || u < 1) {
		printf("invalid value for u in function addEdge");
		exit(0);
	}
	if (v > G->order || v < 1) {
		printf("invalid value for v in function addEdge");
		exit(1);
	}
	addArc(G, u, v);
	addArc(G, v, u);
	(G->size--);

}
void addArc(Graph G, int u, int v) {
	if (u > G->order || u < 1) {
		printf("invalid value for u in function addArc");
		exit(0);
	}
	if (v > G->order || v < 1) {
		printf("invalid value for v in function addArc");
		exit(1);
	}
	moveFront(G->adj[u]);
	while (index(G->adj[u]) != -1 && v > get(G->adj[u])) {
		moveNext(G->adj[u]);
	}
	if (index(G->adj[u]) == -1) {
		append(G->adj[u], v);
	}
	else {
		insertBefore(G->adj[u], v);
	}
	G->size++;
}
//based upon BFS algorithm provided in textbook
void BFS(Graph G, int s) {
	int u, v;
	List Q = newList();
	G->source = s;
	for (int i = 0; i < (G->order+1); i++) {
		G->color[i] = white;
		G->parent[i] = nil;
		G->dist[i] = inf;
	}
	G->color[s] = gray;
	G->dist[s] = 0;
	G->parent[s] = nil;
	append(Q, s);
	while (length(Q) != 0) {
		u = front(Q);
		deleteFront(Q);
		moveFront(G->adj[u]);
		while (index(G->adj[u]) != -1) {
			v = get(G->adj[u]);
			if (G->color[v] == white) {
				G->color[v] = gray;
				G->parent[v] = u;
				G->dist[v] = G->dist[u] + 1;
				append(Q, v);
			}
			moveNext(G->adj[u]);
		}
		G->color[u] = black;
	}
	freeList(&Q);
}

/*** Other operations ***/
void printGraph(FILE* out, Graph G) {
	for (int i = 1; i < (G->order+1); i++) {
		fprintf(out, "%i:", i);
		printList(out, G->adj[i]);
		fprintf(out, "%c", '\n');

	}
}
