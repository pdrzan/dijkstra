# Dijkstra's Shortest Path in C

An efficient implementation of Dijkstra’s Algorithm in C that calculates both the minimum distance and the complete vertex-by-vertex path from a source node to all other nodes in a weighted graph. In this implementation, the paths to every vertex is recorded and returned by the `dijkstra` function, along with their cost and length.

## Usage

You can simply add `dijkstra.c` and `dijkstra.h` files to your project and use the `dijkstra` function. Example:

> [!WARNING]
> The caller is responsible for freeing the memory returned by the dijkstra function.

## Example

```c
#include <stdio.h>
#include <stdlib.h>

#include "dijkstra.c"

int main() {
    int number_of_vertices = 3;

    int **matrix = malloc(sizeof(int*) * number_of_vertices);
    for (int index = 0; index < number_of_vertices; index++) {
      matrix[index] = calloc(number_of_vertices, sizeof(int));
    }

    matrix[0][1] = 5;
    matrix[1][2] = 10;

    ShortestPaths results = dijkstra(number_of_vertices, 0, matrix);

    printf("Distance to vertex 2: %d\n", results.distance[2]);
    printf("Path: ");
    for(int index = 0; index < results.path_lengths[2]; index++) {
      printf("%d ", results.paths[2][index]);
    }
    printf("\n");

    for(int index = 0; index < number_of_vertices; index++) {
        free(results.paths[index]);
        free(matrix[index]);
    }

    free(results.paths);
    free(results.distance);
    free(results.path_lengths);
    free(matrix);

    return 0;
}
```
