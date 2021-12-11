#include<stdio.h>
#include<stdlib.h>
#include"maze.h"
#include"graph.h"
#include"dfs.h"

int main(int argc, char** argv) {
	int i;
	int seed = (argc > 2) ? atoi(argv[2]) : 0;
	/* maze_t* maze = maze_create_from_file(argc > 1 ? argv[1] : ""); */
	/* if(maze == NULL) { */
		/* fprintf(stderr, "file not exist\n"); */
		/* exit(EXIT_FAILURE); */
	/* } */

	maze_t* maze = maze_create(10, 10, 2);
	maze_print(maze);

	graph_t* G = maze_create_graph(maze, seed);

	size_t* min_path = malloc(sizeof(*min_path) * G->N);
	size_t min_path_length = -1;

	double ans = dfs(G, 0, maze->height * maze->width - 1, min_path, &min_path_length);

	printf("%lf\n", ans);
	printf("%d\n", min_path_length);

	/* for(i = 0; i < min_path_length; i++) { */
	/* 	printf("%lu\n", min_path[i]); */
	/* } */
}
