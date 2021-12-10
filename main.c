#include<stdio.h>
#include<stdlib.h>
#include"maze.h"
#include"graph.h"
#include"dfs.h"

int main(int argc, char** argv) {
	int seed = (argc > 2) ? atoi(argv[2]) : 0;
	/* maze_t* maze = maze_create_from_file(argc > 1 ? argv[1] : ""); */
	/* if(maze == NULL) { */
		/* fprintf(stderr, "file not exist\n"); */
		/* exit(EXIT_FAILURE); */
	/* } */

	maze_t* maze = maze_create(8, 8, 1);
	/* maze_print(maze); */

	/* graph_t* G = maze_create_graph(maze, seed); */
	/* graph_print(G); */

	/* double ans = dfs(G, 0, maze->height * maze->width - 1); */
	/* printf("%lf\n", ans); */
}
