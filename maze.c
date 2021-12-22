#include<stdio.h>
#include<stdlib.h>
#include<wchar.h>
#include<locale.h>
#include"maze.h"
#include"graph.h"

/* wszystkie ściany zamnkięte */
#define BLANK 15

double rand10() {
	return rand() / (RAND_MAX / 10.0);
}

wchar_t get_wall(maze_t* maze, int i, int j) {
	static const wchar_t walls[] = {L' ', L'┃', L'━', L'┗', L'┃', L'┃', L'┏', L'┣', L'━', L'┛', L'━', L'┻', L'┓', L'┫', L'┳', L'╋'};
	char wall = 0;

	char left_up    = (i > 0 && j > 0) ? maze->maze[i - 1][j - 1] : 0;
	char right_up   = (i > 0 && j < maze->width) ? maze->maze[i - 1][j] : 0;
	char left_down  = (i < maze->height && j > 0) ? maze->maze[i][j - 1] : 0;
	char right_down = (i < maze->height && j < maze->width) ? maze->maze[i][j] : 0;

	/* naprawde chcialbym tego nigdy nie napisac */
	wall |= ((left_up & S) != 0) ? W : 0;
	wall |= ((left_up & E) != 0) ? N : 0;

	wall |= ((right_up & W) != 0) ? N : 0;
	wall |= ((right_up & S) != 0) ? E : 0;

	wall |= ((left_down & E) != 0) ? S : 0;
	wall |= ((left_down & N) != 0) ? W : 0;

	wall |= ((right_down & N) != 0) ? E : 0;
	wall |= ((right_down & W) != 0) ? S : 0;

	return walls[wall];
}

void maze_create_graphical_reprezentation(maze_t* maze) {
	int i, j;
	short cell;
	wchar_t** to_print = malloc(sizeof(*to_print) * (maze->height * 2 + 1));
	for(i = 0; i < maze->height * 2 + 1; i++) {
		to_print[i] = malloc(sizeof(**to_print) * (maze->width * 2 + 1));
		for(j = 0; j < maze->width * 2 + 1; j++) {
			to_print[i][j] = L' ';
			if(i % 2 == 0 && j % 2 == 0)
				to_print[i][j] = get_wall(maze, i / 2, j / 2);
		}
	}

	for(i = 0; i < maze->height; i++) {
		for(j = 0; j < maze->width; j++) {
			cell = maze->maze[i][j];
			to_print[i * 2 + 1 - 1][j * 2 + 1] = ((cell & N) != 0) ? L'━' : L' ';
			to_print[i * 2 + 1 + 1][j * 2 + 1] = ((cell & S) != 0) ? L'━' : L' ';
			to_print[i * 2 + 1][j * 2 + 1 + 1] = ((cell & E) != 0) ? L'┃' : L' ';
			to_print[i * 2 + 1][j * 2 + 1 - 1] = ((cell & W) != 0) ? L'┃' : L' ';
		}
	}
	maze->to_print = to_print;
}

void maze_print(maze_t* maze) {
	int i, j;
	/* jeżeli graficzna reprezentacja labiryntu jeszcze nie istnieje */
	if(maze->to_print == NULL) {
		maze_create_graphical_reprezentation(maze);
	}

	setlocale(LC_CTYPE, "UTF-8");
	for(i = 0; i < maze->height * 2 + 1; i++) {
		for(j = 0; j < maze->width * 2 + 1; j++) {
			putwchar(maze->to_print[i][j]);
		}
		putchar('\n');
	}
}

graph_t* maze_create_graph(maze_t* maze, int seed) {
	int i, j, from, to;
	short cell;
	graph_t* G = graph_create(maze->height * maze->width);

	/* dla wag */
	srand(seed);
	for(i = 0; i < maze->height; i++) {
		for(j = 0; j < maze->width; j++) {
			cell = maze->maze[i][j];
			from = i * maze->width + j;
			/* jeżeli ściana północna jest otwarta */
			if((cell & N) == 0) {
				/* oblicz numer węzłu sąsiada */
				to = (i - 1) * maze->width + j;
				graph_add_edge(G, from, to, rand10());
			}

			if((cell & S) == 0) {
				to = (i + 1) * maze->width + j;
				graph_add_edge(G, from, to, rand10());
			}

			if((cell & E) == 0) {
				to = i * maze->width + j + 1;
				graph_add_edge(G, from, to, rand10());
			}
			
			if((cell & W) == 0) {
				to = i * maze->width + j - 1;
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

void maze_remove_random_walls(maze_t* maze, int amount, int seed) {
	if(maze->height < 3 || maze->width < 3) return;
	int i;
	static const dir_t dirs[] = {N, E, S, W};
	static const int di[] = {-1, 0, 0, 1, 0, 0, 0, 0};
	static const int dj[] = {0, 1, 0, 0, 0, 0, 0, -1};

	srand(seed);
	for(i = 0; i < amount; i++) {
		dir_t dir = dirs[rand() % 4];
		int ci = 1 + rand() % (maze->height - 2);
		int cj = 1 + rand() % (maze->width - 2);
		int ni = ci + di[dir - 1];
		int nj = cj + dj[dir - 1];

		/* nie można użyć xora, bo zamykalibyśmy otwarte */ 
		maze->maze[ci][cj] &= ~dir;
		maze->maze[ni][nj] &= ~opposite(dir);
	}
}

maze_t* maze_create(size_t height, size_t width, int seed) {
	int i, j;
	/* stwórz miejsce i zapisz wartości w labiryncie */
	maze_t* maze = malloc(sizeof(*maze));
	maze->height = height;
	maze->width = width;
	/* dopiero przy pierwszym wywołaniu maze_print ta wartość jest inicjalizowana */
	maze->to_print = NULL;

	maze->maze = malloc(sizeof(*maze->maze) * maze->height);

	for(i = 0; i < maze->height; i++) {
		maze->maze[i] = malloc(sizeof(**maze->maze) * maze->width);
		for(j = 0; j < maze->width; j++) {
			maze->maze[i][j] = BLANK;
		}
	}

	srand(seed);
	maze_backtracker(maze, 0, 0);
	/* dla 10% komórek ta funkcja zostanie wywołana, nie oznacza to jednak że zniknie 10% ścian */
	maze_remove_random_walls(maze, (int)(height * width / 10.0), seed);
	return maze;
}
