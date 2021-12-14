CC = cc

compile: main.c maze.c maze.h graph.c graph.h dfs.c dfs.h
	$(CC) main.c maze.c graph.c dfs.c
# sol: main.o graph.o maze.o dfs.o
# 	$(CC) -o sol -c main.o graph.o maze.o dfs.o
# main.o: main.c
# 	$(CC) -o main.o -c main.c
# graph.o: graph.h graph.c
# 	$(CC) -o graph.o -c graph.c
# maze.o: maze.h maze.c
# 	$(CC) -o maze.o -c maze.c
# dfs.o: dfs.h dfs.c
# 	$(CC) -o dfs.o -c dfs.c


