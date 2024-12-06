#include "bfs.h"
#include <deque>
#include <omp.h>
#include <chrono>
#include <iostream>
#include <string>
#include "../include/graph.h"

std::vector<int> serial_bfs(const std::vector<Node> &node_list, const std::vector<Edge> &edge_list, unsigned int source_node_no)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> cost(node_list.size(), -1);
    std::vector<bool> visited(node_list.size(), false);

    visited[source_node_no] = true;
    std::deque<unsigned int> current;
    current.push_back(source_node_no);
    cost[source_node_no] = 0;

    while (!current.empty())
    {
        unsigned int index = current.front();
        current.pop_front();
        Node cur_node = node_list[index];
        for (unsigned int i = cur_node.start; i < cur_node.start + cur_node.edge_num; i++)
        {
            unsigned int id = edge_list[i].dest;
            if (!visited[id])
            {
                visited[id] = true;
                cost[id] = cost[index] + 1;
                current.push_back(id);
            }
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Serial BFS used time: " << std::chrono::duration<float>(end - start).count() << " seconds\n";

    return cost;
}

std::vector<int> parallel_bfs(const std::vector<Node> &node_list, const std::vector<Edge> &edge_list,
                              unsigned int source_node_no, int num_threads, const std::string &schedule_type, int chunk_size)
{
    auto start = std::chrono::high_resolution_clock::now();

    std::vector<int> cost(node_list.size(), -1);
    std::vector<AtomicBoolWrapper> visited(node_list.size());

    visited[source_node_no].store(true);
    cost[source_node_no] = 0;

    std::deque<unsigned int> current, next;
    current.push_back(source_node_no);

    omp_set_num_threads(num_threads);

    while (!current.empty())
    {
        int num_nodes = current.size();

        if (schedule_type == "static")
        {
#pragma omp parallel for schedule(static, chunk_size)
            for (int i = 0; i < num_nodes; i++)
            {
                unsigned int index;
#pragma omp critical
                {
                    index = current.front();
                    current.pop_front();
                }

                Node cur_node = node_list[index];
                std::vector<unsigned int> local_next;

                for (unsigned int j = cur_node.start; j < cur_node.start + cur_node.edge_num; j++)
                {
                    unsigned int id = edge_list[j].dest;
                    if (!visited[id].load() && !visited[id].exchange(true))
                    {
                        cost[id] = cost[index] + 1;
                        local_next.push_back(id);
                    }
                }

#pragma omp critical
                next.insert(next.end(), local_next.begin(), local_next.end());
            }
        }
        else if (schedule_type == "dynamic")
        {
#pragma omp parallel for schedule(dynamic, chunk_size)
            for (int i = 0; i < num_nodes; i++)
            {
                unsigned int index;
#pragma omp critical
                {
                    index = current.front();
                    current.pop_front();
                }

                Node cur_node = node_list[index];
                std::vector<unsigned int> local_next;

                for (unsigned int j = cur_node.start; j < cur_node.start + cur_node.edge_num; j++)
                {
                    unsigned int id = edge_list[j].dest;
                    if (!visited[id].load() && !visited[id].exchange(true))
                    {
                        cost[id] = cost[index] + 1;
                        local_next.push_back(id);
                    }
                }

#pragma omp critical
                next.insert(next.end(), local_next.begin(), local_next.end());
            }
        }
        else if (schedule_type == "guided")
        {
#pragma omp parallel for schedule(guided, chunk_size)
            for (int i = 0; i < num_nodes; i++)
            {
                unsigned int index;
#pragma omp critical
                {
                    index = current.front();
                    current.pop_front();
                }

                Node cur_node = node_list[index];
                std::vector<unsigned int> local_next;

                for (unsigned int j = cur_node.start; j < cur_node.start + cur_node.edge_num; j++)
                {
                    unsigned int id = edge_list[j].dest;
                    if (!visited[id].load() && !visited[id].exchange(true))
                    {
                        cost[id] = cost[index] + 1;
                        local_next.push_back(id);
                    }
                }

#pragma omp critical
                next.insert(next.end(), local_next.begin(), local_next.end());
            }
        }

        current.swap(next);
        next.clear();
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::cout << "Parallel BFS used time: " << std::chrono::duration<float>(end - start).count() << " seconds\n";

    return cost;
}
