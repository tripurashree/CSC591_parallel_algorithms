#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge
{
    unsigned int src;
    unsigned int dest;
};

struct Node
{
    unsigned int start;
    unsigned int edge_num;
};

void generate_random_graph(std::vector<Node> &node_list, std::vector<Edge> &edge_list, unsigned int num_nodes);

#endif
