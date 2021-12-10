#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"graph.h"

graph_t* graph_create(size_t N) {
	int i, j;
	graph_t* G = malloc(sizeof(graph_t));
	G->N = N;
	G->E = malloc((G->N) * sizeof(*(G->E)));
	G->edge_exists = malloc((G->N) * sizeof(*(G->edge_exists)));

	for(i = 0; i < G->N; i++) {
		G->E[i] = malloc((G->N) * sizeof(**(G->E)));
		G->edge_exists[i] = malloc((G->N) * sizeof(**(G->edge_exists)));
	}

	for(i = 0; i < G->N; i++) {
		for(j = 0; j < G->N; j++) {
			G->edge_exists[i][j] = false;
		}
	}

	return G;
}

bool graph_add_edge(graph_t* G, int from, int to, double weight) {
	if(G->edge_exists[from][to] == false) {
		G->E[from][to] = weight;
		G->edge_exists[from][to] = true;
		return true;
	}
	return false;
}

void graph_free(graph_t** G) {
	int i;
	for(i = 0; i < (*G)->N; i++) {
		free((*G)->E[i]);
		free((*G)->edge_exists[i]);
	}
	free((*G)->E);
	free((*G)->edge_exists);
	(*G) = NULL;
}

void graph_print(graph_t* G) {
	int i, j;
	for(i = 0; i < G->N; i++) {
		for(j = 0; j < G->N; j++) {
			if(G->edge_exists[i][j] == true)
				printf("\033[0;31m");

			printf("%6.1lf ", G->E[i][j]);

			if(G->edge_exists[i][j] == true)
				printf("\033[0m");
		}
		putchar('\n');
	}
}
