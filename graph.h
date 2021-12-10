#ifndef _GRAPH_H_
#define _GRAPH_H_
#include<stdio.h>
#include<stdbool.h>

/* vertices are numbers from 0..N-1 */
typedef struct graph {
	size_t N;
	double** E;
	bool** edge_exists;

} graph_t;

graph_t* graph_create(size_t N);
bool graph_add_edge(graph_t* G, int from, int to, double weight);
void graph_free(graph_t** G);
void graph_print(graph_t* G);

#endif


