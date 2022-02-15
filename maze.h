#ifndef _MAZE_H_
#define _MAZE_H_
#include<stdio.h>
#include"graph.h"

typedef enum {
	N = 1, E = 2, S = 4, W = 8
} dir_t;

typedef struct {
	size_t height;
	size_t width;

	char** maze;
	wchar_t** to_print;
} maze_t;

void maze_print(maze_t* maze);
maze_t* maze_create(size_t height, size_t width, int seed);
graph_t* maze_create_graph(maze_t* maze, int seed);

#endif
