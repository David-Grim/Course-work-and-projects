//Graph.c
//David Grim
//dgrim

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
	int* disc;
	int* fin;
	int order;
	int size;
}GraphObj;

Graph newGraph(int n) {
	Graph G = malloc(sizeof(GraphObj));
	G->adj = malloc(sizeof(List) * (n + 1));
	G->color = malloc(sizeof(int) * (n + 1));
	G->parent = malloc(sizeof(int) * (n + 1));
	G->disc = malloc(sizeof(int) * (n + 1));
	G->fin = malloc(sizeof(int) * (n + 1));
	G->order = n;
	G->size = 0;

	for (int i = 0; i < (n + 1); i++) {
		G->color[i] = white;
		G->parent[i] = nil;
		G->disc[i] = inf;
		G->fin[i] = inf;
		G->adj[i] = newList();
	}
	return G;
}

void freeGraph(Graph* pG) {
	for (int i = 0; i < (*pG)->order + 1; i++) {
		freeList(&(*pG)->adj[i]);
	}
	free((*pG)->color);
	free((*pG)->adj);
	free((*pG)->disc);
	free((*pG)->fin);
	free((*pG)->parent);
	free(*pG);

}

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

int getParent(Graph G, int u) {
	if (G == NULL) {
		printf("ERROR: function getParent was called on a graph that was null");
		exit(0);
	}
	if (u > G->order || u < 1)
		exit(1);
	return G->parent[u];
}

int getDiscover(Graph G, int u) {
	if (G == NULL) {
		printf("ERROR: function getDiscover was called on a graph that was null");
		exit(0);
	}
	if (u > G->order || u < 1)
		exit(1);
	return G->disc[u];
}

int getFinish(Graph G, int u) {
	if (G == NULL) {
		printf("ERROR: function getFinish was called on a graph that was null");
		exit(0);
	}
	if (u > G->order || u < 1)
		exit(1);
	return G->fin[u];
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

void DFS(Graph G, List S) {
	int time = 0;//time starts at 0
	moveFront(S);
	for (int i = 1; i < G->order + 1; i++) {//for all x in V(G)
		G->color[i] = white;//color[x] = white
		G->parent[i] = nil;//p[x] = nil
	}
	while (index(S) != -1) { //for all x in V(G)
		if (G->color[get(S)] == white) {//if color[x] == white
			visit(G, get(S), S, &time);//visit(x)
		}
		moveNext(S);
	}
	//need to delete old times from list
	for (int i = (length(S) / 2); i > 0; i--) {
		deleteBack(S);
	}
}

/* Other Functions */
Graph transpose(Graph G) {
	Graph G2 = newGraph(G->order);
	for (int i = 0; i < G->order + 1; i++) {
		moveFront(G->adj[i]);
		while (index(G->adj[i]) != -1) {
			addArc(G2, get(G->adj[i]), i);
			moveNext(G->adj[i]);
		}
	}
	return G2;
}

Graph copyGraph(Graph G) {
	Graph G2 = newGraph(G->order);
	for (int i = 1; i < G->order + 1; i++) {
		moveFront(G->adj[i]);
		while (index(G->adj[i]) != -1) {
			addArc(G2, i, get(G->adj[i]));
			moveNext(G->adj[i]);
		}
	}
	return G2;
}

void printGraph(FILE* out, Graph G) {
	for (int i = 1; i < (G->order + 1); i++) {
		fprintf(out, "%i", i);
		fprintf(out, "%c", ':');
		printList(out, G->adj[i]);
		fprintf(out, "%c", '\n');
	}
}

void visit(Graph G, int x, List L, int* time) {
	int y = 0;// to keep as to the algorithm as possible
	G->disc[x] = ++(*time);//pre increment like in the algorithm
	G->color[x] = gray;//start visit
	moveFront(G->adj[x]);
	while (index(G->adj[x]) != -1) {//for all y in adj[x]
		y = get(G->adj[x]);
		if (G->color[y] == white) {//if color[y] == white
			G->parent[y] = x;//p[y] = x
			visit(G, y, L, time);//visit(y)
		}
		moveNext(G->adj[x]);
	}
	prepend(L, x);
	G->color[x] = black;//finished visit
	G->fin[x] = ++(*time);// store finish time
}
