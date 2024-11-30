#include "graph.h"
#include <random>
#include <iostream>

void generate_random_graph(std::vector<Node> &node_list, std::vector<Edge> &edge_list, unsigned int num_nodes)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 50);
    std::uniform_int_distribution<> node_dis(0, num_nodes - 1);

    node_list.resize(num_nodes);
    unsigned int current_edge_start = 0;

    for (unsigned int i = 0; i < num_nodes; i++)
    {
        unsigned int num_edges = dis(gen);
        node_list[i].start = current_edge_start;
        node_list[i].edge_num = num_edges;

        for (unsigned int j = 0; j < num_edges; j++)
        {
            Edge edge;
            edge.src = i;
            edge.dest = (i == 0) ? 1 : (j == 0 ? (i - 1) : node_dis(gen));
            edge_list.push_back(edge);
        }
        current_edge_start += num_edges;
    }

    std::cout << "Generated random graph with " << num_nodes << " nodes and " << edge_list.size() << " edges.\n";
}
