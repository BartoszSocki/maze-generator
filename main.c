#include<stdio.h>
#include<stdlib.h>
#include"maze.h"
#include"graph.h"
#include"dfs.h"

int main(int argc, char** argv) {
	int i;
	int height = (argc > 1) ? atoi(argv[1]) : 5;
	int width = (argc > 2) ? atoi(argv[2]) : 5;
	int seed = (argc > 3) ? atoi(argv[3]) : 0;

	if(height <= 1 || width <= 1) {
		fprintf(stderr, "invalid size of the maze, maze should be at least 2x2\n");
		exit(EXIT_FAILURE);
	}

	maze_t* maze = maze_create(height, width, seed);

	printf("maze before:\n");

	maze_print(maze);

	graph_t* G = maze_create_graph(maze, seed);

	size_t* min_path = malloc(sizeof(*min_path) * G->N);
	size_t min_path_length = 0;

	double ans = dfs(G, 0, maze->height * maze->width - 1, min_path, &min_path_length);

	printf("length of the shortest path:\n%lf\n", ans);

	/* zaznaczenie drogi */
	printf("path: \n");
	printf("[0,0]");
	for(i = 0; i < min_path_length; i++) {
		int x = 2 * (min_path[i] / maze->width) + 1;
		int y = 2 * (min_path[i] % maze->width) + 1;
		printf(" -> [%d, %d]", min_path[i] / maze->width, min_path[i] % maze->width);
		maze->to_print[x][y] = '@';
	}
	printf("\n");

	/* oznaczenie komórki końcowej i początkowej */
	maze->to_print[1][1] = 'S';
	maze->to_print[2 * maze->height - 1][2 * maze->width - 1] = 'E';

	printf("maze after:\n");
	maze_print(maze);
}
