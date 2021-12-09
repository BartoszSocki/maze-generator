#include<stdio.h>
#include<stdlib.h>
#include"maze.h"

maze_t* maze_create_from_file(char* filename) {
	int i, j;
	FILE* in = fopen(filename, "r");
	if(in == NULL)
		return NULL;

	size_t height, width;
	fscanf(in, "%zd", &height);
	fscanf(in, "%zd", &width);
	/* printf("%zu %zu\n", height, width); */

	maze_t* maze = malloc(sizeof(*maze));
	maze->height = height;
	maze->width = width;

	maze->maze = malloc(sizeof(*maze->maze) * maze->height);

	for(i = 0; i < maze->height; i++) {
		maze->maze[i] = malloc(sizeof(**maze->maze) * maze->width);
	}

	for(i = 0; i < maze->height; i++) {
		for(j = 0; j < maze->width; j++) {
			fscanf(in, "%hd", &(maze->maze[i][j]));
		}
	}

	for(i = 0; i < maze->height; i++) {
		for(j = 0; j < maze->width; j++) {
			printf("%d ", maze->maze[i][j]);
		}
		printf("\n");
	}

	fclose(in);
}

