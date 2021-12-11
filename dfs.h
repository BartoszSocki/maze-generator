#ifndef _DFS_H_
#define _DFS_H_
#include<stdbool.h>
#include"graph.h"

double dfs(graph_t* G, int node_beg, int node_end, size_t* min_path, size_t* min_path_length);

#endif
