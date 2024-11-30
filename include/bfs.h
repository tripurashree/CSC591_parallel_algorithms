#ifndef BFS_H
#define BFS_H

#include <vector>
#include <atomic>
#include "graph.h"

class AtomicBoolWrapper
{
    std::atomic<bool> value;

public:
    AtomicBoolWrapper() : value(false) {}
    AtomicBoolWrapper(const AtomicBoolWrapper &other) : value(other.value.load()) {}
    AtomicBoolWrapper &operator=(const AtomicBoolWrapper &other)
    {
        value.store(other.value.load());
        return *this;
    }
    bool load() const { return value.load(); }
    void store(bool desired) { value.store(desired); }
    bool exchange(bool desired) { return value.exchange(desired); }
};
std::vector<int> serial_bfs(const std::vector<Node> &node_list, const std::vector<Edge> &edge_list, unsigned int source_node_no);
std::vector<int> parallel_bfs(const std::vector<Node> &node_list, const std::vector<Edge> &edge_list, unsigned int source_node_no, int num_threads);
#endif // BFS_H
