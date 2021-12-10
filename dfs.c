#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"graph.h"

void helper(graph_t* G, size_t node_beg, size_t node_end, double curr_value, double* min_value, bool* visited, size_t curr_path, size_t* path_length, size_t* min_path, size_t* min_path_length) {
	int node_next;
	if(node_beg == node_end) {
		if(*min_value > curr_value) {
			*min_value = curr_value;
			
		}
		return;
	}

	for(node_next = 0; node_next < G->N; node_next++) {
		if((G->edge_exists[node_beg][node_next] == true) && (visited[node_next] == false)) {
			visited[node_next] = true;
			/* curr_path[path_length] = next_node */
			helper(G, node_next, node_end, curr_value + G->E[node_beg][node_next], min_value, visited);
			visited[node_next] = false;
		}
	}
}

double dfs(graph_t* G, size_t node_beg, size_t node_end) {
	bool* visited = calloc(sizeof(*visited), G->N);
	double min_value = G->N * G->N * 10.0;
	double curr_value = 0.0;
	helper(G, node_beg, node_end, curr_value, &min_value, visited);
	return min_value;
}
