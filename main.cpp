#include "./include/graph.h"
#include "./include/performance.h"

int main()
{
    unsigned int num_nodes = 10000;
    unsigned int source_node_no = 0;

    std::vector<Node> node_list;
    std::vector<Edge> edge_list;

    generate_random_graph(node_list, edge_list, num_nodes);
    compare_bfs_performance(node_list, edge_list, source_node_no);

    return 0;
}
