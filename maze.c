#include<stdio.h>
#include<stdlib.h>
#include"maze.h"
#include"graph.h"

#define BLANK 15

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

void maze_print(maze_t* maze) {
	int i, j;
	short cell;
	char** to_print = malloc(sizeof(*to_print) * (maze->height * 2 + 1));
	for(i = 0; i < maze->height * 2 + 1; i++) {
		to_print[i] = malloc(sizeof(**to_print) * (maze->width * 2 + 1));
		for(j = 0; j < maze->width * 2 + 1; j++) {
			to_print[i][j] = ((i % 2 == 0) && (j % 2 == 0)) ? '+' : ' ';
		}
	}

	for(i = 0; i < maze->height; i++) {
		for(j = 0; j < maze->width; j++) {
			cell = maze->maze[i][j];
			to_print[i * 2 + 1 - 1][j * 2 + 1] = ((cell & N) != 0) ? '-' : ' ';
			to_print[i * 2 + 1 + 1][j * 2 + 1] = ((cell & S) != 0) ? '-' : ' ';
			to_print[i * 2 + 1][j * 2 + 1 + 1] = ((cell & E) != 0) ? '|' : ' ';
			to_print[i * 2 + 1][j * 2 + 1 - 1] = ((cell & W) != 0) ? '|' : ' ';
		}
	}

	for(i = 0; i < maze->height * 2 + 1; i++) {
		for(j = 0; j < maze->width * 2 + 1; j++) {
			putchar(to_print[i][j]);
		}
		putchar('\n');
	}

	for(i = 0; i < maze->height; i++) {
		for(j = 0; j < maze->width; j++) {
			printf("%2d ", maze->maze[i][j]);
		}
		printf("\n");
	}
	
}

graph_t* maze_create_graph(maze_t* maze, int seed) {
	int i, j, from, to;
	short cell;
	graph_t* G = graph_create(maze->height * maze->width);

	srand(seed);
	for(i = 0; i < maze->height; i++) {
		for(j = 0; j < maze->width; j++) {
			cell = maze->maze[i][j];
			if((cell & N) == 0) {
				from = i * maze->width + j;
				to   = (i - 1) * maze->width + j;
				graph_add_edge(G, from, to, rand10());
			}

			if((cell & S) == 0) {
				from = i * maze->width + j;
				to   = (i + 1) * maze->width + j;
				graph_add_edge(G, from, to, rand10());
			}

			if((cell & E) == 0) {
				from = i * maze->width + j;
				to   = i * maze->width + j + 1;
				graph_add_edge(G, from, to, rand10());
			}
			
			if((cell & W) == 0) {
				from = i * maze->width + j;
				to   = i * maze->width + j - 1;
				graph_add_edge(G, from, to, rand10());
			}
		}
	}
	return G;
}

dir_t opposite(dir_t dir) {
	switch(dir) {
		case N: return S;
		case S: return N;
		case E: return W;
		case W: return E;
	}
}

dir_t* shuffle_dirs() {
	int i, j;
	dir_t temp;
	dir_t* dirs = malloc(sizeof(*dirs) * 4);
	dirs[0] = N;
	dirs[1] = E;
	dirs[2] = S;
	dirs[3] = W;

	for(i = 0; i < 4; i++) {
		j = i + rand() / (RAND_MAX / (4 - i) + 1);
		temp = dirs[j];
		dirs[j] = dirs[i];
		dirs[i] = temp;
	}

	return dirs;
}

void maze_backtracker(maze_t* maze, int ci, int cj) {
	int i;
	static const int di[] = {-1, 0, 0, 1, 0, 0, 0, 0};
	static const int dj[] = {0, 1, 0, 0, 0, 0, 0, -1};
	dir_t* dirs = shuffle_dirs();

	for(i = 0; i < 4; i++) {
		int ni = ci + di[dirs[i] - 1];
		int nj = cj + dj[dirs[i] - 1];
		if((ni >= 0 && ni < maze->height) && (nj >= 0 && nj < maze->width) && (maze->maze[ni][nj] == BLANK)) {
			maze->maze[ci][cj] ^= dirs[i];
			maze->maze[ni][nj] ^= opposite(dirs[i]);
			maze_backtracker(maze, ni, nj);
		}
	}
	free(dirs);
}

maze_t* maze_create(size_t height, size_t width, int seed) {
	int i, j;
	maze_t* maze = malloc(sizeof(*maze));
	maze->height = height;
	maze->width = width;

	maze->maze = malloc(sizeof(*maze->maze) * maze->height);

	for(i = 0; i < maze->height; i++) {
		maze->maze[i] = malloc(sizeof(**maze->maze) * maze->width);
		for(j = 0; j < maze->width; j++) {
			maze->maze[i][j] = BLANK;
		}
	}

	srand(seed);
	maze_backtracker(maze, 0, 0);
	maze_print(maze);
	return maze;
}


