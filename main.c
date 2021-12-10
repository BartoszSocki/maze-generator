#include<stdio.h>
#include<stdlib.h>
#include"maze.h"
#include"graph.h"
#include"dfs.h"

int main(int argc, char** argv) {
	int seed = (argc > 1) ? atoi(argv[1]) : 0;
	/* int seed = 12; */
	maze_t* maze = maze_create_from_file("data");
	graph_t* G = maze_create_graph(maze, seed);
	graph_print(G);

	double ans = dfs(G, 0, maze->height * maze->width - 1);
	printf("%lf\n", ans);
}
