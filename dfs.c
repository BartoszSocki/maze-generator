#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"graph.h"

void helper(graph_t* G, size_t node_beg, size_t node_end, double curr_value, double* min_value, bool* visited, size_t* curr_path, size_t path_length, size_t* min_path, size_t* min_path_length) {
	int i, node_next;

	if(curr_value > *min_value)
		return;

	/* jeżeli jesteśmy w na końcu to */
	if(node_beg == node_end) {
		/* jeżeli suma węzłów na obecnej ścieżce jest mniejsza od obecnego minimum */
		if(*min_value > curr_value) {
			/* zapisujemy wartości */
			*min_value = curr_value;
			*min_path_length = path_length;
			for(i = 0; i < path_length; i++) {
				min_path[i] = curr_path[i];
			}
		}
		return;
	}

	/* dla każdego sąsiada */
	for(node_next = 0; node_next < G->N; node_next++) {
		if((G->edge_exists[node_beg][node_next] == true) && (visited[node_next] == false)) {
			visited[node_next] = true;
			curr_path[path_length] = node_next;
			helper(G, node_next, node_end, curr_value + G->E[node_beg][node_next], min_value, visited, curr_path, path_length + 1, min_path, min_path_length);
			visited[node_next] = false;
		}
	}
}

double dfs(graph_t* G, size_t node_beg, size_t node_end, size_t* min_path, size_t* min_path_length) {
	/* zmienne pomocnicze */
	bool* visited = calloc(sizeof(*visited), G->N);
	double min_value = G->N * 10.0 + 1.0;
	size_t* curr_path = malloc(sizeof(*curr_path) * G->N);
	int i;

	helper(G, node_beg, node_end, 0.0, &min_value, visited, curr_path, 0, min_path, min_path_length);

	return min_value;
}
