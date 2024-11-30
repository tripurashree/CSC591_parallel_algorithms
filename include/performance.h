#ifndef PERFORMANCE_H
#define PERFORMANCE_H

#include <vector>
#include "graph.h"

// Function declarations
bool verify_results(const std::vector<int> &serial_result, const std::vector<int> &parallel_result);
void compare_bfs_performance(const std::vector<Node> &node_list, const std::vector<Edge> &edge_list, unsigned int source_node_no);

#endif // PERFORMANCE_H
