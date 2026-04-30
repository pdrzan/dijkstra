/**
 * @file dijkstra.c
 * @brief Implementation of Dijkstra's algorithm for shortest paths.
 * @author Pedro Zanelato (https://www.github.com/pdrzan)
 */

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dijkstra.h"

/**
 * @brief Copies an array of integers from a source to a target destination.
 *
 * @param source Pointer to the source array.
 * @param target Pointer to the destination array.
 * @param length The number of elements to copy.
 *
 * @return void
 */
void copy(int *source, int *target, int length)
{
  for (int index = 0; index < length; index++) {
    target[index] = source[index];
  }
}

/**
 * @brief Finds the unvisited vertex with the minimum distance value.
 *
 * This is a helper function for the Dijkstra algorithm to select the next 
 * node to process (greedy approach).
 *
 * @param number_of_vertices Total number of vertices in the graph.
 * @param distance Array containing the current shortest distances from the source.
 * @param visited Boolean array tracking which vertices have been processed.
 *
 * @return int The index of the closest unvisited vertex.
 */
int closest(int number_of_vertices, int *distance, bool *visited)
{
  int min = INT_MAX, min_index;

  for (int vertex = 0; vertex < number_of_vertices; vertex++) {
    if (!visited[vertex] && distance[vertex] <= min) {
      min = distance[vertex];
      min_index = vertex;
    }
  }

  return min_index;
}

/**
 * @brief Computes the shortest paths from a starting vertex to all other vertices.
 *
 * Uses Dijkstra's algorithm to calculate both the minimum distances and the 
 * actual paths (sequences of vertices).
 *
 * @param number_of_vertices The total number of nodes in the graph.
 * @param initial_vertex The index of the source vertex.
 * @param distance_matrix A 2D adjacency matrix representing edge weights.
 *
 * @return ShortestPaths A structure containing distance arrays and dynamic path arrays.
 *
 * @note This function performs multiple dynamic memory allocations (malloc).
 * The caller is responsible for freeing:
 * 1. Every individual array inside shortestPaths.paths
 * 2. The shortestPaths.paths pointer itself
 * 3. shortestPaths.distance and shortestPaths.path_lengths pointers
 *
 * @warning If initial_vertex is not correctly handled, the first iteration 
 * may attempt to copy from an uninitialized predecessor.
 */
ShortestPaths dijkstra(int number_of_vertices, int initial_vertex, int **distance_matrix)
{
  bool *visited = malloc(sizeof(bool) * number_of_vertices);
  int *predecessors = calloc(number_of_vertices, sizeof(int));

  ShortestPaths shortestPaths;

  shortestPaths.distance = malloc(sizeof(int) * number_of_vertices);
  shortestPaths.paths = malloc(sizeof(int*) * number_of_vertices);
  shortestPaths.path_lengths = calloc(number_of_vertices, sizeof(int));

  for (int vertex = 0; vertex < number_of_vertices; vertex++) {
    shortestPaths.distance[vertex] = INT_MAX;
    visited[vertex] = false;
  }

  shortestPaths.distance[initial_vertex] = 0;

  for (int count = 0; count < number_of_vertices; count++) {
    int closest_vertex = closest(number_of_vertices, shortestPaths.distance, visited);
    int predecessor = predecessors[closest_vertex];
    int path_length = shortestPaths.path_lengths[predecessor] + 1;

    shortestPaths.paths[closest_vertex] = malloc(sizeof(int) * path_length);
    copy(shortestPaths.paths[predecessor], shortestPaths.paths[closest_vertex], path_length - 1);
    shortestPaths.paths[closest_vertex][path_length - 1] = closest_vertex;
    shortestPaths.path_lengths[closest_vertex] = path_length;

    visited[closest_vertex] = true;

    for (int vertex = 0; vertex < number_of_vertices; vertex++) {
      if (
        !visited[vertex]
        && distance_matrix[closest_vertex][vertex]
        && shortestPaths.distance[closest_vertex] + distance_matrix[closest_vertex][vertex] < shortestPaths.distance[vertex]
      ) {
        shortestPaths.distance[vertex] = shortestPaths.distance[closest_vertex] + distance_matrix[closest_vertex][vertex];
        predecessors[vertex] = closest_vertex;
      }
    }
  }

  free(visited);
  free(predecessors);

  return shortestPaths;
}
