/**
 * @struct ShortestPaths
 * @brief Container for Dijkstra algorithm results.
 */
typedef struct ShortestPaths {
  int **paths;
  int *distance;
  int *path_lengths;
} ShortestPaths;
