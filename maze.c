#include<stdio.h>
#include<stdlib.h>
#include"maze.h"
#include"graph.h"

double rand10() {
	return rand() / (RAND_MAX / 10.0);
}

maze_t* maze_create_from_file(char* filename) {
	int i, j;
	FILE* in = fopen(filename, "r");
	if(in == NULL)
		return NULL;

	size_t height, width;
	fscanf(in, "%zd", &height);
	fscanf(in, "%zd", &width);

	maze_t* maze = malloc(sizeof(*maze));
	maze->height = height;
	maze->width = width;

	maze->maze = malloc(sizeof(*maze->maze) * maze->height);

	for(i = 0; i < maze->height; i++) {
		maze->maze[i] = malloc(sizeof(**maze->maze) * maze->width);
		for(j = 0; j < maze->width; j++) {
			fscanf(in, "%d", &(maze->maze[i][j]));
		}
	}
	fclose(in);
	return maze;
}

graph_t* maze_create_graph(maze_t* maze, int seed) {
	int i, j;
	short cell;
	graph_t* G = graph_create(maze->height * maze->width);

	srand(seed);
	for(i = 0; i < maze->height; i++) {
		for(j = 0; j < maze->width; j++) {
			cell = maze->maze[i][j];
			if((cell & N) == 0) {
				int from = i * maze->width + j;
				int to   = (i - 1) * maze->width + j;
				graph_add_edge(G, from, to, rand10());
			}

			if((cell & S) == 0) {
				int from = i * maze->width + j;
				int to   = (i + 1) * maze->width + j;
				graph_add_edge(G, from, to, rand10());
			}

			if((cell & E) == 0) {
				int from = i * maze->width + j;
				int to   = i * maze->width + j + 1;
				graph_add_edge(G, from, to, rand10());
			}
			
			if((cell & W) == 0) {
				int from = i * maze->width + j;
				int to   = i * maze->width + j - 1;
				graph_add_edge(G, from, to, rand10());
			}
		}
	}
	return G;
}
